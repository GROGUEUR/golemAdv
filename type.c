#include "type.h"
#include "texture.h"
#include <stdio.h>
#include <string.h>

int creer_perso(perso_t * perso, char * nom, char * classe,SDL_Renderer* ecran){
	strcpy(perso->Nom,nom);
	perso->lvl=1;
	perso->Xplvl=20;
	perso->Xp=0;
	int i;
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
		/*perso->MarcheHori=loadTexture("./Ressource/MageHori.png",ecran);
		perso->MarcheVert=loadTexture("./Ressource/MageVert.png",ecran);
		perso->IdleAnim=loadTexture("./Ressource/MageIdle.png",ecran);
		perso->AttAnim=loadTexture("./Ressource/MageAtt.png",ecran);*/
		
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
		perso->MarcheHori=loadTexture("./Ressource/GuerrierHori.png",ecran);
		perso->MarcheVert=loadTexture("./Ressource/GuerrierVert.png",ecran);
		perso->IdleAnim=loadTexture("./Ressource/GuerrierIdle.png",ecran);
		perso->AttAnim=loadTexture("./Ressource/GuerrierAtt.png",ecran);
	}
	else{
		free(perso);
		perso=NULL;
		printf("Erreur Classe invalide");
		return 1;
	}
	for(i=0;i<TAILLE_EQUIP;i++){
		perso->stuff[i]=NULL;
	}
	return 0;
}
