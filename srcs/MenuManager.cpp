//
// MenuManager.cpp for MenuManager in /home/clarissebergereepitecheu/Rendu/CPP/TMP/cpp_indie_studio
//
// Made by clarisse.bergere@epitech.eu
// Login   <clarisse.bergere@epitech.eu>
//
// Started on  Wed Jun 14 12:11:13 2017 clarisse.bergere@epitech.eu
// Last update Mon Jun 19 20:29:28 2017 Pierre Capon
//

#include "Except.hpp"
#include "MenuManager.hpp"
#include "Graphic.hpp"

MenuManager::MenuManager(Sound *music) {
  _device = createDevice(video::EDT_OPENGL,
                         core::dimension2d<u32>(WIDTH_WINDOW, HEIGHT_WINDOW),
                         32,
                         false,
                         true,
                         true,
                         0);
  _receiver = new MenuReceiver(music);
  _usersType[0] = USER;
  for (int i = 1; i < 4; ++i)
    _usersType[i] = IA;
}

void MenuManager::winScreen() {
  irr::video::ITexture *texture;
  texture = _driver->getTexture("./assets/win.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _screen = _env->addImage(texture, core::position2d<int>(0, 0));
  _device->setEventReceiver(_receiver);
  while (1)
    this->draw();
}

void MenuManager::replayHomeMenu() {
  irr::video::ITexture *texture;

  texture = _driver->getTexture("./assets/simpsons_pic/homer_screen_start.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _screen = _env->addImage(texture,
                           core::position2d<int>(0, 0));
  _playButton = _env->addButton(core::rect<s32>((WIDTH_WINDOW/2) - 300, 470, (WIDTH_WINDOW/2) + 300, 470 + 100), 0, GUI_PLAY_BUTTON,
                                0);
  _playButton->setUseAlphaChannel(true);
  _playButton->setDrawBorder(0);
  texture = _driver->getTexture("./assets/simpsons_pic/start.tga");
  if (!texture)
    throw AssetError("Can't find image");
  _playButton->setImage(texture);
  _optionsButton = _env->addButton(core::rect<s32>(0, HEIGHT_WINDOW - 100, 300, HEIGHT_WINDOW), 0, GUI_OPTIONS_BUTTON,
                                   0);
  _optionsButton->setUseAlphaChannel(true);
  _optionsButton->setDrawBorder(0);
  texture = _driver->getTexture("./assets/simpsons_pic/option.tga");
  if (!texture)
    throw AssetError("Can't find image");
  _optionsButton->setImage(texture);
  for (int i = 0; i < 4; ++i)
    _buttons.pop_back();
  _buttons.push_back(_env->addButton(core::rect<s32>(10, 150, 20 + 180, 150 + 300), 0, GUI_USER1_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(290, 150, 300 + 180, 150 + 300), 0, GUI_USER2_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(570, 150, 580 + 180, 150 + 300), 0, GUI_USER3_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(850, 150, 860 + 180, 150 + 300), 0, GUI_USER4_BUTTON, 0));
  texture = _driver->getTexture("./assets/simpsons_pic/user_pic.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _buttons.at(0)->setImage(texture);
  for (int i = 1; i < 4; ++i) {
    texture = _driver->getTexture("./assets/simpsons_pic/ia_pic.jpg");
    if (!texture)
      throw AssetError("Can't find image");
    _buttons.at(i)->setImage(texture);
  }
  _env->addEditBox(L"Player1", core::rect<s32>(10, 400, 200, 450));
  _env->addEditBox(L"Player2", core::rect<s32>(290, 400, 300 + 180, 450));
  _env->addEditBox(L"Player3", core::rect<s32>(570, 400, 580 + 180, 450));
  _env->addEditBox(L"Player4", core::rect<s32>(850, 400, 860 + 180, 450));
  _musicButton = _env->addButton(core::rect<s32>(WIDTH_WINDOW - 300, HEIGHT_WINDOW - 100, WIDTH_WINDOW, HEIGHT_WINDOW), 0, GUI_SOUND_BUTTON, 0);
  _musicButton->setUseAlphaChannel(true);
  _musicButton->setDrawBorder(0);
  _musicButton->setImage(_driver->getTexture("./assets/simpsons_pic/soundon.tga"));
}

void MenuManager::gameOverScreen() {
  irr::video::ITexture *texture;

  texture = _driver->getTexture("./assets/game_over.png");
  if (!texture)
    throw AssetError("Can't find image");
  _screen = _env->addImage(texture, core::position2d<int>(-120, -120));
  _device->setEventReceiver(_receiver);
  while (1)
    this->draw();
}

void MenuManager::drawSplashScreen() {
  irr::video::ITexture *texture;

  texture = _driver->getTexture("./assets/simpsons_pic/homer_screen_start.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _screen = _env->addImage(texture,
                           core::position2d<int>(0, 0));
  _screen->setScaleImage(true);
  this->draw();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  this->FirstView();
}

void MenuManager::FirstView() {
  irr::video::ITexture *texture;

  _playButton = _env->addButton(core::rect<s32>((WIDTH_WINDOW/2) - 300, 470, (WIDTH_WINDOW/2) + 300, 470 + 100), 0, GUI_PLAY_BUTTON,
                                0);
  texture = _driver->getTexture("./assets/simpsons_pic/start.tga");
  if (!texture)
    throw AssetError("Can't find image");
  _playButton->setImage(texture);
  _playButton->setUseAlphaChannel(true);
  _playButton->setDrawBorder(0);
  _optionsButton = _env->addButton(core::rect<s32>(0, HEIGHT_WINDOW - 100, 300, HEIGHT_WINDOW), 0, GUI_OPTIONS_BUTTON,
                                   0);
  _optionsButton->setUseAlphaChannel(true);
  _optionsButton->setDrawBorder(0);
  texture = _driver->getTexture("./assets/simpsons_pic/option.tga");
  if (!texture)
    throw AssetError("Can't find image");
  _optionsButton->setImage(texture);
  _buttons.push_back(_env->addButton(core::rect<s32>(10, 150, 20 + 180, 150 + 300), 0, GUI_USER1_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(290, 150, 300 + 180, 150 + 300), 0, GUI_USER2_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(570, 150, 580 + 180, 150 + 300), 0, GUI_USER3_BUTTON, 0));
  _buttons.push_back(_env->addButton(core::rect<s32>(850, 150, 860 + 180, 150 + 300), 0, GUI_USER4_BUTTON, 0));
  texture = _driver->getTexture("./assets/simpsons_pic/user_pic.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _buttons.at(0)->setImage(texture);
  for (int i = 1; i < 4; ++i) {
    texture = _driver->getTexture("./assets/simpsons_pic/ia_pic.jpg");
    if (!texture)
      throw AssetError("Can't find image");
    _buttons.at(i)->setImage(texture);
  }
  _env->addEditBox(L"Player1", core::rect<s32>(10, 400, 200, 450));
  _env->addEditBox(L"Player2", core::rect<s32>(290, 400, 300 + 180, 450));
  _env->addEditBox(L"Player3", core::rect<s32>(570, 400, 580 + 180, 450));
  _env->addEditBox(L"Player4", core::rect<s32>(850, 400, 860 + 180, 450));
  _musicButton = _env->addButton(core::rect<s32>(WIDTH_WINDOW - 300, HEIGHT_WINDOW - 100, WIDTH_WINDOW, HEIGHT_WINDOW), 0, GUI_SOUND_BUTTON, 0);
  _musicButton->setUseAlphaChannel(true);
  _musicButton->setDrawBorder(0);
  _musicButton->setImage(_driver->getTexture("./assets/simpsons_pic/soundon.tga"));
}

void MenuManager::Update() {
  irr::video::ITexture *texture;
  _users = _receiver->getUsersInfos();
  for (int i = 0; i < 4; ++i) {
    if (_users->at(i) == true) {
      if (_usersType[i] == IA) {
        texture = _driver->getTexture("./assets/simpsons_pic/user_pic.jpg");
        if (!texture)
          throw AssetError("Can't find image");
        _buttons.at(i)->setImage(texture);
        _usersType[i] = USER;
      } else {
        texture = _driver->getTexture("./assets/simpsons_pic/ia_pic.jpg");
        if (!texture)
          throw AssetError("Can't find image");
        _buttons.at(i)->setImage(texture);
        _usersType[i] = IA;
      }
    }
  }
  if (_receiver->getMusicStatus() == false)
    _musicButton->setImage(_driver->getTexture("./assets/simpsons_pic/soundoff.tga"));
  else
    _musicButton->setImage(_driver->getTexture("./assets/simpsons_pic/soundon.tga"));
}

void MenuManager::optionsScreen() {
  irr::video::ITexture *texture;

  texture = _driver->getTexture("./assets/simpsons_pic/homer_screen.jpg");
  if (!texture)
    throw AssetError("Can't find image");
  _screen = _env->addImage(texture, core::position2d<int>(0, 0));
  _backButton = _env->addButton(core::rect<s32>(0, 500, 200, 500 + 100), 0, GUI_BACK_BUTTON, 0);
  texture = _driver->getTexture("./assets/return_button.png");
  if (!texture)
    throw AssetError("Can't find image");
  _backButton->setImage(texture);
}

void MenuManager::draw() {
  _driver->beginScene(true, true, video::SColor(0, 200, 200, 200));
  _env->drawAll();
  _driver->endScene();
}

irr::IrrlichtDevice *MenuManager::Start() {
  _env = _device->getGUIEnvironment();
  _driver = _device->getVideoDriver();
  this->drawSplashScreen();
  _device->setEventReceiver(_receiver);
  _status = HOME;
  while ((_device->run())
         && ((_receiver->getStatus() == HOME)
             || (_receiver->getStatus() == OPTIONS))) {
    if (_receiver->getStatus() == OPTIONS) {
      if (_status != OPTIONS)
        this->optionsScreen();
    }
    if (_receiver->getStatus() == HOME) {
      if (_status != HOME)
        this->replayHomeMenu();
      this->Update();
    }
    _status = _receiver->getStatus();
    this->draw();
  }
  return (_device);
}

void MenuManager::createPlayers(GamePtrU &_game) {
  for (int i = 0; i < 4; ++i)
    _game->addPlayer(_usersType[i] == IA ? IAPLAYER : USERPLAYER, i);
}
