#pragma once
#include "NodeImg.h"


class ClassImg : public NodeImg
{
public:
	ClassImg() {}
	ClassImg(const char* fileName);
	void calc();
	int16_t getRadius();
	void calcNearClass(ClassImg* first, ClassImg* second);
	void calcRadius();
	virtual ~ClassImg() {}
protected:
	int16_t radius = 0;
	double d1 = .0;
	double beta = .0;
	double kfe = .0;
	ClassImg* nearClass = nullptr;
};
