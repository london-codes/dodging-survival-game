#include "Meteor.h"





void Meteor::update(float dt)
{
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);
}


void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}