#pragma once

#include "terrainchunk.h"
#include "loader.h"
#include "camera.h"
#include "shader.h"
#include "light.h"
#include "player.h"
#include "vec2.h"
#include "Settings.h"

class Terrain
{
public:
	Terrain(Loader loader);
	~Terrain();

	void update(Loader loader, Player player);
	void render(GLFWwindow* window, Settings settings, Camera camera, vector<Light> allLights, Vec4 clipPlane);
	
	Vec3 getChunkIndex(Vec3 pos); 
	int getNumberOfChunksLoaded(); 
	int getQueueSize(); 

	const int LOADING_DISTANCE = 12; 

private: 
	
	void addToQueue(Vec3 pos);

	vector<Vec3> queue;
	vector<TerrainChunk> chunks; 
	Shader shader;
	GLuint grassTexture, rockTexture, sandTexture;
};

