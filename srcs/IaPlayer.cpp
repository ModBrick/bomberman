//
// ia.cpp for indie in /home/pcapon/project/cpp/cpp_indie_studio/srcs/Inputs/
//
// Made by Pierre Capon
// Login   <capon_p@pierre.capon@epitech.eu>
//
// Started on  Wed Jun 14 10:55:15 2017 Pierre Capon
// Last update Mon Jun 19 15:22:16 2017 Pierre Capon
//

#include <iostream>
#include <math.h>
#include "IaPlayer.hpp"
#include "MovePlayer.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Map.hpp"

extern GamePtrU _game;

IaPlayer::IaPlayer(GameObject* player)
{
  _player = player;
  _first = 0;
  _isEscape = 0;
  _bombPut = -1;
  _isStop = -1;
  _isStuck = 0;
}

void IaPlayer::goUp()
{
  core::vector3df pos = _player->getNode()->getPosition();
  core::vector3df rot = _player->getNode()->getRotation();
  rot.Y = 0;
  _player->getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  _player->setOldPos(core::vector3df(pos));
  _player->setPos(core::vector3df(pos.X, pos.Y, pos.Z + f32(10)));
}

void IaPlayer::goDown()
{
  core::vector3df pos = _player->getNode()->getPosition();
  core::vector3df rot = _player->getNode()->getRotation();
  rot.Y = 180;
  _player->getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  _player->setOldPos(core::vector3df(pos));
  _player->setPos(core::vector3df(pos.X, pos.Y, pos.Z - f32(10)));
}

void IaPlayer::goLeft()
{
  core::vector3df pos = _player->getNode()->getPosition();
  core::vector3df rot = _player->getNode()->getRotation();
  rot.Y = 270;
  _player->getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  _player->setOldPos(core::vector3df(pos));
  _player->setPos(core::vector3df(pos.X - f32(10), pos.Y, pos.Z));
}

void IaPlayer::goRight()
{
  core::vector3df pos = _player->getNode()->getPosition();
  core::vector3df rot = _player->getNode()->getRotation();
  rot.Y = 90;
  _player->getNode()->setRotation(core::vector3df(rot.X, rot.Y, rot.Z));
  _player->setOldPos(core::vector3df(pos));
  _player->setPos(core::vector3df(pos.X + f32(10), pos.Y, pos.Z));
}

void IaPlayer::putBomb()
{
  core::vector3df pos = _player->getNode()->getPosition();
  _game->addBomb(std::make_shared<Bomb>(_game->getGraphic(), pos));
}

