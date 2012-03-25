#include "../include/Monde.h"




Monde::Monde() {
    //ctor
    this->sizeX = 1000;
    this->sizeY = 1000;
    this->stepXY = 20;
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

