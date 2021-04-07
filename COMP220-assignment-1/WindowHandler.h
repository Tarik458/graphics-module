#include <iostream>
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include "Vertex.h"
#include "ModelLoader.h"


#pragma once

class WindowHandler
{
	// Public variables.
public:

	SDL_Window* window;
	SDL_Event ev;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint elementBuffer;

	// Public functions.
	void setup();

	void vertices();

	void fullscreen();

	void Loop();

	void cleanup();

	// Private variables.
private:
	SDL_GLContext glContext;

};

