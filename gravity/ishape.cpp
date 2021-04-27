#include "ishape.h"

void gravity::geometry::IShape::setAngle(double angle)
{
    ang = angle;
}

void gravity::geometry::IShape::rotate(double angle)
{
    ang += angle;
}

void gravity::geometry::IShape::setCenter(const gravity::geometry::Vector2D &new_center)
{
    center = new_center;
}

void gravity::geometry::IShape::setCenter(double x, double y)
{
    center.x = x;
    center.y = y;
}

void gravity::geometry::IShape::move(const gravity::geometry::Vector2D &delta)
{
    center += delta;
}

void gravity::geometry::IShape::move(double x, double y)
{
    center.x += x;
    center.y += y;
}

gravity::geometry::Collision::Collision(gravity::geometry::IShape *a, gravity::geometry::IShape *b)
    : a{a}, b{b} {}

bool gravity::geometry::Collision::isCollided()
{
    return a && b;
}

gravity::geometry::Simplex::Simplex()
{
    points.reserve(3);
}

void gravity::geometry::Simplex::add(const gravity::geometry::Vector2D &point)
{
    points.push_back(point);
}

void gravity::geometry::Simplex::add(gravity::geometry::Vector2D &&point)
{
    points.emplace_back(point);
}

gravity::geometry::Vector2D gravity::geometry::Simplex::nextDirection()
{
    if(points.size() < 2)
        throw std::runtime_error("There must be at least two points!");

    Vector2D& a = points.back();

    Vector2D ao = -a;

    if(points.size() == 3)
    {
        Vector2D& b = points[0];
        Vector2D& c = points[1];

        Vector2D ab = b - a;
        Vector2D ac = c - a;

        Vector2D ab_perp(ab.y, -ab.x);

        if(ab_perp.dot(c) >= 0)
            ab_perp = -ab_perp;

        if(ab_perp.dot(ao) > 0)
        {
            points[0] = points[1];
            points[1] = points[2];
            points.pop_back();
            return ab_perp;
        }

        Vector2D ac_perp(ac.y, -ac.x);

        if(ac_perp.dot(b) >= 0)
            ac_perp = -ac_perp;

        if(ac_perp.dot(ao) > 0)
        {
            points[1] = points[2];
            points.pop_back();
            return  ac_perp;
        }

        return Vector2D();
    }

    Vector2D& b = points[0];
    Vector2D ab = b - a;

    Vector2D ab_perp(ab.y, -ab.x);

    if(ab_perp.dot(ao) <= 0)
        ab_perp = -ab_perp;

    return ab_perp;
}

void gravity::geometry::Simplex::reset()
{
    points.clear();
}

gravity::geometry::Collision gravity::geometry::CollisionChecker::operator()(gravity::geometry::IShape &a, gravity::geometry::IShape &b)
{
    simplex.reset();
    Vector2D direction(0, 1);
    Vector2D support_point = support(a, b, direction);
    simplex.add(support_point);
    direction = -direction;

    while(!direction.isNull())
    {
        support_point = support(a, b, direction);

        if(support_point.dot(direction) <= 0)
            return Collision();

        simplex.add(support_point);
        direction = simplex.nextDirection();
    }

    return Collision(&a, &b);
}

gravity::geometry::Vector2D gravity::geometry::CollisionChecker::support(gravity::geometry::IShape &a, gravity::geometry::IShape &b, const gravity::geometry::Vector2D &direction)
{
    return a.farthestPointInDirection(direction) - b.farthestPointInDirection(-direction);
}
