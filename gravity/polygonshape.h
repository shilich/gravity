#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include <ishape.h>

namespace gravity
{

namespace geometry
{

class PolygonShape: public IShape
{
public:
    PolygonShape(const std::vector<Vector2D>& vertex);
    PolygonShape(std::vector<Vector2D>&& vertex);
    PolygonShape(std::initializer_list<Vector2D> vertex);

    PolygonShape(const PolygonShape&) = delete;
    PolygonShape(PolygonShape&&) = delete;

    virtual Vector2D farthestPointInDirection(const Vector2D& direction) override;

private:
    std::vector<Vector2D> points;

    Vector2D updatedPosition(const Vector2D& point);
};

}

}
#endif // POLYGONSHAPE_H
