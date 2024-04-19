/**
* \file init_menu.h
* \brief programme gérant les fonctions pour les menu
* \author Warrick Bonga.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "type.h"
#include "texture.h"
#include "fmap.h"

/** Dimensions de la fenêtre */
#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 780

/** Constante de sortie vide */
#define NOTHING -1

/** Constantes de sortie du menu de l'écran-titre (menu principal) */
#define PLAY 1
#define SETTINGS 2
#define GAMECREDITS 3

/** Constantes de sortie des menus Play, Settings et Credits */
#define BACK 0
#define SAVE1 10
#define SAVE2 20
#define SAVE3 30
#define LOAD 2
#define NEWGAME 1
#define ERASE 3

/** Constantes de sortie du menu de pause */
#define SAVE 1
#define SQUIT 2
#define OPTIONS 3
#define RESUME 4

/** Structure pour stocker les informations sur une image */
typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
} Image;

/** Fonctions des menus */
int menuPrincipal(SDL_Renderer *renderer);
int menuPlay(SDL_Renderer *renderer);
int menuSettings(SDL_Renderer *renderer);
int menuCredits(SDL_Renderer *renderer);
int menuPause(SDL_Renderer *renderer, scene_t * scene, SDL_Texture * map,SDL_Rect);
