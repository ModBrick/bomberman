#include "KeyboardInputComponent.hpp"

/*
** KeyBoard update of object
** object : object to move
*/
void KeyBoardInputComponent::update(GameObject &object){
	if (!object.getNode())
		return ;
	core::vector3df rot = object.getNode()->getRotation();
    object.getNode()->setRotation(core::vector3df(rot.X, rot.Y + 1, rot.Z));
}
