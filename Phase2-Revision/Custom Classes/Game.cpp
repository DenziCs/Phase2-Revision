#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Shuriken Spin") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(0, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));
    physWorld.setContactLimit(50);

    shuriken = new sf::Sprite();
    sf::Texture* star = new sf::Texture();
    if (!star->loadFromFile("Textures/shuriken.png")) {
        return;
    }
    shuriken->setTexture(*star);

    sf::FloatRect bounds = shuriken->getLocalBounds();
    shuriken->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    shuriken->setPosition(Utils::toWindowPoint(Vector(0, 0)));
    
    Particle* particle1 = new Particle(false, 50.f, 0, 0, 1, 20.f, sf::Color::White);
    physWorld.addParticle(particle1);
    origin = particle1;

    Particle* particle2 = new Particle(false, 0.1, 100, 0, 0.8, 15, sf::Color::Blue);
    physWorld.addParticle(particle2);

    Particle* particle3 = new Particle(false, 0.1, 0, 100, 0.8, 15, sf::Color::Blue);
    physWorld.addParticle(particle3);
    reference = particle3;

    Particle* particle4 = new Particle(false, 0.1, -100, 0, 0.8, 15, sf::Color::Blue);
    physWorld.addParticle(particle4);

    Particle* particle5 = new Particle(false, 0.1, 0, -100, 0.8, 15, sf::Color::Blue);
    physWorld.addParticle(particle5);

    AnchoredRod* center = new AnchoredRod(Vector(0, 0), particle1);
    physWorld.anchorList.push_back(center);

    physWorld.linkWithRod(particle1, particle3);

    physWorld.linkWithRod(particle1, particle2);
    physWorld.linkWithRod(particle1, particle4);
    physWorld.linkWithRod(particle1, particle5);

    physWorld.linkWithRod(particle2, particle3);
    physWorld.linkWithRod(particle3, particle4);
    physWorld.linkWithRod(particle4, particle5);
    physWorld.linkWithRod(particle5, particle2);

    particle3->applyForce(Vector(20000, 0));
};

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (gWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (gWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            gWindow.close();
            break;
        default:
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    physWorld.update(deltaTime.asSeconds());
    if (reference->getVelocity().getMagnitude() <= 10) {
        finalVelocity = reference->getVelocity().getMagnitude();
        gWindow.close();
    }

    totalTime += deltaTime.asSeconds();

    Vector distance = reference->getPosition() - origin->getPosition();
    float theta = atan2f(distance.y, distance.x);
    theta *= 180 / acos(-1.0);

    float deltaTheta = abs(theta - previousTheta);
    totalDegrees += deltaTheta;
    previousTheta = theta;

    shuriken->setRotation(-theta);
}

void Game::render() {
    gWindow.clear();
    gWindow.draw(*shuriken);
    physWorld.drawAll(&gWindow);
    gWindow.display();
}