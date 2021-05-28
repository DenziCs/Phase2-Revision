#include "Game.h"

Game::Game() : gWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), "Newton's Cradle") {
    gWindow.setFramerateLimit(60);
    physWorld.setGravity(0, Vector(0, -1));
    physWorld.setLimit(25);
    physWorld.setOrigin(Vector(WINDOW_X / 2, WINDOW_Y / 2));
    physWorld.setContactLimit(25);

    Particle* particle1 = new Particle(false, 10.f, -200, 100, 0.9f, 1.f, 20.f, sf::Color::Blue);
    physWorld.addParticle(particle1);
    particle1->applyForce(Vector(40000, 0));

    Sphere* particle2 = new Sphere(false, 10.f, 200, 100, 0.9f, 1.f, 0.9f, 20.f, sf::Color::White);
    physWorld.addParticle(particle2);
    particle2->applyForce(Vector(-40000, 0));

    Sphere* particle3 = new Sphere(false, 10.f, -200, 0, 0.9f, 1.f, 0.9f, 20.f, sf::Color::White);
    physWorld.addParticle(particle3);
    particle3->applyForce(Vector(40000, 0));

    RectangularPrism* particle4 = new RectangularPrism(false, 10.f, 200, 0, 0.9f, 1.f, 1.f, 40.f, 30.f, sf::Color::Blue);
    physWorld.addParticle(particle4);
    particle4->setRotation(1.0472);
    particle4->applyForce(Vector(-40000, 0));

    RectangularPrism* particle5 = new RectangularPrism(false, 10.f, -200, -100, 0.9f, 1.f, 1.f, 40.f, 30.f, sf::Color::Blue);
    physWorld.addParticle(particle5);
    particle5->setRotation(-0.7854);
    particle5->applyForce(Vector(40000, 0));

    RectangularPrism* particle6 = new RectangularPrism(false, 10.f, 200, -100, 0.9f, 1.f, 0.9f, 40.f, 30.f, sf::Color::White);
    physWorld.addParticle(particle6);
    particle6->setRotation(0.5236);
    particle6->applyForce(Vector(-40000, 0));

    physWorld.setDrawLinks(false);
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