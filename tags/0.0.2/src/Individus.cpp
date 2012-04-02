#include "../include/Individus.h"

#define M_PI  3.14159265358979323846


Individus::Individus()
{
//ctor
    this->x = 0;
    this->y = 0;
    this->angle = 0;

    this->eaten = 0;

    // 6 etant le nombre de sensors
    this->frontalSensor.assign(6,0);

    // 6 etant le nombre de neuroes de sortie de deplacement 3 par moteur encodage 8bits
    this->motors.assign(6,0);

    // Positionnement aléatoire de l'individus
    if (1) {
        this->x = 500 - rand()%1000;
        this->y = 500 - rand()%1000;

        this->angle = rand()%360;
    }


    // Initialisation aléatoire du moteur
    if (1) {
        this->motors[0] = rand()%2;
        this->motors[1] = rand()%2;
        this->motors[2] = rand()%2;

        this->motors[3] = rand()%2;
        this->motors[4] = rand()%2;
        this->motors[5] = rand()%2;
    }



}

Individus::~Individus()
{
    //dtor
}

void Individus::avance(double vitesse) {

    double xn = this->x + (cos(this->angle * M_PI / 180) * vitesse);
    double yn = this->y + (sin(this->angle * M_PI / 180) * vitesse);

    this->x = xn;
    this->y = yn;

    if (xn > 500) {
        this->x *= -1;
        this->x += 20;
    }

    if ( xn < -500) {
        this->x *= -1;
        this->x -= 20;
    }


    if (yn < -500) {
        this->y *= -1;
        this->y -= 20;
    }

    if (yn > 500) {
        this->y *= -1;
        this->y += 20;
    }



}

void Individus::tourneDroite(double vitesse) {
    this->angle -= vitesse;

    this->avance(vitesse / 4);


}

void Individus::tourneGauche(double vitesse) {
    this->angle += vitesse;

    this->avance(vitesse / 4);
}


void Individus::deplacementAleatoire() {

    switch (rand()%3) {
        case 1:
            this->avance( ((double)(rand()%1000)) / 1000 ) ;
        break;
        case 2:
            this->tourneDroite( ((double)(rand()%1000))  / 100);
        break;
        case 0:
            this->tourneGauche( ((double)(rand()%1000))  / 100);
        break;
    }



}

void Individus::moove() {

    // this->logicalBrainMoove();
    // this->deplacementAleatoire();
    // this->avance(0.8);
    // this->tourneGauche(0.1);
    this->deplacementMotors();


}


void Individus::deplacementMotors() {

    vector<bool> rightMotor;
    vector<bool> leftMotor;

    int vitesseRightMotor;
    int vitesseLeftMotor;
    int tourneAmplitude;

    for(int i = 0; i < this->motors.size(); i++) {
        if (i < (this->motors.size() / 2)) {
            rightMotor.push_back(this->motors[i]);
        } else {
            leftMotor.push_back(this->motors[i]);
        }
    }

    BinaryConverter bin;
    vitesseLeftMotor = bin.toDecimalConvert(leftMotor);
    vitesseRightMotor = bin.toDecimalConvert(rightMotor);

    if (vitesseLeftMotor > vitesseRightMotor) {
        tourneAmplitude = vitesseLeftMotor - vitesseRightMotor;
        this->tourneDroite(tourneAmplitude);
        this->avance(vitesseRightMotor);
    } else {
        tourneAmplitude = vitesseRightMotor - vitesseLeftMotor;
        this->tourneGauche(tourneAmplitude);
        this->avance(vitesseLeftMotor);
    }
    // printf ("mLeft : %d / mRight : %d \n", vitesseLeftMotor , vitesseRightMotor );
}

/*

101010101010101010101010101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010101010101010101010101010


101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010
101010101010101010101010101010101010101010101010



*/



