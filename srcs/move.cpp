/*
** move.cpp for move in /home/josselin/rendu/cpp_indie_studio/srcs
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Wed Jun 07 14:20:08 2017 josselin
** Last update May Jun 15 15:21:29 2017
*/

#include "MovePlayer.hpp"
#include "Player.hpp"
#include "GameObject.hpp"
#include "Bomb.hpp"
#include "Game.hpp"

extern GamePtrU _game;

void MovePlayerForward::doAction(GameObject &player) {
  core::vector3df pos = player.getNode()->getPosition();
  core::vector3df rot = player.getNode()->getRotation();
  rot.Y = 0;
  player.getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  player.setOldPos(core::vector3df(pos));
  player.setPos(core::vector3df(pos.X, pos.Y, pos.Z + f32(0.7)));
}

void MovePlayerBack::doAction(GameObject &player) {
  core::vector3df pos = player.getNode()->getPosition();
  core::vector3df rot = player.getNode()->getRotation();
  rot.Y = 180;
  player.getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  player.setOldPos(core::vector3df(pos));
  player.setPos(core::vector3df(pos.X, pos.Y, pos.Z - f32(0.7)));
}

void MovePlayerLeft::doAction(GameObject &player) {
  core::vector3df pos = player.getNode()->getPosition();
  core::vector3df rot = player.getNode()->getRotation();
  rot.Y = 270;
  player.getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  player.setOldPos(core::vector3df(pos));
  player.setPos(core::vector3df(pos.X - f32(0.7), pos.Y, pos.Z));
}

void MovePlayerRight::doAction(GameObject &player) {
  core::vector3df pos = player.getNode()->getPosition();
  core::vector3df rot = player.getNode()->getRotation();
  rot.Y = 90;
  player.getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  player.setOldPos(core::vector3df(pos));
  player.setPos(core::vector3df(pos.X + f32(0.7), pos.Y, pos.Z));
}

void MovePlayerBomb::doAction(GameObject &player) {
  this->_isMoving = false;
  core::vector3df pos = player.getNode()->getPosition();
  // Player *p = dynamic_cast<Player>(player);
  // if (time(NULL) - p->getLastBombTime < 3)
  //   return;
  _game->addBomb(std::make_shared<Bomb>(_game->getGraphic(), pos));
}
