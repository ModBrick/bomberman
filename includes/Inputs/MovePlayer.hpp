/*
** MovePlayer.hpp for move in /home/josselin/rendu/cpp_indie_studio/includes/Inputs
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Wed Jun 07 13:21:20 2017 josselin
** Last update Feb Jun 12 16:25:52 2017
*/

#pragma once

#include "GameObject.hpp"

class IMovePlayer
{
public:
  IMovePlayer(){};
  virtual void doAction(GameObject &) = 0;
  virtual ~IMovePlayer(){};
  virtual bool getIsMoving() = 0;
  virtual void setIsMoving(bool state) = 0;
};

class MovePlayerForward: public IMovePlayer
{
public:
  MovePlayerForward(){ _isMoving = 0;};
  virtual void doAction(GameObject &player);
  virtual void setIsMoving(bool state){
    _isMoving = state;
  }
  virtual bool getIsMoving(){
    return (_isMoving);
  };
private:
  bool _isMoving;
};

class MovePlayerBack: public IMovePlayer
{
public:
  MovePlayerBack(){ _isMoving = 0;};
  virtual void doAction(GameObject &player);
  virtual void setIsMoving(bool state){
    _isMoving = state;
  }
  virtual bool getIsMoving(){
    return (_isMoving);
  };
private:
  bool _isMoving;
};

class MovePlayerLeft: public IMovePlayer
{
public:
  MovePlayerLeft(){ _isMoving = 0;};
  virtual void doAction(GameObject &player);
  virtual void setIsMoving(bool state){
    _isMoving = state;
  }
  virtual bool getIsMoving(){
    return (_isMoving);
  };
private:
  bool _isMoving;
};

class MovePlayerRight: public IMovePlayer
{
public:
  MovePlayerRight(){ _isMoving = 0;};
  virtual void doAction(GameObject &player);
  virtual void setIsMoving(bool state){
    _isMoving = state;
  }
  virtual bool getIsMoving(){
    return (_isMoving);
  };
private:
  bool _isMoving;
};

class MovePlayerBomb: public IMovePlayer
{
public:
  MovePlayerBomb(){ _isMoving = 0;};
  virtual void doAction(GameObject &player);
  virtual void setIsMoving(bool state){
    _isMoving = state;
  }
  virtual bool getIsMoving(){
    return (_isMoving);
  };
private:
  bool _isMoving;
};

typedef std::shared_ptr<IMovePlayer> IMovePlayerPtr;
typedef std::shared_ptr<MovePlayerForward> MovePlayerForwardPtr;
typedef std::shared_ptr<MovePlayerBack> MovePlayerBackPtr;
typedef std::shared_ptr<MovePlayerLeft> MovePlayerLeftPtr;
typedef std::shared_ptr<MovePlayerRight> MovePlayerRightPtr;
typedef std::shared_ptr<MovePlayerBomb> MovePlayerBombPtr;
