/**
* \file utils.h
* \brief programme gérant le menu d'entrer de nom
* \author Warrick Bonga.
* \version 1.9.5
* \date 12 Avril 2024.
*/

#include <stdio.h>
#include <string.h>
#include "../lib/texture.h"
#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 780

#define LETTER_WIDTH 20
#define LETTER_HEIGHT 50

void entrerLettre(SDL_Event event, char * name, int * indice,  SDL_Color color, int * quit);
char * entrerNom(SDL_Renderer * renderer);
void sauvegarder(int nb_save, perso_t * perso1, perso_t * perso2, perso_t * perso3);
void chargerSave(int nb_save, perso_t * perso1, perso_t * perso2, perso_t * perso3);
void ecraserSave();
