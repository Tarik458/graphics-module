#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gl\glew.h>

#pragma once

class CameraController
{
public:
	glm::mat4 translateModel;
	glm::mat4 mvp, view, projection;

	glm::vec3 position, forward, sideways, rotation;

	CameraController()
	{
		camSetup();
	}

	void camSetup();

	void walk(char direction);

	void setRotation(float camRotY, float camRotX);

	void camUpdate(GLuint programID, unsigned int transformLoc);

};

