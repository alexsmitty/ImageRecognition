#include "BaseClassImg.h"

void BaseClassImg::calc()
{
	calcCenterVec();
	calcDelta();
	calcBinMatrix();
	calcEtalonVec();
}

std::vector<std::vector<int16_t>> BaseClassImg::getDelta()
{
    return m_delta;
}

void BaseClassImg::calcDelta()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < nodeSize; j++)
        {
            if (i == 0)
                m_delta[i][j] = m_centerVec[j] - 10;
            else
                m_delta[i][j] = m_centerVec[j] + 10;
        }
    }
}
