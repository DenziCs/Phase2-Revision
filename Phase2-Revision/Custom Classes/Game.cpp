#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(9.8, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));

    Vector e = physWorld.asWindowPoint(Vector(0, 0));
    Particle* particle1 = new Particle(10.f, e.x, e.y, 80.f, 1.f, 5, sf::Color::White);
    physWorld.addParticle(particle1);

    e = physWorld.asWindowPoint(Vector(0, 100));
    Particle* particle2 = new Particle(10.f, e.x, e.y, 80.f, 1.f, 5, sf::Color::White);
    physWorld.addAnchorPoint(particle2);
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