#include "GeneticAlgorithm.h"
//#include "Randoms.h"

int getRandomInt(int d1,int d2)
{
    return rand()%(d2+1) + d1;
};

double getRandomDouble(int d1,int d2)
{
    int accuracy=1000;
    int id1=(int)(d1*accuracy);
    int id2=(int)(d2*accuracy);
    int result=rand()%(id2+1) + id1;
    return (double)(result)/(double)(accuracy);
};

GeneticAlgorithm::GeneticAlgorithm(int sizeOfPopulation,double crossProb,double mutationProb,int capacityOfPack, std::string pathToFile)
{
    this->sizeOfPopulation=sizeOfPopulation;
    this->crossProb=crossProb;
    this->mutationProb=mutationProb;
    kp=new KnapsackProblem(capacityOfPack,pathToFile);
    genoSize=kp->getGenoSize();
    population=std::vector<Individual*>();
    createPopulation();
}
GeneticAlgorithm::~GeneticAlgorithm()
{
   clearPopulation();
   delete kp;
}

void GeneticAlgorithm::run(int numberOfIter)
{
    if(numberOfIter<=0)
    {
        //std::cout<<"Wrong number of iteration"<<std::endl;
        return;
    }
    std::vector<Individual*> newPopulation=std::vector<Individual*>();
    while(newPopulation.size()<=(unsigned)sizeOfPopulation)
    {
        //get 2 random
        Individual* fp=getRandomBestInd();
        Individual* sp=getRandomBestInd();
        //children
        std::vector<Individual*> children=fp->cross(sp,crossProb);
        //children mutation
        children.at(0)->mutation(mutationProb);
        children.at(1)->mutation(mutationProb);

        newPopulation.push_back(children.at(0));
        newPopulation.push_back(children.at(1));
    }
    //?
    clearPopulation();
    changeOnBestHalf(newPopulation);
    sizeOfPopulation=newPopulation.size();
    population=newPopulation;
    run(numberOfIter-1);
}




void GeneticAlgorithm::changeOnBestHalf(std::vector<Individual*>& population)
{
    sortingIncreaseOfPopulation(population);
    for( int ii=0; (unsigned)ii<population.size()/2; ii++)
    {
        *population.at(population.size()/2+ii)=*population.at(ii);
    }    

}

void GeneticAlgorithm::sortingIncreaseOfPopulation(std::vector<Individual*>& population){
    int ii, jj;
     for(ii=0; (unsigned)ii<population.size()-1; ii++)
        for(jj=0; (unsigned)jj<population.size()-ii-1; jj++)
            if (population.at(jj)->fitness(kp)<population.at(jj+1)->fitness(kp))
            {
                Individual* temp=new Individual(1);
                *temp=*population.at(jj);
                *population.at(jj)=*population.at(jj+1);
                *population.at(jj+1)=*temp;
                delete temp;
            }   
}

Individual* GeneticAlgorithm::getBest()
{
    Individual* bestIndv=population.at(0);
    int bestFitness=bestIndv->fitness(kp);

    for(int i=1;i<sizeOfPopulation;i++)
    {
        if(bestFitness<population.at(i)->fitness(kp))
        {
            bestFitness=population.at(i)->fitness(kp);
            bestIndv=population.at(i);
        }
    }
    return bestIndv;
}

void GeneticAlgorithm::showBest()
{
    Individual* best=getBest();
    best->printGenoType();
    std::cout<<"The fitness: "<<best->fitness(kp)<<std::endl;
    std::cout<<"Taken capacity: "<<best->getCapacity(kp)<<" of "<<kp->getCapacityOfPack()<<std::endl;
}

Individual* GeneticAlgorithm::getRandomBestInd()
{
    Individual* first=population.at(getRandomInt(0,sizeOfPopulation-1));
    Individual* second=population.at(getRandomInt(0,sizeOfPopulation-1));
    if(first->fitness(kp)>=second->fitness(kp)) return first;
    else return second;
}

void GeneticAlgorithm::createPopulation()
{
    for(int i=0;i<sizeOfPopulation;i++) population.push_back(new Individual(genoSize));
}

void GeneticAlgorithm::clearPopulation()
{
    for(Individual* i : population) delete i;
}