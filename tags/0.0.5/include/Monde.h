#ifndef MONDE_H
#define MONDE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <math.h>
#include <vector>

using namespace std;

#include "Individus.h"
#include "Item.h"


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

        int nbIndividus;
        int nbItems;

    protected:
    private:
        double sizeX;
        double sizeY;
        double stepXY;
};

#endif // MONDE_H
