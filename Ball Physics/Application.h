#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
#include <iostream>
#include <cmath>

#define pi std::acos(-1)

class Application {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    //objects
    sf::CircleShape ball;
    sf::RectangleShape line;
    sf::ConvexShape triangle;
    sf::CircleShape center;
    sf::Mouse pointer;
    sf::Cursor hand;
    sf::Cursor arrow;
    sf::SoundBuffer soundBuf;
    sf::Sound collide;
    //logics
    bool isPressed=false;
    bool ballMoving=false;
    float ballAngle;
    float ballSpeed;
    const float ballRadius = 20;
    float drag=0.85f;
    sf::Vector2f velocity;
    //text
    //resources
    //functions
    void initWindows();
    void initVariables();
    void resetBall();
    float getAngle();
    sf::Vector2f getCursorPos();
public:
    Application();
    void pollEvents();
    void update();
    void updateArrow();
    void updatePhysics();
    void updateCollision();
    void render();
    const sf::RenderWindow* getWindow() const;
    ~Application();
};
