#pragma once
#include "ClassImg.h"
class BaseClassImg : public ClassImg
{
public:
	BaseClassImg(){}
	BaseClassImg(const char* fileName) : ClassImg(fileName) {}
	void calc();
	std::vector<std::vector<int16_t>> getDelta();
	~BaseClassImg() {}
	void calcDelta();
};
