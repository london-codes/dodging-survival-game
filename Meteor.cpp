#include "Meteor.h"
#include "Textures.h"


Meteor::Meteor()// size with default value and I think thats it
    : visual(TEXTURES.meteor), velocity{ 0.f, 0.f } // to test
{


    // hit box
    hitBox.setPointCount(4);
    hitBox.setPoint(0, sf::Vector2f{ -7, -8 });
    hitBox.setPoint(1, sf::Vector2f{ 8, -8 });
    hitBox.setPoint(2, sf::Vector2f{ 8, 7 });
    hitBox.setPoint(3, sf::Vector2f{ -7, 7 });
    hitBox.setPosition({ 100.f,450.f });

    // visual
    visual.setOrigin({ visual.getLocalBounds().size.x / 2, visual.getLocalBounds().size.y / 2 });
    visual.setPosition({ 100.f,450.f });

    // luanch
    launchTime = launchClock.getElapsedTime().asSeconds() + Random::get(2, 10);
    // set launch time probably set like global speed for all rocks and then divy that speed up for the x and y
    //veleocities. maybe just get a random number thats a likea fraction or acutually made genreate a random angle
    // between where you want it to shoot off then clac the sin cos of its x y velcoties
}

//CURENTTLY NOTE USING MIGHT GET RID OF
void Meteor::collision(float otherMass, sf::Vector2f otherVelocity)
{
    //velocity = velocity * -1.f;

    velocity.x = ((mass - otherMass) / (mass + otherMass)) * velocity.x
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.x;
    velocity.y = ((mass - otherMass) / (mass + otherMass)) * velocity.y
        + ((2 * otherMass) / (mass + otherMass)) * otherVelocity.y;

}

void Meteor::update(float dt)
{
    if (launchTime <= launchClock.getElapsedTime().asSeconds())
    {
        velocity = launchVelocity;
        launchTime = 100.f;
    }
        

    hitBox.move(velocity * dt);
    visual.move(velocity * dt);

}


void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}