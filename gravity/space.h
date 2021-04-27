#ifndef SPACE_H
#define SPACE_H

#include <SFML/Graphics.hpp>
#include "bodymanager.h"

class Space : public sf::Drawable, public sf::Transformable
{
public:
    Space() = default;
    ~Space();

    void add(std::string const& name, gravity::physics::IBody *body, sf::Sprite *sprite);

    const gravity::physics::IBody& operator[](std::string const& key) const;
    gravity::physics::IBody& operator[](std::string const& key);

    void render(double time);

private:
    gravity::physics::BodyManager<std::string> bm;
    std::map<std::string, sf::Sprite*> sprites;

    void updateSprites();

    static void getOrbitVertex(const gravity::physics::IBody& body, sf::VertexArray& vertex, unsigned count = 30);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // SPACE_H
