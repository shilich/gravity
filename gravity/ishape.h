#ifndef ISHAPE_H
#define ISHAPE_H

#include <vector>
#include <stdexcept>
#include "vector2d.h"

namespace gravity
{

namespace geometry
{

class IShape
{
public:
    IShape() = default;

    IShape(const IShape&) = delete;
    IShape(IShape&&) = delete;

    virtual ~IShape() {}

    virtual Vector2D farthestPointInDirection(const Vector2D& direction) = 0;

    void setAngle(double angle);
    void rotate(double angle);

    void setCenter(const Vector2D& new_center);
    void setCenter(double x, double y);
    void move(const Vector2D& delta);
    void move(double x, double y);

protected:
    Vector2D center{0, 0};
    double ang{0};
};

class Collision
{
public:
    Collision() = default;
    Collision(IShape *a, IShape *b);

    bool isCollided();

    IShape *a{nullptr}, *b{nullptr};
};

class CollisionChecker;

class Simplex
{
    friend class CollisionChecker;
private:
    Simplex();

    void add(const Vector2D& point);
    void add(Vector2D&& point);

    Vector2D nextDirection();

    void reset();
private:
    std::vector<Vector2D> points;
};

class CollisionChecker
{
public:
    CollisionChecker() = default;

    Collision operator()(IShape& a, IShape& b);
private:
    Simplex simplex;

    static Vector2D support(IShape& a, IShape& b, const Vector2D& direction);
};

}

}
#endif // ISHAPE_H
