/*
** EventReciever.hpp for EventReciever in /home/josselin/rendu/cpp_indie_studio/includes/Inputs
**
** Made by josselin
** Login   <josselin@epitech.net>
**
** Started on  Wed Jun 07 10:56:05 2017 josselin
** Last update Fri Jun 16 13:27:50 2017 Clarisse Bergere
*/

#pragma once

#include <irr/irrlicht.h>
#include <map>
#include "GameObject.hpp"
#include "IComponent.hpp"
#include "MovePlayer.hpp"

class EventReceiverPlayer : public irr::IEventReceiver, public IComponent
{

public:
    //Le constructeur.
    EventReceiverPlayer(GameObject* player);
    //Capte automatiquement les events.
    virtual bool OnEvent(const irr::SEvent &event);
    virtual void update(GameObject &)
    {
      for(std::map<std::string, IMovePlayerPtr>::iterator i = move.begin();
      i!=move.end(); i++)
      {
        if(i->second->getIsMoving() == true)
        {
          i->second->doAction(*_player);
          return;
        }
      }
    };
    //Met a jour la position du mesh.
private:
    //Le modele qu'on va controler.
    GameObject* _player;
    std::map <std::string, IMovePlayerPtr> move;
    //Indique si on est deja en mouvement ou pas.
};

typedef std::shared_ptr<EventReceiverPlayer> EventReceiverPlayerPtr;
