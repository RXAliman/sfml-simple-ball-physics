#include <iostream>
#include "Application.h"

int main()
{
    Application app;
    while (app.getWindow()->isOpen())
    {
        app.update();
        app.render();
    }
    return 0;
}
/*
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define pi std::acos(-1)

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Testing", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape ball;
    sf::CircleShape pivot;
    sf::Clock clock;

    float angle=0;
    float posX,posY;
    float ballSpeed=0.5f;
    const float drag=0.1f;
    const int distance=50;
    bool running=false;

    ball.setRadius(20);
    ball.setFillColor(sf::Color::White);
    ball.setOutlineColor(sf::Color::Black);
    ball.setOutlineThickness(3.f);
    ball.setOrigin(20,20);
    ball.setPosition(400,300);

    pivot.setRadius(5);
    pivot.setFillColor(sf::Color::Red);
    pivot.setOrigin(10,10);
    pivot.setPosition(400,300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Right)
                    angle+=10;
                else if (event.key.code == sf::Keyboard::Left)
                    angle-=10;
                if (event.key.code == sf::Keyboard::Space)
                    running=!running;
            }
        }
        window.clear(sf::Color(100,100,100,255));

        //update
        if (angle==360) angle=0;
        posX=distance*std::sin(angle*pi/180);
        posY=-distance*std::cos(angle*pi/180);
        pivot.setPosition(405+posX,305+posY);
        if (running) {
            ball.move(ballSpeed*std::sin(angle*pi/180),-ballSpeed*std::cos(angle*pi/180));
            if (clock.getElapsedTime().asMilliseconds() > 500) {
                clock.restart();
                ballSpeed-=drag;
            }
            if (ballSpeed < 0) ballSpeed = 0;
        }
        else {
            ballSpeed = 0.5f;
            ball.setPosition(400,300);
        }
        std::cout << ball.getPosition().x << ',' << ball.getPosition().y << std::endl;

        //render
        window.draw(ball);
        window.draw(pivot);
        window.display();
    }
    return 0;
}
*/
