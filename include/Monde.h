#ifndef MONDE_H
#define MONDE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <math.h>
#include <vector>

#include <iostream>
#include <string>
#include <fstream>

#include "Individus.h"
#include "Item.h"

using namespace std;

class Monde
{
    public:
        Monde();

        virtual ~Monde();
        void draw();
        void drawTerrain();
        void checkEat();

        void respawnItems();
        void createIndividus(int nbr);
        void createItems(int nbr);

        double calculDistance(Individus * individus, Item * item);
        vector<Individus> individus;
        vector<Item> items;


        void saveIndividus(string filename);
        void loadIndividus(string filename);


        int nbIndividus;
        int nbItems;

    protected:
    private:
        double sizeX;
        double sizeY;
        double stepXY;
        int generation;
        int duration;
};

#endif // MONDE_H
