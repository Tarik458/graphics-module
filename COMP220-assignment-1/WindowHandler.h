#include <iostream>
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>



#pragma once

class WindowHandler
{
	// Public variables.
public:
	SDL_Window* window;
	SDL_Event ev;
	GLuint vertexArray;
	GLuint vertexBuffer;

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

