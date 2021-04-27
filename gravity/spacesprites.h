#ifndef SIMPLECIRCLESPRITE_H
#define SIMPLECIRCLESPRITE_H

#include <SFML/Graphics.hpp>

class SimpleCircleSprite : public sf::Sprite
{
public:
    SimpleCircleSprite(float radius);

private:
    float radius;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
};

#endif // SIMPLECIRCLESPRITE_H
