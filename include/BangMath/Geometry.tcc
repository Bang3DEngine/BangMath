#include "BangMath/Geometry.h"

#include <algorithm>
#include <array>
#include <vector>

namespace Bang
{
template <typename T>
T Geometry::GetPointToLineDistance2D(const Vector2G<T> &point,
                                     const Vector2G<T> &lineP0,
                                     const Vector2G<T> &lineP1)
{
    Vector2G<T> lineP0ToPoint = (point - lineP0);
    Vector2G<T> lineDir = (lineP1 - lineP0).NormalizedSafe();
    T lengthOfPointToLineP0OnLine = Vector2G<T>::Dot(lineP0ToPoint, lineDir);
    T a = lineP0ToPoint.SqLength();
    T b = Math::Pow(lengthOfPointToLineP0OnLine, 2.0f);
    T distance = Math::Sqrt(Math::Abs(a - b));
    return distance;
}

template <typename T>
void Geometry::IntersectSegment2DSegment2D(const Segment2DG<T> &segment0,
                                           const Segment2DG<T> &segment1,
                                           bool *intersected,
                                           Vector2G<T> *intersPoint)
{
    const Vector2G<T> &p0 = segment0.GetOrigin();
    const Vector2G<T> &p1 = segment0.GetDestiny();
    const Vector2G<T> &q0 = segment1.GetOrigin();
    const Vector2G<T> &q1 = segment1.GetDestiny();

    Orientation orient0 = Geometry::GetOrientation(p0, p1, q0);
    Orientation orient1 = Geometry::GetOrientation(p0, p1, q1);
    if (orient0 == orient1 && orient0 != Orientation::ZERO)
    {
        *intersected = false;
        return;
    }

    Orientation orient2 = Geometry::GetOrientation(q0, q1, p0);
    Orientation orient3 = Geometry::GetOrientation(q0, q1, p1);
    if (orient2 == orient3 && orient2 != Orientation::ZERO)
    {
        *intersected = false;
        return;
    }

    const T x1 = p0.x, x2 = p1.x, x3 = q0.x, x4 = q1.x;
    const T y1 = p0.y, y2 = p1.y, y3 = q0.y, y4 = q1.y;

    const T d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0)
    {
        *intersected = false;
        return;
    }

    const T pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    const T x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    const T y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    *intersected = true;
    *intersPoint = Vector2G<T>(x, y);
}

template <typename T>
void Geometry::IntersectRay2DSegment2D(const Ray2DG<T> &ray,
                                       const Segment2DG<T> &segment,
                                       bool *intersected,
                                       Vector2G<T> *intersPoint)
{
    T maxSqDist = Math::Max(
        Vector2G<T>::SqDistance(ray.GetOrigin(), segment.GetOrigin()),
        Vector2G<T>::SqDistance(ray.GetOrigin(), segment.GetDestiny()));
    Segment2DG<T> raySegment(
        ray.GetOrigin(), ray.GetOrigin() + (maxSqDist * ray.GetDirection()));
    Geometry::IntersectSegment2DSegment2D(
        segment, raySegment, intersected, intersPoint);
}

template <typename T>
void Geometry::IntersectRayPlane(const RayG<T> &ray,
                                 const PlaneG<T> &plane,
                                 bool *intersected,
                                 T *distanceFromIntersectionToRayOrigin)
{
    const Vector3G<T> &planeNormal = plane.GetNormal();
    T dot = Vector3G<T>::Dot(planeNormal, ray.GetDirection());
    if (Math::Abs(dot) > 0.001f)
    {
        *distanceFromIntersectionToRayOrigin =
            Vector3G<T>::Dot(plane.GetPoint() - ray.GetOrigin(), planeNormal) /
            dot;
        *intersected = (*distanceFromIntersectionToRayOrigin >= 0.0f);
    }
    else
    {
        *intersected = false;
    }
}

