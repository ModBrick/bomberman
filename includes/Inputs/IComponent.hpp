#pragma once

#include <memory>
#include "irr/irrlicht.h"

class GameObject;

class IComponent {
public:
  virtual ~IComponent() {}
  virtual void update(GameObject &) = 0;
};

typedef std::shared_ptr<IComponent> IComponentPtr;
