#pragma once

#include <memory>
#include "irr/irrlicht.h"
#include "IComponent.hpp"
#include "GameObject.hpp"

using namespace irr;

class KeyBoardInputComponent : public IComponent
{
public:
	KeyBoardInputComponent() {};
	~KeyBoardInputComponent() {};

public:
	virtual void update(GameObject &player);
};

typedef std::shared_ptr<KeyBoardInputComponent> KeyBoardInputComponentPtr;
