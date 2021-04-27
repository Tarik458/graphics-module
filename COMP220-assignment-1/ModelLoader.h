#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Mesh.h"

#pragma once

// Inspiration from: https://learnopengl.com/Model
class ModelHandler
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
    string primaryTex;
    float modelPos;
    glm::mat4 model;
    glm::mat4 translateVar;
    float radRotation;

    ModelHandler(string const& path, string const& primaryTex, float modelPos, bool gamma = false) : gammaCorrection(gamma)
    {
        this->primaryTex = primaryTex;
        this->modelPos = modelPos;
        model = glm::mat4(modelPos);
        translateVar = glm::mat4(1.0f);
        loadModel(path);
    }

    void draw(GLuint& ProgramID);
    void rotation(float radRotation, glm::vec3 axis);
    void scale(glm::vec3 scale);
    void translate(glm::vec3 translation);

private:
	void loadModel(const string& filePath);

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

    unsigned int TextureFromFile(const char* path, const string& directory, const string primaryTex);
};

