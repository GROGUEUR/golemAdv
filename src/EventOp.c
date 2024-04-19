/**
* \file EventOp.c
* \brief programme gérant les events dans l'open-world
* \author Cognard Luka,François Lépine.
* \version 1.9.8
* \date 16 Avril 2024.
*/

#include "../lib/EventOp.h"
#include <time.h>

/** Fonction pour réaliser une transition en fondu */
void transitionFondu(SDL_Renderer* renderer, int largeur_ecran, int hauteur_ecran, int duree) {
    /** Nombre d'images et délai d'affichage */
    int nbFrames = 60;
    int delay = duree / nbFrames;

    /** Boucle pour effectuer le fondu */
    for (int i = 0; i <= nbFrames; ++i) {
        /** Calculer l'alpha en fonction du progrès de la transition */
        Uint8 alpha = (Uint8)(255 * (1.0 * i / nbFrames));

        /** Affichage du fondu */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_Rect rect = {0, 0, largeur_ecran, hauteur_ecran};
        SDL_RenderFillRect(renderer, &rect);

        /** Mettre à jour l'affichage */
        SDL_RenderPresent(renderer);

        /** Délai d'affichage */
        SDL_Delay(delay);
    }
}

/** fonction faisant l'écran de chargement entre certaine scene  */
void chargement(scene_t * scene, SDL_Renderer* pRenderer,scene_t futurScene){
	SDL_Texture * loading=loadTexture("../Ressource/load.png",pRenderer);
	SDL_Texture * golemHead=loadTexture("../Ressource/Golemhead.png",pRenderer);
	SDL_Rect selLoadSprite={0,0,32,32};
	SDL_Rect selHeadSprite={0,0,13,12};
	SDL_Rect destLoadingHead={(1360-128)/2,(780-128)/2,128,128};
	SDL_Rect destLoading={destLoadingHead.x,destLoadingHead.y+128*0.6,192,192};
	time_t start_time = time(NULL); // Enregistrement du temps de départ
	while (1) {
		SDL_RenderClear(pRenderer);
		SDL_RenderCopy(pRenderer,golemHead,&selHeadSprite,&destLoadingHead);
		SDL_RenderCopy(pRenderer,loading,&selLoadSprite,&destLoading);
		selHeadSprite.x=(selHeadSprite.x+13)%104;
		selLoadSprite.x=(selLoadSprite.x+32)%128;
		SDL_Delay(75);
		SDL_RenderPresent(pRenderer);
		time_t current_time = time(NULL);
		if (current_time - start_time >= 1) {
		    break; // Sortir de la boucle après 5 secondes
		}
	}
	*scene=futurScene;
}

/** fonction gérant l'affichage et les évenements de la cinématique de début de jeux */
void cinematic_start(SDL_Renderer* pRenderer,int * next,SDL_Rect * P1,SDL_Rect * P2,SDL_Rect * P3,SDL_Rect * P4, scene_t * scene,SDL_Texture ** storyP1,SDL_Texture ** storyP2,SDL_Texture ** storyP3,SDL_Texture ** storyP4,int *skipOn,SDL_Texture ** Map1,SDL_Texture ** Map2,SDL_Texture ** Map3,SDL_Texture ** Map4,SDL_Texture ** Map5,SDL_Texture ** Map6,int colli[125][250]){

    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0) {
    
          /** récuperation des touche relacher */
          switch(event.type){
          	case SDL_KEYUP:
          	/** regarde si la touche entrer a été relacher */
		  	if(event.key.keysym.sym==SDLK_RETURN){
		  		SDLK_RETURN:*next+=1;
		  	}break;
		  	
		/** récupération de la position de la sourit */
		case SDL_MOUSEMOTION:
			/** regarde si la sourit est sur le bouton skip */
			  if ((event.motion.y >=0 && event.motion.y <= 60) && (event.motion.x >=1360-70 && event.motion.x <= 1354)){
			  	*skipOn=0;
			  }
			  else{
			  	*skipOn=-1;
			  }break;
			  
		/** récupération d'un bouton relacher venant de la sourit */
		case SDL_MOUSEBUTTONUP:
			/** vérifie que la sourit est sur le bouton skip pour réagir au clique */
			if(*skipOn==0){
				/** passe l'histoire réinitialisation de toutes les variables utilisé ici plus passage sur l'écran de chargement vers l'OP  */
				chargement(scene,pRenderer,OP);
				SDL_DestroyTexture((*storyP1));
			     	SDL_DestroyTexture((*storyP2));
			     	SDL_DestroyTexture((*storyP3));
			     	SDL_DestroyTexture((*storyP4));
			     	P1->x=0;
			     	P2->x=1360;
			     	P3->x=1360*2;
			     	P4->x=1360*3;
				*next=0;
				*skipOn=-1;
				
				/** chargement des textures des map */
				*Map1=loadTexture("../Ressource/Mapping/map/map1.png",pRenderer);
				*Map2=loadTexture("../Ressource/Mapping/map/map2.png",pRenderer);
				*Map3=loadTexture("../Ressource/Mapping/map/map3.png",pRenderer);
				*Map4=loadTexture("../Ressource/Mapping/map/map4.png",pRenderer);
				*Map5=loadTexture("../Ressource/Mapping/map/map5.png",pRenderer);
				*Map6=loadTexture("../Ressource/Mapping/map/map6.png",pRenderer);
				return ;
			}break;
		
          }
    }
    
    int i=0;
    SDL_Color blanc={255,255,255};
    
    /** texte de l'histoire séparé en 2 partie  ici 1er partie */
    char texteN1[8][100]={"A la recherche des plus grands tresors, le chercheur de tresors C",
    			   "Intriguer par un bruit etrange, il trouve un caillou anime,",
    			   "De retour dans la plaine ou tout a commence, G et ses amis s'arretent dans un village",
    			   "Mais leur sejour se transforme en cauchemar lorsque le village se revele etre",
    			   "Alors que le python attaque le village ou se trouvent C et G,",
    			   "G tente desesperement de proteger C, mais le python surpuissant triomphe,laissant G",
    			   "Consume par la colere et la soif de vengeance, son esprit est envahi",
    			   "Il nourrit un desir ardent de venger la mort de son ami, pret a tout"
    			  };
    			  
    /** texte de l'histoire séparé en 2 partie  ici 2eme partie */
    char texteN2[8][150]={"explore une grotte oubliee dans une vaste plaine, decouvrant un mystere inattendu.",
    			   "realisant que cette pierre insolite est le veritable tresor de la grotte.",
    			   "paisible pour celebrer leur amitie, ignorant le danger imminent.",
    			   "sous la menace d'un tyran redoutable, un python dominant le grand marais voisin.",
    			   "la destruction est imparable, les habitants sont massacres et la zone est devastee.",
    			   "seul devant la tragedie de la perte de son ami, un destin qu'il n'aurait jamais pu anticiper.",
    			   "par des pensees sombres et determinees.",
    			   "pour tuer de ses propres mains celui qu'il considere comme le meurtrier."
    			  };
    			  
    /** chargement des textures des textes */
    SDL_Texture* texte[8];
    SDL_Texture* texte2[8];
    for(i=0;i<8;i++){
	    texte[i]=loadTextureFont("../Ressource/font/LifeCraft.ttf",pRenderer,texteN1[i],34,blanc);
	    texte2[i]=loadTextureFont("../Ressource/font/LifeCraft.ttf",pRenderer,texteN2[i],34,blanc);
    }
    
    /** chargement de la texture, déclaration des dimensions/coordonnées du bouton skip */
    SDL_Texture* skip=loadTexture("../Ressource/skip.png",pRenderer);
    SDL_Rect skipDest={1360-70,0,64,60};
    
    /** déclaration des dimensions/coordonnées des textes */
    SDL_Rect textDest[8];
    SDL_Rect textDest2[8];
    SDL_Rect fontTexte={(1360-1100)/2,780-32*3.5,1100,32*3};
    for(i=0;i<8;i++){
	    SDL_QueryTexture(texte[i], NULL, NULL, &textDest[i].w, &textDest[i].h);
	    textDest[i].x=(1360-textDest[i].w)/2;
	    textDest[i].y=780-textDest[i].h*3;
	    
	    
	    SDL_QueryTexture(texte2[i], NULL, NULL, &textDest2[i].w, &textDest2[i].h);
	    textDest2[i].x=(1360-textDest2[i].w)/2;
	    textDest2[i].y=780-textDest2[i].h*1.5;
    }
    
    /** affiche la première partie de l'histoire texte numero 1 puis 2 après appuyer sur entrée */
    if(*next<=1){
        SDL_RenderCopy(pRenderer,(*storyP1),NULL,P1);
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 200);
	SDL_RenderFillRect(pRenderer, &fontTexte);
	SDL_RenderCopy(pRenderer,texte[*next],NULL,&textDest[*next]);
	SDL_RenderCopy(pRenderer,texte2[*next],NULL,&textDest2[*next]);
    }
    
    /** affiche la deuxième partie de l'histoire de même */
    else if (*next<=3){
    		while(P2->x != 0){
    			SDL_RenderClear(pRenderer);
    			P1->x-=5;
    			P2->x-=5;
    			if(P2->x<0){
    				P2->x=0;
    				P1->x=0-1360;
    			}
    			SDL_RenderCopy(pRenderer,(*storyP1),NULL,P1);
    			SDL_RenderCopy(pRenderer,(*storyP2),NULL,P2);
    			SDL_RenderPresent(pRenderer);
    		}
    		SDL_RenderClear(pRenderer);
    		SDL_RenderCopy(pRenderer,(*storyP2),NULL,P2);
    		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 200);
		SDL_RenderFillRect(pRenderer, &fontTexte);
    		SDL_RenderCopy(pRenderer,texte[*next],NULL,&textDest[*next]);
		SDL_RenderCopy(pRenderer,texte2[*next],NULL,&textDest2[*next]);
    }
    
    /** affiche la troisième partie de l'histoire de même */	
    else if (*next<=5){
    		if(P3->x>1360) 
    			P3->x=1360;
    		while(P3->x != 0){
    			SDL_RenderClear(pRenderer);
    			P2->x-=5;
    			P3->x-=5;
    			if(P3->x<0){
    				P3->x=0;
    				P2->x=0-1360;
    			}
    			SDL_RenderCopy(pRenderer,(*storyP2),NULL,P2);
    			SDL_RenderCopy(pRenderer,(*storyP3),NULL,P3);
    			SDL_RenderPresent(pRenderer);
    		}
    		SDL_RenderClear(pRenderer);
    		SDL_RenderCopy(pRenderer,(*storyP3),NULL,P3);
    		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 200);
		SDL_RenderFillRect(pRenderer, &fontTexte);
    		SDL_RenderCopy(pRenderer,texte[*next],NULL,&textDest[*next]);
		SDL_RenderCopy(pRenderer,texte2[*next],NULL,&textDest2[*next]);
    }
    
    /** affiche la quatrième partie de l'histoire de même */
    else if (*next<=7){
    		if(P4->x>1360){
    			if(P3->x>1360){
	    			P3->x=1360;
	    			while(P3->x != 0){
		    			SDL_RenderClear(pRenderer);
		    			P2->x-=5;
		    			P3->x-=5;
		    			if(P3->x<0){
		    				P3->x=0;
		    				P2->x=0-1360;
		    			}
		    			SDL_RenderCopy(pRenderer,(*storyP2),NULL,P2);
		    			SDL_RenderCopy(pRenderer,(*storyP3),NULL,P3);
		    			SDL_RenderPresent(pRenderer);
		    		}
	    		}
    			P4->x=1360;
    		}
    		while(P4->x != 0){
    			SDL_RenderClear(pRenderer);
    			P3->x-=5;
    			P4->x-=5;
    			if(P4->x<0){
    				P4->x=0;
    				P3->x=0-1360;
    			}
    			SDL_RenderCopy(pRenderer,(*storyP3),NULL,P3);
    			SDL_RenderCopy(pRenderer,(*storyP4),NULL,P4);
    			SDL_RenderPresent(pRenderer);
    		}
    		SDL_RenderClear(pRenderer);
    		SDL_RenderCopy(pRenderer,(*storyP4),NULL,P4);
    		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 200);
		SDL_RenderFillRect(pRenderer, &fontTexte);
    		SDL_RenderCopy(pRenderer,texte[*next],NULL,&textDest[*next]);
		SDL_RenderCopy(pRenderer,texte2[*next],NULL,&textDest2[*next]);
    }
    
    /** fin de l'histoire réinitialisation de toutes les variables utilisé ici plus passage sur l'écran de chargement vers l'OP  */
    else {
    	chargement(scene,pRenderer,OP);
    	/** destruction des images illustrant l'histoire */
     	SDL_DestroyTexture((*storyP1));
     	SDL_DestroyTexture((*storyP2));
     	SDL_DestroyTexture((*storyP3));
     	SDL_DestroyTexture((*storyP4));
     	P1->x=0;
     	P2->x=1360;
     	P3->x=1360*2;
     	P4->x=1360*3;
     	*next=0;
     	
     	/** chargement des textures des map */
	*Map1=loadTexture("../Ressource/Mapping/map/map1.png",pRenderer);
	*Map2=loadTexture("../Ressource/Mapping/map/map2.png",pRenderer);
	*Map3=loadTexture("../Ressource/Mapping/map/map3.png",pRenderer);
	*Map4=loadTexture("../Ressource/Mapping/map/map4.png",pRenderer);
	*Map5=loadTexture("../Ressource/Mapping/map/map5.png",pRenderer);
	*Map6=loadTexture("../Ressource/Mapping/map/map6.png",pRenderer);
    }
    
    /** destruction de toutes les textures créer */
    for(i=0;i<8;i++){
	    SDL_DestroyTexture(texte[i]);
    	    SDL_DestroyTexture(texte2[i]);
    }
    SDL_RenderCopy(pRenderer,skip,NULL,&skipDest);
    SDL_DestroyTexture(skip);
    
    /** delais d'affichage */
}

/**
* fonction DetectEventsOp qui s'occupera de gérer la détection
* des évènement quand nous somme sur l'openWorld 
*/

void DetectEventsOp(int* MouseOver,int* KeyIsPressed, int *Action, scene_t* scene,int w,int h,int* choiceShop,int* vendeur,int* numperso){
    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0) {
    	   switch(event.type){
    	   	case SDL_QUIT:
    	   		if(*Action==0){
    	   			*scene=PAUSE;
    	   		};break;
    	   
		  /** récuperation des touche enfoncer */
		  case SDL_KEYDOWN:
		  
		  /** regarde qu'elle touche est enfoncer */
		  	if(*Action==0){
			  	switch(event.key.keysym.sym){
			  		case SDLK_q:
			  		/** test si la touche est maintenu change la variable KeyIsPressed */
			  			    if (*KeyIsPressed <= 0) {
				           		*KeyIsPressed = 1;
				       	    };break;
			       	case SDLK_d:
				       	    if (*KeyIsPressed <= 0) {
						       *KeyIsPressed = 2;
						   };break;
			       	case SDLK_z:
				       	    if (*KeyIsPressed <= 0) {
						       *KeyIsPressed = 3;
						   };break;
			       	case SDLK_s:
				       	    if (*KeyIsPressed <= 0) {
						       *KeyIsPressed = 4;
						   };break;
				       
			  	}
			};break;
		  
		  /** récupération des coordonnée de la souris */
		 case SDL_MOUSEMOTION:
			  
			  if(*Action==0){
			  /** regarde si la sourit est dans les case d'objets */
				  if (event.motion.y >= h-48 && event.motion.y <= h){
				  	if(event.motion.x >= w-48 && event.motion.x <= w){
				  		*MouseOver=3;
				  	}
				  	else if(event.motion.x >= w-96 && event.motion.x <= w-48){
				  		*MouseOver=2;
				  	}
				  	else if(event.motion.x >= w-144 && event.motion.x <= w-96){
				  		*MouseOver=1;
				  	}
				  	else{
				  		*MouseOver=-1;
				  	}
				  }
				  else{
				  	*MouseOver=-1;
				  }
			  };break;
				  
		  /** récuperation des touche relacher changement de KeyIsPressed */
		  case SDL_KEYUP:
		       /** regarde qu'elle touche a été relacher 
		       * et change la variable KeyIsPressed en fonction de la touche 
		       */
		       switch(event.key.keysym.sym){
		       	/** touche de déplacement z,q,s,d */
		       	case SDLK_d:*KeyIsPressed = 0;break;
		       	case SDLK_q:*KeyIsPressed = -1;break;
		       	case SDLK_z:*KeyIsPressed = -2;break;
		       	case SDLK_s:*KeyIsPressed = -3;break;
		       	
		       	/** touche pour changer de personnage */
		       	case SDLK_TAB:*numperso +=1 ;break;
		       	
		       	/** touche d'interaction */
		               case SDLK_f:
		               	if(*vendeur){
		               		if(*Action==4){
		               			*Action=0;
		               			*vendeur=0;
		               		}
		               		else if(*Action==2){
		               			*scene=SHOP;
		               		}
		               		else if(*Action==3){
		               			*scene=SELL;
		               		}
		               	}
		               	else{
		               		*Action+=1;
		               	};break;
		               	
		               /** touche pour faire pause */
		               case SDLK_ESCAPE: 
		               	if(*Action==0){
		               		*scene=PAUSE;
		               	};break;
		               	
		               /** touche d'ouverture d'inventaire sac */
		               case SDLK_i: 
		               	if(*Action==0){
		               		*scene=INVENTORY;
		               	};break;
		               	
		               /** touche d'ouverture d'inventaire équipements/armes */
		               case SDLK_e: 
		               	if(*Action==0){
		               		*scene=EQUIPEMENT;
		               	};break;
		               	
		               /** touche d'ouverture des stats */
		               case SDLK_t: 
		               	if(*Action==0){
		               		*scene=STAT;
		               	};break;
		               	
		               /** touche flèche du haut pour les choix du vendeur */
		               case SDLK_UP:
		               	      if(*Action>0){
		               	      	if(*choiceShop==1){
		               	      		*choiceShop=3;
		               	      	}
		               	      	else{
		               	      		*choiceShop-=1;
		               	      	}
		               	      }
		               	      
		               	      else{
		               	      	*choiceShop=1;
		               	      };break;
		               	
		               /** touche flèche du bas pour les choix du vendeur */      
		               case SDLK_DOWN:
		               	      if(*Action>0){
		               	      	if(*choiceShop==3){
		               	      		*choiceShop=1;
		               	      	}
		               	      	else{
		               	      		*choiceShop+=1;
		               	      	}
		               	      }
		               	    
		               	      else{
		               	      	*choiceShop=1;
		               	      };break;
		               	      
		               /** touche entrer pour valider les choix du vendeur */  
		               case SDLK_RETURN:
		               		if(*vendeur==1 && (*Action==1 || *Action==5)){
				       		if(*choiceShop==3){
				       			*Action=4;
				       			*choiceShop=1;
				       		}
				       		else if(*choiceShop==1){
				       			*Action=2;
				       			*choiceShop=1;
				       		}
				       		else if(*choiceShop==2){
				       			*Action=3;
				       			*choiceShop=1;
				       		}
				       	}
		       };break;
		 
		 /** détection clique sourit relaché */  
		 case SDL_MOUSEBUTTONUP:
		 
		 	/** icone d'inventaire sac d'objets */
		 	if(*MouseOver==1){
		 		*MouseOver=-1;
		 		*scene=INVENTORY;
		 	}
		 	
		 	/** icone des stats */
		 	else if(*MouseOver==2){
		 		*MouseOver=-1;
		 		*scene=STAT;
		 	}
		 	
		 	/** icone d'inventaire équipements/armes */
		 	else if(*MouseOver==3){
		 		*MouseOver=-1;
		 		*scene=EQUIPEMENT;
		 	};break;
	    }          
    }
}

