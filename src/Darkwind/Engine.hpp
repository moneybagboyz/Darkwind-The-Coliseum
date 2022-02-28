#pragma once
#include "Actor.hpp"
#include "Map.hpp"
#include "libtcod.hpp"

class Engine {
public :
    TCODList<Actor *> actors;
    Actor *player;
    Map *map;
    tcod::Console console;

    Engine();
    ~Engine();
    void update();
    void render();
};



extern Engine engine;
