#include <iostream>
#include <time.h> 

#include "GeneticAlgorithm.h"

int main() 
{
    
    srand (time(NULL));//random seed
	std::cout<<"Start"<<std::endl;

    int sizeOfPopl=100;
    double cross=0.6;
    double mutat=0.1;
    int capacityOfPack=20;
    std::string path="D:\\Projects\\C++\\lab4\\lib\\kpitems.txt";
    GeneticAlgorithm ga(sizeOfPopl,cross,mutat,capacityOfPack,path);
    int iterations=100;
    ga.run(iterations);
    ga.showBest();

    std::cout<<"end"<<std::endl;
      
    return 0;
}