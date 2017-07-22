//
//  GrassRenderer.cpp
//  Game_PC
//
//  Created by Kris Temmerman on 20/06/2017.
//
//

#include "GrassRenderer.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;
void GrassRenderer::setup()
{
    mGlsl = gl::GlslProg::create( gl::GlslProg::Format().vertex( loadAsset( "grass.vert" ) )
                                 .fragment( loadAsset( "grass.frag" ) )
                                 .geometry( loadAsset( "grass.geom" ) ) );
    mGlsl->uniform("uNoiseMap", 0);
    mGlsl->uniform("uShadowMap", 1);
    texture =gl::Texture::create( loadImage(getAssetPath("noise.jpg")),gl::Texture::Format().wrap(GL_REPEAT));
    
    
    mGlslShadow = gl::GlslProg::create( gl::GlslProg::Format().vertex( loadAsset( "grassShadow.vert" ) )
                                 .fragment( loadAsset( "grassShadow.frag" ) )
                                 .geometry( loadAsset( "grassShadow.geom" ) ) );
    mGlslShadow->uniform("uNoiseMap", 0);
    

}

void GrassRenderer::draw(ci::gl::FboRef shadowFBO,ci::mat4 &shadowMatrix,PlayerLevel &playerLevel,double currentTime)
{

    mGlsl->bind();
    mGlsl->uniform("time", (float)currentTime/20);
    texture->bind(0);
    shadowFBO->getDepthTexture()->bind(1);
    
    mGlsl->uniform( "uShadowMatrix",  shadowMatrix );
    
    gl::pushMatrices();
    gl::translate( playerLevel.player->playerWorldOffset);
    
    for(auto tile : playerLevel.playerTiles)
    {
        tile->drawGrass();
    }
    
    
    gl::popMatrices();
    
    
    shadowFBO->getDepthTexture()->unbind();



}
void GrassRenderer::drawShadowMap(PlayerLevel &playerLevel,double currentTime)
{
    mGlslShadow->bind();
    mGlslShadow->uniform("time", (float)currentTime/20);
    texture->bind(0);
    
    gl::pushMatrices();
    gl::translate( playerLevel.player->playerWorldOffset);
    
    for(auto tile : playerLevel.playerTiles)
    {
        tile->drawGrass();
    }
    
    
    gl::popMatrices();

    
    
    texture->unbind();


}
