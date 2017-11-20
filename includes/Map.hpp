/*
 * @Author: Boris
 * @Date: 2017-05-04 22:08:18
 * @Last Modified by: Boris
 * @Last Modified time: 2017-05-04 23:05:37
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include "irr/irrlicht.h"
#include "Graphic.hpp"
#include "GameObject.hpp"

using namespace irr;

#define MAGIC_HEADER 0x32948

#define SIZE_BLOCK 10

#define POS(x, size) ((-((size) / 2 * SIZE_BLOCK)) + ((x)*SIZE_BLOCK))

enum TileType {
    EMPTY_BLOCK,
    SOLID_BLOCK,
    BOX_BLOCK
};

struct MapHeader {
    s32 magic;
    char name[255];
    u32 height;
    u32 width;
    char pathMiniJpg[4096];
};

/*
** MapBlock are used to fill map
*/

class MapBlock : public GameObject {
public:
    MapBlock() = delete;

    MapBlock &operator=(const MapBlock &) = delete;

    MapBlock(MapBlock &) = delete;

    MapBlock(Graphic &g,
             TileType t,
             scene::ISceneNode *parent,
             core::vector3df pos);

private:
    TileType _type;

public:
    TileType getType() const { return _type; }

    void setType(TileType type) { _type = type; }
};

typedef std::vector<MapBlock *> lineBlock;

class Map {
public:
    Map(Graphic &);

    ~Map();

    Map(const Map &) = delete;

    Map &operator=(const Map &) = delete;

private:
    std::vector<lineBlock> _map;
    GameObject *_ground;
    Graphic &_graphic;

private:
    MapBlock *createBlock(TileType, core::vector3df) const;

    TileType DetermineType(s32 i, s32 j, bool grid, core::vector2d<s32>);

public:
    void loadRandomMap(core::vector2d<s32>, bool grid = false);

    void loadMap(const std::string &);

    void saveMap();

public:
    std::vector<lineBlock> getMap() const { return _map; }

    core::vector2d<s32> &getSize() const;

    GameObject &getGround() const { return *_ground; }
};

typedef std::shared_ptr<Map> MapPtr;
typedef std::unique_ptr<Map> MapPtrU;