int IaPlayer::canSave(int x, int y, std::vector<lineBlock> map)
{
  int mapsizeX = map[0].size();
  int mapsizeY = map.size();
  (void)mapsizeY;
  //CHECK -1 A GAUCHE
  if (map[y][x-1]->getType() == EMPTY_BLOCK)
  {
    if (map[y-1][x-1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y -1;
      return(1);
    }
    if (map[y+1][x - 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y +1;
      return(1);
    }
  }
  //CHECK -2 A GAUCHE
  if (( x-2 >= 0 ) && (map[y][x-1]->getType() == EMPTY_BLOCK) &&
                      (map[y][x-2]->getType() == EMPTY_BLOCK))
  {
    if (map[y-1][x-2]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -2;
      _Escapetarget.Y = y -1;
      return(1);
    }
    if (map[y+1][x - 2]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -2;
      _Escapetarget.Y = y +1;
      return(1);
    }
  }
  //CHECK -3 A GAUCHE
  if (( x-3 >= 0 ) && (map[y][x-1]->getType() == EMPTY_BLOCK) &&
                      (map[y][x-2]->getType() == EMPTY_BLOCK) &&
                      (map[y][x-3]->getType() == EMPTY_BLOCK))
  {
    _Escapetarget.X = x -3;
    _Escapetarget.Y = y;
    return(1);
  }
  //CHECK +1 A DROITE
  if (map[y][x+1]->getType() != SOLID_BLOCK)
  {
    if (map[y-1][x+1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y -1;
      return(1);
    }
    if (map[y+1][x + 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y +1;
      return(1);
    }
  }
  //CHECK +2 A DROITE
  if (( x+2 < mapsizeX ) && (map[y][x+1]->getType() == EMPTY_BLOCK) &&
                            (map[y][x+2]->getType() == EMPTY_BLOCK))
  {
    if (map[y-1][x+2]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +2;
      _Escapetarget.Y = y -1;
      return(1);
    }
    if (map[y+1][x + 2]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +2;
      _Escapetarget.Y = y +1;
      return(1);
    }
  }
  //CHECK +3 A DROITE
  if (( x+3 < mapsizeX ) && (map[y][x+1]->getType() == EMPTY_BLOCK) &&
                            (map[y][x+2]->getType() == EMPTY_BLOCK) &&
                            (map[y][x+3]->getType() == EMPTY_BLOCK))
  {
    _Escapetarget.X = x +3;
    _Escapetarget.Y = y;
    return(1);
  }
  //CHECK +1 EN HAUT
  if (map[y+1][x]->getType() == EMPTY_BLOCK)
  {
    if (map[y+1][x+1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y +1;
      return(1);
    }
    if (map[y+1][x - 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y +1;
      return(1);
    }
  }
  //CHECK +2 EN HAUT
  if (( y+2 < mapsizeY ) && (map[y+1][x]->getType() == EMPTY_BLOCK) &&
                            (map[y+2][x]->getType() == EMPTY_BLOCK))
  {
    if (map[y+2][x+1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y +2;
      return(1);
    }
    if (map[y+2][x - 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y +2;
      return(1);
    }
  }
  //CHECK +3 EN HAUT
  if (( x+3 < mapsizeX ) && (map[y+1][x]->getType() == EMPTY_BLOCK) &&
                            (map[y+2][x]->getType() == EMPTY_BLOCK) &&
                            (map[y][x+3]->getType() == EMPTY_BLOCK))
  {
    _Escapetarget.X = x +3;
    _Escapetarget.Y = y;
    return(1);
  }
  //CHECK -1 EN BAS
  if (map[y-1][x]->getType() == EMPTY_BLOCK)
  {
    if (map[y-1][x+1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y -1;
      return(1);
    }
    if (map[y-1][x - 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y -1;
      return(1);
    }
  }
  //CHECK -2 EN BAS
  if (( y-2 >= 0) && (map[y-1][x]->getType() == EMPTY_BLOCK) &&
                     (map[y-2][x]->getType() == EMPTY_BLOCK))
  {
    if (map[y-2][x+1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x +1;
      _Escapetarget.Y = y -2;
      return(1);
    }
    if (map[y-2][x - 1]->getType() == EMPTY_BLOCK)
    {
      _Escapetarget.X = x -1;
      _Escapetarget.Y = y -2;
      return(1);
    }
  }
  //CHECK -3 EN BAS
  if (( x-3 >= 0 ) && (map[y-1][x]->getType() == EMPTY_BLOCK) &&
                            (map[y-2][x]->getType() == EMPTY_BLOCK) &&
                            (map[y][x-3]->getType() == EMPTY_BLOCK))
  {
    _Escapetarget.X = x -3;
    _Escapetarget.Y = y;
    return(1);
  }
  return (0);
}

void IaPlayer::moveToTarget(int x, int y, std::vector<lineBlock> map)
{
  int goalx = _target.X;
  int goaly = _target.Y;
  if (_isEscape == 1)
  {
    goalx = _Escapetarget.X;
    goaly = _Escapetarget.Y;
  }
  if (_isStuck == 1)
  {
    goalx = _unstuckTarget.X;
    goaly = _unstuckTarget.Y;
  }
  if ((y > goaly) && (((map[y-1][x]->getType() != SOLID_BLOCK) && (_isEscape == 0)) ||
                      ((_isEscape == 1) && map[y-1][x]->getType() == EMPTY_BLOCK)))
  {
      if ((_isEscape != 1) && (_bombPut == -1) && map[y-1][x]->getType() == BOX_BLOCK && (canSave(x, y, map) == 1))
      {
        _bombPut = 1;
      }
    else
    {
      goDown();
      //printf("DOWN\n");
    }
  }
  else if ((y < goaly) && (((map[y+1][x]->getType() != SOLID_BLOCK) && (_isEscape == 0)) ||
                      ((_isEscape == 1) && map[y+1][x]->getType() == EMPTY_BLOCK)))
  {
    if ((_isEscape != 1) && (_bombPut == -1) && map[y+1][x]->getType() == BOX_BLOCK && (canSave(x, y, map) == 1))
      {
        _bombPut = 1;
      }
    else
    {
      goUp();
      //printf("UP\n");
    }
  }
  else if ((x > goalx) && (((map[y][x-1]->getType() != SOLID_BLOCK) && (_isEscape == 0)) ||
                      ((_isEscape == 1) && map[y][x-1]->getType() == EMPTY_BLOCK)))
  {
    if ((_isEscape != 1) && (_bombPut == -1) && map[y][x-1]->getType() == BOX_BLOCK && (canSave(x, y, map) == 1))
      _bombPut = 1;
    else
    {
      goLeft();
      //printf("LEFT\n");
    }
  }
  else if ((x < goalx) && (((map[y][x+1]->getType() != SOLID_BLOCK) && (_isEscape == 0)) ||
                      ((_isEscape == 1) && map[y][x+1]->getType() == EMPTY_BLOCK)))
  {
    if ((_isEscape != 1) && (_bombPut == -1) && map[y][x+1]->getType() == BOX_BLOCK && (canSave(x, y, map) == 1))
      {
        _bombPut = 1;
      }
    else
    {
      goRight();
      //printf("RIGHT\n");
    }
  }
  else
  {
    if ((y == goaly) && (x > goalx))
      {
          _isStuck = 1;
          if (map[y-1][x]->getType() == EMPTY_BLOCK && map[y-1][x-1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x-1;
            _unstuckTarget.Y = y-1;
          }
          else if (map[y+1][x]->getType() == EMPTY_BLOCK && map[y+1][x-1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x-1;
            _unstuckTarget.Y = y+1;
          }
      }
    if ((y == goaly) && (x < goalx))
      {
          _isStuck = 1;
          if (map[y-1][x]->getType() == EMPTY_BLOCK && map[y-1][x+1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x+1;
            _unstuckTarget.Y = y-1;
          }
          else if (map[y+1][x]->getType() == EMPTY_BLOCK && map[y+1][x+1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x+1;
            _unstuckTarget.Y = y+1;
          }
      }
    if ((x == goalx) && (y > goaly))
      {
          _isStuck = 1;
          if (map[y][x+1]->getType() == EMPTY_BLOCK && map[y-1][x+1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x+1;
            _unstuckTarget.Y = y-1;
          }
          else if (map[y-1][x]->getType() == EMPTY_BLOCK && map[y-1][x-1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x-1;
            _unstuckTarget.Y = y-1;
          }
      }
    if ((x == goalx) && (y < goaly))
      {
          _isStuck = 1;
          if (map[y][x+1]->getType() == EMPTY_BLOCK && map[y+1][x+1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x+1;
            _unstuckTarget.Y = y+1;
          }
          else if (map[y-1][x]->getType() == EMPTY_BLOCK && map[y-1][x-1]->getType() == EMPTY_BLOCK)
          {
            _unstuckTarget.X = x-1;
            _unstuckTarget.Y = y+1;
          }
      }
  }
}

void IaPlayer::runIA()
{
  std::vector<lineBlock> map = _game->getMap()->getMap();
  core::vector3df pos = _player->getNode()->getPosition();
  size_t mapsizeX = map[0].size();
  size_t mapsizeY = map.size();
  int y = (int)(pos.Z / SIZE_BLOCK) + (mapsizeY / 2);
  int x = (((int)pos.X)/ SIZE_BLOCK) + (mapsizeX / 2);

  if (_first == 0)
  {
    targetPlayer(x, y, map);
    _first = 1;
  }
  if (_bombPut == 0)
  {
    putBomb();
    _isEscape = 1;
    _bombPut = -1;
    _time = std::time(0);
  }
  else if (_bombPut > 0)
  {
    _bombPut--;
  }
  if (_isStuck == 1)
  {
    if (x == _unstuckTarget.X && y == _unstuckTarget.Y)
      _isStuck = 0;
    moveToTarget(x, y, map);
    return;
  }
  if ((_isEscape == 1) && (std::time(0) - _time <= 3))
  {
    moveToTarget(x, y, map);
  }
  else
  {
    if (_isEscape == 1)
    {
      if ((x !=_Escapetarget.X) || (y != _Escapetarget.Y))
      {
        moveToTarget(x, y, map);
      }
      else
      {
        _isEscape = 0;
      }
    }
    else
    {
      if ((x == _target.X) && (y == _target.Y))
      {
        canSave(x, y, map);
        putBomb();
        _isEscape = 1;
        _bombPut = -1;
        _time = std::time(0);
      }
      else
      {
        targetPlayer(x, y, map);
        moveToTarget(x, y, map);
        //printf("target.X : %i target.Y : %i\n", _target.X, _target.Y);
      }
    }
  }
}

void IaPlayer::targetPlayer(int x, int y, std::vector<lineBlock> map)
{
  int playerposx;
  int playerposy;
  std::vector<PlayerPtr> players = _game->getPlayers();
  core::vector3df pos;
  size_t mapsizeX = map[0].size();
  size_t mapsizeY = map.size();
  _target.Y = 200;//(int)(pos.Z / SIZE_BLOCK) + (mapsizeY / 2);
  _target.X = 200;//(((int)pos.X)/ SIZE_BLOCK) + (mapsizeX / 2);

  for(auto p = players.begin(); p!=players.end(); p++)
  {
    if ((*p)->getDead() == ALIVE)
    {
      pos = (*p)->getNode()->getPosition();
      playerposx = (((int)pos.X)/ SIZE_BLOCK) + (mapsizeX / 2);
      playerposy = (int)(pos.Z / SIZE_BLOCK) + (mapsizeY / 2);
      if ((fabs(_target.X - x) + fabs(_target.Y - y)) >
          (fabs(playerposx - x) + fabs(playerposy - y)) &&
          ((playerposx != x) || (playerposy != y)))
        {
          _target.X = playerposx;
          _target.Y = playerposy;
        }
    }
  }
  if (_target.Y == 200 && _target.X == 200)
  {
    _target.X = rand()%((mapsizeX-1)-1 + 1) + 1;
    _target.Y = rand()%((mapsizeY-1)-1 + 1) + 1;
  }
}

void IaPlayer::update(GameObject &_objet)
{
  (void)_objet;
  runIA();
}
