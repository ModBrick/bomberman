/*
 * @Author: Boris
 * @Date: 2017-05-04 15:47:31
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 16:13:24
 */

#pragma once

#include <memory>
#include "irr/irrlicht.h"

#define HEIGHT_WINDOW 720
#define WIDTH_WINDOW 1080

using namespace irr;

struct SAppContext
{
  irr::IrrlichtDevice           *device;
  irr::s32                      counter;
  irr::gui::IGUIListBox         *listbox;
};

class Graphic
{
public:
  Graphic(irr::IrrlichtDevice *device);
  ~Graphic();
  Graphic(const Graphic &) = delete;
  Graphic &operator=(const Graphic &) = delete;

private:
  IrrlichtDevice *_device;
  video::IVideoDriver *_driver;
  scene::ISceneManager *_sceneManager;
  const scene::IGeometryCreator *_geometryCreator;

public:
  IrrlichtDevice &getDevice() const { return *_device; };
  video::IVideoDriver &getDriver() const { return *_driver; };
  scene::ISceneManager &getSceneManager() const { return *_sceneManager; };
  const scene::IGeometryCreator &getGeometryCreator() const { return *_geometryCreator; };
};

typedef std::shared_ptr<Graphic> GraphicPtr;
typedef std::unique_ptr<Graphic> GraphicPtrU;
