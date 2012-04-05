#include "../include/Monde.h"




Monde::Monde() {
    //ctor
    this->sizeX = 1000;
    this->sizeY = 1000;
    this->stepXY = 20;


    this->generation = 1;
    this->filepath = "data/";


}

Monde::~Monde() {
    //dtor
}


void Monde::checkEat() {

    //penser a implementer le compteur de bouffe
    for (int i =0; i < this->individus.size(); i++) {
        for (int j = 0; j < this->items.size(); j++) {
            double dist = this->calculDistance(&this->individus[i], &this->items[j]);
            if (dist < this->items[j].size) {
                this->items.erase(this->items.begin() + j);

                this->individus[i].eaten++;

            }
        }
    }



}

void Monde::respawnItems() {
    int actualsize = this->items.size();
    if (actualsize < this->nbItems) {
        Item item;
        item.positionAleatoire( this->sizeX / 2 , this->sizeY/2, -this->sizeX / 2, -this->sizeY / 2);
        this->items.push_back(item);
    }
}


double Monde::calculDistance(Individus * individus, Item * item) {
    double x;
    double y;
    double dist;
    x = individus->x - item->x;
    y = individus->y - item->y;
    dist = sqrt((x*x) + (y*y));
    return dist;
}

void Monde::createIndividus(int nbr) {
    this->nbIndividus = nbr;
    for (int i=0; i<nbr; i++) {
        Individus ind;
        this->individus.push_back(ind);

    }
}

void Monde::createItems(int nbr) {
    this->nbItems = nbr;
    for (int i=0; i<nbr; i++) {
        Item item;
        item.positionAleatoire( this->sizeX / 2 , this->sizeY/2, -this->sizeX / 2, -this->sizeY / 2);
        this->items.push_back(item);
    }
}


void Monde::saveIndividus(string filename) {

    string path = this->filepath;
    string filenamePath = path+filename;


    char *nomFichier = const_cast<char*>(filenamePath.c_str());

    ofstream fichier(nomFichier, ios::out | ios::trunc);
    if (fichier) {
        // On ecrit le numero de la generation
        fichier << "GENERATION: " << this->generation << endl;

        // On ecrit le nombre d'individus
        fichier << "INDIVIDUS: " << this->individus.size() << endl;

        // On ecrit le nombre d'items dans le monde
        fichier << "ITEMS: " << this->items.size() << endl;

        // On calcule puis on ecrit le score total des individus
        int scoreTotal = 0;
        for (int i = 0; i < this->individus.size(); i++) {
            scoreTotal += this->individus[i].eaten;
        }
        fichier << "SCORETOTAL: " << scoreTotal << endl;

        // on ecrit les scores de chaqu'un des individus
        fichier << "[INDIVIDUS_SCORES]" << endl;
        for (int i = 0; i < this->individus.size(); i++) {
            fichier << this->individus[i].eaten << ' ';
        }
        fichier << endl;
        fichier << "[/INDIVIDUS_SCORES]" << endl;

        // on ecrit chaque individus
        fichier << "[INDIVIDUS]" << endl;
        for (int i = 0; i < this->individus.size(); i++) {
            fichier << this->individus[i].brain.exportStringBrain(8) << endl;
        }
        fichier << "[/INDIVIDUS]" << endl;

        fichier << "FILEEND" << endl;




        fichier.close();
    }


}


bool Monde::loadLastGeneration(string generationName) {

    string filetotest = this->filepath + generationName + "-";

    string filetoload;
    bool next = true;
    int generation = 0;
    ostringstream oss;



    while (next) {
        generation++;

        ostringstream oss;
        oss << generation;
        string filetotest2 = filetotest + oss.str() + ".txt";

        cout << filetotest2 << endl;



        char *nomFichier = const_cast<char*>(filetotest2.c_str());
        FILE* fp = NULL;

        fp = fopen( nomFichier, "rb" );
        if( fp != NULL ) {

            fclose( fp );
            filetoload = generationName + "-" + oss.str() + ".txt";
        } else {
            next = false;

        }

    }


    cout << "Fichier sera charge:" << filetoload << endl;

    if (!filetoload.empty()) {
        this->loadIndividus(filetoload);
        return true;
    } else {
        return false;
    }
}






void Monde::loadIndividus(string filename) {

    string path = this->filepath;
    string filenamePath = path+filename;

    // On réinitialise le monde
    this->individus.clear();
    this->items.clear();

    this->nbIndividus = 0;
    this->nbItems = 0;

    char *nomFichier = const_cast<char*>(filenamePath.c_str());

    ifstream fichier(nomFichier, ios::in);
    if (fichier) {
        string usefull;


          while(!fichier.eof()) {
                fichier >> usefull;
                // std::cout << usefull << "\n"; // DEBUG

                // On set le numero de la generation
                if (usefull.compare("GENERATION:") == 0) {
                    int nbGenerations;
                    fichier >> nbGenerations;
                    this->generation = nbGenerations;
                }

                // Creation du bon nombre d'Items
                if (usefull.compare("ITEMS:") == 0) {
                    int nbItems;
                    fichier >> nbItems;
                    this->createItems(nbItems);
                }


                // Creation et chargement d'individus
                if (usefull.compare("[INDIVIDUS]") == 0) {

                    string localUsefull = "0";
                    while  (localUsefull.compare("[/INDIVIDUS]") != 0 ) {
                        if (localUsefull.compare("0") == 0) {
                            fichier >> localUsefull;
                        } else {
                            // crea individus
                            // std::cout << localUsefull << "\n"; // DEBUG

                            Individus ind;
                            ind.brain.importStringBrain(localUsefull, 8);
                            this->individus.push_back(ind);
                            this->nbIndividus = this->individus.size();

                            fichier >> localUsefull;

                        }

                    }

                }

            }
       fichier.close();
    }
}





void Monde::draw() {
    this->drawTerrain();

    for(int i=0; i < this->individus.size(); i++) {
        this->individus[i].draw();
        this->individus[i].moove();

        this->individus[i].updateFrontalSensor(this->items);

    }

    for(int i=0; i < this->items.size(); i++) {
        this->items[i].draw();
    }
}


void Monde::drawTerrain() {

    glPushMatrix();
    glTranslated(- this->sizeX / 2, - this->sizeY / 2 , 0);
    glBegin(GL_LINES);
    glColor3ub(100,0,0);

    for (int x=0; x <= this->sizeX; x = x + this->stepXY) {
        glVertex3d(x,0,0);
        glVertex3d(x,this->sizeY,0);
    }

    for (int y=0; y <= this->sizeY; y = y + this->stepXY) {
        glVertex3d(0,y,0);
        glVertex3d(this->sizeX, y,0);
    }


    glEnd();
    glPopMatrix();
}