/**
* fonction chargement_barre_pv qui s'occupe de charger la bonne textures 
* pour la barre de PV selon le % de PV actuel
*/

void chargement_barre_pv(int pourcent,SDL_Texture** pvJauge, SDL_Texture** pvActu,SDL_Renderer* pRenderer){

	/** PV supérieur ou égale a 50% barre verte*/
	if(pourcent>=50){
		*pvJauge=loadTexture("../Ressource/PvJauge.png",pRenderer);
		*pvActu=loadTexture("../Ressource/PvActu.png",pRenderer);
		
	}
	
	/** PV supérieur ou égale a 20% mais inférieur a 50% barre jaune*/
	else if(pourcent>=20){
		*pvJauge=loadTexture("../Ressource/PvMidJauge.png",pRenderer);
		*pvActu=loadTexture("../Ressource/PvMidActu.png",pRenderer);
	}
	/** PV inférieur a 20% barre rouge*/
	else{
		*pvJauge=loadTexture("../Ressource/PvLowJauge.png",pRenderer);
		*pvActu=loadTexture("../Ressource/PvLowActu.png",pRenderer);
	}
}

/**
* fonction ReactEventsOp qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur l'openWorld
*/

void ReactEventsOp(int *avancement_quete,int MouseOver,int KeyIsPressed, int *Action,SDL_Renderer* pRenderer,SDL_Texture* Perso,SDL_Rect marcheHori[3][8],SDL_Rect* dest,int* i,int w,int h,team_t team,int biome,int choiceShop,int* vendeur,int colli[125][250],SDL_Texture * vendeurDialoTexture[5],int *map,SDL_Rect* savedest,int numperso){
     int j, inter=0;
     
     
     int pourcent=0;
     
     
     /** déclarations des textes pour les pnjs */
     char textLore[4][49]={"Bonjour jeune aventurier !!!","Tu es parti pour te venger et je le comprends...",
     			    "Mais avant ca, va voir notre magicien Xero...","Pour en apprendre plus sur notre monde."};
     char textXero[9][61]={"UN...UN GOLEM?! Qui es-tu?","C'est le vieux qui t'envoie donc...","Tu sais Epikrato rode dans les alentours...",
     			    "Il fait regner la peur depuis qu'il pille nos ressources","Je cherche un moyen de l'eradiquer depuis longtemps",
     			    "Si tu te mets en quete de te debarasser de lui je t'aiderais","Tu dis que tu as besoin d'un mage alors aide moi et...",
     			    "je t'aiderais en retour !!!!!","Mais d'abord deviens plus fort. '-' "};
     SDL_Texture * dialogueXero;
     SDL_Texture * dialogueLore;

     /** décllaration texture des icones */
     SDL_Texture* SacIcone=NULL;
     SDL_Texture* StatIcone=NULL;
     SDL_Texture* StuffIcone=NULL;
     
     /** décllaration texture des PV et PM des persos */
     SDL_Texture* firstPerso=NULL;
     SDL_Texture* secondPerso=NULL;
     SDL_Texture* thirdPerso=NULL;
     
     SDL_Texture* pvJauge=NULL;
     SDL_Texture* pmJauge=NULL;
     
     SDL_Texture* pvActu=NULL;
     SDL_Texture* pmActu=NULL;
     
     /** coordonnée et dimensions des PV et PM des persos */
     SDL_Rect firstPersoDest={0,0,48,48};
     SDL_Rect secondPersoDest={0,56,32,32};
     SDL_Rect thirdPersoDest={0,96,32,32};
     
     SDL_Rect pvFirst={56,(48/4),64,8};
     SDL_Rect pvSecond={40,56+(32/4),48,6};
     SDL_Rect pvThird={40,96+(32/4),48,6};
     
     SDL_Rect pmFirst={56,(48/4)*2,64,8};
     SDL_Rect pmSecond={40,56+(32/4)*2,48,6};
     SDL_Rect pmThird={40,96+(32/4)*2,48,6};
     
     /** coordonnée et dimensions des icones */
     SDL_Rect sacIconeDest={w-144,h-48,48,48};
     SDL_Rect statIconeDest={w-96,h-48,48,48};
     SDL_Rect stuffIconeDest={w-48,h-48,48,48};
     
     /** déclarations des dimensions/coordonnées des dialogues */
     SDL_Rect DestLore={200,h/4*3-100,w-400,h/10};
     SDL_Rect DestLoreBack={150,h/4*3-100,w-350,h/9};
     
     /** déclaration des dimensions/coordonnées du perso centré */
     SDL_Rect affPerso={1360/2-32/2,780/2-32/2,32,32};
     
     /** déclaration des dimensions/coordonnées des dialogues du vendeur */
     SDL_Rect dialogue={(w-800)/2,h-155,800,150};
     
     /** déclaration de la couleur du texte */
     SDL_Color blanc={255,255,255};
     
     switch(KeyIsPressed){
        /** déplacement vers la gauche détecte les collisions si oui bloque le personnage */
        case 1:
        	if(colli[dest->y/32][dest->x/32-1]!=0){
        		dest->x-=7;
        	}
        	if(numperso==0){
			SDL_RenderCopyEx(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%6),&affPerso, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else if(numperso==2){
			SDL_RenderCopyEx(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%4),&affPerso, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else{
			SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+4+((++*i)%4),&affPerso);
		};break;
	/** déplacement vers la droite détecte les collisions si oui bloque le personnage */
        case 2:
        	if(colli[dest->y/32][dest->x/32+1]!=0){
        		dest->x+=7;
        	}
        	if(numperso==0){
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%6),&affPerso);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%4),&affPerso);
        	};break;
        /** déplacement vers le haut détecte les collisions si oui bloque le personnage */
        case 3:
        	if(colli[dest->y/32-1][dest->x/32]!=0){
        		dest->y-=7;
        	}
        	if(numperso==0){
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%6),&affPerso);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheBack,marcheHori[2]+((++*i)%4),&affPerso);
        	};break;
        /** déplacement vers le bas détecte les collisions si oui bloque le personnage */
        case 4:
        	if(colli[dest->y/32+1][dest->x/32]!=0){
        		dest->y+=6;
        	}
        	if(numperso==0){
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+((++*i)%6),&affPerso);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheFront,marcheHori[2]+((++*i)%4),&affPerso);
        	};break;
        
        /** cas ou le personnage s'arrète vers la droite */
        case 0:
        	if(numperso!=1){
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+0,&affPerso);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+3,&affPerso);
        	};break;
        
        /** cas ou le personnage s'arrète vers la gauche */
        case -1:
        	if(numperso!=1){
        		SDL_RenderCopyEx(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+0,&affPerso, 0, NULL, SDL_FLIP_HORIZONTAL);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheHori,marcheHori[numperso]+4,&affPerso);
        	};break;
        
        /** cas ou le personnage s'arrète vers le haut */
        case -3:
        	if(numperso==0){
        		SDL_RenderCopy(pRenderer,team.team[0]->MarcheHori,marcheHori[numperso]+0,&affPerso);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheFront,marcheHori[2]+0,&affPerso);
        	};break;
        
        /** cas ou le personnage s'arrète vers le bas */
        case -2:
        	if(numperso==0){
        		SDL_RenderCopyEx(pRenderer,team.team[0]->MarcheHori,marcheHori[numperso]+0,&affPerso, 0, NULL, SDL_FLIP_HORIZONTAL);
        	}
        	else{
        		SDL_RenderCopy(pRenderer,team.team[numperso]->MarcheBack,marcheHori[2]+0,&affPerso);
        	};break;
        
     }
     
     /** réinitialisation du i pour éviter qu'il dépasse la valeur max d'un int
     */
     if(*i%6==0){
     	*i=0;
     }
     
     /** test si le personnage est en face d'un pnj vendeur pour faire une interraction
     * une fois la touche f appuyer
     */
     
     if (colli[dest->y/32][dest->x/32-1]==5 || colli[dest->y/32][dest->x/32+1]==5 || colli[dest->y/32-1][dest->x/32]==5 || colli[dest->y/32+1][dest->x/32]==5){
		if(*Action>0){
			*vendeur=1;
			if(*Action<6){
				SDL_RenderCopy(pRenderer,vendeurDialoTexture[*Action-1],NULL,&dialogue);
			}
			if(*Action==1 || *Action==5 ){
				SDL_Texture* choiceBox=NULL;
				switch(choiceShop){
					case 1: choiceBox=loadTexture("../Ressource/pnj/dialogue/shopChoiceBiy.png",pRenderer);break;
					case 2: choiceBox=loadTexture("../Ressource/pnj/dialogue/shopChoiceSell.png",pRenderer);break;
					case 3: choiceBox=loadTexture("../Ressource/pnj/dialogue/shopChoiceQuit.png",pRenderer);break;
				}
				
				dialogue.x+=dialogue.w-150;
				dialogue.y-=150;
				dialogue.h=dialogue.w=150;
				SDL_RenderCopy(pRenderer,choiceBox,NULL,&dialogue);
				SDL_DestroyTexture(choiceBox);
			}
			inter=1;
		}
		
     }
     else{
	*vendeur=0;
     }
     
     /** test si le personnage est en face d'un pnj pour faire une interraction
     * une fois la touche f appuyer
     */
     if ((colli[dest->y/32][dest->x/32-1]==6 || colli[dest->y/32][dest->x/32+1]==6 || colli[dest->y/32-1][dest->x/32]==6 || colli[dest->y/32+1][dest->x/32]==6)&& (*avancement_quete)==0){
		if(*Action>0){
			if(*Action<5){
				dialogueLore=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,textLore[(*Action)-1],20,blanc);
				SDL_Texture* noirFont=loadTexture("../Ressource/pnj/fond.png",pRenderer);
				SDL_RenderCopy(pRenderer,noirFont,NULL,&DestLoreBack);
				SDL_RenderCopy(pRenderer,dialogueLore,NULL,&DestLore);
				SDL_DestroyTexture(noirFont);
				SDL_DestroyTexture(dialogueLore);
			}
			else{
				*avancement_quete=1;
				*Action=0;
			}
			inter=1;
		}
		
     }
     /** test si le personnage est en face d'un pnj pour faire une interraction
     * une fois la touche f appuyer
     */
     if ((colli[dest->y/32][dest->x/32-1]==15 || colli[dest->y/32][dest->x/32+1]==15 || colli[dest->y/32-1][dest->x/32]==15 || colli[dest->y/32+1][dest->x/32]==15)&& (*avancement_quete)==2){
		if(*Action>0){
			if(*Action<10){
				SDL_Texture* noirFont=loadTexture("../Ressource/pnj/fond.png",pRenderer);
				dialogueXero=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,textXero[(*Action)-1],20,blanc);
				SDL_RenderCopy(pRenderer,noirFont,NULL,&DestLoreBack);
				SDL_RenderCopy(pRenderer,dialogueXero,NULL,&DestLore);
				SDL_DestroyTexture(noirFont);
				SDL_DestroyTexture(dialogueXero);
			}
			else{
				*avancement_quete=3;
				*Action=0;
			}
			inter=1;
		}
		
     }
     
     /** test s'il est possible pour le personnage de changer de zone */
     if (colli[dest->y/32][dest->x/32-1]==3 || colli[dest->y/32][dest->x/32+1]==3 || colli[dest->y/32-1][dest->x/32]==3 || colli[dest->y/32+1][dest->x/32]==3){
		if(*Action>0){
			if(*map==0 && (*avancement_quete)==1){
				(*avancement_quete)=2;
				*map+=1;
				savedest->x=dest->x;
				savedest->y=dest->y;
				savedest->w=dest->w;
				savedest->h=dest->h;
				dest->x= 29*32;
				dest->y= 25*32;
				*Action=0;
			}
			else if(*map==0){
				*map+=1;
				savedest->x=dest->x;
				savedest->y=dest->y;
				savedest->w=dest->w;
				savedest->h=dest->h;
				dest->x= 29*32;
				dest->y= 25*32;
				*Action=0;
			}
			else{
				*map-=1;
				dest->x=savedest->x;
				dest->y=savedest->y;
				dest->w=savedest->w;
				dest->h=savedest->h;
				*Action=0;
			}
		}
		
     }
     
     /** si il n'y a aucune interaction avec des pnjs réinitialise l'action */
     if(!inter){
     	*Action=0;
     }
     
     /** chargement des textures selon si la souris est sur l'icone ou non */
     if(MouseOver==1){
     	SacIcone=loadTexture("../Ressource/IconeSacHover.png",pRenderer);
     }
     else{
     	SacIcone=loadTexture("../Ressource/IconeSacDefault.png",pRenderer);
     }
     
     if(MouseOver==2){
     	StatIcone=loadTexture("../Ressource/IconeStatHover.png",pRenderer);
     }
     else{
     	StatIcone=loadTexture("../Ressource/IconeStatDefault.png",pRenderer);
     }
     
     if(MouseOver==3){
     	StuffIcone=loadTexture("../Ressource/IconeStuffHover.png",pRenderer);
     }
     else{
     	StuffIcone=loadTexture("../Ressource/IconeStuffDefault.png",pRenderer);
     }
     
     /** chargement, affichage et destruction des têtes des persos ainsi que leur PV et PM */
     switch(team.nbPerso){
     	/** cas ou 1 perso sont dans l'équipe */
     	case 1: firstPerso=loadTexture("../Ressource/characters/GolemHead.png",pRenderer);
     		pourcent=(team.team[0]->Pv)/(team.team[0]->PvMax/100.0);
     		SDL_RenderCopy(pRenderer,firstPerso,NULL,&firstPersoDest);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso */
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvFirst);
		pvFirst.w=(pvFirst.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvFirst);
     		
     		/** chargement de la barre de Mana selon le pourcentage de Mana du perso si il c'est PM max son de 0 barre griser */
     		if(team.team[0]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[0]->Mana)/(team.team[0]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
			pmFirst.w=(pmFirst.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmFirst);
		}
     		SDL_DestroyTexture(firstPerso);
     		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		SDL_DestroyTexture(pmJauge);
     		SDL_DestroyTexture(pmActu);break;
     		
     	/** cas ou 2 perso sont dans l'équipe */
     	case 2: 
     		/** chargement des têtes des 2 personnage  */
     		firstPerso=loadTexture("../Ressource/characters/GolemHead.png",pRenderer);
     		secondPerso=loadTexture("../Ressource/characters/MageHead.png",pRenderer);
     		
     		/** affichage des têtes des 2 personnage */
     		SDL_RenderCopy(pRenderer,firstPerso,NULL,&firstPersoDest);
     		SDL_RenderCopy(pRenderer,secondPerso,NULL,&secondPersoDest);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso 1 plus destruction de leur texture */
     		pourcent=(team.team[0]->Pv)/(team.team[0]->PvMax/100.0);
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvFirst);
		pvFirst.w=(pvFirst.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvFirst);
		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso 2 */
		pourcent=(team.team[1]->Pv)/(team.team[1]->PvMax/100.0);
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvSecond);
		pvSecond.w=(pvSecond.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvSecond);
		
		/** chargement de la barre de Mana selon le pourcentage de Mana du perso 1 si il c'est PM max son de 0 barre griser */
		if(team.team[0]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[0]->Mana)/(team.team[0]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
			pmFirst.w=(pmFirst.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmFirst);
		}
		
		/** chargement de la barre de Mana selon le pourcentage de Mana du perso 2 si il c'est PM max son de 0 barre griser */
		if(team.team[1]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[1]->Mana)/(team.team[1]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmSecond);
			pmSecond.w=(pmSecond.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmSecond);
		}
		
		/** destruction de toutes les textures */
		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		SDL_DestroyTexture(pmJauge);
     		SDL_DestroyTexture(pmActu);
     		SDL_DestroyTexture(firstPerso);
     		SDL_DestroyTexture(secondPerso);break;
     	
     	/** cas ou 3 perso sont dans l'équipe */
     	case 3: 
     		/** chargement des têtes des 3 personnage  */
     		firstPerso=loadTexture("../Ressource/characters/GolemHead.png",pRenderer);
     		secondPerso=loadTexture("../Ressource/characters/MageHead.png",pRenderer);
     		thirdPerso=loadTexture("../Ressource/characters/WarriorHead.png",pRenderer);
     		
     		/** affichage des têtes des 3 personnage */
     		SDL_RenderCopy(pRenderer,firstPerso,NULL,&firstPersoDest);
     		SDL_RenderCopy(pRenderer,secondPerso,NULL,&secondPersoDest);
     		SDL_RenderCopy(pRenderer,thirdPerso,NULL,&thirdPersoDest);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso 1 plus destruction de leur texture */
     		pourcent=(team.team[0]->Pv)/(team.team[0]->PvMax/100.0);
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvFirst);
		pvFirst.w=(pvFirst.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvFirst);
		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso 2 plus destruction de leur texture */
		pourcent=(team.team[1]->Pv)/(team.team[1]->PvMax/100.0);
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvSecond);
		pvSecond.w=(pvSecond.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvSecond);
		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		
     		/** chargement de la barre de PV selon le pourcentage de pv du perso 3 */
     		pourcent=(team.team[2]->Pv)/(team.team[2]->PvMax/100.0);
     		chargement_barre_pv(pourcent,&pvJauge,&pvActu,pRenderer);
     		SDL_RenderCopy(pRenderer,pvJauge,NULL,&pvThird);
		pvThird.w=(pvThird.w/100.0)*pourcent;
		SDL_RenderCopy(pRenderer,pvActu,NULL,&pvThird);
		
		/** chargement de la barre de Mana selon le pourcentage de Mana du perso 1 si il c'est PM max son de 0 barre griser */
		if(team.team[0]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[0]->Mana)/(team.team[0]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
			pmFirst.w=(pmFirst.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmFirst);
		}
		
		/** chargement de la barre de Mana selon le pourcentage de Mana du perso 2 si il c'est PM max son de 0 barre griser */
		if(team.team[1]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[1]->Mana)/(team.team[1]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmSecond);
			pmSecond.w=(pmSecond.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmSecond);
		}
		
		/** chargement de la barre de Mana selon le pourcentage de Mana du perso 2 si il c'est PM max son de 0 barre griser */
		if(team.team[2]->ManaMax==0){
     			pmJauge=loadTexture("../Ressource/ZeroMana.png",pRenderer);
     			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmFirst);
     		}
     		else{
	     		pourcent=(team.team[2]->Mana)/(team.team[2]->ManaMax/100.0);
	     		pmJauge=loadTexture("../Ressource/ManaJauge.png",pRenderer);
			pmActu=loadTexture("../Ressource/ManaActu.png",pRenderer);
			SDL_RenderCopy(pRenderer,pmJauge,NULL,&pmThird);
			pmThird.w=(pmThird.w/100.0)*pourcent;
			SDL_RenderCopy(pRenderer,pmActu,NULL,&pmThird);
		}
		
		/** destruction de toutes les textures */
		SDL_DestroyTexture(pvJauge);
     		SDL_DestroyTexture(pvActu);
     		SDL_DestroyTexture(pmJauge);
     		SDL_DestroyTexture(pmActu);
     		
     		SDL_DestroyTexture(firstPerso);
     		SDL_DestroyTexture(secondPerso);
     		SDL_DestroyTexture(thirdPerso);break;
     }
     
     /** affichage des icones */
     SDL_RenderCopy(pRenderer,SacIcone,NULL,&sacIconeDest);
     SDL_RenderCopy(pRenderer,StuffIcone,NULL,&stuffIconeDest);
     SDL_RenderCopy(pRenderer,StatIcone,NULL,&statIconeDest);
     
     /** destruction des textures des icones */
     SDL_DestroyTexture(StuffIcone);
     SDL_DestroyTexture(StatIcone);
     SDL_DestroyTexture(SacIcone);
   
     
     /** delais d'affichage */
     SDL_Delay(40);
     
}



