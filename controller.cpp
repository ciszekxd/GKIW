#include "controller.h"
void Controller::initAll(){
	glfwInit();
	this->window = glfwCreateWindow(900, 900, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);
//	initShaders();
//	spLambert->use();
	std::cout << "hello world";
}

void Controller::endAll() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
GLFWwindow* Controller::getWindow() {
	return this->window;
}