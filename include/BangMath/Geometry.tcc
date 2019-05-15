#include "BangMath/Geometry.h"

#include <algorithm>
#include <array>
#include <vector>

#include "BangMath/Axis.h"
#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
T Geometry::GetPointToLineDistance2D(const Vector2G<T> &point,
                                     const Vector2G<T> &lineP0,
                                     const Vector2G<T> &lineP1)
{
    const auto lineP0ToPoint = (point - lineP0);
    const auto lineDir = (lineP1 - lineP0).NormalizedSafe();
    const auto lengthOfPointToLineP0OnLine =
        Vector2G<T>::Dot(lineP0ToPoint, lineDir);
    const auto a = lineP0ToPoint.SqLength();
    const auto b = Math::Pow(lengthOfPointToLineP0OnLine, 2.0f);
    const auto distance = Math::Sqrt(Math::Abs(a - b));
    return distance;
}

template <typename T>
void Geometry::IntersectSegment2DSegment2D(const Segment2DG<T> &segment0,
                                           const Segment2DG<T> &segment1,
                                           bool *intersected,
                                           Vector2G<T> *intersPoint)
{
    const auto &p0 = segment0.GetOrigin();
    const auto &p1 = segment0.GetDestiny();
    const auto &q0 = segment1.GetOrigin();
    const auto &q1 = segment1.GetDestiny();

    const auto orient0 = Geometry::GetOrientation(p0, p1, q0);
    const auto orient1 = Geometry::GetOrientation(p0, p1, q1);
    if (orient0 == orient1 && orient0 != Orientation::ZERO)
    {
        *intersected = false;
        return;
    }

    const auto orient2 = Geometry::GetOrientation(q0, q1, p0);
    const auto orient3 = Geometry::GetOrientation(q0, q1, p1);
    if (orient2 == orient3 && orient2 != Orientation::ZERO)
    {
        *intersected = false;
        return;
    }

    const auto x1 = p0.x, x2 = p1.x, x3 = q0.x, x4 = q1.x;
    const auto y1 = p0.y, y2 = p1.y, y3 = q0.y, y4 = q1.y;

    const auto d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0)
    {
        *intersected = false;
        return;
    }

    const auto pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    const auto x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    const auto y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    *intersected = true;
    *intersPoint = Vector2G<T>(x, y);
}

