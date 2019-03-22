#pragma once

#include "Individual.h"

class GeneticAlgorithm
{
    public:
    GeneticAlgorithm(int sizeOfPopulation,double crossProb,double mutationProb,int capacityOfPack, std::string pathToFile);
    ~GeneticAlgorithm();
    void run(int numberOfIter);
    Individual* getBest();
    void showBest();

    private:
    void clearPopulation();
    Individual* getRandomBestInd();
    void createPopulation();
    void sortingIncreaseOfPopulation(std::vector<Individual*>& population);
    void changeOnBestHalf(std::vector<Individual*>& population);
    
    std::vector<Individual*> population;
    int sizeOfPopulation;
    double crossProb;
    double mutationProb;
    KnapsackProblem *kp;
    int genoSize;
};