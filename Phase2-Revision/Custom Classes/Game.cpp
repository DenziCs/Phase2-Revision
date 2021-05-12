#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(9.8, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));
    physWorld.setContactLimit(25);

    Particle* particle1 = new Particle(20.f, -170, 0, 80.f, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle1);

    physWorld.anchorWithCable(particle1, Vector(-170, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle2 = new Particle(20.f, -85, 0, 80.f, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle2);
    physWorld.anchorWithCable(particle2, Vector(-85, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle3 = new Particle(20.f, 0, 0, 80.f, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle3);
    physWorld.anchorWithCable(particle3, Vector(0, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle4 = new Particle(20.f, 85, 0, 80.f, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle4);
    physWorld.anchorWithCable(particle4, Vector(85, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle5 = new Particle(20.f, 170, 0, 80.f, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle5);
    physWorld.anchorWithCable(particle5, Vector(170, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    //physWorld.linkWithRod(particle1, particle2);

    //AppliedForceGenerator* gen = new AppliedForceGenerator(Vector(4000, 0));
    //physWorld.addForce(particle1, gen);

    //physWorld.anchorWithSpring(particle1, Vector(0, 40), 5.f, 0.5f);
    particle1->applyForce(Vector(-32000, 0));
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