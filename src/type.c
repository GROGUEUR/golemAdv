/**
* \file type.c
* \brief programme gérant les types
* \author Luka Cognard, Lenny Borry.
* \version 1.9.5
* \date 12 Avril 2024.
*/

#include "../lib/type.h"
#include "../lib/texture.h"
#include <stdio.h>
#include <string.h>

attaque_t creer_attaque(char nom[TAILLE_NOM],type_att_t type_att, char desc[100], effet_t effet, int qte_effet, int duree_effet, int nb_cible, int precision){
	attaque_t attaque;
	strcpy(attaque.nom,nom);
	attaque.type_att = type_att;
	strcpy(attaque.desc,desc);
	attaque.effet = effet;
	attaque.qte_effet = qte_effet;
	attaque.duree_effet = duree_effet;
	attaque.nb_cible = nb_cible;
	attaque.precision = precision;
	return attaque;
}

/** fonction créer un perso renvoie NULL si la création n'as pas fonctionner */
int creer_perso(perso_t * perso, char * nom, char * classe,SDL_Renderer* ecran,float * statPerso){
	strcpy(perso->Nom,nom);
	perso->lvl=1;
	perso->Xplvl=20;
	perso->Xp=0;
	perso->PtComp=0;
	int i;
	/** change les stats de base selon la classe du perso */
	if(!strcmp(classe,"Golem")){
		strcpy(perso->Classe,classe);
		perso->PvMax=30;
		perso->Pv=30;
		perso->ManaMax=0;
		perso->Mana=0;
		perso->Def=15;
		perso->Res=5;
		perso->For=15;
		perso->Int=0;
		perso->Vit=5;
		perso->attaques[0] = (creer_attaque("big tate-pa",PHY,"charge une enorme patate et lance un direct du droit pour envoyer son adversaire sur Saturne",ATTAQUE,40,1,1,80));
		perso->attaques[1] = (creer_attaque("projectile insoupconne",PHY,"lance sa propre tete sur l'adversaire",ATTAQUE,70,1,1,50));
		perso->MarcheHori=loadTexture("../Ressource/characters/golemHorizontalWalk.png",ecran);
		perso->MarcheFront=NULL;
		perso->MarcheBack=NULL;
		/*perso->IdleAnim=loadTexture("../Ressource/GolemIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/GolemAtt.png",ecran);*/
	}
	else if(!strcmp(classe,"Mage")){
		strcpy(perso->Classe,classe);
		perso->PvMax=15;
		perso->Pv=15;
		perso->ManaMax=20;
		perso->Mana=20;
		perso->Def=5;
		perso->Res=10;
		perso->For=5;
		perso->Int=15;
		perso->Vit=10;
		perso->MarcheHori=loadTexture("../Ressource/characters/xeroHorizontalWalk.png",ecran);
		perso->MarcheFront=loadTexture("../Ressource/characters/xeroFrontWalk.png",ecran);
		perso->MarcheBack=loadTexture("../Ressource/characters/xeroBackWalk.png",ecran);
		perso->attaques[0] = (creer_attaque("lancer de livre",MAG,"lance son grimoire sur l'adversaire",ATTAQUE,50,1,1,75));
		perso->attaques[1] = (creer_attaque("rail de ke-co",STA,"jvous fais pas un dessin, le nom parle de lui-meme",VIT,20,3,1,100));
		/*perso->IdleAnim=loadTexture("../Ressource/MageIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/MageAtt.png",ecran);*/
		
	}
	else if(!strcmp(classe,"Guerrier")){
		strcpy(perso->Classe,classe);
		perso->PvMax=20;
		perso->Pv=20;
		perso->ManaMax=10;
		perso->Mana=10;
		perso->Def=10;
		perso->Res=10;
		perso->For=10;
		perso->Int=10;
		perso->Vit=15;
		perso->MarcheHori=loadTexture("../Ressource/characters/toxoHorizontalWalk.png",ecran);
		perso->MarcheFront=loadTexture("../Ressource/characters/toxoFrontWalk.png",ecran);
		perso->MarcheBack=loadTexture("../Ressource/characters/toxoBackWalk.png",ecran);
		perso->attaques[0] = (creer_attaque("allergie au pollen",MAG,"rend son adversaire sensible au pollen, tres efficace au printemps",ATTAQUE,60,1,1,80));
		perso->attaques[1] = (creer_attaque("arrosage",STA,"la plante s'arrose elle-meme et se soigne",SOIN,7,1,1,100));
		/*perso->IdleAnim=loadTexture("../Ressource/GuerrierIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/GuerrierAtt.png",ecran);*/
	}
	else{
		printf("Erreur Classe invalide");
		return 1;
	}
	
	/** initialise les tableau de pointeurs */
	for(i=0;i<TAILLE_EQUIP;i++){
		perso->stuff[i]=NULL;
	}
	for(i=0;i<NB_ARMES;i++){
		perso->armes[i]=NULL;
	}
	
	/** copie les stats des persos */
	statPerso[0]=perso->PvMax;
	statPerso[1]=perso->ManaMax;
	statPerso[2]=perso->For;
	statPerso[3]=perso->Def;
	statPerso[4]=perso->Int;
	statPerso[5]=perso->Res;
	statPerso[6]=perso->Vit;
	statPerso[7]=perso->PtComp;
	return 0;
}

