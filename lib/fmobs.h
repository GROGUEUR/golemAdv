/**
* \file fmobs.c
* \brief programme gérant les fonctions pour les mobs sur la Map
* \author François Lépine.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int copie_fichier_mob_txt(char * fichier_mob_origine,char* fichier_mob_destination);
int charger_map_mobs(char * MOBS_LIGNE,char * MOBS_TXT,char * MOBS_TXT2,char * MAP,int collisions[125][250]);
int detruire_mob(int coordo_x_mob_suppr,int coordo_y_mob_suppr,char * MOBS_TXT,int collisions[125][250]);
