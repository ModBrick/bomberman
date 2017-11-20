//
// MenuReceiver.hpp for MenuReceiver in /home/clarissebergereepitecheu/Rendu/CPP/cpp_indie_studio
//
// Made by clarisse.bergere@epitech.eu
// Login   <clarisse.bergere@epitech.eu>
//
// Started on  Wed Jun 14 19:44:45 2017 clarisse.bergere@epitech.eu
// Last update Sun Jun 18 22:35:04 2017 Clarisse Bergere
//

#pragma once

#include "Sound.hpp"

enum
  {
    GUI_PLAY_BUTTON,
    GUI_SOUND_BUTTON,
    GUI_USER1_BUTTON,
    GUI_USER2_BUTTON,
    GUI_USER3_BUTTON,
    GUI_USER4_BUTTON,
    GUI_OPTIONS_BUTTON,
    GUI_BACK_BUTTON
};

enum UserType
  {
    USER,
    IA
  };

class MenuReceiver : public irr::IEventReceiver
{
private:
  std::vector<bool>      _users[4];
  std::vector<bool>      _oldUsers[4];
  int                    _status;
  bool                   _music;
  Sound                 *_musicManager;

public:
  MenuReceiver(Sound *music);
  ~MenuReceiver() {};
  MenuReceiver(const MenuReceiver&) = delete;
  MenuReceiver &operator=(const MenuReceiver&) = delete;

public:
  void setStatus(int status) { _status = status; };
  int  getStatus() { return (_status); };
  void setMusicOn() { _music = true; };
  void setMusicOff() { _music = false; };
  bool getMusicStatus() { return (_music); };
  bool OnEvent(const irr::SEvent& event);
  std::vector<bool>   *getUsersInfos();

};
