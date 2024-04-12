#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "../lib/EventOp.h"
#include "../lib/init_menu.h"



SDL_Surface* loadTileset(const char* filename);
int saveSurfaceAsPNG(SDL_Surface* surface, const char* filename);
int * charger_map(char * CARTE_LIGNE,char * CARTE_TXT,char * nom_carte);
int afficher_map(int coordo_x,int coordo_y,SDL_Renderer* renderer,char * MAP);