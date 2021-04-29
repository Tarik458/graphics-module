#include <iostream>

#include "ModelLoader.h"
#include "ShaderCompiler.h"
#include "CameraController.h"
#include "RoadBuilder.h"

#pragma once

class WindowHandler
{
public:

	SDL_Window* window;
	SDL_Event ev;

	CameraController cameraController;

	// Public functions.
	WindowHandler()
	{
		setup();
	}

	void setup();

	void modelLoad();

	void fullscreen(bool setFullscreen);

	void Loop();

	void cleanup();

};

