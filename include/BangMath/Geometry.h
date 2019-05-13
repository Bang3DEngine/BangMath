#pragma once

#include <array>
#include <vector>

#include "BangMath/Orientation.h"

namespace Bang
{
template <typename>
class AABoxG;
template <typename>
class BoxG;
template <typename>
class PlaneG;
template <typename>
class PolygonG;
template <typename>
class Polygon2DG;
template <typename>
class QuadG;
template <typename>
class Ray2DG;
template <typename>
class RayG;
template <typename>
class Segment2DG;
template <typename>
class SegmentG;
template <typename>
class SphereG;
template <typename>
class TriangleG;
template <typename>
class Vector2G;
template <typename>
class Vector3G;

class Geometry
{
public:
    template <typename T>
    static T GetPointToLineDistance2D(const Vector2G<T> &point,
                                      const Vector2G<T> &lineP0,
                                      const Vector2G<T> &lineP1);

    template <typename T>
    static void IntersectSegment2DSegment2D(const Segment2DG<T> &segment0,
                                            const Segment2DG<T> &segment1,
                                            bool *intersected,
                                            Vector2G<T> *intersPoint);

    template <typename T>
    static void IntersectRay2DSegment2D(const Ray2DG<T> &ray,
                                        const Segment2DG<T> &segment,
                                        bool *intersected,
                                        Vector2G<T> *intersPoint);

    template <typename T>
    static void IntersectRayPlane(const RayG<T> &ray,
                                  const PlaneG<T> &plane,
                                  bool *intersected,
                                  T *distanceFromIntersectionToRayOrigin);

    template <typename T>
    static void IntersectRayPlane(const RayG<T> &ray,
                                  const PlaneG<T> &plane,
                                  bool *intersected,
                                  Vector3G<T> *intersectionPoint);

    template <typename T>
    static void IntersectSegmentPlane(const SegmentG<T> &segment,
                                      const PlaneG<T> &plane,
                                      bool *intersected,
                                      Vector3G<T> *intersectionPoint);

    template <typename T>
    static void IntersectRayAABox(const RayG<T> &ray,
                                  const AABoxG<T> &aaBox,
                                  bool *intersected,
                                  T *intersectionDistance);

    // Computes the intersection between a ray and a sphere
    template <typename T>
    static void IntersectRaySphere(const RayG<T> &ray,
                                   const SphereG<T> &sphere,
                                   bool *intersected,
                                   Vector3G<T> *intersectionPoint);

    // Returns the two closest points between the ray and the passed line
    template <typename T>
    static void RayLineClosestPoints(const RayG<T> &ray,
                                     const Vector3G<T> &linePoint,
                                     const Vector3G<T> &lineDirection,
                                     Vector3G<T> *pointOnRay = nullptr,
                                     Vector3G<T> *pointOnLine = nullptr);

    // Computes the intersection between a ray and a PLANAR CONVEX polygon
    template <typename T>
    static void IntersectSegmentPolygon(const SegmentG<T> &segment,
                                        const PolygonG<T> &poly,
                                        bool *intersected,
                                        Vector3G<T> *intersection);

    template <typename T>
    static void IntersectSegmentBox(const SegmentG<T> &segment,
                                    const BoxG<T> &box,
                                    bool *intersected,
                                    Vector3G<T> *intersection,
                                    Vector3G<T> *intersectionNormal);

    template <typename T>
    static std::vector<Vector3G<T>> IntersectSegmentPolygon(
        const SegmentG<T> &segment,
        const PolygonG<T> &poly);

    template <typename T>
    static std::vector<Vector3G<T>> IntersectPolygonPolygon(
        const PolygonG<T> &poly0,
        const PolygonG<T> &poly1);

    template <typename T>
    static void IntersectRayTriangle(const RayG<T> &ray,
                                     const TriangleG<T> &triangle,
                                     bool *intersected,
                                     T *distanceFromRayOriginToIntersection);

    template <typename T>
    static void IntersectRayTriangle(const RayG<T> &ray,
                                     const TriangleG<T> &triangle,
                                     bool *intersected,
                                     Vector3G<T> *intersectionPoint);

    template <typename T>
    static bool IntersectAABoxTriangle(const AABoxG<T> &aaBox,
                                       const TriangleG<T> &triangle);

    template <typename T>
    static void IntersectSegmentTriangle(const SegmentG<T> &segment,
                                         const TriangleG<T> &triangle,
                                         bool *intersected,
                                         Vector3G<T> *intersectionPoint);

    template <typename T>
    static std::vector<Vector3G<T>> IntersectTriangleTriangle(
        const TriangleG<T> &triangle0,
        const TriangleG<T> &triangle1);

    template <typename T>
    static std::vector<Vector3G<T>> IntersectBoxBox(
        const std::array<QuadG<T>, 6> &box0,
        const std::array<QuadG<T>, 6> &box1);

    template <typename T>
    static bool IsPointInsideBox(const Vector3G<T> &p,
                                 const std::array<QuadG<T>, 6> &box);

    template <typename T>
    static bool IsPointInsideBox(const Vector3G<T> &p,
                                 const PlaneG<T> &boxTopPlane,
                                 const PlaneG<T> &boxBotPlane,
                                 const PlaneG<T> &boxLeftPlane,
                                 const PlaneG<T> &boxRightPlane,
                                 const PlaneG<T> &boxFrontPlane,
                                 const PlaneG<T> &boxBackPlane);

    // Computes the intersection between two quads
    template <typename T>
    static std::vector<Vector3G<T>> IntersectQuadQuad(const QuadG<T> &quad0,
                                                      const QuadG<T> &quad1);

    // Computes the intersection between a quad and a AABox
    template <typename T>
    static std::vector<Vector3G<T>> IntersectQuadAABox(
        const QuadG<T> &quad,
        const AABoxG<T> &aaBox,
        bool onlyBoundaries = false);

    // Returns the orientation of a point vs a line
    template <typename T>
    static Orientation GetOrientation(const Vector2G<T> &lineP0,
                                      const Vector2G<T> &lineP1,
                                      const Vector2G<T> &point);

    // Returns the orientation of a point vs a plane
    template <typename T>
    static Orientation GetOrientation(const Vector3G<T> &point,
                                      const PlaneG<T> &plane);

    // Returns the point in the ray that is closer to the passed point
    template <typename T>
    static Vector3G<T> RayClosestPointTo(const RayG<T> &ray,
                                         const Vector3G<T> &point);

    // Returns a point projected to sphere
    template <typename T>
    static Vector3G<T> PointProjectedToSphere(const Vector3G<T> &point,
                                              const SphereG<T> &sphere);

    Geometry() = delete;
    virtual ~Geometry() = delete;

private:
    template <typename T>
    static constexpr T Epsilon()
    {
        return static_cast<T>(1e-5);
    }
};
}

#include "BangMath/Geometry.tcc"
