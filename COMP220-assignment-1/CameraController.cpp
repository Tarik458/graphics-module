#include "CameraController.h"

glm::mat4 translateModel;
glm::mat4 mvp, view, projection;

glm::vec3 position(0, 0, 0), forward(0, 0, -1), sideways(-1, 0, 0), rotation(0);
const glm::vec4 cameraDirection(0, 0, -1, 0);
const float walkSpeed = 0.5f, rotationSpeed = 0.1f;

void CameraController::camSetup()
{
	//translateModel = glm::mat4(1.0f);
	//translateModel = glm::translate(translateModel, glm::vec3(0.0f, -2.0f, -10.0f));
	//translateModel = glm::scale(translateModel, glm::vec3(0.02f, 0.02f, 0.02f));
	
}

void CameraController::walk(char direction)
{
	// forward, backward, left, right.
	switch (direction)
	{
	case 'w':
		position += walkSpeed * forward;
		break;
	case 's':
		position -= walkSpeed * forward;
		break;
	case 'a':
		position += walkSpeed * sideways;
		break;
	case 'd':
		position -= walkSpeed * sideways;
		break;
	}
	
}

void CameraController::setRotation(float camRotY, float camRotX)
{
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