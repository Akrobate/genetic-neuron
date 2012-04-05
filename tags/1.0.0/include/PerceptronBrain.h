#ifndef PERCEPTRONBRAIN_H
#define PERCEPTRONBRAIN_H


#include <cstdlib>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>

#include "BinaryConverter.h"


using namespace std;

class PerceptronBrain
{
    public:

        vector<vector <int> > poids;
        vector<bool> in;
        vector<bool> out;

        PerceptronBrain();
        virtual ~PerceptronBrain();
        void initRandomPoids();
        void think();
        void drawBrainConsole();

        vector<int> exportVectorPoids();
        void importVectorPoids(vector<int> import);

        vector<int> importStringVector(string import, int normValue);
        string exportStringVector(vector<int> vect, int normValue);

        string exportStringBrain(int normValue);
        void importStringBrain(string import, int normValue);


    protected:
    private:
        int nbIn;
        int nbOut;
};

#endif // PERCEPTRONBRAIN_H
