#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"
#include <iostream>
//#include "shaderprogram.h"
class Controller
{
protected:
	GLFWwindow* window;
public:
	//inicjuje wszystko co trzeba zainicjowa�
	void initAll();
	//ko�czy wszystko co trzeba sko�czy� przed zamkni�ciem programu
	void endAll();
	//zwraca u�ywane okno
	GLFWwindow* getWindow();
};

