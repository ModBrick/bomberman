/*
** EventReciever.cpp for EventReciever in /home/josselin/rendu/cpp_indie_studio/srcs/Inputs
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Wed Jun 07 10:56:01 2017 josselin
** Last update Fri Jun 16 14:18:55 2017 Clarisse Bergere
*/

#include "EventReceiver.hpp"
#include "MovePlayer.hpp"

enum
{
  GUI_MENU_BUTTON
};

EventReceiverPlayer::EventReceiverPlayer(GameObject* player)
{
  _player = player;
  move["KEY_UP"] = MovePlayerForwardPtr(new MovePlayerForward());
  move["KEY_DOWN"] = MovePlayerBackPtr(new MovePlayerBack());
  move["KEY_LEFT"] = MovePlayerLeftPtr(new MovePlayerLeft());
  move["KEY_RIGHT"] = MovePlayerRightPtr(new MovePlayerRight());
  move["KEY_SPACE"] = MovePlayerBombPtr(new MovePlayerBomb());
}

bool EventReceiverPlayer::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      switch (event.KeyInput.Key)
        {
          case irr::KEY_UP:
            move["KEY_UP"]->setIsMoving(event.KeyInput.PressedDown);
            break;
          case irr::KEY_DOWN:
            move["KEY_DOWN"]->setIsMoving(event.KeyInput.PressedDown);
            break;
          case irr::KEY_LEFT:
            move["KEY_LEFT"]->setIsMoving(event.KeyInput.PressedDown);
            break;
          case irr::KEY_RIGHT:
            move["KEY_RIGHT"]->setIsMoving(event.KeyInput.PressedDown);
            break;
          case irr::KEY_SPACE:
            move["KEY_SPACE"]->setIsMoving(event.KeyInput.PressedDown);
            break;

          default:
            return (false);
        }
    }
  return (true);
}
