#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class KnapsackProblem
{
    public:
    KnapsackProblem(int capacityOfPack, std::string pathToFile);
    ~KnapsackProblem();
    int getValue(int index);
    int getSize(int index);
    int getCapacityOfPack();
    int getGenoSize();

    private:
    void readFile(std::string pathToFile);
    std::vector<std::pair<int,int>> *items;
    int capacityOfPack;
    int numberOfElemPack;
};