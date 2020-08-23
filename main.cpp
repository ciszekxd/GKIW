#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"
//#include "shaderprogram.h"
#include "controller.h"
#include "Drower.h"
#include "ModelCtrl.h"
#include <iostream>


float key_changer = -5.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	
	
	
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			key_changer += 0.3;
		}
		else if (key == GLFW_KEY_RIGHT) {

		}
		else if (key == GLFW_KEY_UP) {
		
		}
		else if (key == GLFW_KEY_DOWN) {
		
		}
	}
}




int main(){
	Controller libcontroll;
	libcontroll.initAll();
	Drower drowIT(libcontroll.getWindow());
	const std::string szkielet = "skeleton.obj";
	ModelCtrl skeleton(0.0, 0.0, 0.0);
	skeleton.loadModel(szkielet);
	
	//
	while (!glfwWindowShouldClose(libcontroll.getWindow())) {
		drowIT.clear();
		skeleton.drawLLD();
		glfwSwapBuffers(libcontroll.getWindow());
		glfwPollEvents();

		drowIT.setCamera(glm::lookAt(
			glm::vec3(0.0f, 0.0f, key_changer),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)));

	}
	//Mesh testMesh = skeleton.meshes[0];
	//for (size_t j = 0; j < 7; j++)
	//{
	//	for (size_t i = 0; i < 3; i++)
	//	{
	//		std::cout << testMesh.vertices[j].Position[i] << std::endl;
	//	}
	//}
	libcontroll.endAll();
	return 0;
}