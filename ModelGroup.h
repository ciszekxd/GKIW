#pragma once
#include "ModelCtrl.h"
#include <string>
class ModelGroup
{
public:
	std::string dirName;
	std::string KfName;
	int TableSize;
	int CurrentFrame;
	std::vector<ModelCtrl> ModelT;
	ModelGroup( int, std::string&,  std::string&, float = 0, float = 0, float = 0 );
	void Draw();
	int GetCurKF();
	void goToNextKF();
};

