#include "vector2d.h"


gravity::geometry::Vector2D::Vector2D(double x, double y)
    : x{x}, y{y} {}

gravity::geometry::Vector2D::Vector2D(const gravity::geometry::Vector2D &that)
    : x{that.x}, y{that.y} {}

gravity::geometry::Vector2D::Vector2D(gravity::geometry::Vector2D &&that)
{
    std::swap(x, that.x);
    std::swap(y, that.y);
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::operator=(const gravity::geometry::Vector2D &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

gravity::geometry::Vector2D& gravity::geometry::Vector2D::operator=(gravity::geometry::Vector2D&& that)
{
    x = y = 0;
    std::swap(x, that.x);
    std::swap(y, that.y);
    return *this;
}


gravity::geometry::Vector2D &gravity::geometry::Vector2D::operator+=(const gravity::geometry::Vector2D &that)
{
    x += that.x;
    y += that.y;
    return *this;
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::operator-=(const gravity::geometry::Vector2D &that)
{
    x -= that.x;
    y -= that.y;
    return *this;
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::operator*=(double num)
{
    x *= num;
    y *= num;
    return *this;
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::operator/=(double num)
{
    x /= num;
    y /= num;
    return *this;
}

gravity::geometry::Vector2D gravity::geometry::Vector2D::operator-() const
{
    gravity::geometry::Vector2D res(-x, -y);
    return res;
}

double gravity::geometry::Vector2D::dot(const gravity::geometry::Vector2D &that) const
{
    return x * that.x + y * that.y;
}

double gravity::geometry::Vector2D::cross(const gravity::geometry::Vector2D &that) const
{
    return x * that.y - y * that.x;
}

double gravity::geometry::Vector2D::length() const
{
    return sqrt(sqrLength());
}

double gravity::geometry::Vector2D::sqrLength() const
{
    return x * x + y * y;
}

gravity::geometry::Vector2D gravity::geometry::Vector2D::normalize() const
{
    gravity::geometry::Vector2D res(*this);
    res /= length();
    return res;
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::normalized()
{
    *this /= length();
    return *this;;
}

gravity::geometry::Vector2D gravity::geometry::Vector2D::rotate(double ang) const
{
    Vector2D res;
    double sinA = sin(ang), cosA = cos(ang);
    res.x = x * cosA - y * sinA;
    res.y = x * sinA + y * cosA;
    return res;;
}

gravity::geometry::Vector2D &gravity::geometry::Vector2D::rotated(double ang)
{
    double sinA = sin(ang), cosA = cos(ang);
    double new_x = x * cosA + y * sinA;
    double new_y = -x * sinA + y * cosA;
    x = new_x;
    y = new_y;
    return *this;
}

double gravity::geometry::Vector2D::angleOX() const
{
    return atan2(y, x);
}

bool gravity::geometry::Vector2D::isNull() const
{
    return x == 0 && y == 0;
}

double gravity::geometry::distance(const gravity::geometry::Vector2D &a, const gravity::geometry::Vector2D &b)
{
    return (a - b).length();
}

double gravity::geometry::angleBetween(const gravity::geometry::Vector2D &a, const gravity::geometry::Vector2D &b)
{
    double res = std::abs(asin(a.normalize().cross(b.normalize())));
    if(a.dot(b) < 0)
        res = M_PI - res;
    return res;
}

gravity::geometry::Vector2D operator+(const gravity::geometry::Vector2D &a, const gravity::geometry::Vector2D &b)
{
    gravity::geometry::Vector2D res = a;
    res += b;
    return res;
}

gravity::geometry::Vector2D operator-(const gravity::geometry::Vector2D &a, const gravity::geometry::Vector2D &b)
{
    gravity::geometry::Vector2D res = a;
    res -= b;
    return res;
}

gravity::geometry::Vector2D operator*(double num, const gravity::geometry::Vector2D &vec)
{
    gravity::geometry::Vector2D res = vec;
    res *= num;
    return res;
}

gravity::geometry::Vector2D operator*(const gravity::geometry::Vector2D &vec, double num)
{
    gravity::geometry::Vector2D res = vec;
    res *= num;
    return res;
}

gravity::geometry::Vector2D operator/(const gravity::geometry::Vector2D &vec, double num)
{
    gravity::geometry::Vector2D res = vec;
    res /= num;
    return res;
}
