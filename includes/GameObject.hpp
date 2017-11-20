#pragma once

#include <string>
#include <vector>
#include "irr/irrlicht.h"
#include "Graphic.hpp"
#include "IComponent.hpp"

using namespace irr;

class IInputComponent;
typedef std::shared_ptr<IInputComponent> IInputComponentPtr;

/*
** Every Object in game will be a Game Object
**
*/
class GameObject
{
/*
** Constructors / Destructors
*/
public:
	GameObject(scene::ISceneNode *, bool);
	~GameObject() {};

/*
** Runtime functions
*/
public:
	void update();

/*
** Getters / Setters
*/
public:
	// Velocity
	f32 getVelocity() const { return _velocity; };
	void setVelocity(f32 v) { _velocity = v; };

	// Mesh
	void setNode(scene::ISceneNode *node) { _node = node; };
	scene::ISceneNode *getNode() { return _node; };

	std::vector<IComponentPtr> & getComponents() { return _components; };

    scene::ISceneNode *getHitbox() { return _hitbox; };

    core::vector3df getOldPos() const { return _oldPos; };
    void setOldPos(const core::vector3df& pos) { _oldPos = pos; };
    void setPos(const core::vector3df& pos) { _node->setPosition(pos); }
/*
** Attributes
*/
protected:
	bool _collidable;
	std::vector<IComponentPtr> _components;
	f32 _velocity;
    core::vector3df _oldPos;
    scene::ISceneNode *_node;
    scene::ISceneNode *_hitbox;
};
