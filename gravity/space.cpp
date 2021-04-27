#include "space.h"

//#include <iostream>

Space::~Space()
{
    for(auto sprite : sprites)
        delete sprite.second;
}

void Space::add(const std::string &name, gravity::physics::IBody *body, sf::Sprite *sprite)
{
    assert(sprite);

    bm.add(name, body);
    sprites.insert({name, sprite});
}

const gravity::physics::IBody &Space::operator[](const std::string &key) const
{
    return bm[key];
}

gravity::physics::IBody &Space::operator[](const std::string &key)
{
    return bm[key];
}

void Space::render(double time)
{
    bm.run(time);
    updateSprites();
}

void Space::updateSprites()
{
    for(auto& it : sprites)
    {
        sf::Sprite& sprite = *(it.second);
        gravity::physics::PhaseCoordinate& body = bm[it.first].coordinate;
        sprite.setPosition(body.position.x, -body.position.y);
        sprite.setRotation(body.angle);
    }
}

void Space::getOrbitVertex(const gravity::physics::IBody &body, sf::VertexArray &vertex, unsigned count)
{
    vertex.clear();
    vertex.resize(count + 1);
    double phi = (body.getOrbit().e < 1) ? (-M_PI) : (-M_PI * .75);
    double step = (body.getOrbit().e < 1) ? (2. * M_PI / count) : (1.5 * M_PI / count);
    gravity::geometry::Vector2D n = body.coordinate.position - body.getOrbit().mass_center;
    n.normalized();
    gravity::geometry::Vector2D r;
    double distance;

    for(unsigned i = 0; i < count + 1; ++i, phi += step)
    {
        distance = body.getOrbit().p / (1. + body.getOrbit().e * cos(phi));
        r = body.getOrbit().mass_center + body.getOrbit().mass_factor * n.rotate(-phi) * distance;

        vertex[i].position = sf::Vector2f(r.x, -r.y);
        vertex[i].color = sf::Color::Red;
    }
}

void Space::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::VertexArray vertex;
    vertex.setPrimitiveType(sf::LineStrip);
    for(const auto& it : sprites)
    {
        if(bm[it.first].getOrbit().exist)
        {
            getOrbitVertex(bm[it.first], vertex, 60);
            target.draw(vertex, states);
        }
        target.draw(*(it.second), states);
    }
}
