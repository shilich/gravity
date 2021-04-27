#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include <ishape.h>

namespace gravity
{

namespace geometry
{

class CircleShape : public IShape
{
public:
    CircleShape(double radius);

    CircleShape(const CircleShape&) = delete;
    CircleShape(CircleShape&&) = delete;

    virtual Vector2D farthestPointInDirection(const Vector2D& direction) override;

private:
    double radius;
};

}

}

#endif // CIRCLESHAPE_H
