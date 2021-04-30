#include "CameraController.h"

glm::mat4 translateModel;
glm::mat4 mvp, view, projection;

glm::vec3 position(0, 0, 0), forward(0, 0, -1), sideways(-1, 0, 0), rotation(0);
const glm::vec4 cameraDirection(0, 0, -1, 0);
float walkSpeed = 0.5f, rotationSpeed = 0.1f;
bool freeCam = true;

void CameraController::camSetup()
{
	//translateModel = glm::mat4(1.0f);
	//translateModel = glm::translate(translateModel, glm::vec3(0.0f, -2.0f, -10.0f));
	//translateModel = glm::scale(translateModel, glm::vec3(0.02f, 0.02f, 0.02f));
	
}

// switch camera from free 3rd person cam to 'driving' cam.
void CameraController::switchControl()
{
	if (freeCam)
	{
		freeCam = false;
		forward = glm::vec3(0, 0, -1);
		sideways = glm::vec3(-1, 0, 0);
		position = glm::vec3(0, 0, position.z);
		walkSpeed = 1.0f;
	}
	else if (!freeCam)
	{
		freeCam = true;
		walkSpeed = 0.5f;
	}
}

void CameraController::walk(char direction)
{
	// forward, backward, left, right.
	if(direction == 'w')
		if (!freeCam)
		{
			position += walkSpeed * 2 * forward;
		}
		else
		{
			position += walkSpeed * forward;
		}
	if (direction == 's')
		position -= walkSpeed * forward;
	if (direction == 'a')
		if (!freeCam && position.x > -6)
		{
			position += walkSpeed * sideways;
		}
		else if (freeCam)
		{
			position += walkSpeed * sideways;
		}
	if (direction == 'd')
		if (!freeCam && position.x < 6)
		{
			position -= walkSpeed * sideways;
		}
		else if (freeCam)
		{
			position -= walkSpeed * sideways;
		}
	
}

void CameraController::setRotation(float camRotY, float camRotX)
{
	if (!freeCam)
	{
		camRotY = 0;
		camRotX = 0;
	}
	rotation.y -= camRotX * rotationSpeed;
	rotation.x -= camRotY * rotationSpeed;

	glm::mat4 viewRotate(1.0f);
	viewRotate = glm::rotate(viewRotate, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	viewRotate = glm::rotate(viewRotate, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	forward = glm::normalize(glm::vec3(viewRotate * cameraDirection));
	viewRotate = glm::rotate(viewRotate, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	sideways = glm::normalize(glm::vec3(viewRotate * cameraDirection));
}



void CameraController::camUpdate(GLuint programID, unsigned int transformLoc)
{
	glUseProgram(programID);

	view = glm::lookAt(
		position,
		position + forward,
		glm::vec3(0, 1, 0)
	);
	projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	mvp = projection * view * translateModel;

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp));

}