/*
 * @Author: Boris
 * @Date: 2017-05-04 18:58:35
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 21:26:41
 */

#pragma once

#include <memory>
#include "EventReceiver.hpp"
#include "irr/irrlicht.h"
#include "Graphic.hpp"
#include "GameObject.hpp"
#include "KeyboardInputComponent.hpp"
#include "Bomb.hpp"
#include "IaPlayer.hpp"

#define MARGE "assets/simpsons/marge.obj"
#define HOMER "assets/simpsons/homer.obj"
#define BART "assets/simpsons/bart.obj"
#define LISA "assets/simpsons/lisa.obj"

using namespace irr;

enum State
{
  ALIVE,
  DYING,
  DIE
};
enum PlayerType
{
  IAPLAYER,
  USERPLAYER
};

class Player : public GameObject
{
public:
  Player(Graphic &, PlayerType type, size_t, const char *);
  ~Player();
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;

private:
  size_t _id;
  PlayerType _type;
  scene::ICameraSceneNode *_camFPS;
  scene::ICameraSceneNode *_cam3rdPerson;
  std::vector<BombPtr> _Bomb;
  IaPlayerPtr _ia;
  EventReceiverPlayerPtr _event;
  State _state;
  size_t _maxBomb;
  time_t _lastBombTime;

public:
  EventReceiverPlayer &getEvent() const { return *_event; };
  void setDead(State state) { _state = state; };
  State getDead() const { return _state; };
  PlayerType getType() const { return _type; };
  size_t getMaxBomb() const { return _maxBomb; }
  time_t getLastBombTime() const { return _lastBombTime; }
  void setLastBombTime(time_t time) { _lastBombTime = time; }
};

typedef std::shared_ptr<Player> PlayerPtr;
typedef std::unique_ptr<Player> PlayerPtrU;
