#ifndef TYPE_H
#define TYPE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#define TAILLE_EQUIP 6

typedef enum scene_s{MENUP=0,PLAYSAVE,PARAMETRE,CREDITS,CINEMDEB,OP,PAUSE,INVENTORY,EQUIPEMENT,STAT,FIGHT,CINEMEND}scene_t;

typedef enum typeStuff_s{BASE,TALISMANT}typeStuff_t;

typedef struct equipement_s{
	typeStuff_t typeEquipement;
	float Pv;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
}equipement_t;

typedef struct perso_s{
	char Nom[20];
	char Classe[20];
	int lvl;
	int Xplvl;
	int Xp;
	float PvMax;
	float Pv;
	float ManaMax;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
	SDL_Texture* MarcheHori;
	SDL_Texture* MarcheVert;
	SDL_Texture* IdleAnim;
	SDL_Texture* AttAnim;
	equipement_t * stuff[TAILLE_EQUIP];
}perso_t;

typedef struct pnj_s{
	SDL_Texture* TexturePnj;
	SDL_Texture* TextureDial;
	int NbDialogue;
	SDL_Rect Dialogue[6];
}pnj_t;

int creer_perso(perso_t *,char *, char *,SDL_Renderer*);

#endif