/** met a jour le perso quand il a asser d'xp pour lvl up */
void lvl_up(perso_t* perso,float * statPerso){
	if(perso->Xp>=perso->Xplvl){
		perso->lvl+=1;
		perso->PtComp+=1;
		perso->Xp-=perso->Xplvl;
		perso->Xplvl+=10;
		perso->PvMax+=1;
	}
	statPerso[7]=perso->PtComp;
}

/** fonction qui va créer un objet_t avec ça texture entré en paramètre */
void creer_all_objet(objet_t allObj[9], SDL_Renderer* ecran){
	/** toutes les valeurs des différents objets dans des tableaux */
	float tabVal[18]={20,0,50,0,500,0,0,20,0,50,0,500,20,20,50,50,500,500};
	char tabNom[9][14]={"Potion PV","G.Potion PV","PotionPV max","Potion PM","G.Potion PM","Potion PM max","Elixir","G.Elixir","Elixir max"};
	char tabDesc[9][100]={"Potion restaurant 20 PV","Potion restaurant 50 PV","Potion restaurant les PV au max","Potion restaurant 20 PM","Potion restaurant 50 PM","Potion restaurant les PM au max","Elixir restaurant 20 PV/PM","Elixir restaurant 50 PV/PM","Elixir restaurant PV/PM au max"};
	int couts[9]={5,15,40,5,15,40,15,30,75};
	char tabChemin[9][35]={"../Ressource/PotPv.png","../Ressource/GPotPv.png","../Ressource/PotPvMax.png","../Ressource/PotPm.png","../Ressource/GPotPm.png","../Ressource/PotPmMax.png","../Ressource/Elix.png","../Ressource/GElix.png","../Ressource/ElixMax.png"};
	
	/** création des objets */
	int i,j;
	for(i=0,j=0;i<ALL_OBJETS;i++,j+=2){
		strcpy(allObj[i].nom,tabNom[i]);
		strcpy(allObj[i].desc,tabDesc[i]);
		allObj[i].valPv=tabVal[j];
		allObj[i].valMp=tabVal[j+1];
		allObj[i].cout=couts[i];
		allObj[i].sprite=loadTexture(tabChemin[i],ecran);
	}
}

/** fonction qui va utiliser l'objet et le retiré de l'inventaire*/
void utiliser_obj(inventaire_t *Inv,perso_t *perso,int iObj){
	if(Inv->sac[iObj]!=NULL){
		perso->Pv+=Inv->sac[iObj]->valPv;
		perso->Mana+=Inv->sac[iObj]->valMp;
		if(perso->Pv>perso->PvMax){
			perso->Pv=perso->PvMax;
		}
		if(perso->Mana>perso->ManaMax){
			perso->Mana=perso->ManaMax;
		}
		Inv->sac[iObj]=Inv->sac[Inv->nbObjActu-1];
		Inv->sac[Inv->nbObjActu-1]=NULL;
		Inv->nbObjActu-=1;
	}
	
}

