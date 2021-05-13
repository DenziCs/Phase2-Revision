#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(9.8, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));
    physWorld.setContactLimit(25);

    Particle* particle1 = new Particle(false, 20.f, -170, 0, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle1);
    physWorld.anchorWithCable(particle1, Vector(-170, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle2 = new Particle(false, 20.f, -85, 0, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle2);
    physWorld.anchorWithCable(particle2, Vector(-85, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle3 = new Particle(false, 20.f, 0, 0, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle3);
    physWorld.anchorWithCable(particle3, Vector(0, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle4 = new Particle(false, 20.f, 85, 0, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle4);
    physWorld.anchorWithCable(particle4, Vector(85, WINDOW_Y / 2), 5, WINDOW_Y / 2);

    Particle* particle5 = new Particle(false, 20.f, 170, 0, 1.f, 40.f, sf::Color::Blue);
    physWorld.addParticle(particle5);
    physWorld.anchorWithCable(particle5, Vector(170, WINDOW_Y / 2), 5, WINDOW_Y / 2);
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
        case sf::Event::KeyReleased:
            if (event.key.code && sf::Keyboard::Space) {
                push = true;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (push) {
        (*physWorld.particleList.begin())->applyForce(Vector(-40000, 0));
        push = false;
    }
    physWorld.update(deltaTime.asSeconds());
}

void Game::render() {
    gWindow.clear();
    physWorld.drawAll(&gWindow);
    gWindow.display();
}