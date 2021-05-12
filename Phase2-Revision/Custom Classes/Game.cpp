#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(0, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));
    physWorld.setContactLimit(25);

    Particle* particle1 = new Particle(20.f, -80, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle1);

    Particle* particle2 = new Particle(20.f, -50, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle2);

    Particle* particle3 = new Particle(20.f, -20, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle3);

    Particle* particle4 = new Particle(20.f, 10, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle4);

    Particle* particle5 = new Particle(20.f, 40, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle5);

    //physWorld.linkWithRod(particle1, particle2, 50);

    //physWorld.anchorWithSpring(particle1, Vector(0, 40), 5.f, 0.5f);
    particle1->applyForce(Vector(40000, 0));
    //particle2->applyForce(Vector(-14000, 0));
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