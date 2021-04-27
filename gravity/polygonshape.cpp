#include "polygonshape.h"

gravity::geometry::PolygonShape::PolygonShape(const std::vector<gravity::geometry::Vector2D> &vertex)
{
    std::copy(vertex.begin(), vertex.end(), std::back_inserter(points));
}

gravity::geometry::PolygonShape::PolygonShape(std::vector<gravity::geometry::Vector2D> &&vertex)
    : points{vertex} {}

gravity::geometry::PolygonShape::PolygonShape(std::initializer_list<gravity::geometry::Vector2D> vertex)
{
    std::copy(vertex.begin(), vertex.end(), std::back_inserter(points));
}

gravity::geometry::Vector2D gravity::geometry::PolygonShape::farthestPointInDirection(const gravity::geometry::Vector2D &direction)
{
    double farthest_distance = -INFINITY, distance;
    Vector2D farthest_point = Vector2D();
    for(const Vector2D& point : points)
    {
        distance = updatedPosition(point).dot(direction);
        if(distance > farthest_distance)
        {
            farthest_distance = distance;
            farthest_point = point;
        }
    }
    return farthest_point;
}

gravity::geometry::Vector2D gravity::geometry::PolygonShape::updatedPosition(const gravity::geometry::Vector2D &point)
{
    Vector2D res = point.rotate(ang);
    res += center;
    return res;
}
