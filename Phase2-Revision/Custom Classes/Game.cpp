#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(0, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));

    Vector e = physWorld.asWindowPoint(Vector(0, 0));
    Particle* particle1 = new Particle(20.f, e.x, e.y, 80.f, 1.f, 5.f, sf::Color::White);
    physWorld.addParticle(particle1);
    //particle1->setVelocity(Vector(30, -30));

    physWorld.anchorWithSpring(particle1, Vector(400, 50), 5, 0.5f);
    particle1->applyForce(Vector(-90, 4800));

    /*
    e = physWorld.asWindowPoint(Vector(75, -75));
    Particle* particle2 = new Particle(1.5f, e.x, e.y, 80.f, 1.f, 7.f, sf::Color::Blue);
    physWorld.addParticle(particle2);
    particle2->setVelocity(Vector(-10, 10));
    */

    //AppliedForceGenerator* gen = new AppliedForceGenerator(Vector(0, 98));
    //physWorld.addForce(particle1, gen);
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
}

void Game::render() {
    gWindow.clear();
    physWorld.drawAll(&gWindow);
    gWindow.display();
}