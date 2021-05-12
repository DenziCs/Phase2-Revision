#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(9.8, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));

    Particle* particle1 = new Particle(20.f, 0, -10, 80.f, 1.f, 5.f, sf::Color::Blue);
    physWorld.addParticle(particle1);

    physWorld.anchorWithSpring(particle1, Vector(0, 40), 5.f, 0.5f);
    particle1->applyForce(Vector(96000, 48000));
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