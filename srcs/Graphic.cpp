/*
 * @Author: Boris
 * @Date: 2017-05-04 15:54:31
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 16:39:07
 */

#include "Except.hpp"
#include "Graphic.hpp"

Graphic::Graphic(irr::IrrlichtDevice *device)
{
    _device = device;
    if (!device)
        throw DeviceError("Can't find video device");
    _driver = _device->getVideoDriver();
    _sceneManager = _device->getSceneManager();
    if (!_driver || !_sceneManager)
        throw DeviceError("Can't load driver");
    _geometryCreator = _sceneManager->getGeometryCreator();
    if (!_geometryCreator)
        throw DeviceError("Can't create scene");
}

Graphic::~Graphic() {}
