#include "ModelLoader.h"

struct Vertex
{
	float x, y, z;
};

Assimp::Importer importer;
// Import models using Assimp.
bool ModelLoader::LoadModel(const char* filePath, std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

	// error check
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode || !scene->HasMeshes())
	{
		return false;
	}
}
