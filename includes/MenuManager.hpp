//
// MenuManager.hpp for MenuManager in /home/clarissebergereepitecheu/Rendu/CPP/TMP/cpp_indie_studio
//
// Made by clarisse.bergere@epitech.eu
// Login   <clarisse.bergere@epitech.eu>
//
// Started on  Wed Jun 14 12:11:27 2017 clarisse.bergere@epitech.eu
// Last update Sun Jun 18 23:00:27 2017 Clarisse Bergere
//

#pragma once

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <irr/irrlicht.h>
#include <Game.hpp>
#include "Sound.hpp"
#include "MenuReceiver.hpp"

#define HOME 1
#define GAME 2
#define QUIT 3
#define OPTIONS 4

class MenuManager
{
private:
  MenuReceiver              *_receiver;
  irr::IrrlichtDevice       *_device;
  irr::gui::IGUIEnvironment *_env;
  video::IVideoDriver       *_driver;
  gui::IGUIImage            *_screen;
  gui::IGUIImage            *_optionsBanner;
  gui::IGUIButton           *_playButton;
  gui::IGUIButton           *_backButton;
  gui::IGUIButton           *_optionsButton;
  gui::IGUIButton           *_musicButton;
  gui::IGUIEditBox          *_nameBox;
  enum UserType             _usersType[4];
  std::vector<bool>         *_users;
  std::vector<gui::IGUIButton*> _buttons;
  int                       _status;

public:
  MenuManager(Sound *music);
  ~MenuManager() {};
  MenuManager(const MenuManager &) = delete;
  MenuManager &operator=(const MenuManager &) = delete;

public:
  void FirstView();
  void createPlayers(GamePtrU& _game);
  void drawSplashScreen();
  void draw();
  void replayHomeMenu();

public:
  irr::gui::IGUIEnvironment *getEnvironment() { return (_env); };
  irr::IrrlichtDevice *Start();
  void Update();

public:
  bool getMusicStatus() { return (_receiver->getMusicStatus()); };
  void winScreen();
  void gameOverScreen();
  void optionsScreen();
};
