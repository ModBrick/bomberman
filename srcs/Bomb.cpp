/*
** Bomb.cpp for bombe in /home/josselin/rendu/cpp_indie_studio/srcs
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Mon Jun 12 15:22:10 2017 josselin
** Last update Sat Jun 17 17:07:35 2017 Pierre Capon
*/

#include <memory>
#include "Bomb.hpp"
#include "Game.hpp"
#include <chrono>
#include <iostream>
#include "effect.hpp"
#include "Map.hpp"

extern GamePtrU _game;

/*
** Constructor Player
** graphic : contain device, scene manager
** input : InputComponent to make the player move (keyboard, gamepad, ai...)
*/

Bomb::Bomb(Graphic &graphic, core::vector3df pos)
        : GameObject(graphic.getSceneManager().addAnimatedMeshSceneNode(
        graphic.getSceneManager().getMesh("assets/bomb.obj")),
                     true) {
  core::vector3df posAbsolute;

  if (pos.X >= 0 && int(pos.X) % 10 > 5)
    pos.X += 10;
  else if (pos.X < 0 && int(pos.X) % 10 < -5)
    pos.X -= 10;
  if (pos.Z >= 0 && int(pos.Z) % 10 > 5)
    pos.Z += 10;
  else if (pos.Z < 0 && int(pos.Z) % 10 < -5)
    pos.Z -= 10;
  posAbsolute.X = (pos.X - ((int) pos.X % SIZE_BLOCK));
  posAbsolute.Z = (pos.Z - ((int) pos.Z % SIZE_BLOCK));
  printf("%d, %d\n", (int) posAbsolute.X, (int) posAbsolute.Z);
  posAbsolute.Y = pos.Y;
  _time = std::time(0);
  _node->setParent(_game->getMap()->getGround().getNode());

  _node->setScale(core::vector3df(4, 4, 4));
  //_components.push_back(input);
  _node->setMaterialFlag(video::EMF_LIGHTING, true);
  // _mesh->setMaterialTexture(0, graphic.getDriver().getTexture("assets/bear.tga"));
  _node->setPosition(posAbsolute);
  _camFPS = graphic.getSceneManager().addCameraSceneNode(_node, _node->getPosition(),
                                                         core::vector3df(0, 0, 100),
                                                         -1, false);
  _range = 2;
}

