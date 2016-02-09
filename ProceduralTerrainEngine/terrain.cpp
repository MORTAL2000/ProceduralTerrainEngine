

#include "terrain.h"


Terrain::Terrain(Loader loader)
{
	shader = Shader();
	shader.createShader("terrain_vert.glsl", "terrain_frag.glsl");
	GLuint texture = loader.loadBMPtexture("lushgrass.bmp");
	
	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			TerrainChunk chunk = TerrainChunk(loader, x * TerrainChunk::SIZE - 40, z * TerrainChunk::SIZE - 40);			
			chunk.getModel().set_texture(texture);
			chunks.push_back(chunk);
		}
	}
	
}

Terrain::~Terrain()
{
	shader.cleanUp(); 
}

void Terrain::render(GLFWwindow* window, Camera camera)
{
	float projectionMatrix[16];
	float viewMatrix[16];
	float modelMatrix[16];

	camera.getProjectionMatrix(projectionMatrix);
	camera.getViewMatrix(viewMatrix);

	shader.start();
	shader.setUniformMat4("projectionMatrix", projectionMatrix);
	shader.setUniformMat4("viewMatrix", viewMatrix);
	
	for (int i = 0; i < chunks.size(); i++)
	{
		Model chunkModel = chunks[i].getModel();
		chunkModel.getModelMatrix(modelMatrix);
		shader.setUniformMat4("modelMatrix", modelMatrix);

		glBindVertexArray(chunkModel.get_id());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, chunkModel.get_texture());
		glDrawElements(GL_TRIANGLES, chunkModel.get_vertexcount(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
	
	shader.stop();
}