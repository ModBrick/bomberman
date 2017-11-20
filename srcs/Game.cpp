/*
 * @Author: Boris
 * @Date: 2017-05-04 16:43:15
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 22:16:00
 */

#include <iostream>
#include "Game.hpp"
#include "Player.hpp"
#include "Colors.h"
#include "Except.hpp"

extern GamePtrU _game;

static bool doPlayerCollideMap(GameObject &player, MapPtr map)
{
    _game->getGraphic().getSceneManager().drawAll();
    for (size_t i = 0; i < map->getMap().size(); ++i)
    {
        for (size_t j = 0; j < map->getMap().at(i).size(); ++j)
        {
            if (map->getMap().at(i).at(j)->getType() != EMPTY_BLOCK && player.getHitbox()->getTransformedBoundingBox().intersectsWithBox(map->getMap().at(i).at(j)->getNode()->getTransformedBoundingBox()))
            {
                return true;
            }
        }
    }
    return false;
}

Game::Game(Graphic &g) : _graphic(g)
{
    loadMap();
    for (size_t i = 0; i < _map->getMap().size(); ++i)
    {
        for (size_t j = 0; j < _map->getMap().at(i).size(); ++j)
            std::cout << _map->getMap().at(i).at(j)->getType() << " ";
        std::cout << std::endl;
    }
    _bckgdColor = video::SColor(0, 0, 0, 0);
    _mainCam = _graphic.getSceneManager().addCameraSceneNode(0,
                                                             core::vector3df(50, _map->getSize().Y * 8, _map->getSize().Y * -1),
                                                             core::vector3df(core::vector3df(0)));
    _mainCam->setTarget(core::vector3df(50, 0, 50));
    _graphic.getSceneManager().setAmbientLight(video::SColorf(0.1f, 0.1f, 0.1f, 0.0));
    _graphic.getSceneManager().addLightSceneNode(0, core::vector3df(50, 100, 50),
                                                 video::SColorf(1.0f, 1.0f, 1.0f, 0.0f),
                                                 60.5f);
    _background = _graphic.getDriver().getTexture("./assets/background.png");
  if (!_background)
    throw AssetError("Can't find image");
}

void Game::addPlayer(PlayerType type, size_t id)
{
    size_t sX = _map->getMap().at(0).size();
    size_t sY = _map->getMap().size();
    switch (id)
    {
    case 0:
        _players.push_back(std::make_shared<Player>(_graphic, type, id, MARGE));
        if (!_players.back()->getNode())
          throw AssetError("Can't load asset");
        _players.back()->getNode()->setParent(_map->getGround().getNode());
        _players.back()->getNode()->setPosition(core::vector3df((int)(POS(1, sX)), 0, (int)(POS(1, sY))));
        break;
    case 1:
        _players.push_back(std::make_shared<Player>(_graphic, type, id, HOMER));
        if (!_players.back()->getNode())
          throw AssetError("Can't load asset");
        _players.back()->getNode()->setParent(_map->getGround().getNode());
        _players.back()->getNode()->setPosition(core::vector3df((int)(POS(1, sX)), 0, (int)(POS((sY - 2), sY))));
        break;
    case 2:
        _players.push_back(std::make_shared<Player>(_graphic, type, id, LISA));
        if (!_players.back()->getNode())
          throw AssetError("Can't load asset");
        _players.back()->getNode()->setParent(_map->getGround().getNode());
        _players.back()->getNode()->setPosition(core::vector3df((int)(POS((sX - 2), sX)), 0, (int)(POS(1, sY))));
        break;
    case 3:
        _players.push_back(std::make_shared<Player>(_graphic, type, id, BART));
        if (!_players.back()->getNode())
          throw AssetError("Can't load asset");
        _players.back()->getNode()->setParent(_map->getGround().getNode());
        _players.back()->getNode()->setPosition(core::vector3df((int)(POS((sX - 2), sX)), 0, (int)(POS((sY - 2), sY))));
        break;
        // _players.back()->getNode()->setPosition(core::vector3df(POS(1.5, _map->getMap().size()), 0, POS(_map->getMap().at(0).size() - 1.5, _map->getMap().at(0).size())));
    }
    _graphic.getDevice().setEventReceiver(&_players.back()->getEvent());
}

void Game::loadMap()
{
    _map = MapPtr(new Map(_graphic));
}

void Game::run()
{
    while (_graphic.getDevice().run())
    {
      _graphic.getDriver().beginScene(true, true, _bckgdColor);
      _graphic.getDriver().draw2DImage(_game->getBackground(), irr::core::position2d<irr::s32>(0, 0), irr::core::rect<irr::s32>(500,213,1409,1013),
                          0,
                          irr::video::SColor (255,255,255,255),
                          true);
      _graphic.getSceneManager().drawAll();
      _graphic.getDriver().endScene();
      for (size_t i = 0; i != _bomb.size(); i++)
            if (_bomb[i]->update() == true)
            {
                _bomb.erase(_bomb.begin() + i);
                break;
            }
        for (size_t i = 0; i != _explosion.size(); i++)
            if (_explosion[i]->update() == true)
            {
                _explosion.erase(_explosion.begin() + i);
                break;
            }
        for (size_t i = 0; i != _players.size(); i++)
        {
            if (_players[i]->getDead() == DYING)
            {
                _players[i]->getNode()->getParent()->removeChild(_players[i]->getNode());
                _players[i]->setDead(DIE);
            }
            else if (_players[i]->getDead() == ALIVE)
                _players[i]->update();
        }
        _graphic.getSceneManager().drawAll();
        for (auto it = _players.begin(); it != _players.end(); it++)
        {
            if ((*it)->getDead() == ALIVE && doPlayerCollideMap(**it, _map))
                (*it)->setPos((*it)->getOldPos());
        }
    }
    _graphic.getDevice().drop();
}

Game::~Game() {}
