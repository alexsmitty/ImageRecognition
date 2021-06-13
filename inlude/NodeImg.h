#include "stdafx.h"
#include "Constans.h"
#pragma once
class ClassImg;

class NodeImg
{
public:
	NodeImg() : m_etalonVec(nodeSize), m_centerVec(nodeSize)
		,m_matrix(nodeSize, std::vector<int16_t>(nodeSize))
		,m_binMatrix(nodeSize, std::vector<int16_t>(nodeSize))
		, m_delta(2, std::vector<int16_t>(nodeSize))
	{}
	NodeImg(const std::vector<std::vector<int16_t>>& newMatrix);
	std::vector<int16_t> getEtalonVec();
	std::vector<int16_t> getCenterVec();
	std::vector<std::vector<int16_t>> getBinMatrix();
	std::vector<std::vector<int16_t>> getMatrix();
	void setDelta(const std::vector<std::vector<int16_t>> &newDelta);
	void setIndex(int16_t newIndex);
	void setMatrix(std::vector<std::vector<int16_t>> newMatrix);
	int16_t getIndex();
	void calc();
	virtual ~NodeImg() {}
protected:
	int16_t index = 0;
	std::vector<std::vector<int16_t>> m_matrix;
	std::vector<std::vector<int16_t>> m_binMatrix;
	std::vector<std::vector<int16_t>> m_delta;
	std::vector<int16_t> m_etalonVec;
	std::vector<int16_t> m_centerVec;
	void calcBinMatrix();
	void calcEtalonVec();
	void calcCenterVec();
};
