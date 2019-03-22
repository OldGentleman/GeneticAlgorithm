#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream> 

#include "KnapsackProblem.h"
class Individual
{
    public:
    Individual(int genoSize);
    Individual(Individual* firstParent, Individual* secondParent, int patrition);
    Individual(Individual& copy);
    ~Individual();

    int fitness(KnapsackProblem* items);
    int getCapacity(KnapsackProblem* items);

    void mutation(double chance);
    std::vector<Individual*> cross(Individual* parent, double chance);

    std::vector<int> getGenoType();
    std::string toString();
    void printGenoType();
    
    private:
    std::vector<int> genoType;
    int genoSize;
};