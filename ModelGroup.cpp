#include "ModelGroup.h"

ModelGroup::ModelGroup(int Tsize, std::string& dirName, std::string& KfName, float x, float y, float z) {
	this->dirName = dirName;
	this->KfName = KfName;
	this->TableSize = Tsize;
	this->CurrentFrame = 0;
	this->NextFrame = (Tsize > 0) ? 1 : 0;

	for (int i = 0; i < Tsize; i++)
	{
		std::cout << this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj" << std::endl;
		this->ModelT.push_back(ModelCtrl(0, 0, 0));
		this->ModelT[i].loadModel(this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj");
	}
		
}

void ModelGroup::Draw()
{
	this->ModelT[CurrentFrame].drawLLD();
}

int ModelGroup::GetCurKF()
{
	return this->CurrentFrame;
}

void ModelGroup::goToNextKF()
{
	int NF = this->NextFrame;
	this->CurrentFrame = NF;
	if (NF+1 == TableSize) {
		NF = 0;
	}
	else {
		NF += 1;
	}
	this->NextFrame = NF;
	//std::cout << this->CurrentFrame << " current"
	
}

void ModelGroup::interpolation(float time)
{

	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(this->ModelT[this->CurrentFrame].getModelPosition()));

	glUniform1f(spLambert->u("time"), time);

	float* CF = ModelT[this->CurrentFrame].getVerticesLLD();
	float* NF = ModelT[this->NextFrame].getVerticesLLD();
	float* CFnormals = ModelT[this->CurrentFrame].getNormalsLLD();
	float* NFnormals = ModelT[this->NextFrame].getNormalsLLD();
	int VertexNumber = ModelT[this->CurrentFrame].getVertexCount();

	// vertex positions at current frame
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, CF);
	

	// vertex positions at next frame
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NF);



	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, CFnormals);
	

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, NFnormals);

	glDrawArrays(GL_TRIANGLES, 0, VertexNumber);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

}

