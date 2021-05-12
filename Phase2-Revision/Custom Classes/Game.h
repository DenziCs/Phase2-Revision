#include"Particle.h"
#include"PhysicsManager.h"
#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<list>
#pragma once
using namespace std;

class Game {
public:
    Game();
    void run();

    static const int WINDOW_X = 800;
    static const int WINDOW_Y = 400;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    PhysicsManager physWorld;
private:
    void processEvents();
    void update(sf::Time);
    void render();

    sf::RenderWindow gWindow;
    bool push = false;
};