#include "ModelLoader.h"


Assimp::Importer importer;
// Import models using Assimp.
bool ModelHandler::LoadModel(const char* filePath, std::vector<Vertex>& vertices, std::vector<unsigned>& indices)
{
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

	// error check
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode || !scene->HasMeshes())
	{
		return false;
	}
	aiMesh* mesh = scene->mMeshes[0];
	if (!mesh) 
	{ 
		return false;
	}

	vertices.clear();
	indices.clear();
	vertices.resize(mesh->mNumVertices);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices[i].x = mesh->mVertices[i].x;
		vertices[i].y = mesh->mVertices[i].y;
		vertices[i].z = mesh->mVertices[i].z;
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return !(vertices.empty() || indices.empty());
}
