#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <stdio.h>  //inclusion pour le printf
#include <vector>

#include <iostream>
#include <string>

#include "include/Monde.h"
#include "include/Evolution.h"
#include "include/Individus.h"
#include "include/Item.h"

#include "include/BinaryConverter.h"

#define M_PI  3.14159265358979323846

using namespace std;

// prototype de main
void Dessiner();
void initGL();
void testsUnit();

// Declaration de globales
double angleZ = 0;
double angleX = 0;
Monde myMonde;
Individus myIndividus;
Individus tousIndividus[100];
Item myItem;
Evolution myEvolution;


bool play = true;


int camMode = 0;

int main(int argc, char *argv[]) {

    SDL_Event event;
    initGL();
    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;

    myMonde.createIndividus(5);
    myMonde.createItems(20);


    myMonde.saveIndividus("fichiertest.txt");
    myMonde.loadIndividus("fichiertest.txt");

    // evolution
    myEvolution.setIndividus(myMonde.individus);
    myEvolution.createNewGeneration();
    myMonde.individus.clear();
    myMonde.individus = myEvolution.newGenerationIndividus;

    myMonde.saveIndividus("apres_evolution.txt");


    while(1)
    {
        start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                   switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                            myMonde.individus[0].angle +=10;
                        break;
                        case SDLK_RIGHT:
                            myMonde.individus[0].angle -=10;
                        break;
                        case SDLK_UP:
                            if (camMode < 4) {
                                camMode++;
                            } else {
                                camMode = 0;
                            }
                        break;
                        case SDLK_DOWN:
                            if (play) {
                                play = false;
                            } else {
                                play = true;
                            }
                        break;
                    }

                break;
                case SDL_KEYUP:
                break;
                case SDL_QUIT:
                    exit(0);
                break;
                }
            }

        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;

  //    angleZ += 0.05 * ellapsed_time;
  //    angleX += 0.05 * ellapsed_time;


        if (play) {
            Dessiner();
        }
        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 10)
        {
            SDL_Delay(10 - ellapsed_time);

        } else {
            printf("time: %d \n", (10 - ellapsed_time));
        }




    }

    return 0;
}


void Dessiner()
{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );

        //gluLookAt(100,100,100, 0,0,0, 0,0,1);

                double lang;
                double lx ;
                double ly;

        switch(camMode) {
            case 0:
                gluLookAt(200,200,200, 0,0,0, 0,0,1);
            break;
            case 1:
                gluLookAt(1,1,900, 0,0,0, 0,0,1);
            break;
            case 2:
                gluLookAt(100,100,100, 0,0,0, 0,0,1);
            break;
            case 3:
                 lang = myMonde.individus[0].angle;
                 lx = myMonde.individus[0].x;
                 ly = myMonde.individus[0].y;

                gluLookAt(lx,ly,100, 0,0,0, 0,0,1);

            break;
            case 4:
                 lang = myMonde.individus[0].angle;
                 lx = myMonde.individus[0].x;
                 ly = myMonde.individus[0].y;

                gluLookAt(lx,ly,100, lx + 20 * cos(lang / 180 * M_PI), ly + 20 *  sin(lang / 180 * M_PI), 1 , 0,0,1);
            break;

        }
        //gluLookAt(200,200,200, 0,0,0, 0,0,1);

        //gluLookAt(1,1,900, 0,0,0, 0,0,1);

        myMonde.draw();
        myMonde.checkEat();
        myMonde.respawnItems();
        //myItem.draw();

        //double dist = myMonde.calculDistance(&myIndividus, &myItem);

        //printf("distance : %8f \n", dist);



      //  myIndividus.avance(0.1);

    glFlush();
    SDL_GL_SwapBuffers();
}


void initGL()
{
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)800/600,1,1000);

	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
}


/***************************
* TESTS UNITAIRES
***************************/


void testsUnit() {

    // Partie debug LOAD/EXPORT BRAIN.
    myMonde.createIndividus(1);
    myMonde.createItems(1);

    printf("Avant lexport:\n");
    myMonde.individus[0].brain.drawBrainConsole();      //Render matrice

    vector<int> poids = myMonde.individus[0].brain.exportVectorPoids(); // export matrice

    myMonde.individus[0].brain.initRandomPoids();       // random poids

    myMonde.individus[0].brain.importVectorPoids(poids);    // load poids

    printf("\n\n\nApres Le Load:\n");
    myMonde.individus[0].brain.drawBrainConsole();      // render matrice


    string strPoids="";

    strPoids = myMonde.individus[0].brain.exportStringVector(poids, 8); // exmport de la chaine
    printf("La chaine de carractere fait: %d\n\n", strPoids.size());


    myMonde.individus[0].brain.initRandomPoids(); // random poids
    printf("avant le importStringVect\n");

    // cout<<strPoids<<endl;

    vector<int> ttmp = myMonde.individus[0].brain.importStringVector(strPoids, 8);

    BinaryConverter bin;
    bin.printBinary(ttmp);

    printf("loaded matrice\n");
    myMonde.individus[0].brain.importVectorPoids(ttmp);    // load poids
    myMonde.individus[0].brain.drawBrainConsole();      // render matrice


   // printf("%s", strPoids);
    //cout<<strPoids<<endl;

    //* test de normalisation
    /*
    printf("\nAvant le normalize:\n");
    BinaryConverter bin;
    vector<bool> test = bin.toBinaryConvert(255);
    bin.printBinary(test);


    printf("\nApres le normalize:\n");
    vector<bool> test2 = bin.normalizeBinary(test, 10);
    bin.printBinary(test2);
    */


}
