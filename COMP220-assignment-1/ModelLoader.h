#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <gl\glew.h>
#include <SDL_opengl.h>

#include <vector>
#include "Vertex.h"

#pragma once
class ModelHandler
{
public:
	Assimp::Importer importer;

	bool loadModel(const char* filePath, std::vector<Vertex>& vertices, std::vector<unsigned>& indices, std::string &texturePath);

};

