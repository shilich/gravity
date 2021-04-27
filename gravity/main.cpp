#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "simplebody.h"
#include "space.h"
#include "spacesprites.h"

using namespace gravity;

void setupSpace(Space& space)
{
    constexpr double planet_mass = 400.;
    constexpr double sun_mass_scale = 200.;
    constexpr double satelite_mass_scale = .1;
    constexpr double start_vel = 17.;
    constexpr double orbit_radius = planet_mass * sun_mass_scale / (start_vel * start_vel);
    constexpr double sun_radius = 40;
    constexpr double planet_radius = 5;
    constexpr double satelite_radius = 2;
    constexpr double satelite_vel = 8.;
    constexpr double satelite_orbit_radius = planet_mass / (satelite_vel * satelite_vel);

    space.add("sun", new physics::SimpleBody(planet_mass * sun_mass_scale, sun_radius), new SimpleCircleSprite(sun_radius));
    space.add("planet", new physics::SimpleBody(planet_mass, planet_radius), new SimpleCircleSprite(planet_radius));
    space.add("satelite", new physics::SimpleBody(planet_mass * satelite_mass_scale, satelite_radius), new SimpleCircleSprite(satelite_radius));

    space["planet"].coordinate.position = geometry::Vector2D(orbit_radius, 0);
    space["planet"].coordinate.velocity = geometry::Vector2D(0, start_vel);

    space["satelite"].coordinate.position = geometry::Vector2D(orbit_radius + satelite_orbit_radius, 0);
    space["satelite"].coordinate.velocity = geometry::Vector2D(0, start_vel - satelite_vel);
}

int main()
{
    /*
    physics::BodyManager<std::string> bm;

    double sun_mass = 100000.;
    double start_vel = 1.;
    double orbit_radius = sun_mass / (start_vel * start_vel);
    double t_max = 1000000.;
    double delta_t = t_max / 1000.;

    bm.add("sun", new physics::SimpleBody(sun_mass, 20));
    bm.add("planet", new physics::SimpleBody(1, 5));
    bm["planet"].coordinate.position = geometry::Vector2D(orbit_radius, 0);
    // m * M / r^2 == m v^2 / r => M / r == v^2 => v = sqr(M / r)
    bm["planet"].coordinate.velocity = geometry::Vector2D(0, start_vel);

    std::ofstream ofs_planet("planet.txt");
    std::ofstream ofs_sun("sun.txt");
    ofs_planet << "{{" << bm["planet"].coordinate.position.x << ", " << bm["planet"].coordinate.position.y << "}";
    ofs_sun << "{{" << bm["sun"].coordinate.position.x << ", " << bm["sun"].coordinate.position.y << "}";
    for(double t = delta_t; t < t_max; t += delta_t)
    {
        std::cout << t << std::endl;
        bm.run(t);
        ofs_planet << ", {" << bm["planet"].coordinate.position.x << ", " << bm["planet"].coordinate.position.y << "}";
        ofs_sun << ", {" << bm["sun"].coordinate.position.x << ", " << bm["sun"].coordinate.position.y << "}";
    }
    ofs_planet << "}";
    ofs_sun << "}";
    ofs_planet.close();
    ofs_sun.close();
*/

    sf::RenderWindow window(sf::VideoMode(800, 600), "Gravity");

    Space space;
    space.setPosition(400, 300);
    setupSpace(space);

    double time_speed = 8.;

    sf::Event event;
    sf::Clock clock;
    float time;
    double next_time = 0.;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        next_time += time * time_speed;
        if(next_time >= .1)
        {
            space.render(next_time);
            next_time = 0.;
        }

        window.clear(sf::Color::Black);

        window.draw(space);

        window.display();
    }

    return 0;
}
