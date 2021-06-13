#include "ImgRecognition.h"

ImgRecognition::ImgRecognition() 
{
	
}

void ImgRecognition::initImage(const char* fileName)
{
    boost::gil::read_image(fileName, m_image, boost::gil::jpeg_tag());
}

void ImgRecognition::initParams()
{
    // Multiple of nodeSize
    m_height = m_image.height() - (m_image.height() % nodeSize);
    m_width = m_image.width() - (m_image.width() % nodeSize);

    // Resize Nodes
    m_nodes.resize(m_height / nodeSize);
    for (auto& it : m_nodes)
        it.resize(m_width / nodeSize);

    // Resize Result Indexes
    m_resultIndexes.resize(m_height / nodeSize);
    for (auto& it : m_nodes)
        it.resize(m_width / nodeSize);

    // Resize Delta Range
    m_resultIndexes.resize(2); // 2 = lower and upper limits of range
    for (auto& it : m_nodes)
        it.resize(m_width / nodeSize);
}

void ImgRecognition::initNodes()
{
    int16_t nodesSizeHor = m_nodes.size();
    int16_t nodesSizeVer = m_nodes[0].size();

    std::vector<std::vector<int16_t>> tmp(nodeSize, std::vector<int16_t>(nodeSize));
    auto imgView = view(m_image);
    
    for (int i = 0; i < nodesSizeHor; i++)
    {
        for (int j = 0; j < nodesSizeVer; j++)
        {
            for (int k = 0; k < nodeSize; k++)
            {
                for (int t = 0; t < nodeSize; t++)
                {
                    tmp[k][t] = imgView[i * nodeSize * + k * m_width + j * nodeSize + t][0];
                }
            }
            m_nodes[i][j] = tmp;
        }
    }
}

void ImgRecognition::initClases(const char* baseFileName, const char* fileName1, const char* fileName2)
{
    BaseClassImg* base = new BaseClassImg(baseFileName);
    base->calc();
    setDefDelta(base->getDelta());
    m_classes.push_back(static_cast<ClassImg>(*base));

    ClassImg* c1 = new ClassImg(fileName1);
    c1->setDelta(m_deltaRange);
    c1->calc();
    m_classes.push_back(*c1);

    ClassImg* c2 = new ClassImg(fileName2);
    c2->setDelta(m_deltaRange);
    c2->calc();
    m_classes.push_back(*c2);
}

void ImgRecognition::setDefDelta(const std::vector<std::vector<int16_t>>& newDelta)
{
    m_deltaRange = newDelta;
}

void ImgRecognition::calcNearClasses()
{
    m_classes[0].calcNearClass(&m_classes[1], &m_classes[2]);
    m_classes[1].calcNearClass(&m_classes[0], &m_classes[2]);
    m_classes[2].calcNearClass(&m_classes[0], &m_classes[1]);
}

void ImgRecognition::calcRadiusClasses()
{
    for (auto& el : m_classes)
        el.calcRadius();
}

void ImgRecognition::exam()
{
    int dist = 0;
    float max = 0.;
    float percent[3] = { 0. };
    for (int it = 0; it < 10; it++)
    {
        for (int jt = 0; jt < 10; jt++)
        {
            max = 0.;
            for (int i = 0; i < m_classes.size(); i++)
            {
                m_nodes[it][jt].setDelta(m_deltaRange);
                m_nodes[it][jt].calc();
                dist = calcDist(m_nodes[it][jt].getEtalonVec(), m_classes[i].getEtalonVec());
                percent[i] = (1. - dist / static_cast<float>(m_classes[i].getRadius())) * 100;
            }
            for (int i = 0; i < m_classes.size(); i++)
            {
                if (max < percent[i])
                {
                    max = percent[i];
                    m_nodes[it][jt].setIndex(i);
                }
            }
        }
    }
}

void ImgRecognition::printResultFile()
{
    std::ofstream fo("result.txt");
    if (fo.is_open())
    {
        for (auto& it : m_nodes)
        {
            for (auto& jt : it)
            {
                fo << std::to_string( jt.getIndex()) << " ";
            }
            fo << std::endl;
        }
    }
    else
    {
        std::cerr << "Error write data";
        system("pause");
        exit(1);
    }
    fo.close();
}

std::vector<ClassImg> ImgRecognition::getClasses()
{
    return m_classes;
}

ImgRecognition::~ImgRecognition()
{
    
}

int ImgRecognition::calcDist(const std::vector<int16_t>& etalonVecL, const std::vector<int16_t>& etalonVecR)
{
    int tmp = 0;
    for (int i = 0; i < nodeSize; i++)
        if (etalonVecL[i] != etalonVecR[i])
            tmp++;
    return tmp;
}
