/**
* \file combat.h
* \brief programme gérant les combats.
* \author Lenny Borry.
* \version 1.9.5
* \date 16 Avril 2024.
*/
#ifndef COMBAT_H
#define COMBAT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "type.h"
#include "texture.h"

void DetectEventsFight(int * menu_combat, int* MouseClick,int *MouseOver, int* quit, int* perso,int* obj, scene_t* scene,int w,int h,int * W, int * H,int* att);
void ReactEventsFight(int *p, int perso,int obj, int MouseClick,int MouseOver,int* menu_combat ,SDL_Renderer* pRenderer,SDL_Texture* fond_combat,int w,int h,inventaire_t* inv,team_t * team, int imob,int H, int W,int att,float statPerso[3][8],scene_t * scene,int* pvMob);
void fin_combat(int vict,mob_t * mob,inventaire_t * inv,team_t* team,float statPerso[3][8],scene_t * scene,int* click,int* over);

int degats_mob(mob_t* mob,attaque_t att,perso_t* perso);
int degats_perso(perso_t* perso,attaque_t att,mob_t* mob);

#endif
