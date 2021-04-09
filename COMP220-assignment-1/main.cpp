#include <iostream>
#include <SDL.h>

#include "WindowHandler.h"


int main(int argc, char ** argsv)
{
	//Create window
	WindowHandler Window;
	Window.setup();
	//Create a Vertex Array object to deal with vertex formats
	Window.model_ShaderLoad();

	const Uint8* keystate;

	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	while (running)
	{
		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&Window.ev))
		{
			//Switch case for every message we are intereted in
			switch (Window.ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (Window.ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_f:
					Window.fullscreen();
					break;
				default:
					break;
				}
			case SDL_MOUSEMOTION:
				Window.cameraController.setRotation(Window.ev.motion.xrel, Window.ev.motion.yrel);
				break;
			default:
				break;
			}

			keystate = SDL_GetKeyboardState(NULL);
			if (keystate[SDLK_w])
			{
				Window.cameraController.walk('w');
			}
			if (keystate[SDLK_s])
			{
				Window.cameraController.walk('s');
			}
			if (keystate[SDLK_a])
			{
				Window.cameraController.walk('a');
			}
			if (keystate[SDLK_d])
			{
				Window.cameraController.walk('d');
			}
		}

		
		Window.Loop();
	}
	

	//Destroy the window and quit SDL2
	Window.cleanup();


	return 0;
}