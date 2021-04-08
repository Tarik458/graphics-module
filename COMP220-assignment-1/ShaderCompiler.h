#include <iostream>
#include <fstream>
#include <sstream>

#include <gl\glew.h>
#include <SDL_opengl.h>

#include <string>
#include <vector>


#pragma once
class ShaderCompiler
{
public:
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

};

