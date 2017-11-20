#include <memory>
#include "Bomb.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include <chrono>
#include <iostream>
#include "effect.hpp"
#include "Except.hpp"

extern GamePtrU _game;
/*
** Constructor Player
** graphic : contain device, scene manager
** input : InputComponent to make the player move (keyboard, gamepad, ai...)
*/

Explosion::Explosion(irr::core::vector3df pos)
{
  //pos.X -=  10;
  _time = std::time(0);
  _particleSystem =
  _game->getGraphic().getSceneManager().addParticleSystemSceneNode(true);
  _emitter = _particleSystem->createSphereEmitter(
  irr::core::vector3df(0,0,0),
  1 * (SIZE_BLOCK / 2), // coordonnees de la boite
  irr::core::vector3df(0,0,0),        // direction de diffusion
  80,100,                                       // nb particules emises a la sec min / max
  irr::video::SColor(255,255,255,255),                  // couleur la plus sombre
  irr::video::SColor(0,255,255,255),            // couleur la plus claire
  0, 2000,                                    // duree de vie min / max
  0,                                            // angle max d'ecart / direction prevue
  irr::core::dimension2df(2,2),           // taille minimum
  irr::core::dimension2df(3,3));          // taille maximum
      // taille maximum

  _particleSystem->setEmitter(_emitter);              // on attache l'emetteur
  _emitter->drop();                                  // plus besoin de ca

  _particleSystem->setParent(_game->getMap()->getGround().getNode());
  _particleSystem->setPosition(pos);
  _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);          // insensible a la lumiere
  _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);     // desactive zbuffer pour surfaces derriere
  irr::video::ITexture *texture;
  texture = _game->getGraphic().getDriver().getTexture("assets/fire.jpg");
  if (!texture)
            throw AssetError("Can't load asset");
  _particleSystem->setMaterialTexture(0, texture);     // on colle une texture
  _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA); // application transparence

  _affector =    // creation du modificateur
  _particleSystem->createFadeOutParticleAffector(
  irr::video::SColor(10,10,10,10),             // la couleur finale
  1000);                                   // temps necessaire a la modification
  _particleSystem->addAffector(_affector);       // ajout du modificateur au particle system
  _affector->drop();                            // plus besoin de ca
}

bool Explosion::update()
{
  if (std::time(0) - _time >= 2)
  {
    _particleSystem->setEmitter(0);
    return (1);
  }
  return(0);
}

Explosion::~Explosion() {}