/**
* fonction DetectEventsInvSac qui s'occupera de gérer la détection
* des évènement quand nous somme sur le menu d'inventaire sur le sac 
*/
void DetectEventsInvSac(int *useOk, int *yonUse,int *yonThrow,int* MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect destThrowButton){

    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    
    /** coordonnés des zones ou ce situe les zones d'objets dans le menu */
    int Y=(h-h/2)+((h/2)/5)-2;
    int H=((h/2)-((h/2)/5)-2)/13;
    
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0){
    	  switch(event.type){
		  
		  /** récuperation des touche enfoncer */
		  case SDL_KEYUP:
		  /** regarde qu'elle touche est enfoncer */  
		  	switch(event.key.keysym.sym){
			       case SDLK_i: *scene=OP ;
			       	     *MouseClick=-1;break;
			       case SDLK_ESCAPE:
		       		if(*yonUse>=1){
		       			*yonUse=-1;
		       		};break;
			       case SDLK_TAB:
			       	*scene=STAT ;
			       	*MouseClick=-1;break;
		  	};break;
		  	
		  /** récuperation des coordonnées de la sourits */
		  case SDL_MOUSEMOTION:
		  
		  /** regarde si la sourit est dans les case d'objets */
			  if (event.motion.x >= (w-w/2)+((w/2)/94)*3 && event.motion.x <= (w-w/2)+((w/2)/94)*3 + (w/4)){
			  	if(event.motion.y >= Y && event.motion.y <= Y+H){
			  		*MouseOver=0;
			  	}
			  	else if(event.motion.y >= Y+H+7 && event.motion.y <= Y+H+7+H){
			  		*MouseOver=1;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*2 && event.motion.y <= Y+(H+7)*2+H){
			  		*MouseOver=2;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*3 && event.motion.y <= Y+(H+7)*3+H){
			  		*MouseOver=3;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*4 && event.motion.y <= Y+(H+7)*4+H){
			  		*MouseOver=4;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*5 && event.motion.y <= Y+(H+7)*5+H){
			  		*MouseOver=5;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*6 && event.motion.y <= Y+(H+7)*6+H){
			  		*MouseOver=6;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*7 && event.motion.y <= Y+(H+7)*7+H){
			  		*MouseOver=7;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*8 && event.motion.y <= Y+(H+7)*8+H){
			  		*MouseOver=8;
			  	}
			  	else if(event.motion.y >= Y+(H+7)*9 && event.motion.y <= Y+(H+7)*9+H){
			  		*MouseOver=9;
			  	}
			  	else{
			  		*MouseOver=-1;
			  	}
			  }
			  else{
			  	*MouseOver=-1;
			  }
			  
			  /** regarde si la sourit est sur le bouton jeter */
			  if(event.motion.x >= destThrowButton.x && event.motion.x <= destThrowButton.x+destThrowButton.w && event.motion.y >= destThrowButton.y && event.motion.y <= destThrowButton.y+destThrowButton.h){
			  	   	if(*MouseClick>=0 && *yonThrow==-1){
			  	   		*yonThrow=0;
			  	   	}
			  	   	
			  }
			  else if(*yonThrow==0){
			  	*yonThrow=-1;
			  }
			  
			  /** regarde si la sourit est sur le bouton utiliser */
			  if(event.motion.x >= destThrowButton.x/1.11 && event.motion.x <= destThrowButton.x/1.11+destThrowButton.w && event.motion.y >= destThrowButton.y && event.motion.y <= destThrowButton.y+destThrowButton.h){
			  	   	if(*MouseClick>=0 && *yonUse==-1){
			  	   		*yonUse=0;
			  	   	}
			  }
			  else if(*yonUse==0){
			  	*yonUse=-1;
			  }
			  
			  /** regarde si la sourit est sur le bouton oui, non ou sur aucun des deux de la boite de texte pour jeter l'objet */
			  if(*yonThrow>=1 && *yonThrow<=3){
			  	if(event.motion.y >= ((h/6)*3)*1.05 && event.motion.y <= ((h/6)*5)/1.48){
			  		if(event.motion.x >= (((w/6)*3)/8)*7.15 && event.motion.x <= (((w/6)*3)/8)*7.65){
			  			*yonThrow=3;
			  		}
			  		else if(event.motion.x >= ((w/6)*3)+((((w/6)*3)/8)*7.65-(((w/6)*3)/8)*7.15)*0.65 && event.motion.x <= ((w/6)*3)+((((w/6)*3)/8)*7.65-(((w/6)*3)/8)*7.15)*1.65){
			  			*yonThrow=2;
			  		}
			  		else{
			  			*yonThrow=1;
			  		}
			  		
			  	}
			  	else{
			  		*yonThrow=1;
			  	}
			  }
			  
			  /** regarde si la sourit est sur un personnage pouvant utiliser un objet */
			  if(*yonUse>=1 && *yonUse<=4){
			  	if(event.motion.x >= (w/2-w/6/2)+(w/2-w/6/2)/45 && event.motion.x <= (w/2-w/6/2)+(w/2-w/6/2)/45+(w/4.8)){
			  		if((event.motion.y >= (h/2-h/6/2)+2 && event.motion.y <= (h/2-h/6/2)+2+((h/6)/3.5)/1.5) && useOk[0]==0){
			  			*yonUse=2;
			  		}
			  		else if((event.motion.y >= (h/2-h/6/2)+2+(((h/6)/3.5)/1.5)*2 && event.motion.y <= (h/2-h/6/2)+2+(((h/6)/3.5)/1.5)*3) && useOk[1]==0){
			  			*yonUse=3;
			  		}
			  		else if((event.motion.y >= (h/2-h/6/2)+2+(((h/6)/3.5)/1.5)*4 && event.motion.y <= (h/2-h/6/2)+2+(((h/6)/3.5)/1.5)*5) && useOk[2]==0){
			  			*yonUse=4;
			  		}
			  		else{
			  			*yonUse=1;
			  		}
			  		
			  	}
			  	else{
			  		*yonUse=1;
			  	}
			  };break;
			  
		   /** récuperation si le bouton de la sourit est lacher */
		   case SDL_MOUSEBUTTONUP:
		   
   			   /** regarde si le bouton est relacher sur une zone d'objet de l'inventaire */
   			   if(*MouseOver!=-1){
   			   	*MouseClick=*MouseOver;
   			   	if(*yonThrow=1){
   			   		*yonThrow=-1;
   			   	}
   			   	if(*yonUse=1){
   			   		*yonUse=-1;
   			   	}
   			   }
   			   
   			   /** regarde si le bouton est relacher sur le bouton jeter */
   			   if(*yonThrow==0){
   			   	*yonThrow=1;
   			   }
   			   
   			   /** regarde si le bouton est relacher sur le bouton oui ou non de la boite de texte pour jeter l'objet */
   			   else if(*yonThrow==2){
   			   	*yonThrow=-1;
   			   }
   			   else if(*yonThrow==3){
   			   	*yonThrow=5;
   			   }
   			   
   			   /** regarde si le bouton est relacher sur le bouton utiliser */
   			   if(*yonUse==0){
   			   	*yonUse=1;
   			   }
   			   else if(*yonUse==2){
   			   	*yonUse=5;
   			   }
   			   else if(*yonUse==3){
   			   	*yonUse=6;
   			   }
   			   else if(*yonUse==4){
   			   	*yonUse=7;
   			   };break;
          }              
    }
}

/**
* fonction ReactEventsInvSac qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur le menu d'inventaire sur le sac 
*/
void ReactEventsInvSac(int *useOk, int *yonUse,int *yonThrow,int MouseClick,int KeyIsPressed,int MouseOver,SDL_Renderer* pRenderer,int w,int h,inventaire_t* inv,SDL_Rect *destThrowButton,perso_t ** team){

     /** declaration de i servant au boucle for et textwidth, textheight pour les dimensions des textes */
     int i, textwidth, textheight;
     
     /** chaine de caractère utiliser pour l'affichage des persos avec leur nb de pv et pm  */
     char pv[4];
     char pvm[4];
     char pm[4];
     char pmm[4];
     char personnage[40];
     
     
     /** chargement des textures nécessaires aux menu */
     SDL_Texture* objClick=loadTexture("../Ressource/objSelect.png",pRenderer);
     SDL_Texture* objOver=loadTexture("../Ressource/objHover.png",pRenderer);
     SDL_Texture* menu=loadTexture("../Ressource/Inventory/MenuInvSac.png",pRenderer);
     
     /** chargement des textures nécessaires au bouton jeter et ça boite */
     SDL_Texture* buttonThrow=loadTexture("../Ressource/Inventory/throwButton.png",pRenderer);
     SDL_Texture* buttonThrowOver=loadTexture("../Ressource/Inventory/throwButtonOver.png",pRenderer);
     SDL_Texture* boxYoNThrow=loadTexture("../Ressource/Inventory/yOnThrow.png",pRenderer);
     
     /** chargement des textures nécessaires au bouton utiliser et ça boite */
     SDL_Texture* buttonUse=loadTexture("../Ressource/Inventory/useButton.png",pRenderer);
     SDL_Texture* buttonUseOver=loadTexture("../Ressource/Inventory/useButtonOver.png",pRenderer);
     SDL_Texture* boxYoNUse=loadTexture("../Ressource/Inventory/yonUse.png",pRenderer);
     
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage du menu */
     int temp=w/5+((w/2)/94)*2.8;
     SDL_Rect destMenu={w-w/2,h-h/2,w/2,h/2};
     SDL_Rect destzone={(w-w/2)+((w/2)/94)*3,(h-h/2)+((h/2)/5)-2,(w/4),((h/2)-((h/2)/5)-2)/13};
     SDL_Rect destImage={destzone.x+destzone.w+((w/2)/94)*3+temp/5,(h-h/2)+((h/2)/5)-2,h/4,h/4};
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage des boites utiliser et jeter
     *  ainsi que des personnage pour la boite d'utilisation 
     */
     SDL_Rect destBoxYoNThrow={w/2-w/6/2,h/2-h/6/2,w/6,h/6};
     SDL_Rect destBoxYoNUse={w/2-w/6/2,h/2-h/6/2,w/4.7,h/6};
     SDL_Rect destYoNPerso={destBoxYoNUse.x+destBoxYoNUse.x/45,(h/2-h/6/2)+2,0,(destBoxYoNUse.h/3.5)/1.5};
     
     
     /** declaration et initialisation des textures des noms et descriptions des objets ainsi que la couleur des texte */
     SDL_Texture* nomObj[10];
     SDL_Texture* descObj[10];
     SDL_Color blanc={255,255,255};
     SDL_Color gris={195,195,195};
     for(i=0;i<10;i++){
     	if(inv->sac[i]!=NULL){
     		nomObj[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->sac[i]->nom,destzone.h,blanc);
     		descObj[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->sac[i]->desc,destzone.h,blanc);
     	}
     	else{
     		nomObj[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,". . .",destzone.h,blanc);
     		descObj[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,"aucun objet",destzone.h,blanc);
     	}
     }
     
     /** déclaration et initialisation des texture des textes des personnages dans la boite d'utilisation d'objet*/
     SDL_Texture* perso[3];
     SDL_Texture* persoBlocked[3];
     for(i=0;i<3;i++){
     	if(team[i]!=NULL){
     		strcpy(personnage,team[i]->Nom);
     		sprintf(pv,"%.0f",team[i]->Pv);
     		sprintf(pvm,"%.0f",team[i]->PvMax);
     		sprintf(pm,"%.0f",team[i]->Mana);
     		sprintf(pmm,"%.0f",team[i]->ManaMax);
     		strcat(personnage," PV: ");
     		strcat(personnage,pv);
     		strcat(personnage,"/");
     		strcat(personnage,pvm);
     		strcat(personnage," PM: ");
     		strcat(personnage,pm);
     		strcat(personnage,"/");
     		strcat(personnage,pmm);
     		perso[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,personnage,(destBoxYoNUse.h/3.5)/1.5,blanc);
     		persoBlocked[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,personnage,(destBoxYoNUse.h/3.5)/1.5,gris);
     	}
     	else{
     		perso[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,". . .",(destBoxYoNUse.h/3.5)/1.5,gris);
     		persoBlocked[i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,". . .",(destBoxYoNUse.h/3.5)/1.5,gris);
     	}
     }
     
     /** declaration de la variable pour les coordonnées et dimensions des noms d'objets */
     SDL_Rect destNom;
     
     /** coordonnées et dimensions de la description des objets */
     SDL_Rect destDesc={destImage.x-destImage.w/4-destImage.w/35,destImage.y+destImage.h+5,w/5+destImage.w/35,destzone.h+10};
     SDL_Rect destNoDesc={destImage.x,destImage.y+destImage.h/2,destImage.w-5,destzone.h+10};
     
     /** coordonnée et destination du bouton jeter */
     destThrowButton->x=destDesc.x+(destDesc.w/3)*1.7;
     destThrowButton->y=destDesc.y+destDesc.h*1.5;
     destThrowButton->w=destDesc.w/3;
     destThrowButton->h=destDesc.h;
     
     /** coordonnée et destination du bouton utiliser */
     SDL_Rect destUseButton={destThrowButton->x/1.11,destThrowButton->y,destThrowButton->w,destThrowButton->h};
     
     /** affichage du menu */
     SDL_RenderCopy(pRenderer,menu,NULL,&destMenu);
     
     /** affichage des objets présent ou non ainsi que la zone sur laquelle la sourit a cliquer ou est positionner */
     for(i=0;i<10;i++){
     	if(MouseClick==i){
     		SDL_RenderCopy(pRenderer,objClick,NULL,&destzone);
     	}
     	else if(MouseOver==i){
     		SDL_RenderCopy(pRenderer,objOver,NULL,&destzone);
     	}
     	
     	/** mise a jour des coordonnées et dimensions des noms d'objets */
     	SDL_QueryTexture(nomObj[i], NULL, NULL, &textwidth, &textheight);
     	destNom.x=destzone.x+(destzone.w/2-textwidth/2);
     	destNom.y=destzone.y+((destzone.h/2-textheight/2));
     	destNom.w=textwidth;
     	destNom.h=textheight;
     	
     	
     	/** affichage des noms d'objets si il n'y a pas d'objet affiche ". . ." */
     	SDL_RenderCopy(pRenderer,nomObj[i],NULL,&destNom);
     	destzone.y+=destzone.h+7;
     }
     
     /** test si il y a un objet a cet emplacement du sac,
     *   si oui affiche l'image, la description et les boutons jeter et utiliser,
     *   sinon affiche le texte "rien"
     */
     if(MouseClick!=-1){
     
        /** cas ou l'objet sélectionner existe dans cet endroit de l'inventaire*/
     	if(inv->sac[MouseClick]!=NULL){
     	
     		/** affichage de l'image de l'objet ainsi que ça description */
     		SDL_RenderCopy(pRenderer,inv->sac[MouseClick]->sprite,NULL,&destImage);
     		SDL_RenderCopy(pRenderer,descObj[MouseClick],NULL,&destDesc);
     		
     		/** regarde yonThrow pour gérer l'affichage du bouton jeter ainsi que ça boite d'interraction pour jeter un objet */
     		if(*yonThrow==0){
     			SDL_RenderCopy(pRenderer,buttonThrowOver,NULL,destThrowButton);
     		}
     		else if(*yonThrow>=1 && *yonThrow <=3){
     			SDL_RenderCopy(pRenderer,buttonThrow,NULL,destThrowButton);
     			SDL_RenderCopy(pRenderer,boxYoNThrow,NULL,&destBoxYoNThrow);
     		}
     		else if(*yonThrow==5){
     			jeter_obj(inv,MouseClick);
     			*yonThrow=-1;
     		}
     		
     		else{
     			SDL_RenderCopy(pRenderer,buttonThrow,NULL,destThrowButton);
     		}
     		
     		/** regarde yonUse pour gérer l'affichage du bouton utiliser ainsi que ça boite d'interraction pour selectionner un personnage 
     		* met useOk a 0 si le personnage peut utiliser cet objets sinon la met a 1
     		*/
     		if(*yonUse==0){
     			SDL_RenderCopy(pRenderer,buttonUseOver,NULL,&destUseButton);
     		}
     		else if(*yonUse>=1 && *yonUse <=4){
     			SDL_RenderCopy(pRenderer,boxYoNUse,NULL,&destBoxYoNUse);
     			for(i=0;i<3;i++){
     				SDL_QueryTexture(perso[i], NULL, NULL, &textwidth, &textheight);
     				destYoNPerso.w=textwidth;
     				if(team[i]!=NULL){
	     				if(team[i]->Pv==team[i]->PvMax && team[i]->Mana<team[i]->ManaMax){
	     					if(inv->sac[MouseClick]->valPv>0 && inv->sac[MouseClick]->valMp==0){
	     						SDL_RenderCopy(pRenderer,persoBlocked[i],NULL,&destYoNPerso);
	     						useOk[i]=1;
	     					}
	     					else{
	     						SDL_RenderCopy(pRenderer,perso[i],NULL,&destYoNPerso);
	     						useOk[i]=0;
	     					}
	     				}
	     				else if(team[i]->Pv<team[i]->PvMax && team[i]->Mana==team[i]->ManaMax){
	     					if(inv->sac[MouseClick]->valPv==0 && inv->sac[MouseClick]->valMp>0){
	     						SDL_RenderCopy(pRenderer,persoBlocked[i],NULL,&destYoNPerso);
	     						useOk[i]=1;
	     					}
	     					else{
	     						SDL_RenderCopy(pRenderer,perso[i],NULL,&destYoNPerso);
	     						useOk[i]=0;
	     					}
	     				}
	     				else if(team[i]->Pv==team[i]->PvMax && team[i]->Mana==team[i]->ManaMax){
	     					SDL_RenderCopy(pRenderer,persoBlocked[i],NULL,&destYoNPerso);
	     					useOk[i]=1;
	     				}
	     				else{
	     					SDL_RenderCopy(pRenderer,perso[i],NULL,&destYoNPerso);
	     					useOk[i]=0;
	     				}
	     			}
	     			else{
	     				SDL_RenderCopy(pRenderer,perso[i],NULL,&destYoNPerso);
	     				useOk[i]=1;
	     			}
     				
     				destYoNPerso.y+=destYoNPerso.h*2;
     			}
     			SDL_RenderCopy(pRenderer,buttonUse,NULL,&destUseButton);
     		}
     		
     		/** regarde si un personnage a été sélectionner */
     		else if(*yonUse>4){
     			utiliser_obj(inv,team[*yonUse-5],MouseClick);
     			*yonUse=-1;
     		}
     		else{
     			SDL_RenderCopy(pRenderer,buttonUse,NULL,&destUseButton);
     		}
     		
     	}
     	
     	/** cas ou l'objet sélectionner n'existe pas dans cet endroit de l'inventaire*/
     	else{
     		SDL_RenderCopy(pRenderer,descObj[MouseClick],NULL,&destNoDesc);
     	}
     	
     }
     
     /** destruction des textures utiliser pour le menu */
     SDL_DestroyTexture(objOver); 
     SDL_DestroyTexture(objClick);
     SDL_DestroyTexture(menu);
     
     /** destruction des textures utiliser pour le bouton jeter et ça boite */
     SDL_DestroyTexture(buttonThrow);
     SDL_DestroyTexture(buttonThrowOver);
     SDL_DestroyTexture(boxYoNThrow);
     
     /** destruction des textures utiliser pour le bouton utiliser et ça boite */
     SDL_DestroyTexture(buttonUse);
     SDL_DestroyTexture(buttonUseOver);
     SDL_DestroyTexture(boxYoNUse);
     
     /** destruction des textures des noms et descriptions des objets */
     for(i=0;i<10;i++){
     	SDL_DestroyTexture(nomObj[i]);
     	SDL_DestroyTexture(descObj[i]);
     }
     
     /** destruction des textures des noms,pv et pm des personnages */
     for(i=0;i<3;i++){
     	SDL_DestroyTexture(perso[i]);
     	SDL_DestroyTexture(persoBlocked[i]);
     }
     
}

