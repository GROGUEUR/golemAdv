#ifndef TYPE_H
#define TYPE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#define TAILLE_EQUIP 4
#define NB_ARMES 2
#define NB_ATT 4

/** déclaration du type scene pour différencier les events, affichage etc... */
typedef enum scene_s{MENUP=0,PLAYSAVE,PARAMETRE,CREDITS,CINEMDEB,OP,PAUSE,INVENTORY,EQUIPEMENT,STAT,FIGHT,CINEMEND}scene_t;

/** déclaration des type de stuff entre multiplicateur et somme */
typedef enum typeStuff_s{CASQUE=0,PLASTRON,BOTTE,TALISMANT}typeStuff_t;

typedef enum effet_s{SOIN=0,TAUX_CRIT,FOR,INT,DEF,RES,MANA,VIT,ATTAQUE}effet_t;

/** déclaration du type equipement pour donner les stats aux stuff */
typedef struct equipement_s{
	char nom[20];
	char desc[100];
	typeStuff_t typeEquipement;
	float Pv;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
}equipement_t;

typedef struct attaque_s{
    char nom[20];
    char type_att[3];
    char desc[100];
    effet_t effet;
    float qte_effet;
    int duree_effet;
    int nb_cible;
    int precision;
    
}attaque_t;

typedef struct arme_s{
	char nom[20];
	char desc[100];
	attaque_t att;
	SDL_Texture * artwork;
}arme_t;

/** déclaration du type perso pour les stats, animation, etc... */
typedef struct perso_s{
	char Nom[20];
	char Classe[20];
	int lvl;
	int Xplvl;
	int Xp;
	int PtComp;
	float PvMax;
	float Pv;
	float ManaMax;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
	float Vit;
	SDL_Texture* MarcheHori;
	SDL_Texture* MarcheVert;
	SDL_Texture* IdleAnim;
	SDL_Texture* AttAnim;
	equipement_t * stuff[TAILLE_EQUIP];
	arme_t * armes[NB_ARMES];
	attaque_t * attaques[NB_ATT];

}perso_t;

/** déclaration du type pnj pour leur texture dialogue etc */
typedef struct pnj_s{
	SDL_Texture* TexturePnj;
	SDL_Texture* TextureDial;
	int NbDialogue;
	SDL_Rect Dialogue[6];
}pnj_t;

typedef struct mob_s{
	char nom[20];
	int lvl;
	int Xp_don;
	float PvMax;
	float Pv;
	float ManaMax;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
	float Vit;
	SDL_Texture* MarcheHori;
	SDL_Texture* MarcheVert;
	SDL_Texture* IdleAnim;
	SDL_Texture* AttAnim;
	attaque_t * attaques[NB_ATT];
}mob_t;

/** déclaration objet_t qui seront les potions et objets utilisable */
typedef struct objet_s{
	char nom[13];
	char desc[100];
	float valPv;
	float valMp;
	int cout;
	SDL_Texture* sprite;
}objet_t;

typedef struct inventaire_s{
	objet_t * sac[10];
	equipement_t * stuff[36];
}inventaire_t;

/** déclaration des fonction par rapport aux personnage et objet */

int creer_perso(perso_t *,char *, char *,SDL_Renderer*);
int charger_perso(perso_t*,SDL_Renderer*,char*,char*,int,int,int,int,float,float,float,float,float,float,float,float,float,char*,char*,char*,char*);
void lvl_up(perso_t*);
void creer_all_objet(objet_t *, SDL_Renderer* );
void utiliser_obj(objet_t *,perso_t *);
/*int creer_mob(mob_t *,char *,SDL_Renderer*,int);*/
#endif
