#include "ibody.h"

#include <cassert>
//#include <iostream>

using namespace gravity::physics;
using namespace gravity::geometry;

PhaseCoordinate PhaseCoordinate::update(double dt, const Vector2D &acceleration, double angular_acceleration) const
{
    PhaseCoordinate res;
    res.velocity = velocity + dt * acceleration;
    res.position = position + dt * (velocity + dt * acceleration / 2.);
    res.angular_velocity = angular_velocity + dt * angular_acceleration;
    res.angle = angle + dt * (angular_velocity + dt * angular_acceleration / 2.);
    res.angle -= int(res.angle / M_PI) * M_PI;
    return res;
}

PhaseCoordinate &PhaseCoordinate::updated(double dt, const Vector2D &acceleration, double angular_acceleration)
{
    position = position + dt * (velocity + dt * acceleration / 2.);
    velocity = velocity + dt * acceleration;
    angle = angle + dt * (angular_velocity + dt * angular_acceleration / 2.);
    angular_velocity = angular_velocity + dt * angular_acceleration;
    angle -= int(angle / M_PI) * M_PI;
    return *this;
}

IBody::IBody(IShape *shape, double mass, double elasticity)
    : mass{mass}, elasticity{elasticity}
{
    assert(shape && "The body must have a shape!");
    this->shape = shape;
}

IBody::~IBody()
{
    delete shape;
}

void IBody::update(double dt, const Vector2D &acceleration, double angular_acceleration)
{
    coordinate.updated(dt, acceleration, angular_acceleration);
    shape->setCenter(coordinate.position);
    shape->setAngle(coordinate.angle);
}

Vector2D IBody::accelerationFromBody(const IBody &that) const
{
    CollisionChecker collided;
    if(this == &that /*|| collided(*shape, *that.shape).isCollided()*/) //проверка колизий не работает :(
        return Vector2D();

    Vector2D r = that.coordinate.position - coordinate.position;
    Vector2D res = that.mass * r.normalize() / r.sqrLength();
    return res;
    //    return that.mass * r / (len_r * len_r * len_r);
}

void IBody::setOrbit(const IBody &that)
{
    if(this == &that)
    {
        orbit.exist = false;
        return;
    }
    orbit.exist = true;
    orbit.mass_center = (mass * coordinate.position + that.mass * that.coordinate.position) / (mass + that.mass);
    orbit.mass_factor = that.mass / (mass + that.mass);

    double mu = mass * orbit.mass_factor;

    Vector2D r = coordinate.position - that.coordinate.position;
    Vector2D v = coordinate.velocity - that.coordinate.velocity;
    double L = mu * r.cross(v);
    double E = mu * v.sqrLength() / 2. - mass * that.mass / r.length();

    orbit.p = L * L / (mu * mass * that.mass);
    orbit.e = sqrt(1. + 2. * E * L * L / (mu * mass * mass * that.mass * that.mass));
}

void IBody::disableOrbit()
{
    orbit.exist = false;
}

const Orbit &IBody::getOrbit() const
{
    return orbit;
}
