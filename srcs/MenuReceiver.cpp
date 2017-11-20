//
// MenuReceiver.cpp for MenuReceiver in /home/clarissebergereepitecheu/Rendu/CPP/cpp_indie_studio
//
// Made by clarisse.bergere@epitech.eu
// Login   <clarisse.bergere@epitech.eu>
//
// Started on  Wed Jun 14 19:44:27 2017 clarisse.bergere@epitech.eu
// Last update Sun Jun 18 23:34:29 2017 Clarisse Bergere
//

#include "MenuManager.hpp"

MenuReceiver::MenuReceiver(Sound *music)
{
  _music = true;
  _musicManager = music;
  for (int i = 0; i < 4; ++i)
    _users->push_back(false);
  for (int i = 0; i < 4; ++i)
    _oldUsers->push_back(false);
  _status = HOME;
}

std::vector<bool> *MenuReceiver::getUsersInfos()
{
  for (int i = 0; i < 4; ++i)
    _oldUsers->at(i) = _users->at(i);
  for (int i = 0; i < 4; ++i)
    _users->at(i) = false;
  return (_oldUsers);
}

bool MenuReceiver::OnEvent(const irr::SEvent& event)
{
  if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32 id = event.GUIEvent.Caller->getID();
      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
        {
	  switch (id)
	    {
	    case GUI_PLAY_BUTTON:
	      {
		_status = GAME;
		return true;
              }
	    case GUI_USER1_BUTTON:
	      {
		_users->at(0) = true;
		return true;
	      }
	    case GUI_USER2_BUTTON:
	      {
		_users->at(1) = true;
		return true;
	      }
	    case GUI_USER3_BUTTON:
	      {
		_users->at(2) = true;
		return true;
	      }
	    case GUI_USER4_BUTTON:
	      {
		_users->at(3) = true;
		return true;
	      }
      case GUI_OPTIONS_BUTTON:
        {
        _status = OPTIONS;
        return true;
	     }
       case GUI_SOUND_BUTTON:
         {
          if (_music == false)
            {
              _musicManager->setPause(false);
              _music = true;
            }
          else
            {
              _musicManager->setPause(true);
              _music = false;
            }
         return true;
       }
       case GUI_BACK_BUTTON:
       {
         _status = HOME;
         return true;
       }
	    }
    }
  }
return (false);
}
