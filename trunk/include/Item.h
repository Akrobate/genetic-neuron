#ifndef ITEM_H
#define ITEM_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <math.h>



class Item
{
    public:

        double x;
        double y;

        double size;

        Item();
        virtual ~Item();
        void draw();
        void positionAleatoire(double xmax,double  ymax,double  xmin,double ymin);
    protected:
    private:
        double angle;
};

#endif // ITEM_H
