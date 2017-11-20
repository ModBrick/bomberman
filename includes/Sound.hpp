#pragma once

#include <iostream>
#include "irr/irrlicht.h"
#include "Game.hpp"
#include "Graphic.hpp"
#include "irr/irrKlang.h"

class Sound {
private:
    irrklang::ISoundEngine *_engine;
    irrklang::ISound *_music;

public:
    Sound();

    ~Sound() { deleteAll(); };

    Sound(const Sound &) = delete;

    Sound &operator=(const Sound &) = delete;

public:
    void playInLoop(std::string musicName);

    void playSingle(std::string musicName);

    void setPause(bool pause);

    void deleteAll();

    void stopMusic(void) { _engine->stopAllSounds(); };

};
