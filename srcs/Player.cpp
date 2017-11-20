/*
 * @Author: Boris
 * @Date: 1017-05-04 19:14:10
 * @Last Modified by: Boris
 * @Last Modified time: 1017-05-04 1:06:01
 */

#include <memory>
#include "Player.hpp"
#include "Game.hpp"
#include "Except.hpp"

extern GamePtrU _game;

/*
** Constructor Player
** graphic : contain device, scene manager
** input : InputComponent to make the player move (keyboard, gamepad, ai...)
*/

Player::Player(Graphic &graphic, PlayerType type, size_t id, const char *path)
: GameObject(graphic.getSceneManager().addAnimatedMeshSceneNode(
                 graphic.getSceneManager().getMesh(path)),
             false)
{
  irr::video::ITexture *texture;
   _id = id;
    _state = ALIVE;
    _type = type;

  //_components.push_back(input);
  _node->setMaterialFlag(video::EMF_LIGHTING, false);

  texture = graphic.getDriver().getTexture("./assets/simpsons/ffaa31e9.png");
  if (!texture)
    throw AssetError("Can't load asset");
  _node->setMaterialTexture(0, texture);
  _node->setScale(core::vector3df(6, 6, 6));
  // _mesh->setMaterialTexture(0, graphic.getDriver().getTexture("assets/bomberman_1.0.9.mtl"));
  _hitbox =  graphic.getSceneManager()
          .addSphereSceneNode(0.5, 255, _node, -1);
  _hitbox->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
  _camFPS = graphic.getSceneManager().addCameraSceneNode(_node, _node->getPosition(),
                                                           core::vector3df(0, 0, 100),
                                                           -1, false);
  if (type == IAPLAYER)
    {
        _ia = IaPlayerPtr(new IaPlayer(this));
        _components.push_back(_ia);
    }
    else
    {
        _event = EventReceiverPlayerPtr(new EventReceiverPlayer(this));
        _components.push_back(_event);
    }
}

Player::~Player() {}