/** fonction supprime un objet de l'inventaire*/
int jeter_obj(inventaire_t *Inv,int iObj){
	if(Inv->nbObjActu>0){
		if(Inv->sac[iObj]==NULL){
			return 1;
		}
		Inv->sac[iObj]=Inv->sac[Inv->nbObjActu-1];
		Inv->sac[Inv->nbObjActu-1]=NULL;
		Inv->nbObjActu-=1;
		return 0;
	}
	return 1;
}

/** fonction ajoute un objet dans l'inventaire */
int ajouter_obj(inventaire_t *Inv,objet_t * allObj,int iObj){
	if(Inv->nbObjActu<10){
		Inv->sac[Inv->nbObjActu]=&allObj[iObj];
		Inv->nbObjActu+=1;
		return 0;
	}
	return 1;
}

/** fonction qui initialise l'inventaire et permet de le réinitialiser */
void init_and_reinit_inv(inventaire_t* inv){
	int i;
	inv->bourse=0;
	inv->nbObjActu=inv->nbEquActu=inv->nbArmActu=0;
	for (i=0;i<NB_INV_OBJETS;i++){
		inv->sac[i]=NULL;
	}
	for (i=0;i<NB_INV_EQUIPEMENTS;i++){
		inv->equipements[i]=NULL;
	}
	for (i=0;i<NB_INV_ARMES;i++){
		inv->armes[i]=NULL;
	}
}

/** affichage d'un perso pour des test ou autre effaçable une fois inutile */
void aff_perso(perso_t perso){
	printf("name: %s\n",perso.Nom);
	printf("class: %s\n",perso.Classe);
	printf("lvl: %d\n",perso.lvl);
	printf("xplevel: %d\n",perso.Xplvl);
	printf("xp: %d\n",perso.Xp);
	printf("ptcomp: %d\n",perso.PtComp);
	printf("PvMax: %.0f\n",perso.PvMax);
	printf("Pv: %.0f\n",perso.Pv);
	printf("ManaMax: %.0f\n",perso.ManaMax);
	printf("Mana: %.0f\n",perso.Mana);
	printf("for: %.0f\n",perso.For);
	printf("def: %.0f\n",perso.Def);
	printf("res: %.0f\n",perso.Res);
	printf("int: %.0f\n",perso.Int);
	printf("vit: %.0f\n",perso.Vit);
}

/** charge toutes les textures de chaque équipements */
void creer_all_sprite_equipement(SDL_Texture* allSprite[ALL_EQUIPEMENTS], SDL_Renderer* ecran){
	char chemin[ALL_EQUIPEMENTS][52]={"../Ressource/Sprites/Casques/casquev1.png","../Ressource/Sprites/Plastroncs/plastroncv1.png","../Ressource/Sprites/Bottes/bottesv1.png",
			     "../Ressource/Sprites/Casques/casquev2.png","../Ressource/Sprites/Plastroncs/plastroncv2.png","../Ressource/Sprites/Bottes/bottesv2.png",
			     "../Ressource/Sprites/Casques/casquev3.png","../Ressource/Sprites/Plastroncs/plastroncv3.png","../Ressource/Sprites/Bottes/bottesv3.png",
			     "../Ressource/Sprites/Casques/casquev4_1.png","../Ressource/Sprites/Plastroncs/plastroncv4_1.png","../Ressource/Sprites/Bottes/bottesv4_1.png",
			     "../Ressource/Sprites/Casques/casquev4_2.png","../Ressource/Sprites/Plastroncs/plastroncv4_2.png","../Ressource/Sprites/Bottes/bottesv4_2.png",
			     "../Ressource/Sprites/Casques/casquev5.png","../Ressource/Sprites/Plastroncs/plastroncv5.png","../Ressource/Sprites/Bottes/bottesv5.png",
			     "../Ressource/Sprites/Casques/casque_ult.png","../Ressource/Sprites/Plastroncs/plastronc_ult.png","../Ressource/Sprites/Bottes/bottes_ult.png",
			     "../Ressource/Sprites/Talismans/talisman_bleu.png","../Ressource/Sprites/Talismans/talisman_cyan.png","../Ressource/Sprites/Talismans/talisman_orange.png",
			     "../Ressource/Sprites/Talismans/talisman_rose.png","../Ressource/Sprites/Talismans/talisman_rouge.png","../Ressource/Sprites/Talismans/talisman_vert.png",
			     "../Ressource/Sprites/Talismans/talisman_violet.png","../Ressource/Sprites/Talismans/talisman_rainbow.png","../Ressource/Sprites/Talismans/talisman_ult.png"};
	int i;
	for (i=0;i<ALL_EQUIPEMENTS;i++){
		allSprite[i]=loadTexture(chemin[i],ecran);
	}
}

