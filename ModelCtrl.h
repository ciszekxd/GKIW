#pragma once
/*#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shaderprogram.h"
#include <vector>*/

#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "basicallyIntegralPartOfAssimp.cpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
class ModelCtrl
{
public:
	glm::mat4 ModelPosition;
	std::vector<Mesh> vertices;
	std::vector<Texture> normals;
	std::vector<Mesh> meshes;
	int vertexCount;
	
	ModelCtrl(float=0, float=0, float=0);
	void loadModel(const std::string& path);
	void processNode(aiNode*,const aiScene*);
	Mesh processMesh(aiMesh*, const aiScene*);
	void Draw();

	
	//void conversion();

};