/**
* fonction DetectEventsStats qui s'occupera de gérer la détection
* des évènement quand nous somme sur le menu des stats des personnages 
*/
void DetectEventsStats(int *numPage,int *MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect *destStatAction,team_t * team,float Stats[3][8]){
    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    *MouseClick=-1;
    
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0){
    	  switch(event.type){
		  
		  /** récuperation des touche enfoncer */
		  case SDL_KEYUP:
		  /** regarde qu'elle touche est enfoncer */  
		  	switch(event.key.keysym.sym){
			       case SDLK_t: 
			       	     Stats[*numPage][0]=team->team[*numPage]->PvMax;
					     Stats[*numPage][1]=team->team[*numPage]->ManaMax;
					     Stats[*numPage][2]=team->team[*numPage]->For;
					     Stats[*numPage][3]=team->team[*numPage]->Def;
					     Stats[*numPage][4]=team->team[*numPage]->Int;
					     Stats[*numPage][5]=team->team[*numPage]->Res;
					     Stats[*numPage][6]=team->team[*numPage]->Vit;
					     Stats[*numPage][7]=team->team[*numPage]->PtComp;
			       	     *scene=OP ;
			       	     *MouseClick=-1;
			       	     *numPage=0;break;
			      case SDLK_TAB:
			      		     Stats[*numPage][0]=team->team[*numPage]->PvMax;
					     Stats[*numPage][1]=team->team[*numPage]->ManaMax;
					     Stats[*numPage][2]=team->team[*numPage]->For;
					     Stats[*numPage][3]=team->team[*numPage]->Def;
					     Stats[*numPage][4]=team->team[*numPage]->Int;
					     Stats[*numPage][5]=team->team[*numPage]->Res;
					     Stats[*numPage][6]=team->team[*numPage]->Vit;
					     Stats[*numPage][7]=team->team[*numPage]->PtComp;
			       	     *scene=EQUIPEMENT;
			       	     *MouseClick=-1;
			       	     *numPage=0;break;
		  	};break;
		  	
		  /** récuperation des coordonnées de la sourits */
		  case SDL_MOUSEMOTION:
		  
		  	/** regarde si la sourit est sur les fleche pour changer de perso sur le bouton valider */
		  	if (event.motion.y >= destStatAction[0].y && event.motion.y <= destStatAction[0].y+destStatAction[0].h){
		  		if(event.motion.x>=destStatAction[0].x && event.motion.x<=destStatAction[0].x+destStatAction[0].w){
		  			*MouseOver=16;
		  		}
		  		else if(event.motion.x>=destStatAction[0].x-destStatAction[0].w*2 && event.motion.x<=destStatAction[0].x-destStatAction[0].w){
		  			*MouseOver=15;
		  		}
		  		else if(event.motion.x>=destStatAction[0].x-destStatAction[0].w*7 && event.motion.x<=destStatAction[0].x-destStatAction[0].w*3){
		  			*MouseOver=14;
		  		}
		  		else{
		  			*MouseOver=-1;
		  		}
		  	}
		  	
		  	/** regarde si la sourit est sur un bouton + */
		  	else if(event.motion.x >= destStatAction[1].x-destStatAction[1].h*1.5 && event.motion.x <= destStatAction[1].x-destStatAction[1].h*1.5+destStatAction[1].h){
		  		if(event.motion.y>=destStatAction[1].y && event.motion.y<=destStatAction[1].y+destStatAction[1].h){
		  			*MouseOver=6;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5 && event.motion.y<=destStatAction[1].y-destStatAction[1].h/2){
		  			*MouseOver=5;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*2 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*2){
		  			*MouseOver=4;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*3 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*3.5){
		  			*MouseOver=3;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*4 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*5){
		  			*MouseOver=2;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*5 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*6.5){
		  			*MouseOver=1;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*6 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*8){
		  			*MouseOver=0;
		  		}
		  		else {
		  			*MouseOver=-1;
		  		}
		  	}
		  	
		  	/** regarde si la sourit est sur un bouton - */
		  	else if(event.motion.x >= destStatAction[1].x && event.motion.x <= destStatAction[1].x+destStatAction[1].h){
		  		if(event.motion.y>=destStatAction[1].y && event.motion.y<=destStatAction[1].y+destStatAction[1].h){
		  			*MouseOver=13;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5 && event.motion.y<=destStatAction[1].y-destStatAction[1].h/2){
		  			*MouseOver=12;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*2 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*2){
		  			*MouseOver=11;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*3 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*3.5){
		  			*MouseOver=10;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*4 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*5){
		  			*MouseOver=9;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*5 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*6.5){
		  			*MouseOver=8;
		  		}
		  		else if(event.motion.y>=destStatAction[1].y-destStatAction[1].h*1.5*6 && event.motion.y<=destStatAction[1].y-destStatAction[1].h*8){
		  			*MouseOver=7;
		  		}
		  		else {
		  			*MouseOver=-1;
		  		}
		  	}
		  	
		  	else{
		  		*MouseOver=-1;
		  	};break;
		  /** regarde si la sourit est dans la case + ou - d'une stats */
			  
		   /** récuperation si le bouton de la sourit est lacher */
		   case SDL_MOUSEBUTTONUP:
		   
		   /** regarde si le bouton est relacher sur une zone d'objet de l'inventaire */
		   	*MouseClick=*MouseOver;
		   	switch(*MouseOver){
		   	        case 14:
		   	        	team->team[*numPage]->PvMax=Stats[*numPage][0];
					team->team[*numPage]->ManaMax=Stats[*numPage][1];
					team->team[*numPage]->For=Stats[*numPage][2];
					team->team[*numPage]->Def=Stats[*numPage][3];
					team->team[*numPage]->Int=Stats[*numPage][4];
					team->team[*numPage]->Res=Stats[*numPage][5];
					team->team[*numPage]->Vit=Stats[*numPage][6];
					team->team[*numPage]->PtComp=Stats[*numPage][7];
		   		case 15: 
		   			Stats[*numPage][0]=team->team[*numPage]->PvMax;
					Stats[*numPage][1]=team->team[*numPage]->ManaMax;
					Stats[*numPage][2]=team->team[*numPage]->For;
					Stats[*numPage][3]=team->team[*numPage]->Def;
					Stats[*numPage][4]=team->team[*numPage]->Int;
					Stats[*numPage][5]=team->team[*numPage]->Res;
					Stats[*numPage][6]=team->team[*numPage]->Vit;
					Stats[*numPage][7]=team->team[*numPage]->PtComp;
		   			*numPage-=1;break;
		   		case 16: 
		   			Stats[*numPage][0]=team->team[*numPage]->PvMax;
					Stats[*numPage][1]=team->team[*numPage]->ManaMax;
					Stats[*numPage][2]=team->team[*numPage]->For;
					Stats[*numPage][3]=team->team[*numPage]->Def;
					Stats[*numPage][4]=team->team[*numPage]->Int;
					Stats[*numPage][5]=team->team[*numPage]->Res;
					Stats[*numPage][6]=team->team[*numPage]->Vit;
					Stats[*numPage][7]=team->team[*numPage]->PtComp;
		   			*numPage+=1;break;
		   	};break;
		   			   
          }      
    }
}

