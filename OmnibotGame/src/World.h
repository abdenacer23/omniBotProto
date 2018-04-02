#pragma once
#include "cinder/app/App.h"
#include "Tile.h"
#include "FloorMapping.hpp"  
#include "LeafHandler.h"
#include "GrassHandler.h"
#include "FlowerHandler.h"

#include "RenderData.h"
#include "Player.h"




class World
{
public:
	World();

	void setup();
	
	float worldSize;

	std::vector<TileRef> tiles;
	void draw();

	void resolvePlayerPos(PlayerRef player);
	void updateGL();
	void drawPlayerTiles(int index, RenderDataRef renderdata);
	void drawPlayerTilesShadow(int index, RenderDataRef renderdata);
	FloorMapping floorMapping;
	LeafHandler leafHandler;
	GrassHandler grassHandler;
	FlowerHandler flowerHandler;
};
