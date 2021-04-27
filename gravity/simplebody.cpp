#include "simplebody.h"

using namespace gravity::geometry;
using namespace gravity::physics;

SimpleBody::SimpleBody(double mass, double radius)
    : IBody{new CircleShape(radius), mass, 0.0} {}
