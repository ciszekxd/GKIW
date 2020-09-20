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
#include <cmath>

float key_X  = 0.0f;
float key_Y = 0.0f;
float key_Z = -5.0f;
float key_Side = 0.0f;
float speed = 0.3;
float key_Y_Side = 0.0f;
bool nextKF = 0;
bool secondPassed = 0;


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
	ModelGroup SceletonA(9,dane1, dane2, 5.0f, 5.0f, 5.0f);
	ModelCtrl testb(2.0f, 2.0f, 2.0f);
	std::string szkielet = "betterSkeletonTextured.obj";
	testb.loadModel(szkielet);
	//

	float Time=0;
	glfwSetTime(0);

	while (!glfwWindowShouldClose(libcontroll.getWindow())) {
		drowIT.clear();

		glUniform4f(spLambert->u("color"), 1, 0, 0, 0);
		Time = fmod(glfwGetTime(), 1.0);
		if (Time < 0.1) secondPassed = 0;

		SceletonA.interpolation(Time+0.001);



		glfwSwapBuffers(libcontroll.getWindow());
		glfwPollEvents();
		if ((!secondPassed && (Time > 0.9)))
		{
			SceletonA.goToNextKF();
			
			secondPassed = 1;
			std::cout << "next frame" << std::endl;
		}
		drowIT.setCamera(key_X, key_Y, key_Z, key_Side, key_Y_Side);
		
	}
	libcontroll.endAll();
}