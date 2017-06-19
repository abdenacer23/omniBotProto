//
//  LevelTile.cpp
//  Game_PC
//
//  Created by Kris Temmerman on 16/06/2017.
//
//

#include "LevelTile.hpp"
#include "glm/gtc/random.hpp"
using namespace ci;
using namespace ci::app;
using namespace std;



LevelTileRef LevelTile::create()
{
    return  make_shared<LevelTile>();
}



void LevelTile::setup(int x,int y, float _size)
{
    xR =x;
    yR =y;
    
    size =_size;
    
    posXWorld = xR*size;
    posYWorld= yR*size;
    
    
    testColor.r = glm::linearRand(0.f, 1.f);
    testColor.g = glm::linearRand(0.f, 1.f);
    testColor.b = glm::linearRand(0.f, 1.f);
    
}
void LevelTile::draw()
{
    gl::color(testColor);
    gl::drawSolidRect(Rectf( -size/2,  -size/2,size/2, size/2));
    gl::drawString(to_string(xR)+"-"+to_string(yR), vec2(5,5));
}
