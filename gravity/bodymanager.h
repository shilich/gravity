#ifndef BODYMANAGER_H
#define BODYMANAGER_H

#include <map>
#include <cassert>
#include <stdexcept>
#include "ibody.h"

//#include <iostream>

namespace gravity
{

namespace physics
{

template <typename KEY_T>
class BodyManager
{
public:
    BodyManager() = default;
    BodyManager(double dt);

    ~BodyManager();

    IBody *add(KEY_T key, IBody* body);

    const IBody& operator[](KEY_T key) const;
    IBody& operator[](KEY_T key);

    void run(double time);

    class body_iterator: public std::iterator<std::input_iterator_tag, IBody>
    {
        friend class BodyManager;
    public:
        body_iterator(const body_iterator& it);

        bool operator!=(const body_iterator& that);
        bool operator==(const body_iterator& that);

        typename body_iterator::reference operator*() const;
        IBody* operator->();

        body_iterator& operator++();
    private:
        body_iterator(typename std::map<KEY_T, IBody*>::iterator bodies_iterator);
        typename std::map<KEY_T, IBody*>::iterator b;
    };

    body_iterator begin();
    body_iterator end();

private:
    double dt{.1};

    void oneStep(double delta, bool final = false);

    std::map<KEY_T, IBody*> bodies;
    std::map<KEY_T, std::pair<geometry::Vector2D, double> > acc;
};

template<typename KEY_T>
BodyManager<KEY_T>::BodyManager(double dt)
    : dt{dt} {}

template<typename KEY_T>
BodyManager<KEY_T>::~BodyManager()
{
    for(auto body : bodies)
        delete body.second;
}

template<typename KEY_T>
IBody *BodyManager<KEY_T>::add(KEY_T key, IBody *body)
{
    assert(body);

    if(bodies.find(key) != bodies.end())
        throw std::invalid_argument("The key allready exists!");

    bodies.insert({key, body});
    acc.insert({key, {geometry::Vector2D(), 0.}});

    return body;
}

template<typename KEY_T>
const IBody &BodyManager<KEY_T>::operator [](KEY_T key) const
{
    return *bodies.at(key);
}

template<typename KEY_T>
IBody &BodyManager<KEY_T>::operator [](KEY_T key)
{
    return *bodies[key];
}

template<typename KEY_T>
void BodyManager<KEY_T>::run(double time)
{
    double t = 0.;
    for(; t < time; t += dt)
        oneStep(dt);
    oneStep(time - t + dt, true);
}

template<typename KEY_T>
typename BodyManager<KEY_T>::body_iterator BodyManager<KEY_T>::begin()
{
    return body_iterator(bodies.begin());
}

template<typename KEY_T>
typename BodyManager<KEY_T>::body_iterator BodyManager<KEY_T>::end()
{
    return body_iterator(bodies.end());
}

template<typename KEY_T>
void BodyManager<KEY_T>::oneStep(double delta, bool final)
{
    double max_acc = 0.;
    double tmp;
    geometry::Vector2D tmp_acc;
    IBody* orbit_center = nullptr;
    for(auto& a : bodies)
    {
        geometry::Vector2D& acceleration = acc[a.first].first = geometry::Vector2D();
        double& angular_acceleration = acc[a.first].second = 0.;
        IBody& body = *(a.second);
        max_acc = 0.;
        for(const auto& b : bodies)
        {
            tmp_acc = body.accelerationFromBody(*(b.second));
            acceleration += tmp_acc;
            if(final)
            {
                tmp = tmp_acc.sqrLength();
                if(tmp > max_acc)
                {
                    max_acc = tmp;
                    orbit_center = b.second;
                }
            }
        }
        acceleration += body.acceleration(delta);
        angular_acceleration = body.angularAcceleration(delta);

        if(final)
        {
            if(max_acc > .01 /** body.coordinate.velocity.sqrLength()*/)
                body.setOrbit(*orbit_center);
            else
                body.disableOrbit();
        }
    }

    for(auto& body : bodies)
        body.second->update(delta, acc[body.first].first, acc[body.first].second);
}

//-------------------body_iterator--------------------------------------------------------

template<typename KEY_T>
BodyManager<KEY_T>::body_iterator::body_iterator(typename std::map<KEY_T, IBody*>::iterator bodies_iterator)
    : b{bodies_iterator} {}

template<typename KEY_T>
BodyManager<KEY_T>::body_iterator::body_iterator(const BodyManager<KEY_T>::body_iterator& it)
    : b{it.b} {}

template<typename KEY_T>
bool BodyManager<KEY_T>::body_iterator::operator!=(const BodyManager<KEY_T>::body_iterator& that)
{
    return b != that.b;
}

template<typename KEY_T>
bool BodyManager<KEY_T>::body_iterator::operator==(const BodyManager<KEY_T>::body_iterator& that)
{
    return b == that.b;
}

template<typename KEY_T>
typename BodyManager<KEY_T>::body_iterator::reference BodyManager<KEY_T>::body_iterator::operator*() const
{
    return *b->second;
}

template<typename KEY_T>
IBody* BodyManager<KEY_T>::body_iterator::operator->()
{
    return b->second;
}

template <typename KEY_T>
typename BodyManager<KEY_T>::body_iterator& BodyManager<KEY_T>::body_iterator::operator++()
{
    return b++;
}

}

}

#endif // BODYMANAGER_H
