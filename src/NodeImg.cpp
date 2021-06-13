#include "NodeImg.h"

NodeImg::NodeImg(const std::vector<std::vector<int16_t>>& newMatrix) : m_etalonVec(nodeSize), m_centerVec(nodeSize)
, m_matrix(nodeSize, std::vector<int16_t>(nodeSize))
, m_binMatrix(nodeSize, std::vector<int16_t>(nodeSize))
, m_delta(2, std::vector<int16_t>(nodeSize))
{
	m_matrix = newMatrix;
}

std::vector<int16_t> NodeImg::getEtalonVec() 
{
	return m_etalonVec;
}

std::vector<int16_t> NodeImg::getCenterVec() 
{
    return m_centerVec;
}

std::vector<std::vector<int16_t>> NodeImg::getBinMatrix() 
{
    return m_binMatrix;
}

std::vector<std::vector<int16_t>> NodeImg::getMatrix() 
{
    return m_matrix;
}

void NodeImg::setDelta(const std::vector<std::vector<int16_t>>& newDelta)
{
	m_delta = newDelta;
}

void NodeImg::setIndex(int16_t newIndex)
{
    index = newIndex;
}

void NodeImg::setMatrix(std::vector<std::vector<int16_t>> newMatrix)
{
    m_matrix = newMatrix;
}

int16_t NodeImg::getIndex()
{
    return index;
}

void NodeImg::calc()
{
	calcCenterVec();
    // Need delta from base class
    calcBinMatrix();
	calcEtalonVec();
}

void NodeImg::calcBinMatrix()
{
    for (int i = 0; i < nodeSize; i++)
    {
        for (int j = 0; j < nodeSize; j++)
        {
            if (m_matrix[i][j] >= m_delta[0][j] && m_matrix[i][j] <= m_delta[1][j])
                m_binMatrix[i][j] = 1;
            else
                m_binMatrix[i][j] = 0;
        }
    }
}

void NodeImg::calcEtalonVec()
{
    int counter = 0;
    for (int i = 0; i < nodeSize; i++)
    {
        counter = 0;
        for (int j = 0; j < nodeSize; j++)
        {
            if (m_binMatrix[j][i] == 1)
                ++counter;
        }
        if (counter > 25)
            m_etalonVec[i] = 1;
        else
            m_etalonVec[i] = 0;
    }
}

void NodeImg::calcCenterVec()
{
    int sum = 0;
    for (int i = 0; i < nodeSize; i++)
    {
        sum = 0;
        for (int j = 0; j < nodeSize; j++)
            sum += m_matrix[j][i];
        m_centerVec[i] = sum / nodeSize;
    }

}
