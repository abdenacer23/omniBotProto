#include "LeafHandler.h"
#include "GSettings.h"
#include "glm/gtc/random.hpp"
#include "cinder/gl/gl.h"
#include "cinder/Perlin.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;
using namespace ci;
using namespace ci::app;


LeafHandler::LeafHandler(){}


void LeafHandler::setup()
{


	setupRendering();

	
	buildTiles();
	buildLeafs();
	


}
void LeafHandler::setupRendering()
{
	gradientMap = gl::Texture::create(loadImage(loadAsset("leafs/gradient.png")));
	mGlsl = gl::GlslProg::create(loadAsset("leafs/leaf_shader.vert"), loadAsset("leafs/leaf_shader.frag"));
}
void LeafHandler::buildLeafs()
{
	int numLeafs = 100000;
	ci::Perlin pnois = Perlin();


	for (int i = 0; i< numLeafs; i++)
	{
		LeafRef p = Leaf::create();

		glm::vec2 randomPos;
		bool found = false;
		while (!found)
		{

			randomPos = glm::vec2(glm::linearRand(0, GSettings::worldSize), glm::linearRand(0, GSettings::worldSize));
			
			if (pnois.fBm(randomPos.x / 1000, randomPos.y / 1000)<0.1)
			{

				if (glm::linearRand(0.0, 1.0)>0.99)
				{
						//found = true;
				}

			}
			else if (pnois.fBm(randomPos.x / 200, randomPos.y / 200) < -0.1)
			{
				if (glm::linearRand(0.0, 1.0)>0.8)
				{
					found = true;
				}

			}
			else{

					found = true;
			}
			
		}

		p->friction = glm::linearRand(0.95f, 0.98f);

		float noise = (pnois.fBm(randomPos.x / 500, randomPos.y / 500) + 0.3f) * 3;
		

		p->scale = glm::linearRand(1.0f, 2.0f);

		p->rotation.x = glm::linearRand(0, 7);
		p->rotation.y = glm::linearRand(0, 7);
		p->rotation.z = glm::linearRand(0, 7);
		p->position.x = randomPos.x ;
		p->position.y = randomPos.y ;
		p->position.z = glm::linearRand(0.0f, 5.f);

		p->positionStart = p->position;




		
		p->color = vec2(noise + glm::linearRand(-0.1f, 0.2f), glm::linearRand(0.3f, 0.8f));

		int indexX = p->position.x / GSettings::tileSize;
		int indexY = p->position.y / GSettings::tileSize;

		indexX %= GSettings::numTiles;
		indexY %= GSettings::numTiles;

		int tileIndex = indexX + indexY*GSettings::numTiles;
		tiles[tileIndex]->addLeaf(p);
		//colors.push_back(vec2(noise + glm::linearRand(-0.1f, 0.2f), glm::linearRand(0.3f, 0.8f)));
		//positions.push_back(p->matrix);

		//particles.push_back(p);

	}
	for (auto t : tiles)
	{
		t->makeBatch(buildVBOMesh(), mGlsl);
	}

}

void LeafHandler::buildTiles()
{
	for (int y = 0; y<GSettings::numTiles; y++)
	{
		for (int x = 0; x<GSettings::numTiles; x++)
		{
			LeafTileRef tile = LeafTile::create();
			tile->setup(x, y);

			tiles.push_back(tile);
		}

	}
}

void LeafHandler::draw(vector<int>&indices, vector<ci::vec2> &positions)
{

	mGlsl->bind();
	mGlsl->uniform("uGradientMap", 0);
	gradientMap->bind(0);

	for (int i = 0; i < indices.size(); i++)
	{
		gl::pushMatrices();
		gl::translate(positions[i]);
		tiles[indices[i]]->draw();
		gl::popMatrices();
	}
	gl::getStockShader(gl::ShaderDef().color())->bind();
}



ci::gl::VboMeshRef  LeafHandler::buildVBOMesh()
{

	vector<vec3> posTemp;

	posTemp.push_back(vec3(0, -7, 3));
	posTemp.push_back(vec3(-3.3, -3.5, 1));
	posTemp.push_back(vec3(3.3, -3.5, 1));
	posTemp.push_back(vec3(-4, 0, 0));
	posTemp.push_back(vec3(4, 0, 0));
	posTemp.push_back(vec3(-3.3, 3.5, 1));
	posTemp.push_back(vec3(3.3, 3.5, 1));
	posTemp.push_back(vec3(0, 7, 3));



	vector<unsigned short> indexTemp;

	indexTemp.push_back(0);
	indexTemp.push_back(2);
	indexTemp.push_back(1);

	indexTemp.push_back(1);
	indexTemp.push_back(2);
	indexTemp.push_back(3);

	indexTemp.push_back(3);
	indexTemp.push_back(2);
	indexTemp.push_back(4);

	indexTemp.push_back(3);
	indexTemp.push_back(4);
	indexTemp.push_back(5);

	indexTemp.push_back(5);
	indexTemp.push_back(4);
	indexTemp.push_back(6);

	indexTemp.push_back(5);
	indexTemp.push_back(6);
	indexTemp.push_back(7);





	auto vertices = vector<VertexData>();

	for (auto p : posTemp)
	{
		VertexData right;
		right.position = p;



		vertices.push_back(right);


	}
	auto layout = geom::BufferLayout();

	layout.append(geom::Attrib::POSITION, 3, sizeof(VertexData), offsetof(VertexData, position));


	// upload your data to the GPU
	auto buffer = gl::Vbo::create(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	ci::gl::VboMeshRef meshRef;
	// construct a VAO that describes the data in the buffer according to your layout.
	meshRef = gl::VboMesh::create(vertices.size(), GL_TRIANGLES, { { layout, buffer } }, indexTemp.size());
	meshRef->bufferIndices(indexTemp.size()*sizeof(unsigned short), indexTemp.data());

	return meshRef;
	 
}
