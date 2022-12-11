#include "Application.h"

Application::Application() {
    initVariables();
    initWindows();
}

//ACCESSORS
const sf::RenderWindow* Application::getWindow() const {
    return this->window;
}
float Application::getAngle() {
    float angle,distance;
    sf::Vector2f cursorRelative=sf::Vector2f(this->getCursorPos().x-this->ball.getPosition().x,
                                             -1*(this->getCursorPos().y-this->ball.getPosition().y));
    distance=sqrt(pow(this->ball.getPosition().x-this->getCursorPos().x,2)+
                  pow(this->ball.getPosition().y-this->getCursorPos().y,2));
    angle=(180/pi)*asin(abs(cursorRelative.x)/distance);

    if (cursorRelative.x>=0) {
        if (cursorRelative.y<0) angle=180-angle;
    }
    else if (cursorRelative.x<0) {
        if (cursorRelative.y>=0) angle=360-angle;
        else angle+=180;
    }
    return angle;
}
sf::Vector2f Application::getCursorPos() {
    return sf::Vector2f(this->pointer.getPosition(*this->window).x,this->pointer.getPosition(*this->window).y);
}

//PRIVATE FUNCTIONS
void Application::initVariables() {
    //initiate variables
    //initiate objects
    this->ball.setRadius(this->ballRadius);
    this->ball.setFillColor(sf::Color::White);
    this->ball.setOrigin(ball.getRadius(),ball.getRadius());
    this->ball.setPosition(400,300);

    this->line.setOrigin(4,-4);
    this->line.setSize(sf::Vector2f(8,-80));
    this->line.setPosition(sf::Vector2f(400,300));
    this->line.setFillColor(sf::Color::Red);

    this->center.setOrigin(5.5,5.5);
    this->center.setRadius(5.5);
    this->center.setPosition(400,300);
    this->center.setFillColor(sf::Color::Red);

    if (!this->hand.loadFromSystem(sf::Cursor::Hand)) this->window->close();
    if (!this->arrow.loadFromSystem(sf::Cursor::Arrow)) this->window->close();

    if (!this->soundBuf.loadFromFile("resources/ball.wav")) this->window->close();
    else this->collide.setBuffer(this->soundBuf);

    this->triangle.setPointCount(3);
    this->triangle.setPoint(0,sf::Vector2f(300,300));
    this->triangle.setPoint(1,sf::Vector2f(310,280));
    this->triangle.setPoint(2,sf::Vector2f(320,300));
    this->triangle.setFillColor(sf::Color::Red);
    this->triangle.setOrigin(310,295);
    this->triangle.setPosition(400,300);
}
void Application::initWindows() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(videoMode, "BallPhysics", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(120);
}
void Application::resetBall()
{
    this->ballMoving=false;
    this->ball.setPosition(400,300);
}

//PUBLIC FUNCTIONS
void Application::update()
{
    this->pollEvents();
    if (this->isPressed) this->updateArrow();
    if (this->ballMoving) {
        this->updatePhysics();
        this->updateCollision();
    }
    if ((this->ball.getGlobalBounds().contains(this->getCursorPos()) && !this->ballMoving) || this->isPressed)
        this->window->setMouseCursor(this->hand);
    else this->window->setMouseCursor(this->arrow);
}
void Application::updateArrow()
{
    float length;
    this->line.setSize(sf::Vector2f(0,0));
    this->line.setPosition(this->ball.getPosition());

    this->center.setPosition(this->ball.getPosition().x,this->ball.getPosition().y);
    length=sqrt(pow(this->ball.getPosition().x-this->getCursorPos().x,2)+pow(this->ball.getPosition().y-this->getCursorPos().y,2));

    this->line.setSize(sf::Vector2f(8,-length-10));
    this->line.setRotation(this->getAngle());
    this->ballSpeed=length*0.02;

    this->triangle.setPosition(this->getCursorPos());
    this->triangle.setRotation(this->getAngle());
}
void Application::updatePhysics()
{
    this->velocity=sf::Vector2f(this->ballSpeed*sin(this->ballAngle*pi/180),-this->ballSpeed*cos(this->ballAngle*pi/180));
    this->ball.move(this->velocity);
}
void Application::updateCollision()
{
    //left collision
    if (this->ball.getPosition().x-ball.getRadius() < 0)
    {
        if (this->ballAngle==270) this->ballAngle=90;
        else if (this->ballAngle>270) this->ballAngle=90-(this->ballAngle-270);
        else this->ballAngle=90+(270-this->ballAngle);
        this->collide.play();
    }
    //top collision
    if (this->ball.getPosition().y-ball.getRadius() < 0)
    {
        if (this->ballAngle==0) this->ballAngle=180;
        else if (this->ballAngle<90) this->ballAngle=180-this->ballAngle;
        else this->ballAngle=180+(360-this->ballAngle);
        this->collide.play();
    }
    //right collision
    if (this->ball.getPosition().x+ball.getRadius() > 800)
    {
        if (this->ballAngle==90) this->ballAngle=270;
        else if (this->ballAngle<90) this->ballAngle=270+(90-this->ballAngle);
        else this->ballAngle=270-(this->ballAngle-90);
        this->collide.play();
    }
    //bottom collision
    if (this->ball.getPosition().y+ball.getRadius() > 600)
    {
        if (this->ballAngle==180) this->ballAngle=0;
        else if (this->ballAngle<180) this->ballAngle=180-this->ballAngle;
        else this->ballAngle=360-(this->ballAngle-180);
        this->collide.play();
    }
}
void Application::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (this->event.key.code == sf::Keyboard::Space) this->resetBall();
            if (this->event.key.code == sf::Keyboard::Enter) this->resetBall();
            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.mouseButton.button == sf::Mouse::Left) {
                if (this->ball.getGlobalBounds().contains(this->getCursorPos()) && !this->ballMoving) this->isPressed=true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (this->event.mouseButton.button == sf::Mouse::Left && this->isPressed) {
                this->ballAngle=this->getAngle();
                this->isPressed=false;
                this->ballMoving=true;
            }
            break;
        default:
            break;
        }
    }
}
void Application::render()
{
    this->window->clear(sf::Color(50,50,50,255));
    //draw objects
    this->window->draw(this->ball);
    if (this->isPressed) {
        this->window->draw(this->line);
        this->window->draw(this->center);
        this->window->draw(this->triangle);
    }
    this->window->display();
}

Application::~Application() {
    delete this->window;
}
