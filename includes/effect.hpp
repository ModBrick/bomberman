/*
** effect.hpp for effect in /home/josselin/rendu/cpp_indie_studio/includes
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Tue Jun 13 17:17:30 2017 josselin
** Last update Mar Jun 13 18:06:10 2017
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

class IEffect
{
  public:
    IEffect(){};
    ~IEffect(){};
    virtual bool update() = 0;
};

class Explosion: public IEffect
{
  public:
    Explosion(irr::core::vector3df pos);
    ~Explosion();
    bool update();

  private:
    irr::scene::IParticleSphereEmitter* _emitter;
    irr::scene::IParticleSystemSceneNode* _particleSystem;
    irr::scene::IParticleAffector* _affector;
    std::time_t _time;
};

typedef std::shared_ptr<Explosion> ExplosionPtr;
typedef std::unique_ptr<Explosion> ExplosionPtrU;
