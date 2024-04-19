/**
* \file fmap.h
* \brief programme gérant les fonctions pour la Map
* \author François Lépine.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 780

SDL_Surface* loadTileset(const char* filename);
int saveSurfaceAsPNG(SDL_Surface* surface, const char* filename);
int charger_map(char * CARTE_LIGNE,char * CARTE_TXT,char * nom_carte, int tab[125][250]);
int afficher_map(int coordo_x,int coordo_y,SDL_Renderer* renderer,SDL_Texture*);
