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

void DetectEventsFight(int * menu_combat, int* MouseClick,int *MouseOver, int* quit, int* perso, scene_t* scene,int w,int h,int * W, int * H);
void ReactEventsFight(int *p, int perso, int MouseClick,int MouseOver,int menu_combat ,SDL_Renderer* pRenderer,SDL_Texture* fond_combat,int w,int h,inventaire_t* inv,team_t * team, mob_t ** mobs,int H, int W);
mob_t * mob_creer(char nom[TAILLE_NOM],int lvl,int Xp_don,float PvMax,float Pv,float ManaMax,float Mana,float Def,float Res,float For,float Int,float Vit,SDL_Texture* MarcheHori,SDL_Texture* MarcheVert,SDL_Texture* IdleAnim,SDL_Texture* AttAnim,attaque_t * attaques[NB_ATT]);
#endif
