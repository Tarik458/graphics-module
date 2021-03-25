#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#pragma once
class ModelLoader
{
public:
	struct Vertex;
	Assimp::Importer importer;
	bool LoadModel(const char* filePath, std::vector<Vertex>& vertices, std::vector<unsigned>& indices);

};