void Individus::logicalBrainMoove() {

    int sSize = this->frontalSensor.size();
    int r = -1;

    for (int i=0; i<sSize; i++) {
        if (this->frontalSensor[i]==true) {
            r = i;
        }
    }

    switch (r) {
        case 0:
            this->tourneGauche(7);
        break;
        case 1:
            this->tourneGauche(3);
        break;
        case 2:
            this->tourneGauche(0.5);
        break;
        case 3:
            this->tourneDroite(0.5);
        break;
        case 4:
            this->tourneDroite(3);
        break;
        case 5:
            this->tourneDroite(7);
        break;
    }

   // this->avance(1 + ((double)(this->eaten) / 1));
   this->avance(1);

}






void Individus::draw() {

    double height = 1.5;
    glPushMatrix();

    glTranslated(this->x, this->y, 0);

    if (this->angle >= 360) {
        this->angle = 0;
    }

    if (this->angle < 0) {
        this->angle += 360;
    }



    glRotated(this->angle - 180, 0, 0, 1);
    glScaled(10,10,10);
    glBegin(GL_LINES);
       glColor3ub(0,200,0);
        glVertex3d( -2, 0, 1);
        glVertex3d(1, 1, 1);

        glVertex3d(1, 1, 1);
        glVertex3d( 1,-1, 1);

        glVertex3d( 1,-1, 1);
        glVertex3d( -2, 0, 1);

        glVertex3d( -2, 0, 1);
        glVertex3d( 0, 0, height);

        glVertex3d(1, 1, 1);
        glVertex3d(0, 0, height);

        glVertex3d( 1,-1, 1);
        glVertex3d( 0, 0, height);
    glEnd();

    // Positionnement du moniteur Sensor
    glRotated(90, 0,0,1);
    glTranslated(-0.75,-1,1);
    glScaled(0.25,0.25,0.25);
    this->drawFrontalSensor();


    glPopMatrix();

}

void Individus::drawFrontalSensor() {
       int sSize = this->frontalSensor.size();

        glBegin(GL_QUADS);
            for (int i = 0; i < sSize; i++) {
                if (this->frontalSensor[i]) {
                    glColor3ub(0,200,0);
                } else {
                    glColor3ub(200,0,0);
                }
                glVertex3d( 0+i, 0, 0);
                glVertex3d(1+i, 0, 0);
                glVertex3d(1+i, 1, 0);
                glVertex3d(0+i, 1, 0);
        }
        glEnd();
}


void Individus::updateFrontalSensor(vector<Item> items) {

        double tmp = 0;
        double x;
        double y;
        double dist;

        int firstParcours = true;

        double minDist = 0;
        int keyLePlusProche = 0;
        bool visible = false;

        double angleR = -1;


        for (int i=0; i < items.size(); i++) {
            x = this->x - items[i].x;
            y = this->y - items[i].y;
            dist = sqrt((x*x) + (y*y)); // 1. Calcul toutes les distances
            if (firstParcours) {
                minDist = dist;
                firstParcours = false;
            }

            // 2. Trouve le plus proche
                // 2.1 Determine si visible
                double _angle = (atan2(this->x - items[i].x , this->y - items[i].y) / M_PI *180) + 180;
                double _angleR = (_angle + this->angle) ;

                if (_angleR > 360) {
                    _angleR -= 360;
                }
                _angleR -= 90;

                // Visibilité entre -90 et 90
                if ((_angleR < 90) && (_angleR > -90)) {
                  if (dist <= minDist) {
                      minDist = dist;
                      keyLePlusProche = i;
                      visible = true;
                      angleR = _angleR;
                  }
                }

        }

    // 3. Stoque la data dans le sensor
    angleR += 90;      // variation entre 0 et180°
    int step = 0;

    int sSize = this->frontalSensor.size();
    step = (int) ((180) / sSize );

    //printf ("step: %d \n", step);

    if (visible) {
        for (int i =0; i<sSize; i++) {
            if ((angleR > (step*i)) && (angleR <= (step * (i+1) ) ) ) {
                this->frontalSensor[i] = 1;
            } else {
                this->frontalSensor[i] = 0;
            }
        }
    } else {
        for (int i =0; i<sSize; i++) {
            this->frontalSensor[i] = 0;
        }
    }
   //this->frontalSensor
}