template <typename T>
void Geometry::IntersectRayPlane(const RayG<T> &ray,
                                 const PlaneG<T> &plane,
                                 bool *intersected,
                                 Vector3G<T> *intersectionPoint)
{
    float t;
    Geometry::IntersectRayPlane(ray, plane, intersected, &t);
    *intersected = *intersected && (t >= 0.0f);
    *intersectionPoint = *intersected ? ray.GetPoint(t) : ray.GetOrigin();
}

template <typename T>
void Geometry::IntersectSegmentPlane(const SegmentG<T> &segment,
                                     const PlaneG<T> &plane,
                                     bool *intersected,
                                     Vector3G<T> *intersectionPoint)
{
    T intDist;
    const Vector3G<T> segmDir = segment.GetDirection();
    RayG<T> segmentRay(segment.GetOrigin(), segmDir);
    Geometry::IntersectRayPlane(segmentRay, plane, intersected, &intDist);

    *intersected = *intersected && (intDist <= segment.GetLength());
    if (*intersected)
    {
        *intersectionPoint = segment.GetOrigin() + (intDist * segmDir);
    }
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/
// minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
template <typename T>
void Geometry::IntersectRayAABox(const RayG<T> &ray,
                                 const AABoxG<T> &aaBox,
                                 bool *intersected,
                                 T *intersectionDistance)
{
    T tmin = (aaBox.GetMin().x - ray.GetOrigin().x) / ray.GetDirection().x;
    T tmax = (aaBox.GetMax().x - ray.GetOrigin().x) / ray.GetDirection().x;

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    T tymin = (aaBox.GetMin().y - ray.GetOrigin().y) / ray.GetDirection().y;
    T tymax = (aaBox.GetMax().y - ray.GetOrigin().y) / ray.GetDirection().y;

    if (tymin > tymax)
    {
        std::swap(tymin, tymax);
    }

    if ((tmin > tymax) || (tymin > tmax))
    {
        *intersected = false;
        return;
    }

    if (tymin > tmin)
    {
        tmin = tymin;
    }

    if (tymax < tmax)
    {
        tmax = tymax;
    }

    T tzmin = (aaBox.GetMin().z - ray.GetOrigin().z) / ray.GetDirection().z;
    T tzmax = (aaBox.GetMax().z - ray.GetOrigin().z) / ray.GetDirection().z;

    if (tzmin > tzmax)
    {
        std::swap(tzmin, tzmax);
    }

    if ((tmin > tzmax) || (tzmin > tmax))
    {
        *intersected = false;
        return;
    }

    if (tzmin > tmin)
    {
        tmin = tzmin;
    }

    if (tzmax < tmax)
    {
        tmax = tzmax;
    }

    *intersected = true;
    *intersectionDistance = tmin;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/
// minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
template <typename T>
void Geometry::IntersectRaySphere(const RayG<T> &ray,
                                  const SphereG<T> &sphere,
                                  bool *intersected,
                                  Vector3G<T> *intersectionPoint)
{
    const Vector3G<T> rayOriginToSphereCenter =
        sphere.GetCenter() - ray.GetOrigin();

    const T sphereRadius2 = sphere.GetRadius() * sphere.GetRadius();
    const T tca = Vector3G<T>::Dot(rayOriginToSphereCenter, ray.GetDirection());
    // if (tca < 0)  { *intersected = false; return; }

    const T d2 = rayOriginToSphereCenter.SqLength() - tca * tca;
    if (d2 > sphereRadius2)
    {
        *intersected = false;
        return;
    }

    const T thc = Math::Sqrt(sphereRadius2 - d2);
    T t0 = tca - thc;
    T t1 = tca + thc;

    if (t0 > t1)
    {
        std::swap(t0, t1);
    }

    if (t0 < 0)
    {
        t0 = t1;
        if (t0 < 0)
        {
            *intersected = false;
            return;
        }
    }

    *intersected = true;
    *intersectionPoint = ray.GetPoint(t0);
}

template <typename T>
void Geometry::RayLineClosestPoints(const RayG<T> &ray,
                                    const Vector3G<T> &linePoint,
                                    const Vector3G<T> &lineDirection,
                                    Vector3G<T> *pointOnRay,
                                    Vector3G<T> *pointOnLine)
{
    Vector3G<T> lineToRayPerp =
        Vector3G<T>::Cross(ray.GetDirection(), lineDirection).NormalizedSafe();

    if (pointOnRay)
    {
        bool intersected;
        Vector3G<T> planeBitangent = lineDirection.NormalizedSafe();
        PlaneG<T> plane(linePoint,
                        Vector3G<T>::Cross(lineToRayPerp, planeBitangent));
        Geometry::IntersectRayPlane(ray, plane, &intersected, pointOnRay);
    }

    if (pointOnLine)
    {
        RayG<T> lineRay(linePoint, lineDirection);
        Vector3G<T> planeBitangent = ray.GetDirection();
        PlaneG<T> plane(ray.GetOrigin(),
                        Vector3G<T>::Cross(lineToRayPerp, planeBitangent));

        T t = 0.0f;
        bool intersected = false;
        Geometry::IntersectRayPlane(lineRay, plane, &intersected, &t);
        if (intersected)
        {
            *pointOnLine = linePoint + (t * lineDirection.NormalizedSafe());
        }
    }
}

template <typename T>
void Geometry::IntersectSegmentPolygon(const SegmentG<T> &segment,
                                       const PolygonG<T> &poly,
                                       bool *intersected,
                                       Vector3G<T> *intersection)
{
    bool intersectedWithPlane;
    IntersectRayPlane(RayG<T>(segment.GetOrigin(), segment.GetDirection()),
                      poly.GetPlane(),
                      &intersectedWithPlane,
                      intersection);

    *intersected = false;
    if (intersectedWithPlane)
    {
        T intSegDist =
            Vector3G<T>::Distance(*intersection, segment.GetOrigin());
        if (intSegDist <= segment.GetLength())
        {
            // Segment intersects with plane, but is it inside the polygon?
            Axis3D axisToProj;
            Vector3G<T> apn =
                Vector3G<T>::Abs(poly.GetNormal());  // To know where to project
            if (apn.x > apn.y && apn.x > apn.z)
            {
                axisToProj = Axis3D::X;
            }
            else if (apn.y > apn.x && apn.y > apn.z)
            {
                axisToProj = Axis3D::Y;
            }
            else
            {
                axisToProj = Axis3D::Z;
            }

            Polygon2DG<T> projectedPolygon = poly.ProjectedOnAxis(axisToProj);
            Vector2G<T> projectedIntersPoint =
                intersection->ProjectedOnAxis(axisToProj);

            if (projectedPolygon.Contains(projectedIntersPoint))
            {
                *intersected = true;
            }
        }
    }
}

template <typename T>
void Geometry::IntersectSegmentBox(const SegmentG<T> &segment,
                                   const BoxG<T> &box,
                                   bool *intersected,
                                   Vector3G<T> *intersectionPoint,
                                   Vector3G<T> *intersectionNormal)
{
    *intersected = false;

    Vector3G<T> extX = box.GetExtentX();
    Vector3G<T> extY = box.GetExtentY();
    Vector3G<T> extZ = box.GetExtentZ();
    Vector3G<T> extXNorm = extX.NormalizedSafe();
    Vector3G<T> extYNorm = extY.NormalizedSafe();
    Vector3G<T> extZNorm = extZ.NormalizedSafe();

    std::array<PlaneG<T>, 6> planes;
    planes[0] = PlaneG<T>(box.GetCenter() + extX, extXNorm);
    planes[1] = PlaneG<T>(box.GetCenter() - extX, -extXNorm);
    planes[2] = PlaneG<T>(box.GetCenter() + extY, extYNorm);
    planes[3] = PlaneG<T>(box.GetCenter() - extY, -extYNorm);
    planes[4] = PlaneG<T>(box.GetCenter() + extZ, extZNorm);
    planes[5] = PlaneG<T>(box.GetCenter() - extZ, -extZNorm);

    T closestPlaneIntersectionSqDist = Math::Infinity<T>();
    for (int i = 0; i < 6; ++i)
    {
        const PlaneG<T> &plane = planes[i];

        bool planeIntersected;
        Vector3G<T> planeIntPoint;
        Geometry::IntersectSegmentPlane(
            segment, plane, &planeIntersected, &planeIntPoint);
        if (planeIntersected)
        {
            std::array<Orientation, 6> oriPlanes;
            for (int j = 0; j < 6; ++j)
            {
                oriPlanes[j] =
                    Geometry::GetOrientation(planeIntPoint, planes[j]);
            }

            T sqDist =
                Vector3G<T>::SqDistance(planeIntPoint, segment.GetOrigin());
            if (sqDist < closestPlaneIntersectionSqDist)
            {
                // Is the point enclosed by the planes on the other axes?
                const Orientation &ori0 = oriPlanes[(i + 1) % 6];
                const Orientation &ori1 = oriPlanes[(i + 2) % 6];
                const Orientation &ori2 = oriPlanes[(i + 3) % 6];
                const Orientation &ori3 = oriPlanes[(i + 4) % 6];
                const Orientation &ori4 = oriPlanes[(i + 5) % 6];

                if (ori0 == Orientation::NEGATIVE &&
                    ori1 == Orientation::NEGATIVE &&
                    ori2 == Orientation::NEGATIVE &&
                    ori3 == Orientation::NEGATIVE &&
                    ori4 == Orientation::NEGATIVE)
                {
                    // Vector3G<T> intDir = (planeIntPoint -
                    // segment.GetOrigin());
                    T normalSign = 1.0;  // Math::Sign(
                                         // Vector3G<T>::Dot(segmDir,
                                         // plane.GetNormal()) );
                    closestPlaneIntersectionSqDist = sqDist;
                    *intersected = true;
                    *intersectionPoint = planeIntPoint;
                    *intersectionNormal = normalSign * plane.GetNormal();
                }
            }
        }
    }
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectSegmentPolygon(
    const SegmentG<T> &segment,
    const PolygonG<T> &poly)
{
    std::vector<Vector3G<T>> result;

    bool intersected;
    Vector3G<T> intersectionPoint;
    Geometry::IntersectSegmentPolygon(
        segment, poly, &intersected, &intersectionPoint);
    if (intersected)
    {
        result.push_back(intersectionPoint);
    }

    return result;
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectPolygonPolygon(
    const PolygonG<T> &poly0,
    const PolygonG<T> &poly1)
{
    std::vector<Vector3G<T>> intersectionPoints;
    const std::array<PolygonG<T>, 2> polys = {{poly0, poly1}};
    for (uint pi = 0; pi < 2; ++pi)
    {
        const PolygonG<T> &p0 = polys[pi];
        const PolygonG<T> &p1 = polys[1 - pi];
        for (uint i = 0; i < p0.GetPoints().size(); ++i)
        {
            SegmentG<T> segment(p0.GetPoint(i),
                                p0.GetPoint((i + 1) % p0.GetPoints().size()));
            const std::vector<Vector3G<T>> intPoints =
                Geometry::IntersectSegmentPolygon(segment, p1);
            for (const auto &intPoint : intPoints)
            {
                intersectionPoints.push_back(intPoint);
            }
        }
    }
    return intersectionPoints;
}

// http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
template <typename T>
void Geometry::IntersectRayTriangle(const RayG<T> &ray,
                                    const TriangleG<T> &triangle,
                                    bool *intersected,
                                    T *distanceFromRayOriginToIntersection)
{
    T &t = *distanceFromRayOriginToIntersection;
    const Vector3G<T> &rayOrig = ray.GetOrigin();
    const Vector3G<T> rayDir(ray.GetDirection());
    const Vector3G<T> &triP0 = triangle.GetPoint(0);
    const Vector3G<T> &triP1 = triangle.GetPoint(1);
    const Vector3G<T> &triP2 = triangle.GetPoint(2);

    Vector3G<T> v10(triP1 - triP0);
    Vector3G<T> v20(triP2 - triP0);

    Vector3G<T> h(Vector3G<T>::Cross(rayDir, v20));
    T a = Vector3G<T>::Dot(v10, h);

    constexpr T Epsilon = 1e-8;
    if (a > -Epsilon && a < Epsilon)
    {
        *intersected = false;
        return;
    }

    T f = 1.0 / a;
    Vector3G<T> s(rayOrig - triP0);
    T u = f * Vector3G<T>::Dot(s, h);

    if (u < 0.0 || u > 1.0)
    {
        *intersected = false;
        return;
    }

    Vector3G<T> q = Vector3G<T>::Cross(s, v10);
    T v = f * Vector3G<T>::Dot(rayDir, q);

    if (v < 0.0 || u + v > 1.0)
    {
        *intersected = false;
        return;
    }

    // At this stage we can compute t to find out where
    // the intersection point is on the line
    t = (f * Vector3G<T>::Dot(v20, q));
    if (t < Epsilon)
    {
        *intersected = false;
        return;
    }

    *intersected = true;
}

template <typename T>
void Geometry::IntersectRayTriangle(const RayG<T> &ray,
                                    const TriangleG<T> &triangle,
                                    bool *intersected,
                                    Vector3G<T> *intersectionPoint)
{
    T t = 0.0;
    Geometry::IntersectRayTriangle(ray, triangle, intersected, &t);
    *intersected = *intersected && (t >= 0.0);
    *intersectionPoint = *intersected ? ray.GetPoint(t) : ray.GetOrigin();
}

template <typename T, uint N>
void FindProjectionIntervals(const std::array<Vector3G<T>, N> &points,
                             const Vector3G<T> &axis,
                             T &outMinProjection,
                             T &outMaxProjection)
{
    outMinProjection = Math::Infinity<T>();
    outMaxProjection = Math::NegativeInfinity<T>();
    for (const Vector3G<T> &point : points)
    {
        T projection = point.ProjectedOnAxisAsPoint(axis);

        if (projection > outMaxProjection)
        {
            outMaxProjection = projection;
        }

        if (projection < outMinProjection)
        {
            outMinProjection = projection;
        }
    }
}

template <typename T>
bool Geometry::IntersectAABoxTriangle(const AABoxG<T> &aaBox,
                                      const TriangleG<T> &triangle)
{
    const Vector3G<T> &triP0 = triangle[0];
    const Vector3G<T> &triP1 = triangle[1];
    const Vector3G<T> &triP2 = triangle[2];
    std::array<Vector3G<T>, 8> boxPoints = aaBox.GetPointsC();
    std::array<Vector3G<T>, 3> trianglePoints = {{triP0, triP1, triP2}};
    const Vector3G<T> triNormal = triangle.GetNormal();
    const Vector3G<T> triEdge01 = (triP1 - triP0).Normalized();
    const Vector3G<T> triEdge12 = (triP2 - triP1).Normalized();
    const Vector3G<T> triEdge20 = (triP0 - triP2).Normalized();

    /*
    // Discard if box is fully on one side of the triangle plane
    {
        bool allHaveSameSign = true;
        const Plane triPlane = triangle.GetPlane();
        float firstSign = Math::Sign(triPlane.GetDistanceTo(boxPoints[0]));
        for (uint i = 1; i < 8; ++i)
        {
            if (Math::Sign(triPlane.GetDistanceTo(boxPoints[i]) != firstSign))
            {
                allHaveSameSign = false;
                break;
            }
        }

        if (allHaveSameSign)
        {
            return false;
        }
    }

    // Discard if bounding boxes do not intersect
    {
        AABoxG triAABoxG;
        triAABoxG.AddPoint(triP0);
        triAABoxG.AddPoint(triP1);
        triAABoxG.AddPoint(triP2);
        if (!AABoxG.Overlap(triAABoxG))
        {
            return false;
        }
    }
    */

    // Create axes
    std::array<Vector3G<T>, 13> separatingAxes;
    separatingAxes[0] = Vector3G<T>(1, 0, 0);
    separatingAxes[1] = Vector3G<T>(0, 1, 0);
    separatingAxes[2] = Vector3G<T>(0, 0, 1);
    separatingAxes[3] = triNormal;
    separatingAxes[4] = Vector3G<T>::Cross(triEdge01, Vector3G<T>(1, 0, 0));
    separatingAxes[5] = Vector3G<T>::Cross(triEdge12, Vector3G<T>(1, 0, 0));
    separatingAxes[6] = Vector3G<T>::Cross(triEdge20, Vector3G<T>(1, 0, 0));
    separatingAxes[7] = Vector3G<T>::Cross(triEdge01, Vector3G<T>(0, 1, 0));
    separatingAxes[8] = Vector3G<T>::Cross(triEdge12, Vector3G<T>(0, 1, 0));
    separatingAxes[9] = Vector3G<T>::Cross(triEdge20, Vector3G<T>(0, 1, 0));
    separatingAxes[10] = Vector3G<T>::Cross(triEdge01, Vector3G<T>(0, 0, 1));
    separatingAxes[11] = Vector3G<T>::Cross(triEdge12, Vector3G<T>(0, 0, 1));
    separatingAxes[12] = Vector3G<T>::Cross(triEdge20, Vector3G<T>(0, 0, 1));

    // Check for overlap in each of the axes
    for (const Vector3G<T> &separatingAxis : separatingAxes)
    {
        // Find projected interval for triangle points
        T triangleProjectedMin, triangleProjectedMax;
        FindProjectionIntervals<3>(trianglePoints,
                                   separatingAxis,
                                   triangleProjectedMin,
                                   triangleProjectedMax);

        // Find projected interval for box points
        T boxProjectedMin, boxProjectedMax;
        FindProjectionIntervals<8>(
            boxPoints, separatingAxis, boxProjectedMin, boxProjectedMax);

        const bool projectionsOverlap =
            (triangleProjectedMin <= boxProjectedMax &&
             triangleProjectedMax >= boxProjectedMin);
        if (!projectionsOverlap)
        {
            // We have found a separating plane normal to this separating axis
            return false;
        }
    }

    return true;
}

template <typename T>
void Geometry::IntersectSegmentTriangle(const SegmentG<T> &segment,
                                        const TriangleG<T> &triangle,
                                        bool *intersected,
                                        Vector3G<T> *intersectionPoint)
{
    RayG<T> ray(segment.GetOrigin(), segment.GetDirection());

    T t = 0.0;
    Geometry::IntersectRayTriangle(ray, triangle, intersected, &t);

    const T segmentLength = segment.GetLength();
    *intersected = *intersected && (t >= 0.0f) && (t <= segmentLength);
    *intersectionPoint = *intersected ? ray.GetPoint(t) : ray.GetOrigin();
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectBoxBox(
    const std::array<QuadG<T>, 6> &box0,
    const std::array<QuadG<T>, 6> &box1)
{
    std::vector<Vector3G<T>> result;
    for (const QuadG<T> &q0 : box0)
    {
        for (const QuadG<T> &q1 : box1)
        {
            const auto intPoints = Geometry::IntersectQuadQuad(q0, q1);
            for (const auto &intPoint : intPoints)
            {
                result.push_back(intPoint);
            }

            // Points of q0 inside box1
            for (const Vector3G<T> &q0p : q0.GetPoints())
            {
                if (Geometry::IsPointInsideBox(q0p, box1))
                {
                    result.push_back(q0p);
                }
            }

            // Points of q1 inside box0
            for (const Vector3G<T> &q1p : q1.GetPoints())
            {
                if (Geometry::IsPointInsideBox(q1p, box0))
                {
                    result.push_back(q1p);
                }
            }
        }
    }
    return result;
}

template <typename T>
bool Geometry::IsPointInsideBox(const Vector3G<T> &p,
                                const std::array<QuadG<T>, 6> &box)
{
    return Geometry::IsPointInsideBox(p,
                                      box[0].GetPlane(),
                                      box[1].GetPlane(),
                                      box[2].GetPlane(),
                                      box[3].GetPlane(),
                                      box[4].GetPlane(),
                                      box[5].GetPlane());
}

template <typename T>
bool Geometry::IsPointInsideBox(const Vector3G<T> &p,
                                const PlaneG<T> &boxTopPlane,
                                const PlaneG<T> &boxBotPlane,
                                const PlaneG<T> &boxLeftPlane,
                                const PlaneG<T> &boxRightPlane,
                                const PlaneG<T> &boxFrontPlane,
                                const PlaneG<T> &boxBackPlane)
{
    return Geometry::GetOrientation(p, boxTopPlane) == Orientation::NEGATIVE &&
           Geometry::GetOrientation(p, boxBotPlane) == Orientation::NEGATIVE &&
           Geometry::GetOrientation(p, boxLeftPlane) == Orientation::NEGATIVE &&
           Geometry::GetOrientation(p, boxRightPlane) ==
               Orientation::NEGATIVE &&
           Geometry::GetOrientation(p, boxFrontPlane) ==
               Orientation::NEGATIVE &&
           Geometry::GetOrientation(p, boxBackPlane) == Orientation::NEGATIVE;
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectQuadQuad(const QuadG<T> &quad0,
                                                     const QuadG<T> &quad1)
{
    return Geometry::IntersectPolygonPolygon(quad0.ToPolygon(),
                                             quad1.ToPolygon());
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectQuadAABox(const QuadG<T> &quad,
                                                      const AABoxG<T> &aaBox,
                                                      bool onlyBoundaries)
{
    // Do all combinations of quad-quad, similar to QuadQuad
    std::vector<Vector3G<T>> foundIntersectionPoints;
    const std::array<Vector3G<T>, 4> quadPoints = quad.GetPoints();
    const std::array<QuadG<T>, 6> aaBoxQuads = aaBox.GetQuads();
    for (const QuadG<T> &aaBoxQuad : aaBoxQuads)
    {
        std::vector<Vector3G<T>> inters =
            Geometry::IntersectQuadQuad(quad, aaBoxQuad);
        for (const auto &intersPoint : foundIntersectionPoints)
        {
            foundIntersectionPoints.push_back(intersPoint);
        }

        if (!onlyBoundaries)
        {
            for (const Vector3G<T> &p : quadPoints)
            {
                if (aaBox.Contains(p))
                {
                    foundIntersectionPoints.push_back(p);
                }
            }
        }
    }

    return foundIntersectionPoints;
}

template <typename T>
Orientation Geometry::GetOrientation(const Vector2G<T> &lineP0,
                                     const Vector2G<T> &lineP1,
                                     const Vector2G<T> &point)
{
    T det = ((point.x - lineP0.x) * (lineP1.y - lineP0.y)) -
            ((point.y - lineP0.y) * (lineP1.x - lineP0.x));
    if (Math::Abs(det) < Epsilon<T>())
    {
        return Orientation::ZERO;
    }
    return (det > 0) ? Orientation::POSITIVE : Orientation::NEGATIVE;
}

template <typename T>
Orientation Geometry::GetOrientation(const Vector3G<T> &point,
                                     const PlaneG<T> &plane)
{
    T dot = Vector3G<T>::Dot(plane.GetNormal(), (point - plane.GetPoint()));
    if (Math::Abs(dot) < Epsilon<T>())
    {
        return Orientation::ZERO;
    }
    return (dot > 0) ? Orientation::POSITIVE : Orientation::NEGATIVE;
}

template <typename T>
Vector3G<T> Geometry::RayClosestPointTo(const RayG<T> &ray,
                                        const Vector3G<T> &point)
{
    bool intersected;
    Vector3G<T> intersection;
    Geometry::IntersectRayPlane(
        ray, PlaneG<T>(point, ray.GetDirection()), &intersected, &intersection);
    return intersected ? intersection : ray.GetOrigin();
}

template <typename T>
Vector3G<T> Geometry::PointProjectedToSphere(const Vector3G<T> &point,
                                             const SphereG<T> &sphere)
{
    Vector3G<T> closestRayPointToSphereV = sphere.GetCenter() - point;
    Vector3G<T> closestRayPointToSphereDir =
        closestRayPointToSphereV.Normalized();
    return sphere.GetCenter() - closestRayPointToSphereDir * sphere.GetRadius();
}
}