bool Bomb::update() {
  if (std::time(0) - _time >= 3) {
    core::vector3df pos = _node->getPosition();
    pos.X = int(pos.X);
    pos.Z = int(pos.Z);
    this->Player_col(pos);
    s32 x;
    s32 y;
    size_t MAP_SIZE_X = _game->getMap()->getMap().size();
    size_t MAP_SIZE_Y = _game->getMap()->getMap().at(0).size();
    _game->addExplosion(std::make_shared<Explosion>(pos));

    //RIGHT
    x = (int)((((int)pos.Z)/ SIZE_BLOCK) + (MAP_SIZE_X / 2));
    for (int i = 1; i != _range + 1; i++) {
      y = (int)(((int)(pos.X / SIZE_BLOCK) + (MAP_SIZE_Y / 2)) + i);
      if (x >= (int)MAP_SIZE_X || x < 0
          || y >= (int)MAP_SIZE_Y || y < 0)
        break;
      if (_game->getMap()->getMap()[x][y]->getType() == SOLID_BLOCK)
        break;
      else if (_game->getMap()->getMap()[x][y]->getType() == BOX_BLOCK) {
        _game->getMap()->getMap()[x][y]->setType(EMPTY_BLOCK);
        _game->getMap()->getMap()[x][y]->getNode()->remove();
        break ;
      }
      Player_col(core::vector3df(pos.X + (i * SIZE_BLOCK), pos.Y, pos.Z));
      _game->addExplosion(std::make_shared<Explosion>(core::vector3df((pos.X + (i * SIZE_BLOCK)), pos.Y, pos.Z)));
    }
    // LEFT
    for (int i = 1; i != _range + 1; i++) {
      y = (int)(((int)(pos.X / SIZE_BLOCK) + (MAP_SIZE_Y / 2)) - i);
      if (x >= (int)MAP_SIZE_X || x < 0
          || y >= (int)MAP_SIZE_Y || y < 0)
        break;
      if (_game->getMap()->getMap()[x][y]->getType() == SOLID_BLOCK)
        break;
      else if (_game->getMap()->getMap()[x][y]->getType() == BOX_BLOCK) {
        _game->getMap()->getMap()[x][y]->setType(EMPTY_BLOCK);
        _game->getMap()->getMap()[x][y]->getNode()->remove();
        break ;
      }
      Player_col(core::vector3df(pos.X - (i * SIZE_BLOCK), pos.Y, pos.Z));
      _game->addExplosion(std::make_shared<Explosion>(core::vector3df(pos.X - (i * SIZE_BLOCK), pos.Y, pos.Z)));
    }

    // UP
    y = (int)(((int)(pos.X / SIZE_BLOCK) + (MAP_SIZE_Y / 2)));
    for (int i = 1; i != _range + 1; i++) {
      x = (int)((((int)pos.Z)/ SIZE_BLOCK) + (MAP_SIZE_X / 2) + i);
      if (x >= (int)MAP_SIZE_X || x < 0
          || y >= (int)MAP_SIZE_Y || y < 0)
        break;
      if (_game->getMap()->getMap()[x][y]->getType() == SOLID_BLOCK)
        break;
      else if (_game->getMap()->getMap()[x][y]->getType() == BOX_BLOCK) {
        _game->getMap()->getMap()[x][y]->setType(EMPTY_BLOCK);
        _game->getMap()->getMap()[x][y]->getNode()->remove();
        break ;
      }
      Player_col(core::vector3df(pos.X, pos.Y, pos.Z + (i * SIZE_BLOCK)));
      _game->addExplosion(std::make_shared<Explosion>(core::vector3df(pos.X, pos.Y, pos.Z + (i * SIZE_BLOCK))));
    }

    // DOWN
    for (int i = 1; i != _range + 1; i++) {
      x = (int)((((int)pos.Z)/ SIZE_BLOCK) + (MAP_SIZE_X / 2) - i);
      if (x >= (int)MAP_SIZE_X || x < 0
          || y >= (int)MAP_SIZE_Y || y < 0)
        break;
      if (_game->getMap()->getMap()[x][y]->getType() == SOLID_BLOCK)
        break;
      else if (_game->getMap()->getMap()[x][y]->getType() == BOX_BLOCK) {
        _game->getMap()->getMap()[x][y]->setType(EMPTY_BLOCK);
        _game->getMap()->getMap()[x][y]->getNode()->remove();
        break ;
      }
      Player_col(core::vector3df(pos.X, pos.Y, pos.Z - (i * SIZE_BLOCK)));
      _game->addExplosion(std::make_shared<Explosion>(core::vector3df(pos.X, pos.Y, pos.Z - (i * SIZE_BLOCK))));
    }
    _node->getParent()->removeChild(_node);
    return (1);
  }
  return (0);
}

void Bomb::Player_col(core::vector3df pos) {
  std::vector<PlayerPtr> players = _game->getPlayers();
  core::vector3df posP;
  size_t MAP_SIZE_X = _game->getMap()->getMap().size();
  size_t MAP_SIZE_Y = _game->getMap()->getMap().at(0).size();
  core::vector2d<int> player;
  core::vector2d<int> bomb;
  bomb.X = (int)((((int)pos.Z)/ SIZE_BLOCK) + (MAP_SIZE_X / 2));
  bomb.Y = (int)((((int)pos.X )/ SIZE_BLOCK) + (MAP_SIZE_Y / 2));
  for (int i = 0; (size_t) i != players.size(); i++) {
    if (players[i]->getDead() == ALIVE) {
      posP = players[i]->getNode()->getPosition();
      if (posP.X >= 0 && int(posP.X) % 10 > 5)
        posP.X += 10;
      else if (posP.X < 0 && int(posP.X) % 10 < -5)
        posP.X -= 10;
      if (posP.Z >= 0 && int(posP.Z) % 10 > 5)
        posP.Z += 10;
      else if (posP.Z < 0 && int(posP.Z) % 10 < -5)
        posP.Z -= 10;
      player.X = (int)((((int)posP.Z)/ SIZE_BLOCK) + (MAP_SIZE_X / 2));
      player.Y = (int)((((int)posP.X)/ SIZE_BLOCK) + (MAP_SIZE_Y / 2));
      if (player.X == bomb.X &&
          player.Y == bomb.Y)
        players[i]->setDead(DYING);
    }
  }
}

Bomb::~Bomb() {}
