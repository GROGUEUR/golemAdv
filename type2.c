#include "../lib/type.h"
#include "../lib/texture.h"
#include <stdio.h>
#include <string.h>

/** fonction créer un perso renvoie NULL si la création n'as pas fonctionner */
int creer_perso(perso_t * perso, char * nom, char * classe,SDL_Renderer* ecran){
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
		perso->MarcheHori=loadTexture("./Ressource/GolemHori.png",ecran);
		perso->MarcheVert=loadTexture("./Ressource/GolemVert.png",ecran);
		perso->IdleAnim=loadTexture("./Ressource/GolemIdle.png",ecran);
		perso->AttAnim=loadTexture("./Ressource/GolemAtt.png",ecran);
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
		perso->MarcheHori=loadTexture("../Ressource/MageHori.png",ecran);
		perso->MarcheVert=loadTexture("../Ressource/MageVert.png",ecran);
		perso->IdleAnim=loadTexture("../Ressource/MageIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/MageAtt.png",ecran);
		
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
		perso->MarcheHori=loadTexture("../Ressource/GuerrierHori.png",ecran);
		perso->MarcheVert=loadTexture("../Ressource/GuerrierVert.png",ecran);
		perso->IdleAnim=loadTexture("../Ressource/GuerrierIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/GuerrierAtt.png",ecran);
	}
	else{
		free(perso);
		perso=NULL;
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
	for(i=0;i<NB_ATT;i++){
		perso->attaques[i]=NULL;
	}
	return 0;
}

/** met a jour le perso quand il a asser d'xp pour lvl up */
void lvl_up(perso_t* perso){
	if(perso->Xp>=perso->Xplvl){
		perso->lvl+=1;
		perso->PtComp+=1;
		perso->Xp-=perso->Xplvl;
		perso->Xplvl+=10;
		perso->PvMax+=1;
	}	
}

/** fonction qui va charger un perso deja existant quand on va charger une sauvegarde */
int charger_perso(perso_t* perso,SDL_Renderer* ecran,char* nom,char* classe,int lvl,int Xplvl,int Xp,int PtComp,float pvmax,float pv,float manamax,float mana,float def,float res,float For,float Int,float vit,char* casque,char* plastron,char* botte,char* talismant){
	strcpy(perso->Nom,nom);
	perso->lvl=lvl;
	perso->Xplvl=Xplvl;
	perso->Xp=Xp;
	perso->PtComp=PtComp;
	strcpy(perso->Classe,classe);
	perso->PvMax=pvmax;
	perso->Pv=pv;
	perso->ManaMax=manamax;
	perso->Mana=mana;
	perso->Def=def;
	perso->Res=res;
	perso->For=For;
	perso->Int=Int;
	perso->Vit=vit;
	if(classe=="Golem"){
		perso->MarcheHori=loadTexture("./Ressource/GolemHori.png",ecran);
		perso->MarcheVert=loadTexture("./Ressource/GolemVert.png",ecran);
		perso->IdleAnim=loadTexture("./Ressource/GolemIdle.png",ecran);
		perso->AttAnim=loadTexture("./Ressource/GolemAtt.png",ecran);
	}
	else if(classe=="Mage"){
		perso->MarcheHori=loadTexture("../Ressource/MageHori.png",ecran);
		perso->MarcheVert=loadTexture("../Ressource/MageVert.png",ecran);
		perso->IdleAnim=loadTexture("../Ressource/MageIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/MageAtt.png",ecran);
		
	}
	else if(classe=="Guerrier"){
		perso->MarcheHori=loadTexture("../Ressource/GuerrierHori.png",ecran);
		perso->MarcheVert=loadTexture("../Ressource/GuerrierVert.png",ecran);
		perso->IdleAnim=loadTexture("../Ressource/GuerrierIdle.png",ecran);
		perso->AttAnim=loadTexture("../Ressource/GuerrierAtt.png",ecran);
	}
	else{
		free(perso);
		perso=NULL;
		printf("Erreur Classe invalide");
		return 1;
	}
	perso->stuff[0]=malloc(sizeof(equipement_t));
	perso->stuff[1]=malloc(sizeof(equipement_t));
	perso->stuff[2]=malloc(sizeof(equipement_t));
	perso->stuff[3]=malloc(sizeof(equipement_t));
	/*creer_stuff(perso->stuff[0],casque);
	creer_stuff(perso->stuff[1],casque);
	creer_stuff(perso->stuff[2],casque);
	creer_stuff(perso->stuff[3],casque);*/
	return 0;
}

/** fonction qui va créer un objet_t avec ça texture entré en paramètre */
void creer_all_objet(objet_t allObj[9], SDL_Renderer* ecran){
	float tabVal[18]={20,0,50,0,500,0,0,20,0,50,0,500,20,20,50,50,500,500};
	char tabNom[9][14]={"Potion PV","G.Potion PV","PotionPV max","Potion PM","G.Potion PM","Potion PM max","Elixir","G.Elixir","Elixir max"};
	char tabDesc[9][100]={"Potion PV","G.Potion PV","Potion PV max","Potion PM","G.Potion PM","Potion PM max","Elixir","G.Elixir","Elixir max"};
	int couts[9]={5,15,40,5,15,40,15,30,75};
	char tabChemin[9][35]={"../Ressource/PotPv.png","../Ressource/GPotPv.png","../Ressource/PotPvMax.png","../Ressource/PotPm.png","../Ressource/GPotPm.png","../Ressource/PotPmMax.png","../Ressource/Elix.png","../Ressource/GElix.png","../Ressource/ElixMax.png"};
	int i,j;
	for(i=0,j=0;i<9;i++,j+=2){
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

/** fonction supprime un objet de l'inventaire*/
void jeter_obj(inventaire_t *Inv,int iObj){
	if(Inv->nbObjActu>0){
		Inv->sac[iObj]=Inv->sac[Inv->nbObjActu-1];
		Inv->sac[Inv->nbObjActu-1]=NULL;
		Inv->nbObjActu-=1;
	}
}

void ajouter_obj(inventaire_t *Inv,objet_t * allObj,int iObj){
	Inv->sac[Inv->nbObjActu]=&allObj[iObj];
	Inv->nbObjActu+=1;
}
