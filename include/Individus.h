#ifndef INDIVIDUS_H
#define INDIVIDUS_H



#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <math.h>
#include <vector>

#include "Item.h"
#include "BinaryConverter.h"
#include "PerceptronBrain.h"

using namespace std;

class Individus
{
    public:

        PerceptronBrain brain;

        vector<bool> frontalSensor; // capteur a l'avant: 001000
        vector<bool> motors;    // moteur 000 000 premier 3bits moteur gauche 3 derniers bits moteur droite

        double x;
        double y;
        double angle;

        int eaten;

        Individus();
        virtual ~Individus();
        void draw();
        void drawFrontalSensor();

        void avance(double vitesse);
        void tourneDroite(double vitesse);
        void tourneGauche(double vitesse);

        void moove();

        void deplacementMotors();

        void deplacementAleatoire();
        void logicalBrainMoove();

        void neuronalBrainMoove();

        void updateFrontalSensor(vector<Item> items);

        void eat();

    protected:
    private:

};

#endif // INDIVIDUS_H
