#include "ClassImg.h"

ClassImg::ClassImg(const char* fileName)
{
    boost::gil::rgb8_image_t image;
    boost::gil::read_image(fileName, image, boost::gil::jpeg_tag());
    auto imgView = view(image);
    for (int i = 0; i < nodeSize; i++)
        for (int j = 0; j < nodeSize; j++)
            m_matrix[i][j] = imgView[i * 10 + j][0];
}

void ClassImg::calc()
{
    calcCenterVec();
    // Need delta from base class
    calcBinMatrix();
    calcEtalonVec();
}

int16_t ClassImg::getRadius()
{
    return radius;
}

void ClassImg::calcNearClass(ClassImg* first, ClassImg* second)
{
    int distance1 = 0;
    int distance2 = 0;

    for (int i = 0; i < nodeSize; i++)
    {
        if (m_etalonVec[i] != first->m_etalonVec[i])
            distance1 += 1;
        if (m_etalonVec[i] != second->m_etalonVec[i])
            distance2 += 1;
    }
    nearClass = ((distance1 < distance2) ? first : second);
}

void ClassImg::calcRadius()
{
    int k1 = 0, k2 = 0, k3 = 0, k4 = 0;
    std::vector<double> kfeTmp(50);
    double d1b = 0.;
    int dXp = 0., dYp = 0.;

    for (int jRad = 0; jRad < nodeSize; jRad++)
    {
        k1 = 0;
        k3 = 0;
        for (int i = 0; i < nodeSize; i++)
        {
            dXp = m_matrix[i][0] - m_centerVec[0];
            dYp = m_matrix[i][1] - m_centerVec[0];
            if (std::sqrt(std::pow(dXp, 2) + std::pow(dYp, 2)) <= jRad)
            {
                ++k1;
            }

            dXp = nearClass->m_matrix[i][0] - m_centerVec[0];
            dYp = nearClass->m_matrix[i][1] - m_centerVec[0];
            if (std::sqrt(std::pow(dXp, 2) + std::pow(dYp, 2)) <= jRad)
            {
                ++k3;
            }
        }

        

        k2 = nodeSize - k1;
        k4 = nodeSize - k3;

        d1 = static_cast<double>(k1) / nodeSize;
        beta = static_cast<double>(k3) / nodeSize;
        d1b = d1 - beta;
        kfeTmp[jRad] = d1b * log10((1 + d1b + 0.1) / (1 - d1b + 0.1)) / log10(2);
    }

    for (int i = 0; i < nodeSize; i++)
    {
        std::cout << i << "    " << kfeTmp[i] << std::endl;
        
        if (kfe < kfeTmp[i])
        {
            kfe = kfeTmp[i];
            radius = i;
        }
    }
}