#include "circleshape.h"


gravity::geometry::CircleShape::CircleShape(double radius)
    : radius{radius} {}

gravity::geometry::Vector2D gravity::geometry::CircleShape::farthestPointInDirection(const gravity::geometry::Vector2D &direction)
{
    double angle = direction.angleOX();
    return center + Vector2D(radius * cos(angle), radius * sin(angle));
}
