#ifndef SIMPLEBODY_H
#define SIMPLEBODY_H

#include "ibody.h"
#include "circleshape.h"

namespace gravity
{

namespace physics
{

class SimpleBody : public IBody
{
public:
    SimpleBody(double mass, double radius);

    virtual geometry::Vector2D acceleration(double) const override { return geometry::Vector2D(); }
    virtual double angularAcceleration(double) const override { return 0.; }
};

}

}

#endif // SIMPLEBODY_H
