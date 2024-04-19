/**
* \file EventOp.h
* \brief programme gérant les fonctions des évènements
* \author Luka Cognard.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#ifndef EVENTOP_H
#define EVENTOP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "type.h"
#include "texture.h"
#include "../lib/fmap.h"
#include "../lib/fpnj.h"
#include "../lib/fmobs.h"
#include "../lib/fbibliotheque.h"

/**
* déclaration des fonctions DetectEvents pour les sets d'évènement possible selon la scene
*/
void transitionFondu(SDL_Renderer* renderer, int largeur_ecran, int hauteur_ecran, int duree);
void chargement(scene_t * scene, SDL_Renderer* pRenderer,scene_t futurScene);
void cinematic_start(SDL_Renderer* pRenderer,int * next,SDL_Rect * P1,SDL_Rect * P2,SDL_Rect * P3,SDL_Rect * P4, scene_t * scene,SDL_Texture ** storyP1,SDL_Texture ** storyP2,SDL_Texture ** storyP3,SDL_Texture ** storyP4,int *skipOn,SDL_Texture ** Map1,SDL_Texture ** Map2,SDL_Texture ** Map3,SDL_Texture ** Map4,SDL_Texture ** Map5,SDL_Texture ** Map6,int colli[125][250]);
void chargement_barre_pv(int ,SDL_Texture** , SDL_Texture** ,SDL_Renderer*);
void DetectEventsOp(int*, int* , int* ,scene_t*,int,int,int*,int*,int*);
void DetectEventsInvSac(int *useOk, int *yonUse,int *yonThrow,int *MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect destThrowButton);
void DetectEventsStats(int *numPage,int *MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect* destStatAction,team_t * team,float Stats[3][8]);
void DetectEventsInvStuff(int *yonThrow,int* MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect destThrowButton,int *numPage,int* numPagePerso,int* slot,int*);

/**
* déclaration des fonctions ReactEvents pour les sets d'évènement possible selon la scene
*/
void ReactEventsOp(int *,int,int,int*,SDL_Renderer* ,SDL_Texture*,SDL_Rect marcheHori[3][8],SDL_Rect* ,int*,int,int,team_t,int biome,int,int*,int[125][250],SDL_Texture * vendeurDialoTexture[5],int * map,SDL_Rect* savedest,int numperso);

void ReactEventsInvSac(int *useOk, int *yonUse,int *yonThrow,int MouseClick, int KeyIsPressed,int MouseOver,SDL_Renderer* pRenderer,int w,int h,inventaire_t*,SDL_Rect *destThrowButton, perso_t ** team);

void ReactEventsStats(int numPage,int MouseClick, int KeyIsPressed,int MouseOver,SDL_Renderer* pRenderer,int w,int h,team_t * team,float Stats[3][8],SDL_Rect * destStatAction);

void ReactEventsInvStuff(int *,int ,int ,SDL_Renderer* ,int ,int ,inventaire_t* ,SDL_Rect *,team_t * ,int ,int,int,int*);

void EventShop(int *MouseOver,int *Action,SDL_Renderer* pRenderer,int biome,equipement_t allStuff[ALL_EQUIPEMENTS][3],inventaire_t* inv,int w,int h,scene_t* scene,objet_t allPot[ALL_OBJETS],int*,arme_t armes[ALL_ARMES][3]);
void EventSell(int *MouseOver,int *MouseClick,int *Action,SDL_Renderer* pRenderer,inventaire_t* inv,int w,int h,scene_t* scene,int *numPage);
int achat_possible(int choiceBiy,int biome,inventaire_t * inv,objet_t allPot[ALL_OBJETS],equipement_t allStuff[ALL_EQUIPEMENTS][3],arme_t armes[ALL_ARMES][3]);
#endif

