#include "Meteor.h"
#include "Textures.h"


Meteor::Meteor(float size)// size with default value and I think thats it
    :size_m(size), visual(TEXTURES.meteor)
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

    // scaling
    visual.scale({ size_m, size_m });
    hitBox.scale({ size_m, size_m });
    mass = mass * size_m;
    maxHealth = maxHealth * static_cast<int>(size_m);

    // launch mechanics
    respawn();

}

void Meteor::update(float dt)
{
    // if its time shoot out meteor
    if (launchTime <= launchClock.getElapsedTime().asSeconds() and (inPlay == false))
    {
        inPlay = true;
        velocity = launchVelocity;
    }

    // check to see if out of bounds and reset it if it is.    
    sf::Vector2f pos = visual.getPosition();
    if (pos.x < -220 or pos.x > 1820 or pos.y > 1120 or pos.y < -220)
        respawn();

    // move meteor based on velocity
    hitBox.move(velocity * dt);
    visual.move(velocity * dt);

}


void Meteor::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}


// respawn helper.
// How this funciton works is it randomly choose a side to put the metor on as well as a random position to put it based on the side.
// then based on the position it targets the two corners of the screen opposite from it. So if the meteor is placed on the left side
// then it targets the top-right and bottom-right of screen. Then it gets a random angle between those two corners and shoots out the.
// metoer in that direction.
std::pair<sf::Vector2f, float> SpawnInfo(float screenWidth, float screenHeight)
{
    // could switch to radians but degrees is more intuitive. Also easier to use with the randon number generator.
    constexpr float RAD_TO_DEG = 180.f / 3.14159265f;
    int side = Random::get(0, 3); // 0=top, 1=right, 2=bottom, 3=left
    sf::Vector2f pos;
    float angle;
    float bottomAngle;
    float topAngle;

    ////////////////////////////// I think i can use atan2 and think about just cetner make the position start zero zero then claculting the
    // angles af it the position of the metoer is 0,0 and getting the resolution of the screen from assuming 0,0 meteor is the cetner
    switch (side) {
    case 0: // top
        pos = { Random::get(0.f, screenWidth), 0.f };
        topAngle = std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 270.f;
        bottomAngle = -std::atan(pos.x / screenHeight) * RAD_TO_DEG + 270.f;
        angle = Random::get(bottomAngle, topAngle);

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;

        break;
    case 1: // right

        pos = { screenWidth, Random::get(0.f, screenHeight) };
        topAngle = -std::atan(pos.y / screenWidth) * RAD_TO_DEG + 180.f;
        bottomAngle = std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG + 180.f;
        angle = Random::get(topAngle, bottomAngle);

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;

        break;
    case 2: // bottom

        pos = { Random::get(0.f, screenWidth), screenHeight };
        topAngle = std::atan(pos.x / screenHeight) * RAD_TO_DEG + 90.f;
        bottomAngle = -std::atan((screenWidth - pos.x) / screenHeight) * RAD_TO_DEG + 90.f;
        angle = Random::get(bottomAngle, topAngle);

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;
        break;
    case 3: // left

        pos = { 0.f, Random::get(0.f, screenHeight) };
        topAngle = std::atan(pos.y / screenWidth) * RAD_TO_DEG;
        bottomAngle = -std::atan((screenHeight - pos.y) / screenWidth) * RAD_TO_DEG;
        angle = Random::get(bottomAngle, topAngle);

        std::cout << topAngle << std::endl;
        std::cout << bottomAngle << std::endl;
        break;
    default:
        pos = { 0.f, 0.f };
        angle = 0;
    }
    return { pos, angle };
}


// setting up meteor intitally, when out of bounds, or when is destryoed
void Meteor::respawn()
{
    inPlay = false;
    constexpr float DEG_TO_RAD = 3.14159265f / 180.f;
    float screenWidth{ 1600.f };// for now just fix screen to be 1600 x 900
    float screenHeight{ 900.f };

    // sets a new random position on outer screen and angle to shoot out at based on the two opposite sides of the screen
    auto [pos, angle] = SpawnInfo(screenWidth, screenHeight);
    visual.setPosition(pos);
    hitBox.setPosition(pos);
    float xDirection = std::cos(angle * DEG_TO_RAD);
    float yDirection = std::sin(angle * DEG_TO_RAD);
    float speed= Random::get(minSpeed, maxSpeed);
    launchVelocity = { speed * xDirection, speed * -yDirection };

    velocity = { sf::Vector2f(0.f, 0.f) }; // set velocity to zero and wait for launch time
    currHealth = maxHealth; // reset health

    launchTime = launchClock.getElapsedTime().asSeconds() + Random::get(2, 30); // amount of seconds from current time it will be shot out
}