template <typename T>
void Geometry::IntersectRay2DSegment2D(const Ray2DG<T> &ray,
                                       const Segment2DG<T> &segment,
                                       bool *intersected,
                                       Vector2G<T> *intersPoint)
{
    const auto maxSqDist = Math::Max(
        Vector2G<T>::SqDistance(ray.GetOrigin(), segment.GetOrigin()),
        Vector2G<T>::SqDistance(ray.GetOrigin(), segment.GetDestiny()));
    const auto raySegment = Segment2DG<T>(
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
    const auto &planeNormal = plane.GetNormal();
    const auto dot = Vector3G<T>::Dot(planeNormal, ray.GetDirection());
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
    T t;
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
    const auto segmentRay = RayG<T>(segment.GetOrigin(), segmDir);
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
    auto tmin = (aaBox.GetMin().x - ray.GetOrigin().x) / ray.GetDirection().x;
    auto tmax = (aaBox.GetMax().x - ray.GetOrigin().x) / ray.GetDirection().x;

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    auto tymin = (aaBox.GetMin().y - ray.GetOrigin().y) / ray.GetDirection().y;
    auto tymax = (aaBox.GetMax().y - ray.GetOrigin().y) / ray.GetDirection().y;

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

    auto tzmin = (aaBox.GetMin().z - ray.GetOrigin().z) / ray.GetDirection().z;
    auto tzmax = (aaBox.GetMax().z - ray.GetOrigin().z) / ray.GetDirection().z;

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
    const auto rayOriginToSphereCenter = sphere.GetCenter() - ray.GetOrigin();

    const auto sphereRadius2 = sphere.GetRadius() * sphere.GetRadius();
    const auto tca =
        Vector3G<T>::Dot(rayOriginToSphereCenter, ray.GetDirection());
    // if (tca < 0)  { *intersected = false; return; }

    const auto d2 = rayOriginToSphereCenter.SqLength() - tca * tca;
    if (d2 > sphereRadius2)
    {
        *intersected = false;
        return;
    }

    const auto thc = Math::Sqrt(sphereRadius2 - d2);
    auto t0 = tca - thc;
    auto t1 = tca + thc;

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
    const auto lineToRayPerp =
        Vector3G<T>::Cross(ray.GetDirection(), lineDirection).NormalizedSafe();

    if (pointOnRay)
    {
        bool intersected;
        const auto planeBitangent = lineDirection.NormalizedSafe();
        const auto plane = PlaneG<T>(
            linePoint, Vector3G<T>::Cross(lineToRayPerp, planeBitangent));
        Geometry::IntersectRayPlane(ray, plane, &intersected, pointOnRay);
    }

    if (pointOnLine)
    {
        const auto lineRay = RayG<T>(linePoint, lineDirection);
        const auto planeBitangent = ray.GetDirection();
        const auto plane = PlaneG<T>(
            ray.GetOrigin(), Vector3G<T>::Cross(lineToRayPerp, planeBitangent));

        T t = T(0.0);
        auto intersected = false;
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
        const auto intSegDist =
            Vector3G<T>::Distance(*intersection, segment.GetOrigin());
        if (intSegDist <= segment.GetLength())
        {
            // Segment intersects with plane, but is it inside the polygon?
            Axis3D axisToProj;
            const auto apn =
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

            const auto projectedPolygon = poly.ProjectedOnAxis(axisToProj);
            const auto projectedIntersPoint =
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

    const auto extX = box.GetExtentX();
    const auto extY = box.GetExtentY();
    const auto extZ = box.GetExtentZ();
    const auto extXNorm = extX.NormalizedSafe();
    const auto extYNorm = extY.NormalizedSafe();
    const auto extZNorm = extZ.NormalizedSafe();

    std::array<PlaneG<T>, 6> planes;
    planes[0] = PlaneG<T>(box.GetCenter() + extX, extXNorm);
    planes[1] = PlaneG<T>(box.GetCenter() - extX, -extXNorm);
    planes[2] = PlaneG<T>(box.GetCenter() + extY, extYNorm);
    planes[3] = PlaneG<T>(box.GetCenter() - extY, -extYNorm);
    planes[4] = PlaneG<T>(box.GetCenter() + extZ, extZNorm);
    planes[5] = PlaneG<T>(box.GetCenter() - extZ, -extZNorm);

    auto closestPlaneIntersectionSqDist = Math::Infinity<T>();
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

            const auto sqDist =
                Vector3G<T>::SqDistance(planeIntPoint, segment.GetOrigin());
            if (sqDist < closestPlaneIntersectionSqDist)
            {
                // Is the point enclosed by the planes on the other axes?
                const auto &ori0 = oriPlanes[(i + 1) % 6];
                const auto &ori1 = oriPlanes[(i + 2) % 6];
                const auto &ori2 = oriPlanes[(i + 3) % 6];
                const auto &ori3 = oriPlanes[(i + 4) % 6];
                const auto &ori4 = oriPlanes[(i + 5) % 6];

                if (ori0 == Orientation::NEGATIVE &&
                    ori1 == Orientation::NEGATIVE &&
                    ori2 == Orientation::NEGATIVE &&
                    ori3 == Orientation::NEGATIVE &&
                    ori4 == Orientation::NEGATIVE)
                {
                    // Vector3G<T> intDir = (planeIntPoint -
                    // segment.GetOrigin());
                    auto normalSign = T(1.0);  // Math::Sign(
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

    auto intersected = false;
    auto intersectionPoint = Vector3G<T>::Zero();
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
        const auto &p0 = polys[pi];
        const auto &p1 = polys[1 - pi];
        for (uint i = 0; i < p0.GetPoints().size(); ++i)
        {
            const auto segment = SegmentG<T>(
                p0.GetPoint(i), p0.GetPoint((i + 1) % p0.GetPoints().size()));
            const auto intPoints =
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
    auto &t = *distanceFromRayOriginToIntersection;
    const auto &rayOrig = ray.GetOrigin();
    const auto rayDir(ray.GetDirection());
    const auto &triP0 = triangle.GetPoint(0);
    const auto &triP1 = triangle.GetPoint(1);
    const auto &triP2 = triangle.GetPoint(2);

    const auto v10(triP1 - triP0);
    const auto v20(triP2 - triP0);

    const auto h(Vector3G<T>::Cross(rayDir, v20));
    const auto a = Vector3G<T>::Dot(v10, h);

    constexpr auto Epsilon = T(1e-8);
    if (a > -Epsilon && a < Epsilon)
    {
        *intersected = false;
        return;
    }

    const auto f = 1.0 / a;
    const auto s = (rayOrig - triP0);
    const auto u = f * Vector3G<T>::Dot(s, h);

    if (u < 0.0 || u > 1.0)
    {
        *intersected = false;
        return;
    }

    const auto q = Vector3G<T>::Cross(s, v10);
    const auto v = f * Vector3G<T>::Dot(rayDir, q);

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
    for (const auto &point : points)
    {
        const auto projection = point.ProjectedOnAxisAsPoint(axis);

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
    const auto &triP0 = triangle[0];
    const auto &triP1 = triangle[1];
    const auto &triP2 = triangle[2];
    std::array<Vector3G<T>, 8> boxPoints = aaBox.GetPointsC();
    std::array<Vector3G<T>, 3> trianglePoints = {{triP0, triP1, triP2}};
    const auto triNormal = triangle.GetNormal();
    const auto triEdge01 = (triP1 - triP0).Normalized();
    const auto triEdge12 = (triP2 - triP1).Normalized();
    const auto triEdge20 = (triP0 - triP2).Normalized();

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

        const auto projectionsOverlap =
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
    auto ray = RayG<T>(segment.GetOrigin(), segment.GetDirection());

    T t = 0.0;
    Geometry::IntersectRayTriangle(ray, triangle, intersected, &t);

    const auto segmentLength = segment.GetLength();
    *intersected = *intersected && (t >= 0.0) && (t <= segmentLength);
    *intersectionPoint = *intersected ? ray.GetPoint(t) : ray.GetOrigin();
}

template <typename T>
std::vector<Vector3G<T>> Geometry::IntersectBoxBox(
    const std::array<QuadG<T>, 6> &box0,
    const std::array<QuadG<T>, 6> &box1)
{
    std::vector<Vector3G<T>> result;
    for (const auto &q0 : box0)
    {
        for (const auto &q1 : box1)
        {
            const auto intPoints = Geometry::IntersectQuadQuad(q0, q1);
            for (const auto &intPoint : intPoints)
            {
                result.push_back(intPoint);
            }

            // Points of q0 inside box1
            for (const auto &q0p : q0.GetPoints())
            {
                if (Geometry::IsPointInsideBox(q0p, box1))
                {
                    result.push_back(q0p);
                }
            }

            // Points of q1 inside box0
            for (const auto &q1p : q1.GetPoints())
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
    const auto quadPoints = quad.GetPoints();
    const auto aaBoxQuads = aaBox.GetQuads();
    for (const auto &aaBoxQuad : aaBoxQuads)
    {
        const auto inters = Geometry::IntersectQuadQuad(quad, aaBoxQuad);
        for (const auto &intersPoint : inters)
        {
            foundIntersectionPoints.push_back(intersPoint);
        }

        if (!onlyBoundaries)
        {
            for (const auto &p : quadPoints)
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
    const auto det = ((point.x - lineP0.x) * (lineP1.y - lineP0.y)) -
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
    const auto dot =
        Vector3G<T>::Dot(plane.GetNormal(), (point - plane.GetPoint()));
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
    const auto closestRayPointToSphereV = sphere.GetCenter() - point;
    const auto closestRayPointToSphereDir =
        closestRayPointToSphereV.Normalized();
    return sphere.GetCenter() - closestRayPointToSphereDir * sphere.GetRadius();
}
}
