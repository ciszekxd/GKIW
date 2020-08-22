#include "Drower.h"


Drower::Drower(GLFWwindow* window) {
	this->window = window;
	this->cameraPosition = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	this->Perspective = glm::perspective(50.0f * 3.14f / 180.0f, 1.0f, 1.0f, 50.0f);
	
}

void Drower::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 1, 0);
}

void Drower::setCamera(glm::mat4 newMat) {
	this->cameraPosition = newMat;
}



