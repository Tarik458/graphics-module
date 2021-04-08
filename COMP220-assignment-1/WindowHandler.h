#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Vertex.h"
#include "ModelLoader.h"
#include "ShaderCompiler.h"


#pragma once

class WindowHandler
{
public:

	SDL_Window* window;
	SDL_Surface* image;
	SDL_Event ev;

	// Public functions.
	void setup();

	void model_ShaderLoad();

	void fullscreen();

	void Loop();

	void cleanup();

};

