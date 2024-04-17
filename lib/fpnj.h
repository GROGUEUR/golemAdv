/**
* \file fpnj.h
* \brief programme gérant les pnj sur la Map
* \author François Lépine.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int charger_map_pnj(char * PNJ_LIGNE,char * PNJ_TXT,char * MAP,char * nom_carte,int collisions[125][250]);
