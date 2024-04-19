/**
* \file utils.h
* \brief programme gérant les fonctions pour les sauvegardes et l'entrer du pseudo du joueur.
* \author Warrick Bonga.
* \version 1.9.8
* \date 16 Avril 2024.
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../lib/type.h"
#include "../lib/texture.h"
#include "../lib/fmap.h"

#define WINDOW_WIDTH 1360
#define WINDOW_HEIGHT 780

#define LETTER_WIDTH 20
#define LETTER_HEIGHT 50

void entrerLettre(SDL_Event event, char * name, int * indice,  SDL_Color color, int * quit);
char * entrerNom(SDL_Renderer * renderer);
void sauvegarder(int nb_save, int idMap, int x, int y, team_t team, inventaire_t inv, int lorePos, objet_t allPot[ALL_OBJETS], equipement_t allStuff[ALL_EQUIPEMENTS][3], arme_t allArmes[ALL_ARMES][3], SDL_Renderer * renderer,SDL_Texture * Map, SDL_Rect dest);
void chargerSave(int nb_save, int *idMap, int *x, int *y, team_t * team, inventaire_t * inv,int *lorePos, objet_t allPot[ALL_OBJETS], equipement_t allStuff[ALL_EQUIPEMENTS][3], perso_t allPerso[NB_TEAM_PERSOS], arme_t allArmes[ALL_ARMES][3], float stats[NB_TEAM_PERSOS][8], SDL_Renderer * renderer);
void nouvelleSave(int nb_save, char * nom);
