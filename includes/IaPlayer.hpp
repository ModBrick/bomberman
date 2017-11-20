//
// ia.hpp for game in /home/pcapon/project/cpp/cpp_indie_studio/includes/
//
// Made by Pierre Capon
// Login   <capon_p@pierre.capon@epitech.eu>
//
// Started on  Wed Jun 14 10:51:29 2017 Pierre Capon
// Last update Sun Jun 18 23:34:21 2017 Pierre Capon
//


#pragma once

#include <irr/irrlicht.h>
#include <map>
#include <chrono>
#include "Map.hpp"
#include "GameObject.hpp"
#include "IComponent.hpp"
#include "MovePlayer.hpp"


class IaPlayer : public IComponent
{

public:
    //Le constructeur.
    IaPlayer(GameObject* player);
    virtual void update(GameObject &);
    //Met a jour la position du mesh.
private:
    //void callForUpdate();
    void runIA();
    void moveToTarget(int x, int y, std::vector<lineBlock>);
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void stop();
    void putBomb();
    void targetPlayer(int, int, std::vector<lineBlock>);
    int canSave(int, int, std::vector<lineBlock>);

    core::vector2d<s32> _target;
    core::vector2d<s32> _Escapetarget;
    core::vector2d<s32> _unstuckTarget;
    //Le modele qu'on va controler.
    GameObject* _player;
    //std::map <int, IMovePlayerPtr> move;
    int _isEscape;
    int _isStuck;
    int _first;
    int _bombPut;
    int _isStop;
    std::time_t _time;
    //Indique si on est deja en mouvement ou pas.
};

typedef std::shared_ptr<IaPlayer> IaPlayerPtr;
