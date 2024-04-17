/**
* \file prototype.c
* \brief programme principale gérant tout le jeux.
* \author Cognard Luka, Bonga Warrick, François Lépine, Lenny Borry.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/EventOp.h"
#include "../lib/utils.h"
#include "../lib/init_menu.h"
#include "../lib/combat.h"

int main(int argc, char** argv){
    /** initialisation de x pour les coordonnée src et i pour les boucles  
    * ainsi que de w et h pour récupérer la longueur et largeur de la fenètre
    */
    int i,x=0;
    int w=0,h=0;
    int affichage_map=0;
    
    /** Initialisation de SDL pour les VIDEO, EVENTS et AUDIO */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    else{
    
        /** Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1360,780,SDL_WINDOW_SHOWN);
        SDL_GetWindowSize(pWindow,&w,&h);
        
        /** Initialisation de SDL_IMAGE */
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        	fprintf(stderr, "Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        	SDL_Quit();
        	return 1;
    	}
    	
    	/** Initialisation de SDL_TTF */
    	if (TTF_Init() < 0) {
                fprintf(stderr, "Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
                IMG_Quit();
                SDL_Quit();
                return 1;
        }
        
        /** Initialisation de SDL_Mixer */
    	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        	SDL_Log("Erreur lors de l'initialisation de SDL_mixer : %s", Mix_GetError());
        	IMG_Quit();
        	TTF_Quit();
        	SDL_Quit();
        	return 1;
        }
        
        if( pWindow )
        {
            /** Création d'un SDL_Renderer utilisant l'accélération matérielle */
            SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
            if ( pRenderer )
            {
		    /** chargement des texture  du perso, etc ...*/
		    SDL_Texture* pPerso=loadTexture("../Ressource/scorpion.png",pRenderer);
		    SDL_Texture* Map1=NULL;
            	    SDL_Texture* Map2=NULL;
            	    SDL_Texture* Map3=NULL;
            	    SDL_Texture* Map4=NULL;
            	    SDL_Texture* Map5=NULL;
            	    SDL_Texture* Map6=NULL;
            	    SDL_Texture* biblio=NULL;
            	    SDL_Texture* pBlock=loadTexture("../Ressource/blockZone.png",pRenderer);
		    SDL_Texture* pPnj=loadTexture("../Ressource/pnj.png",pRenderer);
                    if ( pPerso != NULL)
                    {
                        /** déclaration des destination du perso, map, block et pnj ainsi que des variable pour la music */
                        SDL_Rect dest = { 33*32,20*32, 32,32};
                        SDL_Rect saveDest = { 33*32,20*32, 32,32};
                        SDL_Rect block = { w-280,h/2, 64,256};
                        SDL_Rect pnj = { w-280,(h/2)-64, 64,64};
                        Mix_Music * backMenu = NULL;
                        Mix_Music * cinemStart = NULL;
                        Mix_Music * backOp = NULL;
                        Mix_Music * backP = NULL;
                        SDL_Texture* vendeurDialoTexture[5]={loadTexture("../Ressource/pnj/dialogue/shopFirstDialogue.png",pRenderer),
                        				       loadTexture("../Ressource/pnj/dialogue/shopBiyDialogue.png",pRenderer),
                        				       loadTexture("../Ressource/pnj/dialogue/shopSellDialogue.png",pRenderer),
                        				       loadTexture("../Ressource/pnj/dialogue/shopQuitDialogue.png",pRenderer),
                        				       loadTexture("../Ressource/pnj/dialogue/shopSecondDialogue.png",pRenderer)};
                        
                        /**
                        * création et initialisation d'un tableau selectionnant tout les sprites de l'animation de marche
                        */
                        
                        SDL_Rect marcheHori[3][8];
                        for (i=0;i<6;i++){
                            marcheHori[0][i].x=x;
                            marcheHori[0][i].y=0;
                            marcheHori[0][i].w=32;
                            marcheHori[0][i].h=32;
                            x+=32;
                        }
                        x=64*4;
                        for (i=0;i<4;i++){
                            marcheHori[1][i].x=x;
                            marcheHori[1][i].y=0;
                            marcheHori[1][i].w=64;
                            marcheHori[1][i].h=64;
                            
                            x+=64;
                        }
                        x=64*3;
                        for (i=4;i<8;i++){
                            marcheHori[1][i].x=x;
                            marcheHori[1][i].y=0;
                            marcheHori[1][i].w=64;
                            marcheHori[1][i].h=64;
                            
                            x-=64;
                        }
             		 x=0;
                        for (i=0;i<4;i++){
                            marcheHori[2][i].x=x;
		             marcheHori[2][i].y=0;
		             marcheHori[2][i].w=64;
		             marcheHori[2][i].h=64;
                            
                            x+=64;
                        }
                        i=0;
                        /**
                        * déclaration de quitOp et quitMenu etant les variables booleennes qui mettent fin respectivement a la boucle de l'open world et des menus
                        * déclaration keyPressed pour gérer les touches
                        * déclaration Action pour les interraction
                        * déclaration MouseHover, Mouseclick pour gérer la sourit
                        * déclaration yonThrow gérant la boite d'interraction pour jeter un objet
                        * déclaration yonUse gérant la boite d'interraction pour utiliser un objet
                        * déclaration tableau useOk etant a 1 si l'objet n'est pas utilisable sur un personnage sinon a 0
                        */
                        int quitOp, quitMenu = 0, KeyIsPressed=0, Action=0,MouseOver=-1,MouseClick=-1,yonThrow=-1, yonUse=-1;
                        int numPage=0, next=0,numPagePerso=0,slot=-1,eOuStuff=-1, choiceShop=1,vendeur=0,choiceBiy=-1, map=0,numperso=0;
                        int choixMenuPr = NOTHING, choixMenuPlay = NOTHING, choixMenuPause = NOTHING;
                        int collision[125][250];
                        int collision2[125][250];
                        int useOk[3];
                        useOk[0]=1;
                        useOk[1]=1;
                        useOk[2]=1;
                        char *nom1=NULL;
                        char *nom2=NULL;
                        char *nom3=NULL;
                        int quitCombat = 0,menu_combat = 0,perso,W,H;
			 int p=0;
			 mob_t ** mobs = NULL;
			 
                        /** déclaration de la scene ou est le jeu */
                        scene_t scene=OP;
                        
                        /** création de tout les objets du jeux */
                        objet_t allPot[ALL_OBJETS];
                        creer_all_objet(allPot,pRenderer);
                        
                        
                        /** création de tout les équipements du jeux en 3 fois,
                        * pour éviter d'avoir le même équipement sur plusieurs perso
                        */
                        equipement_t allStuff[ALL_EQUIPEMENTS][3];
                        SDL_Texture* allSpriteStuff[ALL_EQUIPEMENTS];
                        creer_all_sprite_equipement(allSpriteStuff,pRenderer);
                        creer_all_equipement(allStuff,allSpriteStuff);
                        
                        /** création de tou les personnage possible */
                        perso_t allPerso[NB_TEAM_PERSOS];
                        float statsPerso[NB_TEAM_PERSOS][8];
                        
                        
                        /** déclaration de l'équipe en jeux pour tester */
                        team_t team;
                        init_reinit__team(&team);
                        SDL_Rect destStatAction[2];
                        
                        /** déclaration et initialisation de l'inventaire */
                        inventaire_t inventaire;
                        init_and_reinit_inv(&inventaire);
                        ajouter_obj(&inventaire,allPot,0);
                        ajouter_obj(&inventaire,allPot,8);
                        ajouter_obj(&inventaire,allPot,3);
                        inventaire.bourse=100;
                        SDL_Rect destThrowButton;
                        
                        /** ajoute de l'équipements dans l'inventaire pour tester */
                        ajouter_stuff(allStuff,&inventaire,25);
                        ajouter_stuff(allStuff,&inventaire,18);
                        ajouter_stuff(allStuff,&inventaire,0);
                        ajouter_stuff(allStuff,&inventaire,9);
                        ajouter_stuff(allStuff,&inventaire,9);
                        ajouter_stuff(allStuff,&inventaire,29);
                        ajouter_stuff(allStuff,&inventaire,25);
                        ajouter_stuff(allStuff,&inventaire,18);
                        ajouter_stuff(allStuff,&inventaire,0);
                        ajouter_stuff(allStuff,&inventaire,9);
                        ajouter_stuff(allStuff,&inventaire,29);
                        ajouter_stuff(allStuff,&inventaire,12);
                        ajouter_stuff(allStuff,&inventaire,19);
                        ajouter_stuff(allStuff,&inventaire,20);
                        
                        /** équipe les persos avec le stuff voulu pour tester */
               	 
               	 
                        /** déclaration de la destination/dimensions plus chargement de la texture pour la cinématique du début */
                        SDL_Texture * storyP1=NULL;
			 SDL_Texture * storyP2=NULL;
			 SDL_Texture * storyP3=NULL;
			 SDL_Texture * storyP4=NULL;
                        SDL_Rect page1={0,0,1360,780};
                        SDL_Rect page2={1360,0,1360,780};
                        SDL_Rect page3={1360*2,0,1360,780};
                        SDL_Rect page4={1360*3,0,1360,780};
                        int skipOn=-1;
                        i=0;
                        SDL_Texture* fond_combat = loadTexture("../Ressource/Combat/fond_ecran_combat.jpg",pRenderer);
			/** boucle entière du jeu */
			while(quitMenu != NOTHING){
				quitOp = 0;
				/** boucle menu */
				while(quitMenu == 0){
					if(backMenu==NULL){
						if(backP!=NULL){
							Mix_FreeMusic(backP);
							backP=NULL;
						}
						backMenu = Mix_LoadMUS("../Ressource/Music/MainMenu.mp3");
						Mix_PlayMusic(backMenu, -1);
					}
					switch(choixMenuPr = menuPrincipal(pRenderer)){
						case PLAY:
							choixMenuPlay = menuPlay(pRenderer);
							if((choixMenuPlay - (choixMenuPlay % 10)) == SAVE1){
								quitMenu = 1;
								if(choixMenuPlay % 10 == LOAD){
									/** Placer la fonction de chargement de la sauvegarde ici */
									scene = OP;
								}
								else if(choixMenuPlay % 10 == NEWGAME){
									/** Placer la fonction de création de la sauvegarde ici */
									nom1 = entrerNom(pRenderer);
									creer_perso(&allPerso[0],nom1,"Golem",pRenderer,statsPerso[0]);
									creer_perso(&allPerso[1],"Xero","Mage",pRenderer,statsPerso[1]);
									creer_perso(&allPerso[2],"Toxo","Guerrier",pRenderer,statsPerso[2]);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									equiper_stuff(inventaire.equipements[1],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[4],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[11],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[12],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[2],team.team[1]);
							       	 equiper_stuff(inventaire.equipements[10],team.team[2]);
									chargement(&scene,pRenderer,CINEMDEB);
									storyP1=loadTexture("../Ressource/cinem1.png",pRenderer);
									storyP2=loadTexture("../Ressource/cinem2.png",pRenderer);
									storyP3=loadTexture("../Ressource/cinem3.png",pRenderer);
									storyP4=loadTexture("../Ressource/cinem4.png",pRenderer);
									copie_fichier_mob_txt("../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt");
									charger_map("../Ressource/Mapping/tuiles_plaine.png","../Ressource/Mapping/level.txt",
										    "../Ressource/Mapping/map/map.png",collision);
									charger_map_pnj("../Ressource/pnj/pnj.png","../Ressource/Mapping/pnj.txt",
											 "../Ressource/Mapping/map/map.png","../Ressource/Mapping/map/map.png",collision);
									charger_map_mobs("../Ressource/mobs.png","../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt",
											  "../Ressource/Mapping/map/map.png",collision);
									charger_map_biblio("../Ressource/Mapping/biblio.png","../Ressource/Mapping/biblio.txt",
										    "../Ressource/Mapping/map/biblio.png",collision2);
									charger_map_pnj_biblio("../Ressource/characters/xero.png","../Ressource/Mapping/pnj_biblio.txt",
											 "../Ressource/Mapping/map/biblio.png","../Ressource/Mapping/map/biblio.png",collision2);
									biblio=loadTexture("../Ressource/Mapping/map/biblio.png",pRenderer);
								}
								
							}
							else if((choixMenuPlay - (choixMenuPlay % 10)) == SAVE2){
								quitMenu = 1;
								if(choixMenuPlay % 10 == LOAD){
									/** Placer la fonction de chargement de la sauvegarde ici */
									scene = OP;
								}
								else if(choixMenuPlay % 10 == NEWGAME){
									/** Placer la fonction de création de la sauvegarde ici */
									nom2 = entrerNom(pRenderer);
									creer_perso(&allPerso[0],nom2,"Golem",pRenderer,statsPerso[0]);
									creer_perso(&allPerso[1],"Xero","Mage",pRenderer,statsPerso[1]);
									creer_perso(&allPerso[2],"Toxo","Guerrier",pRenderer,statsPerso[2]);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									equiper_stuff(inventaire.equipements[1],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[4],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[11],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[12],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[2],team.team[1]);
							       	 equiper_stuff(inventaire.equipements[10],team.team[2]);
									chargement(&scene,pRenderer,CINEMDEB);
									storyP1=loadTexture("../Ressource/cinem1.png",pRenderer);
									storyP2=loadTexture("../Ressource/cinem2.png",pRenderer);
									storyP3=loadTexture("../Ressource/cinem3.png",pRenderer);
									storyP4=loadTexture("../Ressource/cinem4.png",pRenderer);
									copie_fichier_mob_txt("../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt");
									charger_map("../Ressource/Mapping/tuiles_plaine.png","../Ressource/Mapping/level.txt",
										    "../Ressource/Mapping/map/map.png",collision);
									charger_map_pnj("../Ressource/pnj/pnj.png","../Ressource/Mapping/pnj.txt",
											 "../Ressource/Mapping/map/map.png","../Ressource/Mapping/map/map.png",collision);
									charger_map_mobs("../Ressource/mobs.png","../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt",
											  "../Ressource/Mapping/map/map.png",collision);
									charger_map_biblio("../Ressource/Mapping/biblio.png","../Ressource/Mapping/biblio.txt",
										    "../Ressource/Mapping/map/biblio.png",collision2);
									charger_map_pnj_biblio("../Ressource/characters/xero.png","../Ressource/Mapping/pnj_biblio.txt",
											 "../Ressource/Mapping/map/biblio.png","../Ressource/Mapping/map/biblio.png",collision2);
								}
							}
							else if((choixMenuPlay - (choixMenuPlay % 10)) == SAVE3){
								quitMenu = 1;
								if(choixMenuPlay % 10 == LOAD){
									/** Placer la fonction de chargement de la sauvegarde ici */
									scene = OP;
								}
								else if(choixMenuPlay % 10 == NEWGAME){
									/** Placer la fonction de création de la sauvegarde ici */
									
									nom3 = entrerNom(pRenderer);
									creer_perso(&allPerso[0],nom3,"Golem",pRenderer,statsPerso[0]);
									creer_perso(&allPerso[1],"Xero","Mage",pRenderer,statsPerso[1]);
									creer_perso(&allPerso[2],"Toxo","Guerrier",pRenderer,statsPerso[2]);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									join_team(&team,allPerso);
									
									equiper_stuff(inventaire.equipements[1],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[4],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[11],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[12],team.team[0]);
							       	 equiper_stuff(inventaire.equipements[2],team.team[1]);
							       	 equiper_stuff(inventaire.equipements[10],team.team[2]);
									chargement(&scene,pRenderer,CINEMDEB);
									storyP1=loadTexture("../Ressource/cinem1.png",pRenderer);
									storyP2=loadTexture("../Ressource/cinem2.png",pRenderer);
									storyP3=loadTexture("../Ressource/cinem3.png",pRenderer);
									storyP4=loadTexture("../Ressource/cinem4.png",pRenderer);
									copie_fichier_mob_txt("../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt");
									charger_map("../Ressource/Mapping/tuiles_plaine.png","../Ressource/Mapping/level.txt",
										    "../Ressource/Mapping/map/map.png",collision);
									charger_map_pnj("../Ressource/pnj/pnj.png","../Ressource/Mapping/pnj.txt",
											 "../Ressource/Mapping/map/map.png","../Ressource/Mapping/map/map.png",collision);
									charger_map_mobs("../Ressource/mobs.png","../Ressource/Mapping/mobs.txt","../Ressource/Mapping/mobs2.txt",
											  "../Ressource/Mapping/map/map.png",collision);
									charger_map_biblio("../Ressource/Mapping/biblio.png","../Ressource/Mapping/biblio.txt",
										    "../Ressource/Mapping/map/biblio.png",collision2);
									charger_map_pnj_biblio("../Ressource/characters/xero.png","../Ressource/Mapping/pnj_biblio.txt",
											 "../Ressource/Mapping/map/biblio.png","../Ressource/Mapping/map/biblio.png",collision2);
								}
							}
							else if((choixMenuPlay - (choixMenuPlay % 10)) == BACK);
							
							if(choixMenuPlay == NOTHING){
								quitMenu = NOTHING;
								quitOp = 1;
							}
							break;
						case SETTINGS:
							menuSettings(pRenderer);
							break;
						case CREDITS:
							menuCredits(pRenderer);
							break;
						case NOTHING:
							quitMenu = NOTHING;
							break;
					}
				}
				
				/** boucle open world */
				while (!quitOp && quitMenu != NOTHING) {
					quitMenu = 0;

					/** récupération de la longueur et de la largeur de la fenètre */
					SDL_GetWindowSize(pWindow,&w,&h);

					/** Regarde sur qu'elle scene nous sommes pour gérer les évènemnets et affichage */
					switch(scene){

						/** Open World */
						case CINEMDEB:
							if(cinemStart == NULL){
								if(backMenu!=NULL){
									Mix_FreeMusic(backMenu);
									backMenu=NULL;
								}
								cinemStart = Mix_LoadMUS("../Ressource/Music/cinemStart.ogg");
								Mix_PlayMusic(cinemStart, -1);
							}
							cinematic_start(pRenderer,&next,&page1,&page2,&page3,&page4,&scene,&storyP1,&storyP2,&storyP3,&storyP4,&skipOn,
							&Map1,&Map2,&Map3,&Map4,&Map5,&Map6,collision);break;
							
						case OP:
							/** activation de la musique */
							if(backOp==NULL){
								if(backMenu!=NULL){
									Mix_FreeMusic(backMenu);
									backMenu=NULL;
								}
								if(cinemStart!=NULL){
									Mix_FreeMusic(cinemStart);
									cinemStart=NULL;
								}
								if(backP!=NULL){
									Mix_FreeMusic(backP);
									backP=NULL;
								}
								backOp = Mix_LoadMUS("../Ressource/Music/OPplaine.ogg");
								Mix_PlayMusic(backOp, -1);
							}
							/** détection des évènements */
							DetectEventsOp(&MouseOver,&KeyIsPressed,&Action,&scene,w,h,&choiceShop,&vendeur,&numperso);
							if(numperso>=team.nbPerso){
								numperso=0;
							}
							/** réaction aux évènements */
							if(Action==0){
								choiceShop=1;
							}
							
							/** nettoyage de l'écran et affichage de la map */
							if(map==0){
								SDL_RenderClear(pRenderer);
								switch(affichage_map++){
									case 0: afficher_map(dest.x,dest.y,pRenderer,Map1);
										break;
									case 1: afficher_map(dest.x,dest.y,pRenderer,Map2);
										break;
									case 2: afficher_map(dest.x,dest.y,pRenderer,Map3);
										break;
									case 3: afficher_map(dest.x,dest.y,pRenderer,Map4);
										break;
									case 4: afficher_map(dest.x,dest.y,pRenderer,Map5);
										break;
									case 5: afficher_map(dest.x,dest.y,pRenderer,Map6);
										affichage_map=0;
										break;
								}
								ReactEventsOp(MouseOver,KeyIsPressed,&Action,pRenderer,pPerso,marcheHori,
								&dest,&i,w,h,team,1,choiceShop,&vendeur,collision,vendeurDialoTexture,&map,&saveDest,numperso);
							}
							else if(map==1){
								SDL_RenderClear(pRenderer);
								afficher_map(dest.x,dest.y,pRenderer,biblio);
								ReactEventsOp(MouseOver,KeyIsPressed,&Action,pRenderer,pPerso,marcheHori,
								&dest,&i,w,h,team,1,choiceShop,&vendeur,collision2,vendeurDialoTexture,&map,&saveDest,numperso);
							}
							
							if (collision[dest.y/32][dest.x/32-1]>=8 || collision[dest.y/32][dest.x/32+1]>=8 
							    || collision[dest.y/32-1][dest.x/32]>=8 || collision[dest.y/32+1][dest.x/32]>=8){
							    MouseOver=-1;
							    MouseClick=-1;
							    SDL_DestroyTexture(Map1);
							    SDL_DestroyTexture(Map2);
							    SDL_DestroyTexture(Map3);
							    SDL_DestroyTexture(Map4);
							    SDL_DestroyTexture(Map5);
							    SDL_DestroyTexture(Map6);
							    chargement(&scene,pRenderer,FIGHT);
							    if (collision[dest.y/32][dest.x/32-1]>=8 ){
									detruire_mob(dest.x/32-1,dest.y/32,"../Ressource/Mapping/mobs2.txt",collision);
									
							    }
							    else if (collision[dest.y/32][dest.x/32+1]>=8){
									detruire_mob(dest.x/32+1,dest.y/32,"../Ressource/Mapping/mobs2.txt",collision);
									
							    }
							    else if (collision[dest.y/32-1][dest.x/32]>=8){
									detruire_mob(dest.x/32,dest.y/32-1,"../Ressource/Mapping/mobs2.txt",collision);
									
							    }
							    else if (collision[dest.y/32+1][dest.x/32]>=8){
									
									detruire_mob(dest.x/32,dest.y/32+1,"../Ressource/Mapping/mobs2.txt",collision);
									
							    }
							    charger_map("../Ressource/Mapping/tuiles_plaine.png","../Ressource/Mapping/level.txt","../Ressource/Mapping/map/map.png",collision);
						        charger_map_pnj("../Ressource/pnj/pnj.png","../Ressource/Mapping/pnj.txt",
										 "../Ressource/Mapping/map/map.png","../Ressource/Mapping/map/map.png",collision);
							};break;

							/** Menu Pause */
						case PAUSE:
							if(backP==NULL){
								Mix_FreeMusic(backOp);
								backOp=NULL;
								backP = Mix_LoadMUS("../Ressource/Music/Pause.mp3");
								Mix_PlayMusic(backP, -1);
							}
							switch(choixMenuPause = menuPause(pRenderer, &scene,Map1)){
								case SAVE:
									/** Appeler fonction sauvegarde */
									break;
								case SQUIT:
									/** Appeler fonction sauvegarde */
									chargement(&scene,pRenderer,MENUP);
									quitOp = 1;
									SDL_DestroyTexture(team.team[0]->MarcheHori);
									SDL_DestroyTexture(team.team[1]->MarcheFront);
									SDL_DestroyTexture(team.team[1]->MarcheBack);
									SDL_DestroyTexture(team.team[1]->MarcheHori);
									SDL_DestroyTexture(team.team[2]->MarcheFront);
									SDL_DestroyTexture(team.team[2]->MarcheBack);
									SDL_DestroyTexture(team.team[2]->MarcheHori);
									SDL_DestroyTexture(Map1);
									SDL_DestroyTexture(Map2);
									SDL_DestroyTexture(Map3);
									SDL_DestroyTexture(Map4);
									SDL_DestroyTexture(Map5);
									SDL_DestroyTexture(Map6);
									break;
								case OPTIONS:
									menuSettings(pRenderer);
								case RESUME:
									/** réaction aux évènements */
									scene = OP;
									break;
								case NOTHING:
									quitOp = 1;
									quitMenu = -1;
									break;
							};break;

						/** Menu Inventaire sac */
						case INVENTORY:
						
							/** met la touche de déplacements utiliser a son état d'arrét pour stoper afficher le personnage en bonne direction */
							if(KeyIsPressed==1){
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed>2){
								KeyIsPressed-=1;
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed==2){
								KeyIsPressed*=0;
							}
							
							/** nettoyage de l'écran et affichage de la map */
							SDL_RenderClear(pRenderer);
							switch(affichage_map++){
								case 0: afficher_map(dest.x,dest.y,pRenderer,Map1);
								        break;
								case 1: afficher_map(dest.x,dest.y,pRenderer,Map2);
								        break;
								case 2: afficher_map(dest.x,dest.y,pRenderer,Map3);
								        break;
								case 3: afficher_map(dest.x,dest.y,pRenderer,Map4);
								        break;
								case 4: afficher_map(dest.x,dest.y,pRenderer,Map5);
								        break;
								case 5: afficher_map(dest.x,dest.y,pRenderer,Map6);
								        affichage_map=0;
								        break;
							}
							DetectEventsInvSac(useOk,&yonUse,&yonThrow,&MouseClick,&MouseOver,&scene,w,h,destThrowButton);
							ReactEventsInvSac(useOk,&yonUse,&yonThrow,MouseClick,KeyIsPressed,MouseOver,pRenderer,w,h,&inventaire,&destThrowButton,team.team);break;
						
						/** Menu Inventaire des stats */
						case STAT:
						
							/** met la touche de déplacements utiliser a son état d'arrét pour stoper afficher le personnage en bonne direction */
							if(KeyIsPressed==1){
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed>2){
								KeyIsPressed-=1;
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed==2){
								KeyIsPressed*=0;
							}
					   	      
					   	        DetectEventsStats(&numPage,&MouseClick,&MouseOver,&scene,w,h,destStatAction,&team,statsPerso);
					   	        
					   	        /** garde le numero de page entre le nombre de perso et la page 1 */
					 	        if(numPage<0){
					 	      	   numPage=0;
					 	        }
					 	        else if(numPage==team.nbPerso){
					 	      	   numPage=team.nbPerso-1;
					 	        }
					 	         /** nettoyage de l'écran et affichage de la map */
							 SDL_RenderClear(pRenderer);
							 switch(affichage_map++){
								case 0: afficher_map(dest.x,dest.y,pRenderer,Map1);
								        break;
								case 1: afficher_map(dest.x,dest.y,pRenderer,Map2);
								        break;
								case 2: afficher_map(dest.x,dest.y,pRenderer,Map3);
								        break;
								case 3: afficher_map(dest.x,dest.y,pRenderer,Map4);
								        break;
								case 4: afficher_map(dest.x,dest.y,pRenderer,Map5);
								        break;
								case 5: afficher_map(dest.x,dest.y,pRenderer,Map6);
								        affichage_map=0;
								        break;
							}
					 	         ReactEventsStats(numPage,MouseClick,KeyIsPressed,MouseOver,pRenderer,w,h,&team,statsPerso,destStatAction);break;
						       
						/** Menu Inventaire des équipements */
						case EQUIPEMENT:
							
							/** met la touche de déplacements utiliser a son état d'arrét pour stoper afficher le personnage en bonne direction */
							if(KeyIsPressed==1){
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed>2){
								KeyIsPressed-=1;
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed==2){
								KeyIsPressed*=0;
							}
							DetectEventsInvStuff(&yonThrow,&MouseClick,&MouseOver,&scene,w,h,destThrowButton,&numPage,&numPagePerso,&slot,&eOuStuff);
							
							/** garde le numero de page entre le nombre max de page calculer et la page 1 */
							if(numPage<0){
					 	      	   numPage=0;
					 	        }
					 	        else {
					 	        	if(((inventaire.nbEquActu+inventaire.nbArmActu)/10.0)>((inventaire.nbEquActu+inventaire.nbArmActu)/10)){
									if(numPage==((inventaire.nbEquActu+inventaire.nbArmActu)/10)+1){
										numPage=((inventaire.nbEquActu+inventaire.nbArmActu)/10);
									}
								}
								else{
									if(numPage==((inventaire.nbEquActu+inventaire.nbArmActu)/10)){
										numPage=((inventaire.nbEquActu+inventaire.nbArmActu)/10)-1;
									}
								}	
					 	        }
					 	        
					 	        /** garde le numero de page entre le nombre de perso et la page 1 */
					 	        if(numPagePerso<0){
					 	      	   numPagePerso=0;
					 	        }
					 	        else if(numPagePerso==team.nbPerso){
					 	      	   numPagePerso=team.nbPerso-1;
					 	        }
					 	        
					 	        /** empèche le joueur de sélectionner uen zone d'équipement/armes ou il n'y a rien */
					 	        if(MouseClick>(inventaire.nbEquActu+inventaire.nbArmActu)){
					 	        	MouseOver=-1;
					 	        	MouseClick=-1;
					 	        }
					 	        
							ReactEventsInvStuff(&yonThrow,MouseClick,MouseOver,pRenderer,w,h,&inventaire,&destThrowButton,&team,numPage,numPagePerso,slot,&eOuStuff);break;
							
						/** Menu du magasin pour acheter de l'équipements/armes et objets*/
						case SHOP:
						
							/** nettoyage de l'écran et affichage de la map */
							SDL_RenderClear(pRenderer);
							 switch(affichage_map++){
								case 0: afficher_map(dest.x,dest.y,pRenderer,Map1);
								        break;
								case 1: afficher_map(dest.x,dest.y,pRenderer,Map2);
								        break;
								case 2: afficher_map(dest.x,dest.y,pRenderer,Map3);
								        break;
								case 3: afficher_map(dest.x,dest.y,pRenderer,Map4);
								        break;
								case 4: afficher_map(dest.x,dest.y,pRenderer,Map5);
								        break;
								case 5: afficher_map(dest.x,dest.y,pRenderer,Map6);
								        affichage_map=0;
								        break;
							}
							EventShop(&MouseOver,&Action,pRenderer,1,allStuff,&inventaire,w,h,&scene,allPot,&choiceBiy);break;
							
						/** Menu de vente pour vendre notre équipements/armes */
						case SELL:
						
							/** nettoyage de l'écran et affichage de la map */
							SDL_RenderClear(pRenderer);
							 switch(affichage_map++){
								case 0: afficher_map(dest.x,dest.y,pRenderer,Map1);
								        break;
								case 1: afficher_map(dest.x,dest.y,pRenderer,Map2);
								        break;
								case 2: afficher_map(dest.x,dest.y,pRenderer,Map3);
								        break;
								case 3: afficher_map(dest.x,dest.y,pRenderer,Map4);
								        break;
								case 4: afficher_map(dest.x,dest.y,pRenderer,Map5);
								        break;
								case 5: afficher_map(dest.x,dest.y,pRenderer,Map6);
								        affichage_map=0;
								        break;
							}
							EventSell(&MouseOver,&MouseClick,&Action,pRenderer,&inventaire,w,h,&scene,&numPage);break;
						case FIGHT:
							/** met la touche de déplacements utiliser a son état d'arrét pour stoper afficher le personnage en bonne direction */
							if(KeyIsPressed==1){
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed>2){
								KeyIsPressed-=1;
								KeyIsPressed*=-1;
							}
							else if(KeyIsPressed==2){
								KeyIsPressed*=0;
							}
							DetectEventsFight(&menu_combat,&MouseClick,&MouseOver, &quitCombat, &perso, &scene,w,h,&W, &H);
							ReactEventsFight(&p,perso, MouseClick,MouseOver,menu_combat,pRenderer,fond_combat,w,h,&inventaire,&team, mobs,H,W);
							if(scene==OP){
								chargement(&scene,pRenderer,OP);
								charger_map_mobs("../Ressource/mobs.png","../Ressource/Mapping/mobs.txt",
										  "../Ressource/Mapping/mobs2.txt","../Ressource/Mapping/map/map.png",collision);
								Map1=loadTexture("../Ressource/Mapping/map/map1.png",pRenderer);
								Map2=loadTexture("../Ressource/Mapping/map/map2.png",pRenderer);
								Map3=loadTexture("../Ressource/Mapping/map/map3.png",pRenderer);
								Map4=loadTexture("../Ressource/Mapping/map/map4.png",pRenderer);
								Map5=loadTexture("../Ressource/Mapping/map/map5.png",pRenderer);
								Map6=loadTexture("../Ressource/Mapping/map/map6.png",pRenderer);
							};break;
					}

					/** Mise a jour de l'écran */
					SDL_RenderPresent(pRenderer);
				}
			}
                        
                        /** réinitialisation de l'inventaire */
                        init_and_reinit_inv(&inventaire);
                        
                        /** Libération de la mémoire associée aux Musiques */
                        Mix_FreeMusic(backOp);
                        backOp=NULL;
                        Mix_FreeMusic(backP);
                        backP=NULL;
                        Mix_FreeMusic(backMenu);
                        backMenu=NULL;
                        Mix_FreeMusic(cinemStart);
                        backMenu=NULL;
                        
                        
                        if(nom1 != NULL)
                        	free(nom1);
                        if(nom2 != NULL)
                        	free(nom2);
                        if(nom3 != NULL)
                        	free(nom3);
                        	
                        /** Libération de la mémoire associée aux texture */
                        SDL_DestroyTexture(pPerso);
                        SDL_DestroyTexture(fond_combat);
                        for(i=0;i<ALL_OBJETS;i++){
			    	SDL_DestroyTexture(allPot[i].sprite);
			    	allPot[i].sprite=NULL;
			 }
			 for(i=0;i<ALL_EQUIPEMENTS;i++){
			    	SDL_DestroyTexture(allSpriteStuff[i]);
			    	allSpriteStuff[i]=NULL;
			 }
			 for(i=0;i<5;i++){
                        	SDL_DestroyTexture(vendeurDialoTexture[i]);
                        	vendeurDialoTexture[i]=NULL;
                        }
                    }
                    else
                    {
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                    }
        
                SDL_DestroyRenderer(pRenderer); /** Libération de la mémoire du SDL_Renderer */
            }
            else
            {
                fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
            }
            SDL_DestroyWindow(pWindow);
        }
     else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }
    
    /** fermeture de toutes les extensions SDL, IMG, TTF et AUDIO */
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

