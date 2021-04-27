#ifndef IBODY_H
#define IBODY_H

#include "vector2d.h"
#include "ishape.h"

namespace gravity
{

namespace physics
{

struct PhaseCoordinate
{
    geometry::Vector2D position;
    geometry::Vector2D velocity;
    double angle;
    double angular_velocity;

    PhaseCoordinate update(double dt, const geometry::Vector2D& acceleration, double angular_acceleration) const;
    PhaseCoordinate& updated(double dt, const geometry::Vector2D& acceleration, double angular_acceleration);
};

struct Orbit
{
    bool exist{false};
    geometry::Vector2D mass_center;
    double p, e;
    double mass_factor;
};

class IBody
{
public:
    IBody(geometry::IShape *shape, double mass, double elasticity);
    virtual ~IBody();

    void update(double dt, const geometry::Vector2D& acceleration, double angular_acceleration);

    geometry::Vector2D accelerationFromBody(const IBody& that) const;

    virtual geometry::Vector2D acceleration(double dt) const = 0;
    virtual double angularAcceleration(double dt) const = 0;

    void setOrbit(const IBody& that);
    void disableOrbit();

    const Orbit& getOrbit() const;

    PhaseCoordinate coordinate;
protected:
    double mass, elasticity;
    geometry::IShape *shape{nullptr};

private:
    Orbit orbit;
};

}

}
#endif // IBODY_H
