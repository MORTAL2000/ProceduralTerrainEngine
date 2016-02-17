#pragma once

#include "model.h"
#include "terrainheightgenerator.h"
#include "loader.h"
#include "camera.h"

class TerrainChunk
{

public:
	TerrainChunk(int x, int z);
	~TerrainChunk();	

	static const int SIZE = 64;						// length of the terrains chunk's sides in OpenGL units
	static const int NUMBER_OF_VERTICES = 64+1;		// number of vertices in along the sides

	void load(Loader loader);

	Model getModel(Camera camera);
	Vec3 getIndex(); 
	Vec3 getPosition(); 

	bool operator==(const TerrainChunk &otherChunk) const;

private: 
	
	Vec3 index;
	Vec3 pos;
	Model models[3]; 
};

