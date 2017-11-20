/*
 * @Author: Boris
 * @Date: 2017-05-04 22:07:51
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 22:16:35
 */

#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <iostream>
#include "Map.hpp"
#include "Except.hpp"

Map::Map(Graphic &g) : _graphic(g) {
  loadRandomMap(core::vector2d<s32>(11, 13), true);
  saveMap();
}


MapBlock *Map::createBlock(TileType type, core::vector3df pos) const
{
    return new MapBlock(_graphic, type, _ground->getNode(), pos);
}

TileType Map::DetermineType(s32 i, s32 j, bool grid, core::vector2d<s32> size) {
  if (grid) {
    if (!(j % 2) && !(i % 2))
      return SOLID_BLOCK;
    else {
      if ((j == 1 && (i <= 2 || i >= size.X - 3)) || // first line                         // TOP
          (j == 2 && (i == 1 || i == size.X - 2)) || // seconde line                       // CORNERS
          (j == size.Y - 3 && (i == 1 || i == size.X - 2)) || //line before last line      // BOTTOM
          (j == size.Y - 2 && (i <= 2 || i >= size.X - 3))) // last line                   // CORNERS
        return EMPTY_BLOCK;
      else
        return BOX_BLOCK;
    }
  }
  return EMPTY_BLOCK;
}

void Map::loadRandomMap(core::vector2d<s32> size, bool grid) {
  _ground = new GameObject(_graphic.getSceneManager().addMeshSceneNode(
          _graphic.getGeometryCreator().createPlaneMesh(core::dimension2d<f32>(SIZE_BLOCK, SIZE_BLOCK),
                                                        core::dimension2d<u32>(size.X, size.Y)),
          0,
          -1,
          core::vector3df(size.X / 2 * SIZE_BLOCK, 0, size.Y / 2 * SIZE_BLOCK)),
          //  core::vector3df(0)),
                           true);
  _ground->getNode()->setMaterialTexture(0,
                                         _graphic.getDriver().getTexture("./assets/simpsontexture/watercartoon.png"));
  for (s32 j = 0; j < size.Y; ++j) {
    _map.push_back(lineBlock());
    if (j == 0 || j == (size.Y - 1))
      for (s32 i = 0; i < size.X; ++i)
        _map.at(j).push_back(createBlock(SOLID_BLOCK, core::vector3df(POS(i, size.X), SIZE_BLOCK / 2, POS(j, size.Y))));
    else {
      _map.at(j).push_back(createBlock(SOLID_BLOCK, core::vector3df(POS(0, size.X), SIZE_BLOCK / 2, POS(j, size.Y))));
      for (s32 i = 1; i < size.X - 1; ++i)
        _map.at(j).push_back(createBlock(DetermineType(i, j, grid, size),
                                         core::vector3df(POS(i, size.X), SIZE_BLOCK / 2, POS(j, size.Y))));
      _map.at(j).push_back(
              createBlock(SOLID_BLOCK, core::vector3df(POS((size.X - 1), size.X), SIZE_BLOCK / 2, POS(j, size.Y))));
    }
  }
}

void Map::loadMap(const std::string &path) {
  std::ifstream file(path);

  if (file.is_open()) {
    MapHeader hdr;
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    if (content.size() < sizeof(MapHeader))
      return;
    std::istringstream s(content);
    s.read((char *) &hdr, sizeof(MapHeader));
    if (hdr.magic != MAGIC_HEADER)
      return;
    s.seekg(sizeof(MapHeader));
    // _ground->setPosition(irr::core::vector3df(0, 0, 0));
    for (size_t i = 0; i < hdr.height; i++) {
      _map.push_back(lineBlock());
      for (size_t j = 0; j < hdr.width; j++)
        _map.at(i).push_back(createBlock((TileType) (char) (s.get() - '0'), core::vector3df(i, 0, j)));
    }
  }
}

void Map::saveMap() {
  MapHeader hdr;
  std::memset(&hdr, 0, sizeof(hdr));
  hdr.magic = MAGIC_HEADER;
  hdr.height = _map.size();
  hdr.width = _map.at(0).size();
  strcpy(hdr.pathMiniJpg, "");
  strcpy(hdr.name, "test");

  std::ofstream file(hdr.name);
  if (file.is_open()) {
    file.write((char *) &hdr, sizeof(hdr));
    for (size_t i = 0; i < hdr.height; ++i)
      for (size_t j = 0; j < hdr.width; ++j) {
        file.put((_map.at(i).at(j) != nullptr) + '0');
      }
  }
}

core::vector2d<s32> &Map::getSize() const { return *new core::vector2d<s32>(_map.size(), _map.at(0).size()); }

Map::~Map() {
}

/*
** MapBlock are used to fill map
*/

MapBlock::MapBlock(Graphic &g, TileType type, scene::ISceneNode *parent, core::vector3df pos)
        : GameObject(g.getSceneManager().addCubeSceneNode(SIZE_BLOCK, parent, -1, pos), true),
          _type(type) {
  irr::video::ITexture *texture;
  if (type == SOLID_BLOCK) {
    texture = g.getDriver().getTexture("./assets/simpsontexture/bankroof.png");
    if (!texture)
      throw AssetError("Missing asset");
    _node->setMaterialTexture(0, texture);
  } else if (type == BOX_BLOCK) {
    texture = g.getDriver().getTexture("./assets/simpsontexture/duff.png");
    if (!texture)
      throw AssetError("Missing asset");
    _node->setMaterialTexture(0, texture);
  } else
    _node->setVisible(false);
}
