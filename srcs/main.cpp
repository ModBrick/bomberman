#include <irr/irrlicht.h>
#include "MenuManager.hpp"
#include "Except.hpp"
#include "Graphic.hpp"
#include "Game.hpp"
#include "Sound.hpp"

GamePtrU _game;

int main(void) {
  try {
  Sound music;
  MenuManager *menu = new MenuManager(&music);

  music.playInLoop("./assets/song.mp3");
  GraphicPtrU _graphic = NULL;
  _graphic = GraphicPtrU(new Graphic(menu->Start()));
  _game = GamePtrU(new Game(*_graphic));
  menu->createPlayers(_game);
  music.stopMusic();
  if (menu->getMusicStatus())
    music.playInLoop("./assets/music.mp3");
  _game->run();
  } catch (IndieError &e) {
    std::cerr << e.what() << std::endl;
  }
}
