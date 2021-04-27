#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#pragma once
using namespace std;

// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string path;
    string type;
};

class Mesh
{
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

    void Draw(GLuint& ProgramID);

private:
    GLuint vertexArray, vertexBuffer;
    void setupMesh();
};

