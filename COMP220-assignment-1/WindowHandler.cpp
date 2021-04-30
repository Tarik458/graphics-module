#include "WindowHandler.h"


SDL_GLContext glContext;

SDL_Window* window;
SDL_Event ev;		//SDL Event structure, this will be checked in the while loop

unsigned int transformLoc;

vector<ModelHandler> roadModels;
vector<ModelHandler> obstacleModels;

ShaderCompiler shaderCompiler;
CameraController cameraController;
RoadBuilder roadBuilder;

GLuint programID;

GLint64 timer, passed;

glm::vec3 backgroundColour(0.0f, 0.5f, 0.5f);
glm::vec3 collisionColour(1.0f, 0.1f, 0.1f);
glm::vec3 bgColourToUse = backgroundColour;

// Create window using SDL and OpenGL.
void WindowHandler::setup()
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		cleanup();
	}
		
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		cleanup();
	}

	// enable mouse cap
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Set context
	glContext = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to initialise GLEW", (char*)glewGetErrorString(glewError), NULL);
		cleanup();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

// Load models and shaders.

void WindowHandler::modelLoad()
{
	// load road and obstacle models into respective "list" vectors.
	roadBuilder.loadRoads(roadModels);
	roadBuilder.loadObstacles(obstacleModels);

	programID = shaderCompiler.LoadShaders("vertShader.glsl", "fragShader.glsl");
	transformLoc = glGetUniformLocation(programID, "transform");

}

// Fullscreen toggle
void WindowHandler::fullscreen(bool setFullscreen)
{
	if (setFullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowSize(window, 1920, 1080);
		glViewport(0, 0, 1920, 1080);
		SDL_UpdateWindowSurface(window);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, 1280, 720);
		glViewport(0, 0, 1280, 720);
		SDL_UpdateWindowSurface(window);
	}
}

// Lets main be cleaner also has access to all variables in this class.
void WindowHandler::Loop()
{
	glClearColor(bgColourToUse.x, bgColourToUse.y, bgColourToUse.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(programID);

	cameraController.view = glm::lookAt(
		cameraController.position,
		cameraController.position + cameraController.forward,
		glm::vec3(0, 1, 0)
	);

	// reposition and draw road models.
	for (std::size_t i = 0; i < roadModels.size(); i++)
	{
		if (roadBuilder.repositionRoad(cameraController.position, roadModels[i].modelPosition))
		{
			roadModels[i].translate(glm::vec3(0, 0, -200));
		}
		cameraController.projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 200.0f);
		cameraController.mvp = cameraController.projection * cameraController.view * roadModels[i].model;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(cameraController.mvp));
		roadModels[i].draw(programID);
	}

	// make sure not to spawn obstacles too quickly.
	glGetInteger64v(GL_TIMESTAMP, &passed);
	GLint64 timePassed = (passed / 1000000) - (timer / 1000000);
	// spawn in obstacle models.
	if (rand() % 41 == 0 &&  timePassed > 500) //more than one second.
	{
		glGetInteger64v(GL_TIMESTAMP, &timer);
		roadBuilder.repositionObstacle(cameraController.position, obstacleModels);
	}

	// check for collisions with and draw obstacles.
	bgColourToUse = backgroundColour;
	for (std::size_t i = 0; i < obstacleModels.size(); i++)
	{
		if (bgColourToUse != collisionColour)
		{
			bgColourToUse = collisionDetect(obstacleModels[i].modelPosition, cameraController.position);
		}
		cameraController.projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 200.0f);
		cameraController.mvp = cameraController.projection * cameraController.view * obstacleModels[i].model;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(cameraController.mvp));
		obstacleModels[i].draw(programID);
	}

	SDL_GL_SwapWindow(window);
	//glClearColor(bgColourToUse.x, bgColourToUse.y, bgColourToUse.z, 1.0f);
}

// background will flash red if there is a collsion.
glm::vec3 WindowHandler::collisionDetect(glm::vec3 modelPos, glm::vec3 camPos)
{
	bool collision = false;
	float collisionRange = 2.5;

	if (camPos.x > modelPos.x - collisionRange && camPos.x < modelPos.x + collisionRange)
	{
		if (camPos.z > modelPos.z - collisionRange && camPos.z < modelPos.z + collisionRange)
		{
			collision = true;
		}
	}

	if (collision)
	{
		return collisionColour;
	}
	else
	{
		return backgroundColour;
	}
}

// Cleans up all SDL and GL stuff when exiting.
void WindowHandler::cleanup()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDeleteProgram(programID);
	SDL_DestroyWindow(window);

	SDL_Quit();
}