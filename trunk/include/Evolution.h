#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <vector>
#include <math.h>
#include "Individus.h"



class Evolution
{
    public:
        Evolution();
        virtual ~Evolution();
        vector<Individus> individus;

        vector<int> parents;
        vector<Individus> children;

        // mutation indice est un indice sur 100 correspondant au pourcentage de mutation a appliquer
        int mutationIndice;


        vector<Individus> newGenerationIndividus;



        vector<int> select2Individus();

        void createNewGeneration();

        vector<Individus> croisement2Individus(vector<Individus> parents);

        vector<Individus> croisement2points(vector<Individus> parents);
        vector<Individus> croisement3points(vector<Individus> parents);

        Individus mutation(Individus indiv);

        // Setters
        void setIndividus(vector <Individus> individus);



    protected:
    private:
};

#endif // EVOLUTION_H