/** créer le tableau avec tout les équipements en 3 fois pour éviter qu'un personnage soit équiper d'éxactement le même équipement */
void creer_all_equipement(equipement_t allStuff[ALL_EQUIPEMENTS][3],SDL_Texture* allSprite[ALL_EQUIPEMENTS]){
	float val[8]={2.0,5.0,7.0,10.0,12.0,20.0,1.1,1.2};
	int cout[9]={20,40,60,80,100,200,75,150,250};
	char tabNom[ALL_EQUIPEMENTS][20]={"Casque en fer","Plastron en fer","Bottes en fer",
			     "Casque ancien","Plastron ancien","Bottes ancien",
			     "Turbant","Marcel","Tong",
			     "Casque de feu","Plastron de feu","Bottes de feu",
			     "Casque geler","Plastron geler","Bottes geler",
			     "Lunette","Kway","Bottes de pluie",
			     "Casque Bestiale","Gi Bestiale","Bottes Bestiale",
			     "Bague Int","Bague Mana","Bague Def","Bague Pv","Bague For","Bague Vit","Bague Res","Bague antique",
			     "Masque Joker"};
	char tabDesc[15][50]={"Octroie +2 de Def et Res","Octroie +5 de Def et Res","Octroie +7 de Def et Res",
			       "Octroie +10 de Def et Res","Octroie +12 de Def et Res","Octroie +20 de Def et Res",
			       "Octroie +10% d'Int","Octroie +10% de Mana","Octroie +10% de Def","Octroie +10% de Pv",
			       "Octroie +10% de For","Octroie +10% de Vit","Octroie +10% de Res","Octroie +10% de tout","Octroie +20% de tout"};
	int i,j;
	
	/** créer tout les casques, plastroncs et bottes par biomes */
	for(i=0;i<21;i++){
		for(j=0;j<3;j++){
			strcpy(allStuff[i][j].nom,tabNom[i]);
			if(i<3){
				strcpy(allStuff[i][j].desc,tabDesc[0]);
				allStuff[i][j].Def=val[0];
				allStuff[i][j].Res=val[0];
				allStuff[i][j].cout=cout[0];
			}
			else if(i<6){
				strcpy(allStuff[i][j].desc,tabDesc[1]);
				allStuff[i][j].Def=val[1];
				allStuff[i][j].Res=val[1];
				allStuff[i][j].cout=cout[1];
			}
			else if(i<9){
				strcpy(allStuff[i][j].desc,tabDesc[2]);
				allStuff[i][j].Def=val[2];
				allStuff[i][j].Res=val[2];
				allStuff[i][j].cout=cout[2];
			}
			else if(i<15){
				strcpy(allStuff[i][j].desc,tabDesc[3]);
				allStuff[i][j].Def=val[3];
				allStuff[i][j].Res=val[3];
				allStuff[i][j].cout=cout[3];
			}
			else if(i<18){
			     strcpy(allStuff[i][j].desc,tabDesc[4]);
			     allStuff[i][j].Def=val[4];
			     allStuff[i][j].Res=val[4];
			     allStuff[i][j].cout=cout[4];
			}
			else{
			     strcpy(allStuff[i][j].desc,tabDesc[5]);
			     allStuff[i][j].Def=val[5];
			     allStuff[i][j].Res=val[5];
			     allStuff[i][j].cout=cout[5];
			}
			
			allStuff[i][j].typeEquipement=i%3;
			allStuff[i][j].numId=j;
			allStuff[i][j].persoEquiper=NULL;
			allStuff[i][j].Pv=0;
			allStuff[i][j].Mana=0;
			allStuff[i][j].For=0;
			allStuff[i][j].Int=0;
			allStuff[i][j].Vit=0;
			allStuff[i][j].artwork=allSprite[i];
		}
	}
	
	/** créer les talismants */
	for(i=21;i<ALL_EQUIPEMENTS;i++){
		for(j=0;j<3;j++){
			strcpy(allStuff[i][j].nom,tabNom[i]);
			strcpy(allStuff[i][j].desc,tabDesc[i-15]);
			allStuff[i][j].typeEquipement=TALISMANT;
			allStuff[i][j].numId=j;
			allStuff[i][j].persoEquiper=NULL;
			if(i==ALL_EQUIPEMENTS-2){
				allStuff[i][j].Pv=val[6];
				allStuff[i][j].Mana=val[6];
				allStuff[i][j].Def=val[6];
				allStuff[i][j].Res=val[6];
				allStuff[i][j].For=val[6];
				allStuff[i][j].Int=val[6];
				allStuff[i][j].Vit=val[6];
				allStuff[i][j].cout=cout[7];
			}
			else if(i==ALL_EQUIPEMENTS-1){
				allStuff[i][j].Pv=val[7];
				allStuff[i][j].Mana=val[7];
				allStuff[i][j].Def=val[7];
				allStuff[i][j].Res=val[7];
				allStuff[i][j].For=val[7];
				allStuff[i][j].Int=val[7];
				allStuff[i][j].Vit=val[7];
				allStuff[i][j].cout=cout[8];
			}
			else{
				allStuff[i][j].Pv=0;
				allStuff[i][j].Mana=0;
				allStuff[i][j].Def=0;
				allStuff[i][j].Res=0;
				allStuff[i][j].For=0;
				allStuff[i][j].Int=0;
				allStuff[i][j].Vit=0;
				allStuff[i][j].cout=cout[6];
			}	
			allStuff[i][j].artwork=allSprite[i];
			
		}
	}
	allStuff[21][0].Int=allStuff[21][1].Int=allStuff[21][2].Int=val[6];
	allStuff[22][0].Mana=allStuff[22][1].Mana=allStuff[22][2].Mana=val[6];
	allStuff[23][0].Def=allStuff[23][1].Def=allStuff[23][2].Def=val[6];
	allStuff[24][0].Pv=allStuff[24][1].Pv=allStuff[24][2].Pv=val[6];
	allStuff[25][0].For=allStuff[25][1].For=allStuff[25][2].For=val[6];
	allStuff[26][0].Vit=allStuff[26][1].Vit=allStuff[26][2].Vit=val[6];
	allStuff[27][0].Res=allStuff[27][1].Res=allStuff[27][2].Res=val[6];
	
}


