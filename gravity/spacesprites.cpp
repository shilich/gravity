#include "spacesprites.h"

SimpleCircleSprite::SimpleCircleSprite(float radius)
    : radius{radius} {}

void SimpleCircleSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::CircleShape shape(radius);
    shape.move(-radius, -radius);

    target.draw(shape, states);
}
