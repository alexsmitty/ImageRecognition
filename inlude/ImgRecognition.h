#pragma once
#include "ClassImg.h"
#include "NodeImg.h"
#include "BaseClassImg.h"
#include "Constans.h"
#include "stdafx.h"

class ImgRecognition
{
public:
	ImgRecognition();
	void initImage(const char* fileName);
	void initParams();
	void initNodes();
	void initClases(const char* fileName1, const char* fileName2, const char* fileName3);
	void setDefDelta(const std::vector<std::vector<int16_t>>& m_deltaRange);
	void calcNearClasses();
	void calcRadiusClasses(); 
	void exam();
	void printResultFile();
	std::vector<ClassImg> getClasses();
	~ImgRecognition();
private:
	boost::gil::rgb8_image_t m_image;
	int16_t m_height = 0;
	int16_t m_width = 0;
	std::vector<ClassImg> m_classes;
	std::vector<std::vector<int16_t>> m_resultIndexes;
	std::vector<std::vector<int16_t>> m_deltaRange;
	int** originalMatrix = nullptr;
	std::vector<std::vector<NodeImg>> m_nodes;
	int calcDist(const std::vector<int16_t>& etalonVecL, const std::vector<int16_t>& etalonVecR);
};

