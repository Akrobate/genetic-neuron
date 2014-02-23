#include "../include/Evolution.h"

Evolution::Evolution(){
    //ctor
    this->mutationIndice = 10;
}

Evolution::~Evolution(){
    //dtor
}

void Evolution::setIndividus(vector <Individus> individus) {
    this->individus = individus;
    this->countIndividus = individus.size();
}

vector<int> Evolution::select2Individus() {
    vector<int> eaten;
    vector<int> wheel;

    vector<Individus> choisen;

    int choisen1;
    int choisen2;

    eaten.assign(this->individus.size(), 0);

    for(int i = 0; i < this->individus.size(); i ++) {
        eaten[i] = this->individus[i].eaten + 1;
    }

    wheel.assign(eaten.size(), 0);

    int total = 0;
    for (int i = 0; i < eaten.size(); i ++) {
        total += eaten[i];
        wheel[i] = total;
    }

    // total est le nombre de points total récolés (+1 pour tous)

    // Choix du premier Individus choisen1
    int choice = rand() % total;
    for (int i = 0; i < wheel.size(); i++) {
        if (i != 0) {
            if ( (wheel[i-1] < choice) && (wheel[i] >= choice)) {
                choisen1 = i;
            }
        } else {
            if (wheel[i] >= choice ) {
                choisen1 = i;
            }
        }
    }


    // Choix du deuxieme Individus (different du premier)
    bool choisen2found = false;
    while(!choisen2found) {
        choice = rand() % total;
        for (int i = 0; i < wheel.size(); i++) {
            if (i != 0) {
                if ( (wheel[i-1] < choice) && (wheel[i] >= choice)) {
                    if (choisen1 != i) {
                        choisen2 = i;
                        choisen2found = true;
                    }
                }
            } else {
                if (wheel[i] >= choice ) {
                    if (choisen1 != i) {
                        choisen2 = i;
                        choisen2found = true;
                    }
                }
            }
        }
    }

    vector<int> result;
    result.push_back(choisen1);
    result.push_back(choisen2);

    return result;

}


vector<Individus> Evolution::croisement2Individus(vector<Individus> parents) {
    // croisement est une alternance entre croisement 2 et 3 points
    if ((rand()%2) == 1) {
        return this->croisement2points(parents);
    } else {
        return this->croisement3points(parents);
    }
}


vector<Individus> Evolution::croisement2points(vector<Individus> parents) {

    string brain1 = parents[0].brain.exportStringBrain(8);
    string brain2 = parents[1].brain.exportStringBrain(8);

    string childbrain1;
    string childbrain2;

    Individus child1;
    Individus child2;

    vector<Individus> result;

    int brainSize = brain1.size();

    int point1 = 0;
    int point2 = 0;

    while ((point1 > point2 ) || (point1 == point2) || (point1 == 0)) {
        point1 = rand()%brainSize;
        point2 = rand()%brainSize;
    }

    for (int i = 0; i < brainSize; i++) {
        if ((i < point1) || (i >= point2))  {
            childbrain1.push_back( brain1[i] );
            childbrain2.push_back( brain2[i] );
        }

        if ((i >= point1) && (i < point2)) {
            childbrain1.push_back( brain2[i] );
            childbrain2.push_back( brain1[i] );
        }
    }

    child1.brain.importStringBrain(childbrain1, 8);
    child2.brain.importStringBrain(childbrain2, 8);

    result.push_back(child1);
    result.push_back(child2);

    return result;
}


vector<Individus> Evolution::croisement3points(vector<Individus> parents) {

   string brain1 = parents[0].brain.exportStringBrain(8);
    string brain2 = parents[1].brain.exportStringBrain(8);

    string childbrain1;
    string childbrain2;

    Individus child1;
    Individus child2;

    vector<Individus> result;

    int brainSize = brain1.size();

    int point1=0;
    int point2=0;
    int point3=0;

    while ((point1 > point2 ) || (point2 > point3) || (point1 == point2) || (point1 == 0) || (point3 == point2) ) {
        point1 = rand()%brainSize;
        point2 = rand()%brainSize;
        point3 = rand()%brainSize;
    }

    for (int i = 0; i < brainSize; i++) {
        if ((i < point1) || ((i >= point2) && (i < point3) ))  {
            childbrain1.push_back( brain1[i] );
            childbrain2.push_back( brain2[i] );
        }

        if ( ((i >= point1) && (i < point2)) || (i >= point3)) {
            childbrain1.push_back( brain2[i] );
            childbrain2.push_back( brain1[i] );
        }
    }

    child1.brain.importStringBrain(childbrain1, 8);
    child2.brain.importStringBrain(childbrain2, 8);

    result.push_back(child1);
    result.push_back(child2);

    return result;


}

Individus Evolution::mutation(Individus indiv) {

    string brain = indiv.brain.exportStringBrain(8);
    int brainSize = brain.size();
    Individus result;

    int genamuter = rand()%brainSize;

    if (brain[genamuter] == '1') {
        brain[genamuter] = '0';
    } else {
        brain[genamuter] = '1';
    }
    result.brain.importStringBrain(brain, 8);
    return result;
}


void Evolution::createNewGeneration() {

    // Principe general:
    // On garde 50% de la population (meilleurs individus)
    // On a 50% de nouveaux individus (enfants)

    vector<int> selectedIds;
    vector<Individus> children;
    vector<Individus> parents;

    // creation des children
    for (int i = 0; i < (this->countIndividus / 4); i++) {

        selectedIds = this->select2Individus();
        parents.push_back(this->individus[selectedIds[0]]);
        parents.push_back(this->individus[selectedIds[1]]);

        children = this->croisement2Individus(parents);
        this->children.push_back( children[0] );
        this->children.push_back( children[1] );

        children.clear();
        parents.clear();

    }


    int _max;
    int _lastMax;
    int _maxid;

    vector<Individus> localInd;
    localInd = this->individus;

    // creation de la nouvelle generation avec les individus concerves
    for (int i = 0; i < (this->countIndividus / 2); i++) {
        for (int j=0; j < localInd.size(); j++) {
            if (j==0) {
                _max = localInd[j].eaten;
                _maxid = j;
            } else {
                if (localInd[j].eaten >= _max) {
                    _max = localInd[j].eaten;
                    _maxid = j;
                }
            }
        }

        // On ajoute le meilleur individus
        this->newGenerationIndividus.push_back ( localInd[_maxid] );

        // On exclut le meilleur individus de la liste restante
        localInd.erase (localInd.begin() + _maxid);

        _max = 0;
        _maxid = 0;


    }

    // On concatene la nouvelle generation avec les enfants
    for (int i = 0; i < this->children.size(); i++) {
        if ((rand() % this->mutationIndice) == 0) {     // mutation des enfant en tenant compte de l'indice
           this->newGenerationIndividus.push_back(this->mutation(this->children[i]));
        } else {
            this->newGenerationIndividus.push_back(this->children[i]);
        }

    }

    // Nouvelle generation crée.
}




