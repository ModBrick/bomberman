#include "GameObject.hpp"
#include "Except.hpp"

/*
** GameObject constructor without texture
** graphic : contain device, scene manager
** inputC : InputComponent to make the object move (can be null)
** path : path of the mesh to load
**
** Throw exception if mesh can't be load
*/

GameObject::GameObject(scene::ISceneNode *node, bool collidable) : _collidable(collidable), _node(node)
{
	if (!_node)
		throw AssetError("Can't load asset");
}

void GameObject::update()
{
	for (auto a = _components.begin(); a != _components.end(); a++)
		(*a)->update(*this);
}