/**
* fonction ReactEventsInvSac qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur le menu d'inventaire sur le sac 
*/
void ReactEventsStats(int numPage,int MouseClick, int KeyIsPressed,int MouseOver,SDL_Renderer* pRenderer,int w,int h,team_t * team,float Stats[3][8],SDL_Rect* destStatAction){

     /** declaration de i servant au boucle for et textwidth, textheight pour les dimensions des textes */
     int i,j, textwidth, textheight;
     
     /** chaine de caractère utiliser pour l'affichage des persos avec leur stats  */
     char nomStat[8][20]={"Vie: ","Mana: ","Force: ","Defense: ","Intelligence: ","Resistance: ","Vitesse: ","PT de competence: "};
     char valStat[8][4];
     char stat[21];
     char lvl[2];
     char nomlvl[28];
     
     /** stat stocker temporairement pour vérifier certaine condition pour pouvoir utiliser le bouton + et - */
     int statTempo[3][8];
     for(j=0;j<team->nbPerso;j++){
		statTempo[j][0]=team->team[j]->PvMax;
		statTempo[j][1]=team->team[j]->ManaMax;
		statTempo[j][2]=team->team[j]->For;
		statTempo[j][3]=team->team[j]->Def;
		statTempo[j][4]=team->team[j]->Int;
		statTempo[j][5]=team->team[j]->Res;
		statTempo[j][6]=team->team[j]->Vit;
		statTempo[j][7]=team->team[j]->PtComp;
     }
     
     /** chargement des textures nécessaire aux menu */
     SDL_Texture* menu=loadTexture("../Ressource/Inventory/MenuStat.png",pRenderer);
     SDL_Texture* boutonValider=NULL;
     
     SDL_Texture* inc=NULL;
     
     SDL_Texture* dec=NULL;
     
     SDL_Texture* arrow=NULL;
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage du menu */
     int temp=w/5+((w/2)/94)*2.8;
     SDL_Rect destMenu={w-w/2,h-h/2,w/2,h/2};
     SDL_Rect destzone={(w-w/2)+((w/2)/94)*3,(h-h/2)+((h/2)/5)-2,(w/4),((h/2)-((h/2)/5)-2)/9.5};
     
     
     /** declaration et initialisation des textures des noms et descriptions des objets ainsi que la couleur des texte */
     SDL_Color blanc={255,255,255};
     SDL_Color gris={195,195,195};
     
     
     /** déclaration et initialisation des texture des textes des personnages dans la boite d'utilisation d'objet*/
     SDL_Texture* allStat[3][8];
     for(j=0;j<team->nbPerso;j++){
	     for(i=0;i<8;i++){
	     	if(team->team[j]!=NULL){
	     		strcpy(stat,nomStat[i]);
	     		sprintf(valStat[i],"%.0f",Stats[j][i]);
	     		strcat(stat,valStat[i]);
	     		allStat[j][i]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,stat,((h/2)-((h/2)/5)-2)/9.5,blanc);
	     	}
	     }
     }
     
     /** declaration de la variable pour les coordonnées et dimensions des noms d'objets */
     SDL_Rect destStat;
     
     /** affichage du menu */
     SDL_RenderCopy(pRenderer,menu,NULL,&destMenu);
     
     /** création de la texture du nom du perso avec son level */
     sprintf(lvl,"%d",team->team[numPage]->lvl);
     strcpy(nomlvl,team->team[numPage]->Nom);
     strcat(nomlvl," lvl: ");
     strcat(nomlvl,lvl);
     SDL_Texture* nomPerso=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,nomlvl,((h/2)-((h/2)/5)-2)/9.5,blanc);
     
     /** calcul des coordonnées et dimensions du nom du perso avec son lvl */
     SDL_QueryTexture(nomPerso, NULL, NULL, &textwidth, &textheight);
     destStat.x=w/4-textheight/2;
     destStat.x*=3;
     destStat.y=destzone.y-destzone.y/30;
     destStat.w=textwidth;
     destStat.h=textheight;
     
     /** affichage du nom du perso avec son lvl puis libère la mémoire */
     SDL_RenderCopy(pRenderer,nomPerso,NULL,&destStat);
     SDL_DestroyTexture(nomPerso);
     
     destzone.y+=destStat.h/2;
     for(i=0;i<7;i++){
        
        /** calcul des coordonnées, dimensions des bouton + et - */
     	destStat.x=(w/4)*3;
     	destStat.y=destzone.y;
     	destStat.w=textheight/1.5;
     	destStat.h=destStat.w;
     	destStat.y+=destStat.h/2;
     	
     	/** chargement de la texture puis affichage du boutons + en on ou off en fonction de si l'on peut utiliser les bouton ou non
     	*  pour eviter de dépasser le nombre de pt de compétences a utiliser enfin libère la mémoire
     	*/
     	if(Stats[numPage][7]<=0){
     		inc=loadTexture("../Ressource/Inventory/statIncOff.png",pRenderer);
     		SDL_RenderCopy(pRenderer,inc,NULL,&destStat);
     	}
     	else{
     		if(MouseOver==i){
     			inc=loadTexture("../Ressource/Inventory/statIncOver.png",pRenderer);
     		}
     		else{
     			inc=loadTexture("../Ressource/Inventory/statIncOn.png",pRenderer);
     		}
     		SDL_RenderCopy(pRenderer,inc,NULL,&destStat);
     		if(MouseClick==i){
     			Stats[numPage][i]+=1;
     			Stats[numPage][7]-=1;
     		}
     	}
     	SDL_DestroyTexture(inc);
     	
     	/** chargement de la texture puis affichage du boutons - en on ou off en fonction de si l'on peut utiliser les bouton ou non
     	*  pour eviter de diminuer en dessous des stats de base enfin libère la mémoire
     	*/
     	destStat.x+=textheight;
     	if(Stats[numPage][7]==team->team[numPage]->PtComp || Stats[numPage][i]==statTempo[numPage][i]){
     		dec=loadTexture("../Ressource/Inventory/statDecOff.png",pRenderer);
     		SDL_RenderCopy(pRenderer,dec,NULL,&destStat);
     	}
     	else{
     		if(MouseOver==i+7){
     			dec=loadTexture("../Ressource/Inventory/statDecOver.png",pRenderer);
     		}
     		else{
     			dec=loadTexture("../Ressource/Inventory/statDecOn.png",pRenderer);
     		}
     		SDL_RenderCopy(pRenderer,dec,NULL,&destStat);
     		
     		if(MouseClick==i+7){
     			Stats[numPage][i]-=1;
     			Stats[numPage][7]+=1;
     		}
     	}
     	SDL_DestroyTexture(dec);
     	
     	/** récupère les dernières coordonnées des boutons + et - pour la detection d'évents */
     	destStatAction[1].x=destStat.x;
     	destStatAction[1].y=destStat.y;
     	destStatAction[1].w=destStat.w;
     	destStatAction[1].h=destStat.h;
     	
     	/** mise a jour des coordonnées et dimensions des stats */
     	SDL_QueryTexture(allStat[numPage][i], NULL, NULL, &textwidth, &textheight);
     	destStat.x=destzone.x;
     	destStat.y=destzone.y;
     	destStat.w=textwidth;
     	destStat.h=textheight;
     	
     	/** affichage des stats */
     	SDL_RenderCopy(pRenderer,allStat[numPage][i],NULL,&destStat);
     	destzone.y+=destStat.h;
     }
     
     /** calcul des coordonnées, dimensions des points de compétences du personnage sur lequel on est */
     SDL_QueryTexture(allStat[numPage][i], NULL, NULL, &textwidth, &textheight);
     destStat.x=destzone.x;
     destStat.y=h-1.5*textheight;
     destStat.w=textwidth;
     destStat.h=textheight;
     
     /** affichage des points de compétences du personnage */
     SDL_RenderCopy(pRenderer,allStat[numPage][7],NULL,&destStat);
     
     /** calculdes coordonnées, dimensions, charge les textures plus affichage du bouton valider pour confirmer les points de compétences attribuer */
     destStat.x+=textwidth*1.25;
     destStat.w=textwidth/2;
     if(statTempo[numPage][7]==0 || Stats[numPage][7]==statTempo[numPage][i]){
        SDL_Texture* boutonValider=loadTexture("../Ressource/Inventory/validButtonOver.png",pRenderer);
     	SDL_RenderCopy(pRenderer,boutonValider,NULL,&destStat);
     }
     else{
     	if(MouseOver==14){
     		SDL_Texture* boutonValider=loadTexture("../Ressource/Inventory/validButtonOver.png",pRenderer);
     		SDL_RenderCopy(pRenderer,boutonValider,NULL,&destStat);
     	}
     	else{
     		SDL_Texture* boutonValider=loadTexture("../Ressource/Inventory/validButton.png",pRenderer);
     		SDL_RenderCopy(pRenderer,boutonValider,NULL,&destStat);
     	}
     }
     
     /** calculdes coordonnées, dimensions de la flèches gauche pour changer de perso */
     destStat.x+=destStat.w*1.25;
     destStat.w=destStat.w/4;
     destStat.h=destStat.w;
     
     /** affichage des flèches pour changer de perso si la sourit est dessus assombris le bouton 
     *  si nous ommes sur le premiers perso on affiche pass la flèche vers la gauche et 
     *  si on est sur le dernier perso la flèche de droite n'est pas afficher
     *  puis libère la mémoire
     */
     if(numPage>0){
     	if(MouseOver==15){
     		arrow=loadTexture("../Ressource/Inventory/leftOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/left.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destStat);
     	SDL_DestroyTexture(arrow);
     }
     
     /** calculdes coordonnées, dimensions de la flèches droite pour changer de perso puis libère la mémoire */
     destStat.x+=destStat.w*2;
     if(numPage<team->nbPerso-1){
     	if(MouseOver==16){
     		arrow=loadTexture("../Ressource/Inventory/rightOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/right.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destStat);
     	SDL_DestroyTexture(arrow);
     }
     
     /** copie des coordonnées des derniers outon pour les detection d'évents */
     destStatAction[0].x=destStat.x;
     destStatAction[0].y=destStat.y;
     destStatAction[0].w=destStat.w;
     destStatAction[0].h=destStat.h;
     
     
     /** destruction des textures utiliser pour le menu */
     SDL_DestroyTexture(menu);
     
     /** destruction des textures des noms et descriptions des objets */
     for(j=0;j<team->nbPerso;j++){
	     for(i=0;i<8;i++){
	     	SDL_DestroyTexture(allStat[j][i]);
	     }
     }
     
     /** destruction de toutes les textures des bouton */
     SDL_DestroyTexture(arrow);
     
     SDL_DestroyTexture(boutonValider);
     
     SDL_DestroyTexture(inc);
     
     SDL_DestroyTexture(dec);
     
}

/**
* fonction DetectEventsInvStuff qui s'occupera de gérer la détection
* des évènement quand nous somme sur le menu d'inventaire pour les équipements/armes 
*/
void DetectEventsInvStuff(int *yonThrow,int* MouseClick,int *MouseOver, scene_t* scene,int w,int h,SDL_Rect destThrowButton,int *numPage,int* numPagePerso,int* slot,int* eOuStuff){

    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    
    /** coordonnés des zones ou ce situe les zones d'objets dans le menu */
    int Y=(h-h/2)+((h/2)/5)-2;
    int H=((h/2)-((h/2)/5)-2)/13;
    
    /** coordonnés du personnage afficher */
    int xPerso=(w/2-h/2)/2;
    int yPerso=(h-h/2)/2;
    
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0){
    	  switch(event.type){
		  
		  /** récuperation des touche relacher */
		  case SDL_KEYUP:
		  
		  /** regarde qu'elle touche est relacher */  
		  	switch(event.key.keysym.sym){
		  	       /** réinitialise toutes les variables utiliser en même temp de changer de scene */
			       case SDLK_e: 
			       	*scene=OP;
			       	*numPage=0;
			       	*MouseClick=-1;
			       	*slot=-1;break;
			       case SDLK_TAB:
			       	*scene=INVENTORY;
			       	*numPage=0;
			       	*MouseClick=-1;
			       	*slot=-1;break;
		  	};break;
		  	
		  /** récuperation des coordonnées de la sourits */
		  case SDL_MOUSEMOTION:
		  
		  /** regarde si la sourit est dans les case d'équipements/armes */
			  if (event.motion.x >= (w-w/2)+((w/2)/94)*3 && event.motion.x <= (w-w/2)+((w/2)/94)*3 + (w/4) && event.motion.y>=h/2){
			  	if(event.motion.y >= Y && event.motion.y <= Y+H){
			  		*MouseOver=0+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+H+7 && event.motion.y <= Y+H+7+H){
			  		*MouseOver=1+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*2 && event.motion.y <= Y+(H+7)*2+H){
			  		*MouseOver=2+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*3 && event.motion.y <= Y+(H+7)*3+H){
			  		*MouseOver=3+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*4 && event.motion.y <= Y+(H+7)*4+H){
			  		*MouseOver=4+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*5 && event.motion.y <= Y+(H+7)*5+H){
			  		*MouseOver=5+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*6 && event.motion.y <= Y+(H+7)*6+H){
			  		*MouseOver=6+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*7 && event.motion.y <= Y+(H+7)*7+H){
			  		*MouseOver=7+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*8 && event.motion.y <= Y+(H+7)*8+H){
			  		*MouseOver=8+((*numPage)*10);
			  	}
			  	else if(event.motion.y >= Y+(H+7)*9 && event.motion.y <= Y+(H+7)*9+H){
			  		*MouseOver=9+((*numPage)*10);
			  	}
			  	else{
			  		*MouseOver=-1;
			  	}
			  }
			  
			  /** regarde si la sourit est dans un slot d'équipement */
			  else if(event.motion.x<w/2){
			  	/** slot 1 et 2 */
			  	if(event.motion.y>=yPerso-64*1.25 && event.motion.y<=yPerso-64*0.25){
			  		if(event.motion.x>=xPerso && event.motion.x<= xPerso+64){
			  			*MouseOver=-2;
			  		}
			  		else if(event.motion.x>=xPerso+h/2-64 && event.motion.x<= xPerso+h/2){
			  			*MouseOver=-3;
			  		}
			  	}
			  	
			  	/** slot 3 et 4 */
			  	else if(event.motion.y>=yPerso+h/4-32 && event.motion.y<=yPerso+h/4+32){
			  		if(event.motion.x>=xPerso-64*1.25 && event.motion.x<= xPerso-64*0.25){
			  			*MouseOver=-4;
			  		}
			  		else if(event.motion.x>=xPerso+h/2+64*0.25 && event.motion.x<= xPerso+h/2+64*1.25){
			  			*MouseOver=-5;
			  		}
			  	}
			  	
			  	/** slot 5 et 6 */
			  	else if(event.motion.y>=yPerso+h/2+64*0.25 && event.motion.y<=yPerso+h/2+64*1.25){
			  		if(event.motion.x>=xPerso && event.motion.x<= xPerso+64){
			  			*MouseOver=-6;
			  		}
			  		else if(event.motion.x>=xPerso+h/2-64 && event.motion.x<= xPerso+h/2){
			  			*MouseOver=-7;
			  		}
			  	}
			  }
			  
			  /** regarde si la sourits est sur le bouton équiper ou déséquiper */
			  else if(event.motion.y>=h/2-((h/6)*2) && event.motion.y<=h/2-h/6 && event.motion.x>=w/2){
			  	
			  	/** bouton équiper */
			  	if(event.motion.x>=w/2 && event.motion.x<=w/2+w/4){
			  		*MouseOver=58;
			  	}
			  	
			  	/** bouton déséquiper */
			  	else{
			  		*MouseOver=59;
			  	}
			  }
			  
			  /** si la sourit n'est sur aucun bouton  */
			  else{
			  	*MouseOver=-1;
			  }
			  
			  /** regarde si la sourit est sur le bouton jeter */
			  if(event.motion.x >= destThrowButton.x && event.motion.x <= destThrowButton.x+destThrowButton.w && event.motion.y >= destThrowButton.y && event.motion.y <= destThrowButton.y+destThrowButton.h){
			  	   	if(*MouseClick>=0 && *yonThrow==-1){
			  	   		*yonThrow=0;
			  	   	}
			  	   	
			  }
			  
			  else if(*yonThrow==0){
			  	*yonThrow=-1;
			  }
			  
			  /** regarde si la sourit est sur le bouton flèche droite ou gauche dans l'inventaire */
			  if(event.motion.y >= destThrowButton.y && event.motion.y <= destThrowButton.y+destThrowButton.h && event.motion.x >= destThrowButton.x-destThrowButton.w*0.5){
			  
			  	/** flèche gauche */
			  	if(event.motion.x >= destThrowButton.x-destThrowButton.w*0.5 && event.motion.x <= destThrowButton.x-destThrowButton.w*0.5+destThrowButton.h){
			  		*MouseOver=54;
			  	}
			  	
			  	/** flèche droite */
			  	else if(event.motion.x >= destThrowButton.x+destThrowButton.w*1.25 && event.motion.x <= destThrowButton.x+destThrowButton.w*1.25+destThrowButton.h){
			  		*MouseOver=55;
			  	}
			  	
			  	else {
			  		*MouseOver=-1;
			  	}
			  }
			  
			  /** regarde si la sourit est sur le bouton flèche droite ou gauche sur les personnages */
			  if(event.motion.y >= destThrowButton.y && event.motion.y <= destThrowButton.y+destThrowButton.h && event.motion.x <= w/2){
			  
			  	/** flèche gauche */
			  	if(event.motion.x >= destThrowButton.h && event.motion.x <= destThrowButton.h*2){
			  		*MouseOver=56;
			  	}
			  	
			  	/** flèche droite */
			  	else if(event.motion.x >= w/2-destThrowButton.h*2 && event.motion.x <= w/2-destThrowButton.h){
			  		*MouseOver=57;
			  	}
			  	
			  	else {
			  		*MouseOver=-1;
			  	}
			  }
			  
			  /** regarde si la sourit est sur le bouton oui, non ou sur aucun des deux de la boite de texte pour jeter l'objet */
			  if(*yonThrow>=1 && *yonThrow<=3){
			  	if(event.motion.y >= ((h/6)*3)*1.05 && event.motion.y <= ((h/6)*5)/1.48){
			  		if(event.motion.x >= (((w/6)*3)/8)*7.15 && event.motion.x <= (((w/6)*3)/8)*7.65){
			  			*yonThrow=3;
			  		}
			  		else if(event.motion.x >= ((w/6)*3)+((((w/6)*3)/8)*7.65-(((w/6)*3)/8)*7.15)*0.65 && event.motion.x <= ((w/6)*3)+((((w/6)*3)/8)*7.65-(((w/6)*3)/8)*7.15)*1.65){
			  			*yonThrow=2;
			  		}
			  		
			  	}
			  	else{
			  		*yonThrow=1;
			  	}
			  };break;
			  
		   /** récuperation si le bouton de la sourit est lacher */
		   case SDL_MOUSEBUTTONUP:
		   
   			   /** regarde si le bouton est relacher sur une zone d'objet de l'inventaire */
   			   if(*MouseOver>-1 && *MouseOver<58){
   			   	*MouseClick=*MouseOver;
   			   	if(*yonThrow=1){
   			   		*yonThrow=-1;
   			   	}
   			   }
   			   
   			   /** regarde si la sourit est relacher sur le bouton équiper ou déséquiper */
   			   if(*MouseOver>57){
   			   	*eOuStuff=*MouseOver-58;
   			   }
   			   
   			   /** regarde si le bouton est relacher sur un slot d'équipements/armes */
   			   if(*MouseOver<-1){
   			   	*slot=*MouseOver;
   			   }
   			   
   			   /** regarde si le bouton est relacher sur le bouton jeter */
   			   if(*yonThrow==0){
   			   	*yonThrow=1;
   			   }
   			   
   			   /** regarde si le bouton est relacher sur le bouton oui ou non de la boite de texte pour jeter l'objet */
   			   else if(*yonThrow==2){
   			   	*yonThrow=-1;
   			   }
   			   else if(*yonThrow==3){
   			   	*yonThrow=5;
   			   }
   			   switch(*MouseClick){
   			   	case 54:*numPage-=1;*MouseClick=-1;break;
   			   	case 55:*numPage+=1;*MouseClick=-1;break;
   			   	case 56:*numPagePerso-=1;*MouseClick=-1;break;
   			   	case 57:*numPagePerso+=1;*MouseClick=-1;break;
   			   };break;
          }              
    }
}

/**
* fonction ReactEventsInvStuff qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur le menu d'inventaire pour les équipements/armes 
*/
void ReactEventsInvStuff(int *yonThrow,int MouseClick,int MouseOver,SDL_Renderer* pRenderer,int w,int h,inventaire_t* inv,SDL_Rect *destThrowButton,team_t * team,int numPage,int numPagePerso,int slot,int* eOuStuff){

     /** declaration de i servant au boucle for et textwidth, textheight pour les dimensions des textes */
     int i=0, textwidth, textheight; 
     
     /** calcule le nombre de page nécessaire selon le nombre d'équipements et d'armes */
     int nbPage;
     if(((inv->nbEquActu+inv->nbArmActu)/10.0)>((inv->nbEquActu+inv->nbArmActu)/10)){
     		nbPage=((inv->nbEquActu+inv->nbArmActu)/10)+1;
     }
     else{
     		nbPage=((inv->nbEquActu+inv->nbArmActu)/10);
     }
     
     /** chargement des textures nécessaires aux menu */
     SDL_Texture* objClick=loadTexture("../Ressource/objSelect.png",pRenderer);
     SDL_Texture* objOver=loadTexture("../Ressource/objHover.png",pRenderer);
     SDL_Texture* menu=loadTexture("../Ressource/Inventory/MenuInvStuff.png",pRenderer);
     
     /** chargement des textures nécessaires au bouton jeter et ça boite */
     SDL_Texture* buttonThrow=loadTexture("../Ressource/Inventory/throwButton.png",pRenderer);
     SDL_Texture* buttonThrowOver=loadTexture("../Ressource/Inventory/throwButtonOver.png",pRenderer);
     SDL_Texture* boxYoNThrow=loadTexture("../Ressource/Inventory/yOnThrow.png",pRenderer);
     
     /** chargement des textures nécessaires a la boite ou se situe le personnage et ces slots d'équipements/armes */
     SDL_Texture* boxCharacter=loadTexture("../Ressource/Inventory/boxCharacter.png",pRenderer);
     SDL_Texture* golem=loadTexture("../Ressource/characters/GolemFront.png",pRenderer);
     SDL_Texture* slotStuff=loadTexture("../Ressource/Inventory/zoneStuff.png",pRenderer);
     SDL_Texture* slotStuffSelect=loadTexture("../Ressource/Inventory/zoneStuffSelected.png",pRenderer);
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage du menu */
     int temp=w/5+((w/2)/94)*2.8;
     SDL_Rect destMenu={w-w/2,h-h/2,w/2,h/2};
     SDL_Rect destzone={(w-w/2)+((w/2)/94)*3,(h-h/2)+((h/2)/5)-2,(w/4),((h/2)-((h/2)/5)-2)/13};
     SDL_Rect destImage={destzone.x+destzone.w+((w/2)/94)*3+temp/5,(h-h/2)+((h/2)/5)-2,h/4,h/4};
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage du perso et des slots d'équiepements/armes */
     SDL_Rect destPerso={(w/2-h/2)/2,(h-h/2)/2,h/2,h/2};
     SDL_Rect destSlot={(w/2-h/2)/2,(h-h/2)/2,64,64};
     SDL_Rect srcPerso={0,0,64,64};
     SDL_Rect destStuffEqu={0,0,48,48};
     
     
     /** declaration des rect correspondant au coordonnées et dimensions d'affichage des boites utiliser et jeter
     *  ainsi que des personnage pour la boite d'utilisation 
     */
     SDL_Rect destBoxYoNThrow={w/2-w/6/2,h/2-h/6/2,w/6,h/6};
     
     /** déclaration de la texture et des coordonnés + dimensions des flèches pour changer de page */
     SDL_Texture* arrow=NULL;
     SDL_Rect destArrow;
     
     /** déclaration de la texture et des coordonnés + dimensions pour les boutons équiper et déséquiper*/
     SDL_Texture* equipOunequipButton=NULL;
     SDL_Rect destEOUButton={w/2,h/2-((h/6)*2),w/4,h/6};
     
     /** declaration et initialisation des textures des noms et descriptions des équipements/armes ainsi que la couleur des texte 
      *  jaune si équiper, blanc sinon
      */
     SDL_Texture* nomObj[10];
     SDL_Texture* descObj[10];
     SDL_Color unequipedColor={255,255,255};
     SDL_Color equipedColor={255,234,69};
     
     for(i=0+(numPage*10);i<10+(numPage*10);i++){
     
     	/** regarde si le on est sur des équipements */
     	if(i < inv->nbEquActu && i > -1){
	     	if(inv->equipements[i]!=NULL){
	     		if(inv->equipements[i]->persoEquiper!=NULL){
	     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->nom,destzone.h,equipedColor);
	     		}
	     		else{
	     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->nom,destzone.h,unequipedColor);
	     		}
	     		descObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->desc,destzone.h,unequipedColor);
	     	}
	}
     	else if(i-inv->nbEquActu < inv->nbArmActu && i > -1){
     		if(inv->armes[i-inv->nbEquActu]!=NULL){
	     		if(inv->armes[i-inv->nbEquActu]->persoEquiper!=NULL){
	     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->nom,destzone.h,equipedColor);
	     		}
	     		else{
	     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->nom,destzone.h,unequipedColor);
	     		}
	     		descObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->desc,destzone.h,unequipedColor);
	     	}
     	}
     	
     	/** sinon si l'inventaire a atteint ça limite mettre a NULL */
     	else{
     		
     		  nomObj[i%10]=NULL;
     		  descObj[i%10]=NULL;
     		
     	}
     }
     
     
     /** declaration de la variable pour les coordonnées et dimensions des noms d'objets */
     SDL_Rect destNom;
     
     /** coordonnées et dimensions de la description des objets */
     SDL_Rect destDesc={destImage.x-destImage.w/4-destImage.w/35,destImage.y+destImage.h+5,w/5+destImage.w/35,destzone.h+10};
     
     /** coordonnée et destination du bouton jeter */
     destThrowButton->x=destDesc.x+(destDesc.w/3);
     destThrowButton->y=destDesc.y+destDesc.h*1.5;
     destThrowButton->w=destDesc.w/3;
     destThrowButton->h=destDesc.h;
     
     /** coordonnée et destination des bouton flèches gauche/droite */
     destArrow.x=destThrowButton->x-destThrowButton->w*0.5;
     destArrow.y=destThrowButton->y;
     destArrow.h=destArrow.w=destThrowButton->h;
     
     /** affichage du menu */
     SDL_RenderClear(pRenderer);
     SDL_RenderCopy(pRenderer,menu,NULL,&destMenu);
     
     /** calcul des coordonnées/dimensions de la boite contenant le personnage et affichage */
     destMenu.x=destMenu.y=0;
     destMenu.w=w/2;
     destMenu.h=h;
     SDL_RenderCopy(pRenderer,boxCharacter,NULL,&destMenu);
     
     /** affichage du personnage selon la page */
     /** page 1 Golem */
     if(numPagePerso==0){
     	SDL_RenderCopy(pRenderer,golem,NULL,&destPerso);
     }
     
     /** page 2 et 3 Toxo/guerrier et xero/mage */
     else{
     	SDL_RenderCopy(pRenderer,team->team[numPagePerso]->MarcheFront,&srcPerso,&destPerso);
     }
     /** destruction de la texture du golem de face */
     SDL_DestroyTexture(golem);
     
     /** affichage des slot d'équipements */
     destSlot.y-=64*1.25;
     
     /** slot 1 */
     if(slot==-2){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     
     /** si un équiements est équiper l'afficher dans le slot */
     if(team->team[numPagePerso]->stuff[0]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->stuff[0]->artwork,NULL,&destStuffEqu);
     }
     
     /** slot 2 */
     destSlot.x+=destPerso.w-64;
     if(slot==-3){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     if(team->team[numPagePerso]->stuff[1]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->stuff[1]->artwork,NULL,&destStuffEqu);
     }
     
     /** slot 3 */
     destSlot.y=destPerso.y+destPerso.h/2-32;
     destSlot.x=destPerso.x-64*1.25;
     if(slot==-4){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     if(team->team[numPagePerso]->stuff[2]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->stuff[2]->artwork,NULL,&destStuffEqu);
     }
     
     /** slot 4 */
     destSlot.x=destPerso.x+destPerso.w+64*0.25;
     if(slot==-5){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     if(team->team[numPagePerso]->stuff[3]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->stuff[3]->artwork,NULL,&destStuffEqu);
     }
     
     
     /** affichage des slot d'armes */
     
     /** slot 1 */
     destSlot.y=destPerso.y+destPerso.h+64*0.25;
     destSlot.x=destPerso.x;
     if(slot==-6){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     if(team->team[numPagePerso]->armes[0]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->armes[0]->artwork,NULL,&destStuffEqu);
     }
     
     /** slot 2 */
     destSlot.x+=destPerso.w-64;
     if(slot==-7){
     	SDL_RenderCopy(pRenderer,slotStuffSelect,NULL,&destSlot);
     }
     else{
     	SDL_RenderCopy(pRenderer,slotStuff,NULL,&destSlot);
     }
     if(team->team[numPagePerso]->armes[1]!=NULL){
     		destStuffEqu.x=destSlot.x+(64-destStuffEqu.h)/2;
     		destStuffEqu.y=destSlot.y+(64-destStuffEqu.h)/2;
     		SDL_RenderCopy(pRenderer,team->team[numPagePerso]->armes[1]->artwork,NULL,&destStuffEqu);
     }
     
     /** affichage des équipements/armes et de la zone sur laquelle la sourit a cliquer ou est positionner */
     for(i=0+(numPage*10);i<10+(numPage*10);i++){
     	/** affiche seulement si il y a un équipements/armes a cet emplacement */
     	if(i<(inv->nbEquActu+inv->nbArmActu)){
     		
     		/** affichage de la zone autour des nom selon si il est selectionner ou non */
     		if(MouseClick==i){
	     		SDL_RenderCopy(pRenderer,objClick,NULL,&destzone);
	     	}
	     	else if(MouseOver==i){
	     		SDL_RenderCopy(pRenderer,objOver,NULL,&destzone);
	     	}
	     	
	     	/** mise a jour des coordonnées et dimensions des noms des équipements/armes */
		SDL_QueryTexture(nomObj[i%10], NULL, NULL, &textwidth, &textheight);
	     	destNom.x=destzone.x+(destzone.w/2-textwidth/2);
	     	destNom.y=destzone.y+((destzone.h/2-textheight/2));
	     	destNom.w=textwidth;
	     	destNom.h=textheight;
	     	
	     	
	     	/** affichage des noms des équipements/armes */
	     	SDL_RenderCopy(pRenderer,nomObj[i%10],NULL,&destNom);
	     	destzone.y+=destzone.h+7;
	}
	
     }
     
     /** test si il y a un équipements/armes a cet emplacement d'inventaire,
     *   si oui affiche l'image, la description et le bouton jeter,
     *   et les flêche pour changer de page si possible
     */
     if(MouseClick!=-1 && MouseClick<(inv->nbEquActu+inv->nbArmActu)){
     	if(MouseClick<inv->nbEquActu){
     		SDL_RenderCopy(pRenderer,inv->equipements[MouseClick]->artwork,NULL,&destImage);
     	}
     	else{
     		SDL_RenderCopy(pRenderer,inv->armes[MouseClick-inv->nbEquActu]->artwork,NULL,&destImage);
     	}
     	
	/** affichage de l'image des équipements/armes ainsi que ça description */
	SDL_RenderCopy(pRenderer,descObj[MouseClick%10],NULL,&destDesc);
	
	/** regarde yonThrow pour gérer l'affichage du bouton jeter ainsi que ça boite d'interraction pour jeter un objet */
	if(*yonThrow==0){
		SDL_RenderCopy(pRenderer,buttonThrowOver,NULL,destThrowButton);
	}
	else if(*yonThrow>=1 && *yonThrow <=3){
		SDL_RenderCopy(pRenderer,buttonThrow,NULL,destThrowButton);
		SDL_RenderCopy(pRenderer,boxYoNThrow,NULL,&destBoxYoNThrow);
	}
	
	/** cas ou l'on a cliquer sur oui */
	else if(*yonThrow==5){
		if(MouseClick<inv->nbEquActu){
			jeter_stuff(inv,MouseClick);
		}
		else if(MouseClick-inv->nbEquActu<inv->nbArmActu){
		 	jeter_arme(inv,inv->armes[MouseClick-inv->nbEquActu]);
		}
		 
		*yonThrow=-1;
	}
	else{
		SDL_RenderCopy(pRenderer,buttonThrow,NULL,destThrowButton);
	}
     }
     
     /** affichage flèche de gauche dans l'inventaire puis libère la mémoire */
     if(numPage>0){
     	if(MouseOver==54){
     		arrow=loadTexture("../Ressource/Inventory/leftOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/left.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
     	SDL_DestroyTexture(arrow);
     }
     
     /** calculdes coordonnées/dimensions et affichage de la flèches droite dans l'inventaire puis libère la mémoire */
     destArrow.x+=destThrowButton->w*1.75;
     if(numPage<nbPage-1){
     	if(MouseOver==55){
     		arrow=loadTexture("../Ressource/Inventory/rightOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/right.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
     	SDL_DestroyTexture(arrow);
     }
     
     /** calculdes coordonnées/dimensions et affichage de la flèches gauche des perso puis libère la mémoire */
     destArrow.x=destArrow.w;
     if(numPagePerso>0){
     	if(MouseOver==56){
     		arrow=loadTexture("../Ressource/Inventory/leftOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/left.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
     	SDL_DestroyTexture(arrow);
     }
     
     /** calculdes coordonnées/dimensions et affichage de la flèches droite des perso puis libère la mémoire */
     destArrow.x=w/2-destArrow.w*2;
     if(numPagePerso<team->nbPerso-1){
     	if(MouseOver==57){
     		arrow=loadTexture("../Ressource/Inventory/rightOver.png",pRenderer);
     	}
     	else{
     		arrow=loadTexture("../Ressource/Inventory/right.png",pRenderer);
     	}
     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
     	SDL_DestroyTexture(arrow);
     }
     
     /** si le bouton équiper est appuyer on équipe l'équipement/armes séléctionner dans l'inventaire au personnage correspondant au numero de page des personnages */
     if(*eOuStuff==0){
     	if(MouseClick<inv->nbEquActu && MouseClick>-1){
     		if(inv->equipements[MouseClick]!=NULL){
     			equiper_stuff(inv->equipements[MouseClick],team->team[numPagePerso]);
     		}
     	}
    
	    else if(MouseClick-inv->nbEquActu<inv->nbArmActu && MouseClick>-1){
	  	    equiper_arme(inv->armes[MouseClick-inv->nbEquActu],team->team[numPagePerso]);
	    }
	 
     	*eOuStuff=-1;
     }
     
     /** chargement->affichage puis libération de la mémoire pour le bouton équiper */
     if((MouseClick<54 && MouseClick>-1) && MouseOver!=58){
     	equipOunequipButton=loadTexture("../Ressource/Inventory/equipButton.png",pRenderer);
     }
     else{
     	equipOunequipButton=loadTexture("../Ressource/Inventory/equipButtonHover.png",pRenderer);
     }
     SDL_RenderCopy(pRenderer,equipOunequipButton,NULL,&destEOUButton);
     SDL_DestroyTexture(equipOunequipButton);
     destEOUButton.x+=destEOUButton.w;
     
     /** si le bouton déséquiper est appuyer on déséquipe l'équipement/armes séléctionner dans les slots du personnage */
     if(*eOuStuff==1 && slot!=-1){
     	if((slot*-1)-2<4){
     		if(team->team[numPagePerso]->stuff[(slot*-1)-2]!=NULL){
     			desequiper_stuff((slot*-1)-2,team->team[numPagePerso]);
     		}
     	}
     	else {
     		if(team->team[numPagePerso]->armes[(slot*-1)-2-4]!=NULL){
     			desequiper_arme(team->team[numPagePerso]->armes[(slot*-1)-2-4],team->team[numPagePerso]);
     		}
     	}
     	 *eOuStuff=-1;
     }
     
     /** chargement->affichage puis libération de la mémoire pour le bouton déséquiper */
     if(slot!=-1 && MouseOver!=59){
     
     	/** cas équipement */
     	if((slot*-1)-2<4){
     		if(team->team[numPagePerso]->stuff[(slot*-1)-2]!=NULL){
     			equipOunequipButton=loadTexture("../Ressource/Inventory/unequipButton.png",pRenderer);
     		}
     		else{
     			equipOunequipButton=loadTexture("../Ressource/Inventory/unequipButtonHover.png",pRenderer);
     		}
     	}
     	
     	/** cas armes */
     	else{
     		if(team->team[numPagePerso]->armes[(slot*-1)-2-4]!=NULL){
     			equipOunequipButton=loadTexture("../Ressource/Inventory/unequipButton.png",pRenderer);
     		}
     		else{
     			equipOunequipButton=loadTexture("../Ressource/Inventory/unequipButtonHover.png",pRenderer);
     		}
     	}
     	
     	
     }
     else{
     	equipOunequipButton=loadTexture("../Ressource/Inventory/unequipButtonHover.png",pRenderer);
     }
     SDL_RenderCopy(pRenderer,equipOunequipButton,NULL,&destEOUButton);
     SDL_DestroyTexture(equipOunequipButton);
     
     /** destruction des textures utiliser pour le menu */
     SDL_DestroyTexture(objOver); 
     SDL_DestroyTexture(objClick);
     SDL_DestroyTexture(menu);
     
     /** destruction des textures utiliser pour le bouton jeter et ça boite */
     SDL_DestroyTexture(buttonThrow);
     SDL_DestroyTexture(buttonThrowOver);
     SDL_DestroyTexture(boxYoNThrow);
     
     /** destruction des textures utiliser pour les slots des équipements/armes */
     SDL_DestroyTexture(slotStuffSelect);
     SDL_DestroyTexture(slotStuff);
     
     /** destruction des textures des noms et descriptions des objets */
     for(i=0;i<10;i++){
     	if(nomObj[i]!=NULL){
     		SDL_DestroyTexture(nomObj[i]);
     	}
     	if(descObj[i]!=NULL){
     		SDL_DestroyTexture(descObj[i]);
     	}
     }
     
}


/** vérifie si on a asser d'argent pour acheter l'item sélectionner, si on a la place pour le stocker ou si on a pas 3 fois le même équipements 
*  si les conditions sont réunies on ne touche pas a achatPossible sinon si l'une des vérifications n'est pas vrai met achatPossible a 0 
*/
int achat_possible(int choiceBiy,int biome,inventaire_t * inv,objet_t allPot[ALL_OBJETS],equipement_t allStuff[ALL_EQUIPEMENTS][3],arme_t armes[ALL_ARMES][3]){
	if((choiceBiy>-1 && choiceBiy<3) || (choiceBiy>9 && choiceBiy<13)){
	
		/** cas ou magasin du biome 1 à 3 */
		if((choiceBiy>-1 && choiceBiy<3) && biome!=5){
			if(ajouter_stuff(allStuff,inv,choiceBiy+(biome-1)*3)==0){
				jeter_stuff(inv,inv->nbEquActu-1);
				if(inv->bourse<allStuff[choiceBiy+(biome-1)*3][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		
		/** cas ou magasin du biome 5 */
		else if(biome==5){
			if(ajouter_stuff(allStuff,inv,choiceBiy+biome*3)==0){
				jeter_stuff(inv,inv->nbEquActu-1);
				if(inv->bourse<allStuff[choiceBiy+biome*3][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		
		/** cas ou magasin du biome 4 */
		else{
			if(ajouter_stuff(allStuff,inv,choiceBiy-10+biome*3)==0){
				jeter_stuff(inv,inv->nbEquActu-1);
				if(inv->bourse<allStuff[choiceBiy-10+biome*3][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
	}
	
	else if((choiceBiy>2 && choiceBiy<7) || (choiceBiy>12 && choiceBiy<17)){
	
		/** cas ou magasin du biome 1 à 3 */
		if((choiceBiy>2 && choiceBiy<7) && biome!=5){
			if(ajouter_arme(armes,inv,(choiceBiy-3)+(biome-1)*4)==0){
		 		jeter_arme(inv,inv->armes[inv->nbArmActu-1]);
				if(inv->bourse<armes[(choiceBiy-3)+(biome-1)*4][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		
		/** cas ou magasin du biome 5 */
		else if(biome==5){
			if(ajouter_arme(armes,inv,(choiceBiy-3)+biome*4)==0){
				jeter_arme(inv,inv->armes[inv->nbArmActu-1]);
				if(inv->bourse<armes[(choiceBiy-3)+biome*4][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		
		/** cas ou magasin du biome 4 */
		else{
			if(ajouter_arme(armes,inv,(choiceBiy-13)+biome*4)==0){
				jeter_arme(inv,inv->armes[inv->nbArmActu-1]);
				if(inv->bourse<armes[(choiceBiy-13)+biome*4][0].cout){
					return 0;
				}
			}
			else{
				return 0;
			}
		}
	}
	
	/** objets */
	else if(choiceBiy>6 && choiceBiy<10){
	
		/** cas différents selon chaque biome */
		switch(biome){
		
			/** biome 1 */
			case 1:
				if(ajouter_obj(inv,allPot,(choiceBiy-7)*3)==0){
					jeter_obj(inv,inv->nbObjActu-1);
					if(inv->bourse<allPot[(choiceBiy-7)*3].cout){
						return 0;
					}
				}
				else{
					return 0;
				};break;
				
			/** biome 2 */
			case 2:
				if(choiceBiy==7){
					if(ajouter_obj(inv,allPot,1)==0){
						jeter_obj(inv,inv->nbObjActu-1);
						if(inv->bourse<allPot[1].cout){
							return 0;
						}
					}
					else{
						return 0;
					}
				}
				else{
					if(ajouter_obj(inv,allPot,(choiceBiy-7)*3)==0){
						jeter_obj(inv,inv->nbObjActu-1);
						if(inv->bourse<allPot[(choiceBiy-7)*3].cout){
							return 0;
						}
					}
					else{
						return 0;
					}
				};break;
				
			/** biome 3 */
			case 3:
				switch(choiceBiy){
					case 7:
						if(ajouter_obj(inv,allPot,1)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[1].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 8:
						if(ajouter_obj(inv,allPot,4)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[4].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 9:
						if(ajouter_obj(inv,allPot,6)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[6].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
				};break;
				
			/** biome 4 */
			case 4:
				switch(choiceBiy){
					case 7:
						if(ajouter_obj(inv,allPot,2)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[2].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 8:
						if(ajouter_obj(inv,allPot,4)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[4].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 9:
						if(ajouter_obj(inv,allPot,7)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[7].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
				};break;
				
			/** biome 5 */
			case 5:
				switch(choiceBiy){
					case 7:
						if(ajouter_obj(inv,allPot,2)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[2].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 8:
						if(ajouter_obj(inv,allPot,5)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[5].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
					case 9:
						if(ajouter_obj(inv,allPot,8)==0){
							jeter_obj(inv,inv->nbObjActu-1);
							if(inv->bourse<allPot[8].cout){
								return 0;
							}
						}
						else{
							return 0;
						};break;
				};break;
		}
		
	}
	return 1;
}

/**
* fonction EventsInvShop qui gère le menu d'achat dans le magasin pour acheter équipement, armes et objets
*/
void EventShop(int *MouseOver,int *Action,SDL_Renderer* pRenderer,int biome,equipement_t allStuff[ALL_EQUIPEMENTS][3],inventaire_t* inv,int w,int h,scene_t* scene,objet_t allPot[ALL_OBJETS],int *choiceBiy,arme_t armes[ALL_ARMES][3]){
	
	
	/** création de la variable event qui récupère les évènements */
	SDL_Event event;
	int achatPossible=achat_possible(*choiceBiy,biome,inv,allPot,allStuff,armes);
	
	/** boucle d'attente d'évènements */
	while (SDL_PollEvent(&event) != 0){
		switch(event.type){
				  
			/** regarde la position de la sourit */
			case SDL_MOUSEMOTION:
			
				/** bouton retour 30 et acheter 29 */
				if(event.motion.y>=(h-h/2)/2+h/2 && event.motion.y<=(h-h/2)/2+h/2+(((h-h/2)/2)/2)){
					if(event.motion.x>=(w-950)/2+950/2 && event.motion.x<=(w-950)/2+950){
						*MouseOver=30;
					}
					else if(event.motion.x>=(w-950)/2 && event.motion.x<=(w-950)/2+950/2){
						*MouseOver=29;
					}
				}
				/** sur les item de la première étagère */
				else if(event.motion.y>=(h-h/2)/2+44 && event.motion.y<=(h-h/2)/2+44+64){
					if(event.motion.x>=(w-950)/2+70 && event.motion.x<=(w-950)/2+70+64){
						*MouseOver=0;
					}
					else if(event.motion.x>=(w-950)/2+70+64*1.3 && event.motion.x<=(w-950)/2+70+64*1.3+64){
						*MouseOver=1;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*2 && event.motion.x<=(w-950)/2+70+(64*1.3)*2+64){
						*MouseOver=2;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*3 && event.motion.x<=(w-950)/2+70+(64*1.3)*3+64){
						*MouseOver=3;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*4 && event.motion.x<=(w-950)/2+70+(64*1.3)*4+64){
						*MouseOver=4;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*5 && event.motion.x<=(w-950)/2+70+(64*1.3)*5+64){
						*MouseOver=5;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*6 && event.motion.x<=(w-950)/2+70+(64*1.3)*6+64){
						*MouseOver=6;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*7 && event.motion.x<=(w-950)/2+70+(64*1.3)*7+64){
						*MouseOver=7;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*8 && event.motion.x<=(w-950)/2+70+(64*1.3)*8+64){
						*MouseOver=8;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*9 && event.motion.x<=(w-950)/2+70+(64*1.3)*9+64){
						*MouseOver=9;
					}
				}
				
				/** sur les item de la deuxième étagère */
				else if(event.motion.y>=(h-h/2)/2+h/2-120 && event.motion.y<=(h-h/2)/2+h/2-120+64){
					if(event.motion.x>=(w-950)/2+70 && event.motion.x<=(w-950)/2+70+64){
						*MouseOver=10;
					}
					else if(event.motion.x>=(w-950)/2+70+64*1.3 && event.motion.x<=(w-950)/2+70+64*1.3+64){
						*MouseOver=11;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*2 && event.motion.x<=(w-950)/2+70+(64*1.3)*2+64){
						*MouseOver=12;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*3 && event.motion.x<=(w-950)/2+70+(64*1.3)*3+64){
						*MouseOver=13;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*4 && event.motion.x<=(w-950)/2+70+(64*1.3)*4+64){
						*MouseOver=14;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*5 && event.motion.x<=(w-950)/2+70+(64*1.3)*5+64){
						*MouseOver=15;
					}
					else if(event.motion.x>=(w-950)/2+70+(64*1.3)*6 && event.motion.x<=(w-950)/2+70+(64*1.3)*6+64){
						*MouseOver=16;
					}
				}
				
				/** sinon sur aucun bouton ou interaction */
				else{
					*MouseOver=-1;
				};break;
			  
			/** récupération d'un bouton relacher venant de la sourit */
			case SDL_MOUSEBUTTONUP:
				
				/** bouton retour actionner on reviet aux choix du vendeur */
				if(*MouseOver==30){
					*Action=5;
					*scene=OP;
					*MouseOver=-1;
					*choiceBiy=-1;
				}
				
				/** toutes les réaction si le bouton acheter est actionner ou si un item est sélectionner */
				/** biome 1 */
				if(biome==1){
				
					/** item sélectionner */
					if(*MouseOver>=0 && *MouseOver<=8){
						*choiceBiy=*MouseOver;
					}
					
					/** bouton acheter cliquer et un objet est sélectionner */
					else if(*MouseOver==29 && *choiceBiy>-1){
						/** on vérifie que l'achat soit possible a chaque fois */
						
						/** cas d'un équipements */
						if(*choiceBiy<3  && achatPossible){
							ajouter_stuff(allStuff,inv,*choiceBiy);
							inv->bourse-=allStuff[*choiceBiy]->cout;
						}
						else if(*choiceBiy>2 && *choiceBiy<7 && achatPossible){
							ajouter_arme(armes,inv,(*choiceBiy-3));
							inv->bourse-= armes[(*choiceBiy-3)][0].cout;
						}
						/** cas d'un objet */
						else if(*choiceBiy>6 && achatPossible){
							ajouter_obj(inv,allPot,(*choiceBiy-7)*3);
							inv->bourse-=allPot[(*choiceBiy-7)*3].cout;
						}
					}
				}
				
				/** biome 4 */
				else if (biome==4){
					
					/** item sélectionner */
					if(*MouseOver>=0 && *MouseOver<=16){
						*choiceBiy=*MouseOver;
					}
					
					/** bouton acheter cliquer et un objet est sélectionner */
					else if(*MouseOver==29 && *choiceBiy>-1){
						/** on vérifie que l'achat soit possible a chaque fois */
						
						/** cas d'un équipements */
						if(((*choiceBiy>-1 && *choiceBiy<3) || (*choiceBiy>9 && *choiceBiy<13)) && achatPossible){
							if(*choiceBiy>-1 && *choiceBiy<3){
								ajouter_stuff(allStuff,inv,*choiceBiy+(biome-1)*3);
								inv->bourse-=allStuff[*choiceBiy+(biome-1)*3]->cout;
							}
							else{
								ajouter_stuff(allStuff,inv,*choiceBiy-10+biome*3);
								inv->bourse-=allStuff[*choiceBiy-10+biome*3]->cout;
							}
						}
						else if(((*choiceBiy>2 && *choiceBiy<7) || (*choiceBiy>12 && *choiceBiy<17)) && achatPossible){
							if(*choiceBiy>2 && *choiceBiy<7){
								
								ajouter_arme(armes,inv,*choiceBiy-3+(biome-1)*4);
								inv->bourse-=armes[*choiceBiy-3+(biome-1)*4][0].cout;
							}
							else{
								ajouter_arme(armes,inv,*choiceBiy-13+biome*4);
								inv->bourse-=armes[*choiceBiy-13+biome*4][0].cout;
							}
						}
						
						
						/** cas objet */
						else if((*choiceBiy>6 && *choiceBiy<10) && achatPossible){
							switch(*choiceBiy){
								case 7:
									ajouter_obj(inv,allPot,2);
									inv->bourse-=allPot[2].cout;break;
								case 8:
									ajouter_obj(inv,allPot,4);
									inv->bourse-=allPot[4].cout;break;
								case 9:
									ajouter_obj(inv,allPot,7);
									inv->bourse-=allPot[7].cout;break;
							}
						}
					}
				}
				
				/** biome 2,3 et 5 */
				else{
					/** item sélectionner */
					if(*MouseOver>=0 && *MouseOver<=9){
						*choiceBiy=*MouseOver;
					}
					
					/** bouton acheter cliquer et un objet est sélectionner */
					else if(*MouseOver==29 && *choiceBiy>-1){
						/** on vérifie que l'achat soit possible a chaque fois */
						
						/** cas d'un équipements */
						/** biome 5 */
						if(biome==5){
							if(*choiceBiy<3 && achatPossible){
								ajouter_stuff(allStuff,inv,*choiceBiy+biome*3);
								inv->bourse-=allStuff[*choiceBiy+biome*3]->cout;
							}
							else if(*choiceBiy>2 && *choiceBiy<7 && achatPossible){
								ajouter_arme(armes,inv,*choiceBiy-3+biome*4);
								inv->bourse-=armes[*choiceBiy-3+biome*4][0].cout;
							}
						}
						
						/** autre biome */
						else{
							if(*choiceBiy<3 && achatPossible){
								ajouter_stuff(allStuff,inv,*choiceBiy+(biome-1)*3);
								inv->bourse-=allStuff[*choiceBiy+(biome-1)*3]->cout;
							}
							else if(*choiceBiy>2 && *choiceBiy<7 && achatPossible){
								ajouter_arme(armes,inv,*choiceBiy-3+(biome-1)*4);
								inv->bourse-=armes[*choiceBiy-3+(biome-1)*4][0].cout;
							}
						}
						
						/** cas objet */
						if(*choiceBiy>6 && achatPossible){
						
							/** objet différents dans chaque magasin selon le biome */
							switch(biome){
								/** biome 2 */
								case 2:
									if(*choiceBiy==7){
											ajouter_obj(inv,allPot,1);
											inv->bourse-=allPot[1].cout;
									}
									else{
											ajouter_obj(inv,allPot,(*choiceBiy-7)*3);
											inv->bourse-=allPot[(*choiceBiy-7)*3].cout;
									};break;
									
								/** biome 3 */
								case 3:
									switch(*choiceBiy){
										case 7:
											ajouter_obj(inv,allPot,1);
											inv->bourse-=allPot[1].cout;break;
										case 8:
											ajouter_obj(inv,allPot,4);
											inv->bourse-=allPot[4].cout;break;
										case 9:
											ajouter_obj(inv,allPot,6);
											inv->bourse-=allPot[6].cout;break;
									};break;
									
								/** biome 5 */
								case 5:
									switch(*choiceBiy){
										case 7:
											ajouter_obj(inv,allPot,2);
											inv->bourse-=allPot[2].cout;break;
										case 8:
											ajouter_obj(inv,allPot,5);
											inv->bourse-=allPot[5].cout;break;
										case 9:
											ajouter_obj(inv,allPot,8);
											inv->bourse-=allPot[8].cout;break;
									};break;
							}
						}
					}
				}
		}
	}
	
	/** déclaration texture */
	SDL_Texture * buttonBack=NULL;
	SDL_Texture * buttonBiy=NULL;
	SDL_Texture * texteBourse=NULL;
	SDL_Texture * textePrix=NULL;
	SDL_Texture * zoneBiy=loadTexture("../Ressource/Menu/shop.png",pRenderer);
	
	/** déclaration rect */
	SDL_Rect destBoxBiy={(w-950)/2,(h-h/2)/2,950,h/2};
	SDL_Rect destBack={destBoxBiy.x+destBoxBiy.w/2,destBoxBiy.y+destBoxBiy.h,destBoxBiy.w/2,destBoxBiy.y/2};
	SDL_Rect destBourse={destBoxBiy.x,destBoxBiy.y-32*2,32*6.5,32*2};
	SDL_Rect destPrix;
	
	/** déclaration couleur */
	SDL_Color blanc={255,255,255};
	SDL_Color selected={255,255,0};
	
	/** déclaration char pour les prix ainsi que la bourse actuel */
	char bourse[4];
	char textBourse[13]="bourse : ";
	char prix[3];
	sprintf(bourse,"%d",inv->bourse);
	strcat(textBourse,bourse);
	texteBourse=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,textBourse,34,blanc);
	
	/** change l'affichage du bouton retour selon si on est dessus ou non */
	if(*MouseOver==30){
		buttonBack=loadTexture("../Ressource/Menu/backButtonHover.png",pRenderer);
	}
	else{
		buttonBack=loadTexture("../Ressource/Menu/backButton.png",pRenderer);
	}
	
	/** change l'affichage du bouton acheter selon si on est dessus ou non, si on a l'argent nécessaire pour l'acheter et si on peut le stocker */
	if(*MouseOver==29 || *choiceBiy==-1 || achatPossible==0){
		buttonBiy=loadTexture("../Ressource/Menu/biyButtonHover.png",pRenderer);
	}
	else{
		buttonBiy=loadTexture("../Ressource/Menu/biyButton.png",pRenderer);
	}
	
	/** affichage des bouton acheter et retour, de la zone d'item et de la bourse actuel en haut a gauche */
	SDL_RenderCopy(pRenderer,buttonBack,NULL,&destBack);
	destBack.x-=destBack.w;
	SDL_RenderCopy(pRenderer,buttonBiy,NULL,&destBack);
	SDL_RenderCopy(pRenderer,zoneBiy,NULL,&destBoxBiy);
	SDL_RenderCopy(pRenderer,texteBourse,NULL,&destBourse);
	
	/** calcul des coordonnées et affichage des items ainsi que leur prix juste en dessous */
	destBoxBiy.x+=70;
	destBoxBiy.y+=44;
	destBoxBiy.w=destBoxBiy.h=64;
	destPrix.h=32;destPrix.w=32;
	if(biome<4){
		for(int i=0;i<3;i++){
		
			sprintf(prix,"%d",allStuff[i%3+(biome-1)*3]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,allStuff[i%3+(biome-1)*3]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.30;
		}
		for(int i=0;i<4;i++){
		
			sprintf(prix,"%d",armes[i%4+(biome-1)*4][0].cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy-3!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,armes[i%4+(biome-1)*4][0].artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.30;
		}
		switch(biome){
		
			case 1:
				for(int i=0;i<2;i++){
					sprintf(prix,"%d",allPot[i*3].cout);
					
					/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
					if(*choiceBiy-7!=i){
						textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
					}
					else{
						textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
					}
					destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
					destPrix.y=destBoxBiy.y+destBoxBiy.w;
					SDL_RenderCopy(pRenderer,allPot[i*3].sprite,NULL,&destBoxBiy);
					SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
					SDL_DestroyTexture(textePrix);
					destBoxBiy.x+=destBoxBiy.w*1.30;
				};break;
			case 2:
				sprintf(prix,"%d",allPot[1].cout);
				
				/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
				if(*choiceBiy-7!=0){
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
				}
				else{
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
				}
				destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
				destPrix.y=destBoxBiy.y+destBoxBiy.w;
				SDL_RenderCopy(pRenderer,allPot[1].sprite,NULL,&destBoxBiy);
				SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
				SDL_DestroyTexture(textePrix);
				destBoxBiy.x+=destBoxBiy.w*1.30;
				
				for(int i=1;i<3;i++){
					sprintf(prix,"%d",allPot[i*3].cout);
					
					/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
					if(*choiceBiy-7!=i){
						textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
					}
					else{
						textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
					}
					destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
					destPrix.y=destBoxBiy.y+destBoxBiy.w;
					SDL_RenderCopy(pRenderer,allPot[i*3].sprite,NULL,&destBoxBiy);
					SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
					SDL_DestroyTexture(textePrix);
					destBoxBiy.x+=destBoxBiy.w*1.30;
				};break;
			case 3:
				sprintf(prix,"%d",allPot[1].cout);
				
				/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
				if(*choiceBiy-7!=0){
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
				}
				else{
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
				}
				destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
				destPrix.y=destBoxBiy.y+destBoxBiy.w;
				SDL_RenderCopy(pRenderer,allPot[1].sprite,NULL,&destBoxBiy);
				SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
				SDL_DestroyTexture(textePrix);
				destBoxBiy.x+=destBoxBiy.w*1.30;
				
				sprintf(prix,"%d",allPot[4].cout);
				
				/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
				if(*choiceBiy-7!=1){
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
				}
				else{
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
				}
				destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
				destPrix.y=destBoxBiy.y+destBoxBiy.w;
				SDL_RenderCopy(pRenderer,allPot[4].sprite,NULL,&destBoxBiy);
				SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
				SDL_DestroyTexture(textePrix);
				destBoxBiy.x+=destBoxBiy.w*1.30;
				
				sprintf(prix,"%d",allPot[6].cout);
				
				/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
				if(*choiceBiy-7!=2){
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
				}
				else{
					textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
				}
				destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
				destPrix.y=destBoxBiy.y+destBoxBiy.w;
				SDL_RenderCopy(pRenderer,allPot[6].sprite,NULL,&destBoxBiy);
				SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
				SDL_DestroyTexture(textePrix);
				destBoxBiy.x+=destBoxBiy.w*1.30;break;
			}
	}
	else if(biome==4){
		for(int i=0;i<3;i++){
			sprintf(prix,"%d",allStuff[i+(biome-1)*3]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,allStuff[i+(biome-1)*3]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.3;
		}
		
		for(int i=0;i<4;i++){
		
			sprintf(prix,"%d",armes[i%4+(biome-1)*4]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy-3!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,armes[i%4+(biome-1)*4]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.30;
		}
		
		sprintf(prix,"%d",allPot[2].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=0){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[2].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
		
		sprintf(prix,"%d",allPot[4].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=1){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[4].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
		
		sprintf(prix,"%d",allPot[7].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=2){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[7].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
		
		destBoxBiy.x=((w-950)/2)+74;
		destBoxBiy.y=(h-h/2)/2+h/2-120;
		for(int i=0;i<3;i++){
			sprintf(prix,"%d",allStuff[i+biome*3]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy-10!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,allStuff[i+biome*3]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.3;
		}
		
		for(int i=0;i<4;i++){
		
			sprintf(prix,"%d",armes[i%4+biome*4]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy-13!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,armes[i%4+biome*4]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.30;
		}
		
	}
	else if(biome==5){
		for(int i=0;i<3;i++){
			sprintf(prix,"%d",allStuff[i+biome*3]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,allStuff[i+biome*3]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.5;
		}
		
		for(int i=0;i<4;i++){
		
			sprintf(prix,"%d",armes[i%4+biome*4]->cout);
			
			/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
			if(*choiceBiy-3!=i){
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
			}
			else{
				textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
			}
			destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
			destPrix.y=destBoxBiy.y+destBoxBiy.w;
			SDL_RenderCopy(pRenderer,armes[i%4+biome*4]->artwork,NULL,&destBoxBiy);
			SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
			SDL_DestroyTexture(textePrix);
			destBoxBiy.x+=destBoxBiy.w*1.30;
		}
		
		sprintf(prix,"%d",allPot[2].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=0){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[2].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
		
		sprintf(prix,"%d",allPot[5].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=1){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[5].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
		
		sprintf(prix,"%d",allPot[8].cout);
		
		/** affiche le prix en blanc de base si l'item est sélectionner l'affiche en jaune */
		if(*choiceBiy-7!=2){
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,blanc);
		}
		else{
			textePrix=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,34,selected);
		}
		destPrix.x=destBoxBiy.x+(destBoxBiy.w-destPrix.w)/2;
		destPrix.y=destBoxBiy.y+destBoxBiy.w;
		SDL_RenderCopy(pRenderer,allPot[8].sprite,NULL,&destBoxBiy);
		SDL_RenderCopy(pRenderer,textePrix,NULL,&destPrix);
		SDL_DestroyTexture(textePrix);
		destBoxBiy.x+=destBoxBiy.w*1.30;
	}
	
	/** destruction texture */
	SDL_DestroyTexture(buttonBiy);
	SDL_DestroyTexture(buttonBack);
	SDL_DestroyTexture(zoneBiy);
	SDL_DestroyTexture(texteBourse);
	
	/** délai d'affichage */
	//SDL_Delay(35);
}

void EventSell(int *MouseOver,int *MouseClick,int *Action,SDL_Renderer* pRenderer,inventaire_t* inv,int w,int h,scene_t* scene,int *numPage){
	
	/** déclaration du nombre de page et des variables pour la taille du texte en largeur et hauteur */
	int  textwidth, textheight,i;
	int nbPage;
     	if(((inv->nbEquActu+inv->nbArmActu)/10.0)>((inv->nbEquActu+inv->nbArmActu)/10)){
     		nbPage=((inv->nbEquActu+inv->nbArmActu)/10)+1;
     	}
     	else{
     		nbPage=((inv->nbEquActu+inv->nbArmActu)/10);
     	}
     	
	/** création de la variable event qui récupère les évènements */
	SDL_Event event;
	
	/** boucle d'attente d'évènements */
	while (SDL_PollEvent(&event) != 0){
		switch(event.type){
				  
			/** regarde la position de la sourit */
			case SDL_MOUSEMOTION:
			
				/** bouton retour 55 et vendre 54 */
				if(event.motion.y>=(h-h/2)/2+h/2 && event.motion.y<=(h-h/2)/2+h/2+(((h-h/2)/2)/2)){
					if(event.motion.x>=(w-950)/2+950/2 && event.motion.x<=(w-950)/2+950){
						*MouseOver=55;
					}
					else if(event.motion.x>=(w-950)/2 && event.motion.x<=(w-950)/2+950/2){
						*MouseOver=54;
					}
				}
				
				/** regarde si la sourit est dans les case d'équipements/armes */
				else if (event.motion.x >= (w-950)/2+70 && event.motion.x <= (w-950)/2+70+950/3 && event.motion.y<=(h-h/2)/2+h/2){
				  	if(event.motion.y >= (h-h/2)/2+22 && event.motion.y <= (h-h/2)/2+22+(h/2)/15){
				  		*MouseOver=0+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+(h/2)/15+7 && event.motion.y <= (h-h/2)/2+22+(h/2)/15+7+(h/2)/15){
				  		*MouseOver=1+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*2 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*2+(h/2)/15){
				  		*MouseOver=2+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*3 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*3+(h/2)/15){
				  		*MouseOver=3+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*4 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*4+(h/2)/15){
				  		*MouseOver=4+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*5 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*5+(h/2)/15){
				  		*MouseOver=5+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*6 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*6+(h/2)/15){
				  		*MouseOver=6+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*7 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*7+(h/2)/15){
				  		*MouseOver=7+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*8 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*8+(h/2)/15){
				  		*MouseOver=8+((*numPage)*10);
				  	}
				  	else if(event.motion.y >= (h-h/2)/2+22+((h/2)/15+7)*9 && event.motion.y <= (h-h/2)/2+22+((h/2)/15+7)*9+(h/2)/15){
				  		*MouseOver=9+((*numPage)*10);
				  	}
				  	else{
				  		*MouseOver=-1;
				  	}
				}
				
				/** regarde si la sourit est sur la flèche gauche ou droite */
				else if (event.motion.x >= (w-950)/2+950*0.65-32  && event.motion.y>=(h-h/2)/2+22+h/6+5+40 && event.motion.y<=(h-h/2)/2+22+h/6+5+40+32){
					if(event.motion.x <= (w-950)/2+950*0.65){
						*MouseOver=56;
					}
					else if(event.motion.x >= (w-950)/2+950*0.65+h/6 && event.motion.x <= (w-950)/2+950*0.65+32+h/6){
						*MouseOver=57;
					}
					else{
						*MouseOver=-1;
					}
				}
				
				else{
					*MouseOver=-1;
				};break;
			case SDL_MOUSEBUTTONUP:
				
				/** bouton retour actionner on revient aux choix du vendeur */
				if(*MouseOver==55){
					*Action=5;
					*scene=OP;
					*MouseOver=-1;
					*MouseClick=-1;
				}
				
				/** bouton vendre actionner seulement si un équipement/armes est sélectionner */
				else if(*MouseOver==54 && *MouseClick!=-1){
					if(*MouseClick<inv->nbEquActu){
				     		inv->bourse+=inv->equipements[*MouseClick]->cout/2;
				     		jeter_stuff(inv,*MouseClick);
				     		*MouseClick=-1;
				     	}
				     	else if(*MouseClick-inv->nbEquActu<inv->nbArmActu){
				     		inv->bourse+=inv->armes[*MouseClick-inv->nbEquActu]->cout/2;
				     		jeter_arme(inv,inv->armes[*MouseClick-inv->nbEquActu]);
				     		*MouseClick=-1;
				     	}
				}
				
				/** MouseClick prend la valeur de l'équipement/armes sélectionner dans l'inventaire */
				else if(*MouseOver < inv->nbEquActu+inv->nbArmActu){
					*MouseClick=*MouseOver;
				}
				
				/** change de page selon la flèche sur laquel on est */
				switch(*MouseOver){
					case 56:*numPage-=1;*MouseClick=-1;break;
					case 57:*numPage+=1;*MouseClick=-1;break;
				};break;
		}
	}
	
	/** vérification du numero de page pour éviter de dépasser le nombre de page ou d'être en dessous de 0 */
	if(*numPage<0){
      	   *numPage=0;
        }
        else if(*numPage>=nbPage){
           if(nbPage>0){	
           	*numPage=nbPage-1;
           }
           else{
           	*numPage=0;
           }
        }
        
	/** déclaration des textures */
	SDL_Texture * buttonBack=NULL;
	SDL_Texture * buttonSell=NULL;
	SDL_Texture * texteBourse=NULL;
	SDL_Texture * boxSell=loadTexture("../Ressource/Inventory/boxCharacter.png",pRenderer);
	SDL_Texture * nomObj[10];
	SDL_Texture * prixStuff[10];
	SDL_Texture * descObj[10];
	SDL_Texture * objClick=loadTexture("../Ressource/objSelect.png",pRenderer);
     	SDL_Texture * objOver=loadTexture("../Ressource/objHover.png",pRenderer);
     	SDL_Texture* arrow=NULL;
     	
	/** déclaration couleur */
	SDL_Color blanc={255,255,255};
	SDL_Color unequipedColor={255,255,255};
	SDL_Color equipedColor={255,234,69};
	
	/** déclaration rect */
	SDL_Rect destBoxSell={(w-950)/2,(h-h/2)/2,950,h/2};
	SDL_Rect destBack={destBoxSell.x+destBoxSell.w/2,destBoxSell.y+destBoxSell.h,destBoxSell.w/2,destBoxSell.y/2};
	SDL_Rect destBourse={destBoxSell.x,destBoxSell.y-32*2,32*6.5,32*2};
	SDL_Rect destNom;
	SDL_Rect destzone={destBoxSell.x+70,destBoxSell.y+22,destBoxSell.w/3,destBoxSell.h/15};
	SDL_Rect destImage={destBoxSell.x+destBoxSell.w*0.65,destBoxSell.y+22,destBoxSell.h/3,destBoxSell.h/3};
	SDL_Rect destDesc={destImage.x+destImage.w/2-(w/5+destImage.w/35)/2,destImage.y+destImage.h+5,w/5+destImage.w/35,destzone.h+10};
	SDL_Rect destArrow={destImage.x-32,destDesc.y+40,32,32};
	
	/** déclaration char pour les prix ainsi que la bourse actuel */
	char bourse[4];
	char textBourse[13]="bourse : ";
	char prix[3];
	
	/** chargement de la texture du texte bourse avec le nombre d'argent posséder */
	sprintf(bourse,"%d",inv->bourse);
	strcat(textBourse,bourse);
	texteBourse=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,textBourse,34,blanc);
	
	/** change l'affichage du bouton retour selon si on est dessus ou non */
	if(*MouseOver==55){
		buttonBack=loadTexture("../Ressource/Menu/backButtonHover.png",pRenderer);
	}
	else{
		buttonBack=loadTexture("../Ressource/Menu/backButton.png",pRenderer);
	}
	
	/** change l'affichage du bouton vendre selon si on est dessus ou non, si un équipement/armes est sélectionner ou non */
	if(*MouseOver==54 || *MouseClick==-1){
		buttonSell=loadTexture("../Ressource/Menu/sellButtonHover.png",pRenderer);
	}
	else if(*MouseClick!=-1 && *MouseClick< inv->nbEquActu+inv->nbArmActu){
		buttonSell=loadTexture("../Ressource/Menu/sellButton.png",pRenderer);
	}
	
	/** affichage des bouton acheter et retour, de la zone d'item et de la bourse actuel en haut a gauche */
	SDL_RenderCopy(pRenderer,buttonBack,NULL,&destBack);
	destBack.x-=destBack.w;
	SDL_RenderCopy(pRenderer,buttonSell,NULL,&destBack);
	SDL_RenderCopy(pRenderer,boxSell,NULL,&destBoxSell);
	SDL_RenderCopy(pRenderer,texteBourse,NULL,&destBourse);
	
	/** chargement des textures des noms, description et des prix des équipement/armes dans l'inventaire */
	for(i=0+(*numPage*10);i<10+(*numPage*10);i++){
	     
	     	/** regarde si le on est sur des équipements */
	     	if(i < inv->nbEquActu){
		     	if(inv->equipements[i]!=NULL){
		     	sprintf(prix,"%d",inv->equipements[i]->cout/2);
		     		if(inv->equipements[i]->persoEquiper!=NULL){
		     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->nom,destzone.h,equipedColor);
		     		}
		     		else{
		     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->nom,destzone.h,unequipedColor);
		     		}
		     		descObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->equipements[i]->desc,destzone.h,unequipedColor);
		     		prixStuff[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,destzone.h,unequipedColor);
		     	}
		}
		
		/** regarde si le on est sur des armes */
	     	else if(i-inv->nbEquActu < inv->nbArmActu){
	     		sprintf(prix,"%d",inv->armes[i-inv->nbEquActu]->cout/2);
	     		if(inv->armes[i-inv->nbEquActu]!=NULL){
		     		if(inv->armes[i-inv->nbEquActu]->persoEquiper!=NULL){
		     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->nom,destzone.h,equipedColor);
		     		}
		     		else{
		     			nomObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->nom,destzone.h,unequipedColor);
		     		}
		     		descObj[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->armes[i-inv->nbEquActu]->desc,destzone.h,unequipedColor);
		     		prixStuff[i%10]=loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,prix,destzone.h,unequipedColor);
		     	}
	     	}
	     	
	     	/** sinon si l'inventaire a atteint ça limite mettre a NULL */
	     	else{
	     		nomObj[i%10]=NULL;
	     		descObj[i%10]=NULL;
	     		prixStuff[i%10]=NULL;
	     	}
	}
	
	/** affichage des équipements/armes et de la zone sur laquelle la sourit a cliquer ou est positionner */
	for(i=0+(*numPage*10);i<10+(*numPage*10);i++){
	     	
	     	/** affiche seulement si il y a un équipements/armes a cet emplacement */
	     	if(i<(inv->nbEquActu+inv->nbArmActu)){
	     		
	     		/** affichage de la zone autour des nom selon si il est selectionner ou non */
	     		if(*MouseClick==i){
		     		SDL_RenderCopy(pRenderer,objClick,NULL,&destzone);
		     	}
		     	else if(*MouseOver==i){
		     		SDL_RenderCopy(pRenderer,objOver,NULL,&destzone);
		     	}
		     	
		     	/** mise a jour des coordonnées et dimensions des noms des équipements/armes */
			SDL_QueryTexture(nomObj[i%10], NULL, NULL, &textwidth, &textheight);
		     	destNom.x=destzone.x+(destzone.w/2-textwidth/2);
		     	destNom.y=destzone.y+((destzone.h/2-textheight/2));
		     	destNom.w=textwidth;
		     	destNom.h=textheight;
		     	
		     	
		     	/** affichage des noms des équipements/armes */
		     	SDL_RenderCopy(pRenderer,nomObj[i%10],NULL,&destNom);
		     	destNom.x+=destNom.w+8;
			SDL_QueryTexture(prixStuff[i%10], NULL, NULL, &textwidth, &textheight);
			destNom.w=textwidth;
		     	destNom.h=textheight;
		     	SDL_RenderCopy(pRenderer,prixStuff[i%10],NULL,&destNom);
		     	destzone.y+=destzone.h+7;
		}
		
	}
	
	/** affichage de l'item sélectionner */
	if(*MouseClick!=-1 && *MouseClick<(inv->nbEquActu+inv->nbArmActu)){
	     	if(*MouseClick<inv->nbEquActu){
	     		SDL_RenderCopy(pRenderer,inv->equipements[*MouseClick]->artwork,NULL,&destImage);
	     	}
	     	else{
	     		SDL_RenderCopy(pRenderer,inv->armes[*MouseClick-inv->nbEquActu]->artwork,NULL,&destImage);
	     	}
	     	
		/** affichage de l'image des équipements/armes ainsi que ça description */
		SDL_RenderCopy(pRenderer,descObj[*MouseClick%10],NULL,&destDesc);
	}
	
	/** affichage flèche de gauche dans l'inventaire puis libère la mémoire */
	if(*numPage>0){
	     	if(*MouseOver==56){
	     		arrow=loadTexture("../Ressource/Inventory/leftOver.png",pRenderer);
	     	}
	     	else{
	     		arrow=loadTexture("../Ressource/Inventory/left.png",pRenderer);
	     	}
	     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
	     	SDL_DestroyTexture(arrow);
	}
	     
	/** calculdes coordonnées/dimensions et affichage de la flèches droite dans l'inventaire puis libère la mémoire */
	destArrow.x+=destArrow.w+destImage.w;
	if(*numPage<nbPage-1){
	     	if(*MouseOver==57){
	     		arrow=loadTexture("../Ressource/Inventory/rightOver.png",pRenderer);
	     	}
	     	else{
	     		arrow=loadTexture("../Ressource/Inventory/right.png",pRenderer);
	     	}
	     	SDL_RenderCopy(pRenderer,arrow,NULL,&destArrow);
	     	SDL_DestroyTexture(arrow);
	}
	
	/** libération de toutes les textures */
	SDL_DestroyTexture(buttonSell);
	SDL_DestroyTexture(buttonBack);
	SDL_DestroyTexture(boxSell);
	SDL_DestroyTexture(texteBourse);
	SDL_DestroyTexture(objClick);
	SDL_DestroyTexture(objOver);
	for(i=0;i<10;i++){
		SDL_DestroyTexture(nomObj[i]);
		SDL_DestroyTexture(descObj[i]);
		SDL_DestroyTexture(prixStuff[i]);
	}
}
