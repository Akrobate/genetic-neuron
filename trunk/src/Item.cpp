#include "../include/Item.h"

Item::Item()
{
    this->size = 8;
    this->x=0;
    this->y=0;
    this->angle = 0;
}

Item::~Item()
{
    //dtor
}


void Item::positionAleatoire(double xmax,double  ymax, double xmin, double ymin) {
    this->x = (rand()%(int)(xmax - xmin)) -xmax;
    this->y = (rand()%(int)(ymax - xmin)) -xmax;



}

void Item::draw()
{
    double height_max = 3.3;
    double height_min = 2.2;
    static bool grossi = true;


    static double height = 3;
    double altitude = 0.5;
    glPushMatrix();

    if (grossi) {
        if (height < height_max) {
            height += 0.0005;
        } else {
            grossi = false;
        }
    } else {
        if (height > height_min) {
            height -= 0.0005;
        } else {
            grossi = true;
        }
    }




    if (this->angle < 360) {
        this->angle += 3;
    } else {
        this->angle = 0;
    }


    glTranslated(this->x, this->y, 0);

    glRotated(this->angle, 0, 0, 1);
    glScaled(this->size, this->size, this->size);
    glBegin(GL_LINES);
       glColor3ub(200,200,0);
        //dessin base
        glVertex3d( -1, -1, altitude + (height/2) );
        glVertex3d(-1, 1, altitude + (height/2) );

        glVertex3d( -1, 1, altitude + (height/2) );
        glVertex3d(1, 1, altitude + (height/2) );

        glVertex3d( 1, 1, altitude + (height/2) );
        glVertex3d(1, -1, altitude + (height/2) );

        glVertex3d( 1, -1, altitude + (height/2) );
        glVertex3d(-1, -1, altitude + (height/2) );

        // pyramide du haut
        glVertex3d( 1, 1, altitude + (height/2) );
        glVertex3d(0, 0, altitude + height );

        glVertex3d( 1, -1, altitude + (height/2) );
        glVertex3d(0, 0,  altitude + height);

        glVertex3d( -1, -1, altitude + (height/2) );
        glVertex3d(0, 0, altitude + height );

        glVertex3d( -1, 1, altitude + (height/2) );
        glVertex3d(0, 0, altitude + height );

        // pyramide du bas
        glVertex3d( 1, 1, altitude + (height/2)  );
        glVertex3d(0, 0, altitude  );

        glVertex3d( 1, -1, altitude + (height/2) );
        glVertex3d(0, 0, altitude  );

        glVertex3d( -1, -1,altitude + (height/2) );
        glVertex3d(0, 0, altitude   );

        glVertex3d( -1, 1, altitude + (height/2) );
        glVertex3d(0, 0, altitude );

    glEnd();
    glPopMatrix();
}
