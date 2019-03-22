#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(int capacityOfPack,std::string pathToFile)
{
    this->capacityOfPack=capacityOfPack;
    items=new std::vector<std::pair<int,int>>;
    readFile(pathToFile);
}

KnapsackProblem::~KnapsackProblem()
{
    delete[] items;
}

int KnapsackProblem::getValue(int index)
{
    return items->at(index).first;
}

int KnapsackProblem::getSize(int index)
{
    return items->at(index).second;
}

int KnapsackProblem::getCapacityOfPack()
{
    return capacityOfPack;
}

int KnapsackProblem::getGenoSize()
{
    return numberOfElemPack;
}

void KnapsackProblem::readFile(std::string pathToFile)
{
    std::ifstream fileIn(pathToFile);
	int countElem = 0;
	if (!fileIn.is_open()) {
		std::cout << "Can't open a file" << std::endl;
		return;
	}
	else {
		int value;
        int size;
		
		while (!fileIn.eof()) {
			fileIn >> value;
		    fileIn >> size;
			items->push_back(std::make_pair(value,size));
			countElem++;
		}
	}
	fileIn.close();
	numberOfElemPack = countElem;
}