#include "Engine.hpp"

// engine constructor
Engine::Engine() {
  TCODConsole::initRoot(100, 50, "Darkwind: The Coliseum", false, TCOD_RENDERER_SDL2);
  player = new Actor(40, 25, '@', TCODColor::white);
  actors.push(player);
  actors.push(new Actor(60, 13, '@', TCODColor::yellow));
  map = new Map(95, 45);
  console = tcod::Console{std::move(tcod::load_xp("Maps/thearena.xp").at(0))};
  for (auto& tile : console) {
    tile.ch = tcod::CHARMAP_CP437.at(tile.ch);
    if (tile.bg == tcod::ColorRGBA{255, 0, 255, 255}) {
      tile.bg = {0, 0, 0, 255};
      tile.fg = {0, 0, 0, 255};
    }
  };
  for (int y=0; y<console.get_height(); y++) {
    for (int x=0; x<console.get_width(); x++) {
      if ( console.at({x,y}).ch != 0x2593 ) {map->setWall (x,y);}
    }
  }
}

// engine deconstructor
Engine::~Engine() {
  actors.clearAndDelete();
  delete map;
}

// player input update
void Engine::update() {
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch (key.vk) {
    case TCODK_KP8:
      if (!map->isWall(player->x, player->y - 1)) {
        player->y--;
      }
      break;
    case TCODK_KP2:
      if (!map->isWall(player->x, player->y + 1)) {
        player->y++;
      }
      break;
    case TCODK_KP4:
      if (!map->isWall(player->x - 1, player->y)) {
        player->x--;
      }
      break;
    case TCODK_KP6:
      if (!map->isWall(player->x + 1, player->y)) {
        player->x++;
      }
      break;
    case TCODK_KP1:
      if (!map->isWall(player->x - 1, player->y + 1)) {
        player->x--;
        player->y++;
      }
      break;
    case TCODK_KP7:
      if (!map->isWall(player->x - 1, player->y - 1)) {
        player->x--;
        player->y--;
      }
      break;
    case TCODK_KP9:
      if (!map->isWall(player->x + 1, player->y - 1)) {
        player->x++;
        player->y--;
      }
      break;
    case TCODK_KP3:
      if (!map->isWall(player->x + 1, player->y + 1)) {
        player->x++;
        player->y++;
      }
      break;
    case TCODK_KP5:
      if (!map->isWall(player->x, player->y)) {
        player->x;
        player->y;
      }
      break;
    default:
      break;
  }
}

// rendering the map
void Engine::render() {
  TCODConsole::root->clear();
  // draw the map
  tcod::blit(*TCODConsole::root, console);
  // draw the actors
  for (Actor** iterator = actors.begin(); iterator != actors.end(); iterator++) {
    (*iterator)->render();
  }
}
