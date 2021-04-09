#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gl\glew.h>

#pragma once

class CameraController
{
public:
	void camSetup();

	void walk(char direction);

	void setRotation(float camRotX, float camRotY);

	void camUpdate(GLuint programID, unsigned int transformLoc);

};

