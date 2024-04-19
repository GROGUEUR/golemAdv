/**
* \file type.h
* \brief programme gérant les fonctions pour les types
* \author Luka Cognard, Lenny Borry.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#ifndef TYPE_H
#define TYPE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#define TAILLE_NOM 25
#define TAILLE_EQUIP 4
#define NB_ARMES 2
#define NB_ATT 4
#define NB_INV_EQUIPEMENTS 36
#define NB_INV_ARMES 18
#define NB_INV_OBJETS 10
#define NB_TEAM_PERSOS 3
#define ALL_OBJETS 9
#define ALL_EQUIPEMENTS 30
#define ALL_ARMES 28

/** déclaration du type perso_t pour l'utiliser dans équipement_t et arme_t */
typedef struct perso_s perso_t;

/** déclaration du type scene pour différencier les events, affichage etc... */
typedef enum scene_s{MENUP=0,PLAYSAVE,PARAMETRE,CREDITS,CINEMDEB,OP,PAUSE,INVENTORY,EQUIPEMENT,STAT,FIGHT,CINEMEND,SHOP,SELL}scene_t;

/** déclaration des type de stuff entre multiplicateur et somme */
typedef enum typeStuff_s{CASQUE=0,PLASTRON,BOTTE,TALISMANT}typeStuff_t;

/** déclaration des type d'arme pour eviter qu'un mage est une épée par exemple */
typedef enum typeArmes_s{EPEE=0,ARC,BATON,CAILLOU}typeArmes_t;

typedef enum effet_s{SOIN=0,TAUX_CRIT,FOR,INT,DEF,RES,MANA,VIT,ATTAQUE}effet_t;

typedef enum type_att_s{PHY=0,MAG,STA,ERR}type_att_t;

/** déclaration du type equipement pour donner les stats aux stuff */
typedef struct equipement_s{
	char nom[TAILLE_NOM];
	char desc[100];
	typeStuff_t typeEquipement;
	/** numId est l'identifiant de l'objet pour pouvoir equiper le même objet plusieurs fois mais avec un id différent 
	* persoEquiper qui est un pointeur sur le personnage équiper avec cet objet
	*/
	int numId;
	perso_t* persoEquiper;
	float Pv;
	float Mana;
	float Def;
	float Res;
	float For;
	float Int;
	float Vit;
	SDL_Texture * artwork;
	/** valeur d'achat et diviser par 2 ça valeur de vente */
	int cout;
}equipement_t;

typedef struct attaque_s{
    char nom[TAILLE_NOM];
    type_att_t type_att;
    char desc[100];
    effet_t effet;
    int qte_effet;
    int duree_effet;
    int nb_cible;
    int precision;
    
}attaque_t;

typedef struct arme_s{
	char nom[TAILLE_NOM];
	char desc[100];
	/** numId est l'identifiant de l'objet pour pouvoir equiper le même objet plusieurs fois mais avec un id différent 
	* persoEquiper qui sera a 0 si il n'est pas équiper sinon 1 pour le 1er perso, 2 pour le 2ème et 3 pour le 3ème dans l'équipe
	*/
	int numId;
	perso_t* persoEquiper;
	typeArmes_t typeArme;
	attaque_t att;
	SDL_Texture * artwork;
	/** valeur d'achat et diviser par 2 ça valeur de vente */
	int cout;
}arme_t;

/** déclaration du type perso pour les stats, animation, etc... */
struct perso_s{
	char Nom[TAILLE_NOM];
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
	SDL_Texture* MarcheFront;
	SDL_Texture* MarcheBack;
	SDL_Texture* IdleAnim;
	SDL_Texture* AttAnim;
	equipement_t * stuff[TAILLE_EQUIP];
	arme_t * armes[NB_ARMES];
	attaque_t attaques[NB_ATT];

};

/** déclaration du type pnj pour leur texture dialogue etc */
typedef struct pnj_s{
	SDL_Texture* Dialogue[6];
	int NbDialogue;
}pnj_t;

typedef struct mob_s{
	char nom[TAILLE_NOM];
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
	SDL_Texture* IdleAnim;
	attaque_t attaques[NB_ATT];
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

/** déclaration inventaire_t servant a gérer les objets et équipement posséder par le joueur */
typedef struct inventaire_s{
	int nbObjActu;
	objet_t * sac[NB_INV_OBJETS];
	int nbEquActu;
	equipement_t * equipements[NB_INV_EQUIPEMENTS];
	int nbArmActu;
	arme_t * armes[NB_INV_ARMES];
	int bourse;
}inventaire_t;

/** déclaration team_t pour gérer l'équipe de personnage */
typedef struct team_s{
	int nbPerso;
	perso_t *team[NB_TEAM_PERSOS];
}team_t;

/** déclaration des fonction lier aux personnages (équiper un éqquipement/arme ou utiliser un objet, lvl up)*/
int creer_perso(perso_t *,char *, char *,SDL_Renderer*,float * statPerso);

void lvl_up(perso_t*,float * statPerso);
void aff_perso(perso_t perso);

void equiper_stuff(equipement_t* equipement, perso_t* perso);
int desequiper_stuff(int iStuff, perso_t* perso);
void utiliser_obj(inventaire_t *,perso_t *,int);

/** déclaration des fonction lier a l'équipe du joueur */
int join_team(team_t *,perso_t *);
void init_reinit__team(team_t *);

/** déclaration des fonction lier aux objets */
void creer_all_objet(objet_t *, SDL_Renderer* );

/** declaration fonction creer_attaque*/
attaque_t creer_attaque(char nom[TAILLE_NOM],type_att_t type_att, char desc[100], effet_t effet, int qte_effet, int duree_effet, int nb_cible, int precision);

/** déclaration des fonction lier aux équipements */
void creer_all_sprite_equipement(SDL_Texture* allSprite[ALL_EQUIPEMENTS], SDL_Renderer* ecran);
void creer_all_equipement(equipement_t allStuff[ALL_EQUIPEMENTS][3],SDL_Texture* allSprite[ALL_EQUIPEMENTS]);


/** déclaration des fonction lier a l'inventaire avec le sac d'objet, les équipements et les armes  */
void init_and_reinit_inv(inventaire_t * inv);
int jeter_obj(inventaire_t *,int );
int ajouter_obj(inventaire_t *,objet_t *,int );
int ajouter_stuff(equipement_t allStuff[ALL_EQUIPEMENTS][3],inventaire_t *,int iStuff);
int jeter_stuff(inventaire_t *Inv,int iStuff);

/**declaration des fonctions en rapport avec les armes et les attaques*/
void afficher_arme(arme_t* arme);
void creer_all_arme(arme_t armes[ALL_ARMES][3],SDL_Renderer* ecran);
void creer_all_att_arme(arme_t armes[ALL_ARMES][3]);
void equiper_arme(arme_t* arme, perso_t* perso);
int desequiper_arme(arme_t * arme, perso_t* perso);
int ajouter_arme(arme_t allArmes[ALL_ARMES][3],inventaire_t *inv,int indArm);
int jeter_arme(inventaire_t *Inv,arme_t* arme);

/** déclaration des fonction en rapport avec les mobs */
mob_t* creer_mob(char * nom,SDL_Renderer* ecran,int lvl);
#endif
