/**
* \file fbibliotheque.h
* \brief programme gérant la Map de la bibliotheque
* \author François Lépine.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "../lib/fmap.h"

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 780

int charger_map_biblio(char * CARTE_LIGNE,char * CARTE_TXT,char * nom_carte, int tab[125][250]);
int charger_map_pnj_biblio(char * PNJ_LIGNE,char * PNJ_TXT,char * MAP,char * nom_carte,int collisions[125][250]);