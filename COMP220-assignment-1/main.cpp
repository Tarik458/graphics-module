#include <iostream>
#include <SDL.h>

#include "WindowHandler.h"


int main(int argc, char ** argsv)
{
	bool fullscreen = false;
	//Create window
	WindowHandler Window;
	Window.setup();
	//Create a Vertex Array object to deal with vertex formats
	Window.model_ShaderLoad();

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

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
			
			case SDL_MOUSEMOTION:
				Window.cameraController.setRotation(Window.ev.motion.yrel, Window.ev.motion.xrel);
				break;
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (Window.ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_f:
					if (!fullscreen)
					{
						Window.fullscreen(true);
						fullscreen = true;
					}
					else
					{
						Window.fullscreen(false);
						fullscreen = false;
					}
				default:
					break;
				}
			default:
				break;
			}
			if (keystate[SDL_SCANCODE_W])
			{
				Window.cameraController.walk('w');
			}
			if (keystate[SDL_SCANCODE_S])
			{
				Window.cameraController.walk('s');
			}
			if (keystate[SDL_SCANCODE_A])
			{
				Window.cameraController.walk('a');
			}
			if (keystate[SDL_SCANCODE_D])
			{
				Window.cameraController.walk('d');
			}
		}
		/*
		
		*/
		Window.Loop();
	}
	

	//Destroy the window and quit SDL2
	Window.cleanup();


	return 0;
}
