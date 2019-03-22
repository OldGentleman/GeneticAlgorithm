#include "Individual.h"
//#include "Randoms.h"

int getRandomIntI(int d1,int d2)
{
    return rand()%(d2+1) + d1;
};

double getRandomDoubleI(int d1,int d2)
{
    int accuracy=1000;
    int id1=(int)(d1*accuracy);
    int id2=(int)(d2*accuracy);
    int result=rand()%(id2+1) + id1;
    return (double)(result)/(double)(accuracy);
};

Individual::Individual(int genoSize)
{   
    this->genoSize=genoSize;
    genoType=std::vector<int>(genoSize);
    for(int i=0; i<genoSize; i++)
    {   
        genoType.at(i)=getRandomIntI(0,1);
    }
}

Individual::Individual(Individual* firstParent, Individual* secondParent, int patrition)
{
    genoType=std::vector<int>(0);
    genoSize=firstParent->genoSize;
    for(int i=0;i<genoSize;i++) genoType.push_back((i<patrition)?firstParent->genoType.at(i):secondParent->genoType.at(i));
}

Individual::Individual(Individual& other)
{
    genoType=other.getGenoType();
}

Individual::~Individual(){}

int Individual::fitness(KnapsackProblem* item)
{
    int valueItems=0;
    int sizeItems=0;
    for(int i=0;i<genoSize;i++)
    {
        valueItems+=item->getValue(i)*genoType.at(i);
        sizeItems+=item->getSize(i)*genoType.at(i);
    }
    return (sizeItems<=item->getCapacityOfPack())?valueItems:0;
}

int Individual::getCapacity(KnapsackProblem* item)
{
    int sizeItems=0;
    for(int i=0;i<genoSize;i++)
    {
        sizeItems+=item->getSize(i)*genoType.at(i);
    }
    return sizeItems;
}

void Individual::mutation(double chance)
{
    for(int i=0;i<genoSize;i++)
    {
        if(getRandomDoubleI(0.0,1.0)<chance) genoType.at(i)= genoType.at(i)==1 ? 0 : 1;
    }
}
std::vector<Individual*> Individual::cross(Individual* parent,double chance)
{
    std::vector<Individual*> result(0);
    if(getRandomDoubleI(0.0,0.1)<chance)
    {
        int patrition=getRandomIntI(1,genoSize-1);
        result.push_back(new Individual(this,parent,patrition));
        result.push_back(new Individual(parent,this,patrition));
    }
    else{
        result.push_back(new Individual(*this));
        result.push_back(new Individual(*parent));
    }
    return result;
}

std::vector<int> Individual::getGenoType()
{
    return genoType;
}

std::string Individual::toString()
{
    std::string strVec;
	for (int i=0;i<genoSize;i++) strVec += std::to_string(genoType.at(i));
	return strVec;

}

void Individual::printGenoType()
{
    std::cout<<this->toString()<<std::endl;
}