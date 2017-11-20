/*
 * @Author: Boris
 * @Date: 2017-05-04 16:35:21
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 22:15:10
 */

#pragma once

#include <memory>
#include <vector>
#include "irr/irrlicht.h"
#include "Graphic.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "effect.hpp"

using namespace irr;

class Game
{
public:
  Game(Graphic &);
  ~Game();
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

private:
  Graphic &_graphic;
  scene::ICameraSceneNode *_mainCam;
  video::SColor _bckgdColor;
  core::array<SJoystickInfo> joystickInfo;

private:
  std::vector<PlayerPtr> _players;
  std::vector<BombPtr> _bomb;
  std::vector<ExplosionPtr> _explosion;
  MapPtr _map;

    irr::video::ITexture *_background;


public:
  void run();
  void addPlayer(PlayerType type, size_t);
  void addBomb(BombPtr bomb){_bomb.push_back(bomb);};
  void addExplosion(ExplosionPtr explosion){_explosion.push_back(explosion);};
  void loadMap();
  irr::video::ITexture *getBackground(void) const { return _background; };

public:
  scene::ICameraSceneNode *getMainCam() const { return _mainCam; }
  Graphic &getGraphic() const { return _graphic; }
  std::vector<PlayerPtr> getPlayers() const { return _players; }
  MapPtr getMap() const { return _map; }
};

typedef std::shared_ptr<Game> GamePtr;
typedef std::unique_ptr<Game> GamePtrU;
