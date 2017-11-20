#include "Sound.hpp"
#include "Except.hpp"

void Sound::playInLoop(std::string musicName)
{
  _engine->play2D(musicName.c_str(), true);
}

void Sound::playSingle(std::string musicName)
{
  _engine->play2D(musicName.c_str(), false);
}

void Sound::deleteAll()
{
  _engine->stopAllSounds();
  _engine->drop();
}

void Sound::setPause(bool pause)
{
  _engine->setAllSoundsPaused(pause);
}

Sound::Sound()
{
 if (!(_engine = irrklang::createIrrKlangDevice()))
   throw DeviceError("Can't find sound device");
}