/** fonction qui ajoute un équipement dans l'inventaire */
int ajouter_stuff(equipement_t allStuff[ALL_EQUIPEMENTS][3],inventaire_t *inv,int iStuff){
	int i;
	int firstIteration=0,seconfIteration=0,thirdIteration=0;
	
	/** regarde si l'inventaire n'est pas pleint */
	if(inv->nbEquActu<NB_INV_EQUIPEMENTS){
	
		/** regarde combien de fois il possède cet équipement si il l'a 3 fois impossible d'ajouter l'objet */
		for(i=0;i<inv->nbEquActu;i++){
			if(inv->equipements[i]!=NULL){
				if(strcmp(inv->equipements[i]->nom,allStuff[iStuff][0].nom)==0){
					if(inv->equipements[i]->numId==0 && firstIteration==0){
						firstIteration=1;
					}
					else if(inv->equipements[i]->numId==1 && seconfIteration==0){
						seconfIteration=1;
					}
					else if(inv->equipements[i]->numId==2 && thirdIteration==0){
						thirdIteration=1;
					}
				}
			}
			
		}
		
		/** ajoute l'équipement avec le numId qui n'est pas présent */
		if(firstIteration==0){
			inv->equipements[inv->nbEquActu]=&allStuff[iStuff][0];
			inv->nbEquActu+=1;
			return 0;
		}
		else{
			if(seconfIteration==0){
				inv->equipements[inv->nbEquActu]=&allStuff[iStuff][1];
				inv->nbEquActu+=1;
				return 0;
			}
			else if(thirdIteration==0){
				inv->equipements[inv->nbEquActu]=&allStuff[iStuff][2];
				inv->nbEquActu+=1;
				return 0;
			}
			
			/** renvoie 2 si il a déja 3 fois l'équipement voulu */
			else{
				return 2;
			}
		}
	}
	
	/** renvoie 1 si l'inventaire est pleint */
	return 1;
}

