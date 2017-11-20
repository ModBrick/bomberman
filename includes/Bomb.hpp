/*
** Bomb.hpp for bomb in /home/josselin/rendu/cpp_indie_studio/includes
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Mon Jun 12 15:24:02 2017 josselin
** Last update Mar Jun 13 21:52:14 2017
*/

#pragma once

#include <memory>
#include <chrono>
#include <iostream>
#include "EventReceiver.hpp"
#include "irr/irrlicht.h"
#include "Graphic.hpp"
#include "GameObject.hpp"
#include "KeyboardInputComponent.hpp"

using namespace irr;

class Bomb : public GameObject
{
  public:
    Bomb(Graphic &, core::vector3df pos);
    ~Bomb();
    Bomb(const Bomb &) = delete;
    Bomb &operator=(const Bomb &) = delete;
    bool update();
    void Player_col(core::vector3df pos);

  private:
    scene::ICameraSceneNode *_camFPS;
    scene::ICameraSceneNode *_cam3rdPerson;
    std::time_t _time;
    float _range;
};

typedef std::shared_ptr<Bomb> BombPtr;
typedef std::unique_ptr<Bomb> BombPtrU;
