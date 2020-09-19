#include "ModelGroup.h"

ModelGroup::ModelGroup(int Tsize, std::string& dirName, std::string& KfName, float x, float y, float z) {
	this->dirName = dirName;
	this->KfName = KfName;
	this->TableSize = Tsize;
	this->CurrentFrame = 0;

	for (int i = 0; i < Tsize; i++)
	{
		std::cout << this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj" << std::endl;
		this->ModelT.push_back(ModelCtrl(0, 0, 0));
		this->ModelT[i].loadModel(this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj");
	}
		
}

void ModelGroup::Draw()
{
	this->ModelT[CurrentFrame].Draw();
}

int ModelGroup::GetCurKF()
{
	return this->CurrentFrame;
}

void ModelGroup::goToNextKF()
{
	this->CurrentFrame += 1;
	if (this->CurrentFrame >= TableSize) this->CurrentFrame = 0;
}

