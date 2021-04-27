#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <algorithm>
#include <cmath>

namespace gravity
{

namespace geometry
{

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(double x, double y);

    Vector2D(const Vector2D& that);
    Vector2D(Vector2D&& that);

    Vector2D& operator=(const Vector2D& that);
    Vector2D& operator=(Vector2D&& that);

    Vector2D& operator+=(const Vector2D& that);
    Vector2D& operator-=(const Vector2D& that);
    Vector2D& operator*=(double num);
    Vector2D& operator/=(double num);

    Vector2D operator-() const;

    double dot(const Vector2D& that) const;
    double cross(const Vector2D& that) const;

    double length() const;
    double sqrLength() const;

    Vector2D normalize() const;
    Vector2D& normalized();

    Vector2D rotate(double ang) const;
    Vector2D& rotated(double ang);

    double angleOX() const;

    bool isNull() const;

    double x{0}, y{0};
};

double distance(const Vector2D& a, const Vector2D& b);

double angleBetween(const Vector2D& a, const Vector2D& b);

}

}

gravity::geometry::Vector2D operator+(const gravity::geometry::Vector2D& a, const gravity::geometry::Vector2D& b);
gravity::geometry::Vector2D operator-(const gravity::geometry::Vector2D& a, const gravity::geometry::Vector2D& b);
gravity::geometry::Vector2D operator*(double num, const gravity::geometry::Vector2D& vec);
gravity::geometry::Vector2D operator*(const gravity::geometry::Vector2D& vec, double num);
gravity::geometry::Vector2D operator/(const gravity::geometry::Vector2D& vec, double num);

#endif // VECTOR2D_H
