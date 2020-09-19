#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"
#include "shaderprogram.h"
#include "controller.h"
#include "Drower.h"
#include "ModelCtrl.h"
#include "ModelGroup.h"
#include <iostream>


float key_X  = 0.0f;
float key_Y = 0.0f;
float key_Z = -5.0f;
float key_Side = 0.0f;
float speed = 0.3;
float key_Y_Side = 0.0f;
bool nextKF = 0;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	
	
	
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			key_Side += speed;
		}
		else if (key == GLFW_KEY_RIGHT) {
			key_Side -= speed;
		}
		else if (key == GLFW_KEY_UP) {
			key_Y_Side += speed;
		}
		else if (key == GLFW_KEY_DOWN) {
			key_Y_Side -= speed;
		}
		else if(key == GLFW_KEY_W){
			std::cout << key_X << std::endl;
			std::cout << key_Z << std::endl;
			std::cout << key_Y << std::endl;
			key_X += sin(key_Side);
			key_Z += cos(key_Side);
			std::cout << key_X << std::endl;
			std::cout << key_Z << std::endl;
			std::cout << key_Y << std::endl;
		}
		else if (key == GLFW_KEY_S){
			key_X -= sin(key_Side) / 10;
			key_Z -= cos(key_Side) / 10;
		}
		else if(key == GLFW_KEY_A){
			key_Y += speed;
			key_Y_Side += speed;
		}
		else if (key == GLFW_KEY_D) {
			key_Y -= speed;
			key_Y_Side -= speed;
		}
		else if (key == GLFW_KEY_X) {
			nextKF = 1;
		}
	}
}




int main(){
	Controller libcontroll;
	libcontroll.initAll();

	glfwSetKeyCallback(libcontroll.getWindow(), key_callback);


	Drower drowIT(libcontroll.getWindow());
	/*const std::string szkielet = "keyFrames\\kf20.obj";
	ModelCtrl skeleton(0.0, 0.0, 0.0);
	skeleton.loadModel(szkielet);*/
	std::string dane1 = "keyFrames";
	std::string dane2 = "kf";
	ModelGroup SceletonA(9,dane1, dane2);
	
	//
	while (!glfwWindowShouldClose(libcontroll.getWindow())) {
		drowIT.clear();
		glUniform4f(spLambert->u("color"), 1, 0, 0, 0);
		SceletonA.Draw();
		glfwSwapBuffers(libcontroll.getWindow());
		glfwPollEvents();
		if (nextKF) {
			SceletonA.goToNextKF();
			nextKF = 0;
		}
		drowIT.setCamera(key_X, key_Y, key_Z, key_Side, key_Y_Side);
		
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