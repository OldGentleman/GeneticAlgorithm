#pragma once

#include <random>

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