/** fonction qui équipe un équipement d'un personnage */
void equiper_stuff(equipement_t* equipement, perso_t* perso){
	if(equipement != NULL && perso!= NULL){
	
		/** si l'équipement est équiper sur un personnage le désequipe */
		if(equipement->persoEquiper!=NULL){
			equipement->persoEquiper->stuff[equipement->typeEquipement]=NULL;	
		}
		
		/** si un équipement du même type est déja équiper le déséquipe de cet objet */
		if(perso->stuff[equipement->typeEquipement]!=NULL){
			perso->stuff[equipement->typeEquipement]->persoEquiper=NULL;
		}
		equipement->persoEquiper=perso;
		perso->stuff[equipement->typeEquipement]=equipement;
	}
}

/** fonction qui déséquipe un équipement d'un personnage */
int desequiper_stuff(int iStuff, perso_t* perso){
	if(perso!= NULL){ 
		if((iStuff >=0 && iStuff<= 4) && perso->stuff[iStuff]!=NULL){
			perso->stuff[iStuff]->persoEquiper=NULL;
			perso->stuff[iStuff]=NULL;
			return 0;	
		}
	}
	return 1;
}

/** fonction qui supprime un équipement de l'inventaire */
int jeter_stuff(inventaire_t *Inv,int iStuff){
	if(Inv->nbEquActu>0){
		if(Inv->equipements[iStuff]==NULL){
			return 1;
		}
		
		/** si l'équipement est équiper sur un personnage le désequipe avant de jeter l'équipement */
		if(Inv->equipements[iStuff]->persoEquiper!=NULL){
			Inv->equipements[iStuff]->persoEquiper->stuff[Inv->equipements[iStuff]->typeEquipement]=NULL;
			Inv->equipements[iStuff]->persoEquiper=NULL;
		}
		Inv->equipements[iStuff]=Inv->equipements[Inv->nbEquActu-1];
		Inv->equipements[Inv->nbEquActu-1]=NULL;
		Inv->nbEquActu-=1;
		return 0;
	}
	return 2;
}

int join_team(team_t * team, perso_t * allPerso){
	if(team->nbPerso<NB_TEAM_PERSOS){
		team->team[team->nbPerso]=&allPerso[team->nbPerso];
		team->nbPerso+=1;
		return 0;
	}
	return 1;
}

void init_reinit__team(team_t * team){
	int i;
	team->nbPerso=0;
	for(i=0;i<NB_TEAM_PERSOS;i++){
		team->team[i]=NULL;
	}
}

