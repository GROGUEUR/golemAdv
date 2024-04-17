/**
* \file combat.c
* \brief programme gérant les combat
* \author Lenny Borry.
* \version 1.9.5
* \date 16 Avril 2024.
*/
#include "../lib/EventOp.h"
#include "../lib/combat.h"
#include <string.h>



mob_t * mob_creer(char nom[TAILLE_NOM],int lvl,int Xp_don,float PvMax,float Pv,float ManaMax,float Mana,float Def,float Res,float For,float Int,float Vit,SDL_Texture* MarcheHori,SDL_Texture* MarcheVert,SDL_Texture* IdleAnim,SDL_Texture* AttAnim,attaque_t * attaques[NB_ATT]){
	mob_t * mob = malloc(sizeof(mob_t));
	strcpy(mob->nom,nom);
	mob->lvl = lvl;
	mob->Xp_don = Xp_don;
	return mob;
} 

/**
* fonction DetectEventsFight qui s'occupera de gérer la détection
* des évènement quand nous sommes en combat
*/
void DetectEventsFight(int * menu_combat, int* MouseClick,int *MouseOver, int* quit, int* perso, scene_t* scene,int w,int h,int * W, int * H){

    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    /** coordonnés du rectangle d'options en combat */

    *W = h/3; /**largeur du grand rectangle*/
    *H = w/4; /**largeur des 4 carres qui coupent le grand rectangle*/

	int lon1 = 0.7 * *H; /**longueur du rectangle indiquant le nom des persos*/
	int lar1 = 0.25 * *W; /**largeur du rectangle indiquant le nom des persos*/

	int lon2 = lon1 ; /**longueur des rectangles "attaque" et "item"*/
	int lar2 = 0.4 * lon2; /**largeur des rectangles "attaque" et "item"*/

	int lon3 = lon1; /**longueur des rectangles de chaque attaque*/
	int lar3 = 0.2 * lon3; /**largeur des rectangles de chaque attaque*/

	int lon4 = lon1/2; /**longueur des rectangles de chaque objet */
	int lar4 = 0.3 * lon4; /**largeur des rectangles de chaque objet */

	int lon5 = lon1/2; /**longueur du rectangle du nom de l'attaque*/
	int lar5 = 0.5 * lon5; /**largeur du rectangle du nom de l'attaque*/

	int lon6 = 0.3 * lon1; /**longueur des rectangles "puissance" et "precision"*/
	int lar6 = 0.4 * lon6; /**largeur des rectangles "puissance" et "precision"*/

	int lon7 = 0.3 * lon1; /**taille du carre dans lequel il y aura le logo representant le type de l'attaque*/
	int lar7 = lon7;

	int lon8 = 0.8 * *H; /**longueur du rectangle de description de l'attaque*/
	int lar8 = 0.5 * lon8; /**largeur du rectangle de description de l'attaque*/

	int lon9 = 0.5 * *H; /**longueur du rectangle du nom de l'objet*/
	int lar9 = 0.15 * lon9; /**largeur du rectangle du nom de l'objet*/

	int lon10 = 0.5 * *W; /**taille du carre du pixel art de l'objet*/
	int lar10 = lon10;

	int lon11 = 0.8 * *H; /**longueur du rectangle de description de l'objet*/
	int lar11 = 0.1 * lon11; /**largeur du rectangle de description de l'objet*/

	int lon12 = 0.25 * *H; /**longueur du rectangle du bouton "utiliser"*/
	int lar12 = 0.2 * lon12; /**largeur du rectangle du bouton "utiliser"*/

	int dlar1 = (*W - 3*lar1)/4; /**ecart vertical entre les boutons indiquant le nom des persos*/
	int dlon1 = (*H - lon1)/2; /**ecart horizontal entre les boutons indiquant le nom des persos*/

	int dlar2 = (*W - 2*lar2)/3; /**ecart vertical entre les boutons "attaque" et "item" */
	int dlon2 = dlon1; /**ecart horizontal entre les boutons "attaque" et "item" */

	int dlar3a = (*W - 4*lar3)/5; /**ecart vertical entre les rectangles de chaque attaque*/
	int dlon3a = dlon1; /**ecart horizontal entre les rectangles de chaque attaque*/

	int dlar3b = (*W - 5*lar4)/6; /**ecart vertical entre les rectangles de chaque objet*/
	int dlon3b = (*H - 2*lon4)/3; /**ecart horizontal entre les rectangles de chaque objet*/

	int dlar4 = (*W - lar5 - lar8)/3; /**ecart vertical entre les rectangles du nom de l'attaque et de description de l'attaque*/
	int dlon4 = (*H - lon5 - lon6 - lon7)/4; /**ecart horizontal entre les rectangles du nom de l'attaque, de la puissance et du logo*/

	int dlar5 = lar5 - 2*lon6; /**ecart vertical entre les rectangles "puissance" et "precision"*/

	int dlar6 = (*W - lon7 - lar8 - dlar4)/2; /**ecart vertical entre les rectangles du logo et de description*/

	int dlar7 = (*W - lar12 - lar11 - lar10 - lar9)/5; /**ecart vertical entre les rectangles du nom, du pixel art, de la description et du bouton"utiliser"de l'objet*/

	int dlon9 = (*H - lon9)/2; /**ecart horizontal de chaque cote du rectangle nom de l'objet*/

	int dlon10 = (*H - lon10)/2; /**ecart horizontal de chaque cote du pixel art de l'objet*/

	int dlon11 = (*H - lon11)/2; /**ecart horizontal de chaque cote du rectangle description de l'objet*/

	int dlon12 = (*H - lon12)/2; /**ecart horizontal de chaque cote du bouton "utiliser"*/

	int lonRet = 10; /**taille du carre du bouton retour*/
	int dlonRet = 2; /**ecart entre le bouton retour et le bord*/
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0) {
    
    	  /** regarde le bouton pour quitter la fenètre si appuyer met quit a 1 ce qui va arrêter la boucle de jeux */
    	  switch(event.type){
		  case SDL_QUIT:*quit = 1;break;
		  	
		  /** récuperation des coordonnées de la souris */
		  case SDL_MOUSEMOTION:
		  
		  	/** regarde si la souris est dans la case des persos */
			if (event.motion.x >= dlon1 && event.motion.x <= *H - dlon1){
	
				/**rectangle perso 1*/
				if(event.motion.y >= 2* *W +dlar1 && event.motion.y <= 2* *W + dlar1 + lar1){
					*MouseOver=0;
				}
				/**rectangle perso 2*/
				else if(event.motion.y >= 2* *W + 2*dlar1 + lar1 && event.motion.y <= 2* *W + 2*dlar1 + 2*lar1){
					*MouseOver=1;
				}
				/**rectangle perso 3*/
				else if(event.motion.y >= 2* *W + 3*dlar1 + 2*lar1 && event.motion.y <= 2* *W + 3*dlar1 + 3*lar1){
					*MouseOver=2;
				}
			}

			/** regarde si la souris est dans la case de attaque ou item*/
			if(*menu_combat >= 1){
				if (event.motion.x >=  *H + dlon1 && event.motion.x <= 2* *H - dlon1){
					/**rectangle attaque*/
					if(event.motion.y >= 2* *W + dlar2 && event.motion.y <= 2* *W + dlar2 + lar2){
			  			*MouseOver=3;
					}
					/**rectangle item*/
					else if(event.motion.y >= 2* *W + 2*dlar2 + lar2 && event.motion.y <= 2* *W + 2*dlar2 + 2*lar2 ){
						*MouseOver=4;
					}
				}

				/**test si la souris est sur le bouton retour*/
				else if((event.motion.x >= 2* *H - lonRet - dlonRet && event.motion.x <= 2* *H - dlonRet) && (event.motion.y >= 2* *W + dlonRet && event.motion.y <= 2* *W + dlonRet + lonRet)){
					*MouseOver=28;
				}
				/** regarde si la souris est dans la case des attaques*/
				if(*menu_combat == 2 || *menu_combat == 4){
					if(event.motion.x >= 2* *H + dlon3a && event.motion.x <= 3* *H - dlon3a){
						/**rectangle attaque 1*/
						if(event.motion.y >= 2* *W + dlar3a && event.motion.y <= 2* *W + dlar3a + lar3){
							*MouseOver=5;
						}
						/**rectangle attaque 2*/
						else if(event.motion.y >= 2* *W + 2*dlar3a + lar3 && event.motion.y <= 2* *W + 2*dlar3a + 2*lar3){
							*MouseOver=6;
						}
						/**rectangle attaque 3*/
						else if(event.motion.y >= 2* *W + 3*dlar3a + 2*lar3 && event.motion.y <= 2* *W + 3*dlar3a + 3*lar3){
							*MouseOver=7;
						}
						/**rectangle attaque 4*/
						else if(event.motion.y >= 2* *W + 4*dlar3a + 3*lar3 && event.motion.y <= 2* *W + 4*dlar3a + 4*lar3){
							*MouseOver=8;
						}
					}
					/**test si la souris est sur le bouton retour*/
					else if((event.motion.x >= 3* *H - lonRet - dlonRet && event.motion.x <= 3* *H - dlonRet) && (event.motion.y >= 2* *W + dlonRet && event.motion.y <= 2* *W + dlonRet + lonRet)){
						*MouseOver=29;
					}
					/** regarde si la souris est dans la case de description d'attaque*/
					if(*menu_combat == 4){
						if(event.motion.x >= 3* *H + dlon4 && event.motion.x <= 3* *H + dlon4 + lon5){
							/**rectangle nom de l'attaque*/
							if(event.motion.y >= 2* *W + dlar4 && event.motion.y <= 2* *W + dlar4 + lar5){
								*MouseOver=19;
							}
							/**rectangle description*/
							else if(event.motion.y >= 2* *W + 2*dlar4 + lar5 && event.motion.y <= 2* *W + 2*dlar4 + lar5 + lar8){
								*MouseOver=20;
							}
						}
						else if(event.motion.x >= 3* *H + 2*dlon4 + lon5 && event.motion.x <= 3* *H + 2*dlon4 + lon5 + lon6){
							/**rectangle puissance*/
							if(event.motion.y >= 2* *W + dlar4 && event.motion.y <= 2* *W + dlar4 + lar6){
								*MouseOver=21;
							}
							/**rectangle precision*/
							else if(event.motion.y >= 2* *W + dlar4 + dlar5 + lar6 && event.motion.y <= 2* *W + dlar4 + dlar5 + 2*lar6){
								*MouseOver=22;
							}
							/**rectangle description*/
							else if(event.motion.y >= 2* *W + 2*dlar4 + dlar5 + 2*lar6 && event.motion.y <= 2* *W + 2*dlar4 + dlar5 + 2*lar6 + lar8){
								*MouseOver=20;
								
							}
						}
						else if(event.motion.x >= 3* *H + 3*dlon4 + lon5 + lon6 && event.motion.x <= 3* *H + 3*dlon4 + lon5 + lon6 +lon7){
							/**rectangle du logo*/
							if(event.motion.y >= 2* *W + dlar6 && event.motion.y <= 2* *W + dlar6 + lar7){
								*MouseOver=23;
							}
							/**rectangle description*/
							else if(event.motion.y >= 2* *W + 2*dlar6 + lar7 && event.motion.y <= 2* *W + 2*dlar6 + lar7 +lar8){
								*MouseOver=20;
								
							}
						}
						/**test si la souris est sur le bouton retour*/
						else if((event.motion.x >= 4* *H - lonRet - dlonRet && event.motion.x <= 4* *H - dlonRet) && (event.motion.y >= 2* *W + dlonRet && event.motion.y <= 2* *W + dlonRet + lonRet)){
							*MouseOver=30;
						}
					}
					
				}
				/** regarde si la souris est dans la case des objets*/
				if(*menu_combat == 3 ||*menu_combat == 5){
					if(event.motion.x >= 2* *H + dlon3b && event.motion.x <= 2* *H + lon4){
						/**rectangle objet 1*/
						if(event.motion.y >= 2* *W + dlar3b && event.motion.y <= 2* *W + dlar3b + lar4){
							*MouseOver=9;
						}
						/**rectangle objet 2*/
						else if(event.motion.y >= 2* *W + 2*dlar3b + dlar4 && event.motion.y <= 2* *W + 2*dlar3b + 2*lar4){
							*MouseOver=10;
						}
						/**rectangle objet 3*/
						else if(event.motion.y >= 2* *W + 3*dlar3b + 2*dlar4 && event.motion.y <= 2* *W + 3*dlar3b + 3*lar4){
							*MouseOver=11;
						}
						/**rectangle objet 4*/
						else if(event.motion.y >= 2* *W + 4*dlar3b + 3*dlar4 && event.motion.y <= 2* *W + 4*dlar3b + 4*lar4){
							*MouseOver=12;
						}
						/**rectangle objet 5*/
						else if(event.motion.y >= 2* *W + 5*dlar3b + 4*dlar4 && event.motion.y <= 2* *W + 5*dlar3b + 5*lar4){
							*MouseOver=13;
						}

					}
					else if(event.motion.x >= 2* *H + 2*dlon3b + lon4 && event.motion.x <= 3* *H - dlon3b){
						/**rectangle objet 6*/
						if(event.motion.y >= 2* *W + dlar3b && event.motion.y <= 2* *W + dlar3b + lar4){
							*MouseOver=14;
						}
						/**rectangle objet 7*/
						else if(event.motion.y >= 2* *W + 2*dlar3b + dlar4 && event.motion.y <= 2* *W + 2*dlar3b + 2*lar4){
							*MouseOver=15;
						}
						/**rectangle objet 8*/
						else if(event.motion.y >= 2* *W + 3*dlar3b + 2*dlar4 && event.motion.y <= 2* *W + 3*dlar3b + 3*lar4){
							*MouseOver=16;
						}
						/**rectangle objet 9*/
						else if(event.motion.y >= 2* *W + 4*dlar3b + 3*dlar4 && event.motion.y <= 2* *W + 4*dlar3b + 4*lar4){
							*MouseOver=17;
						}
						/**rectangle objet 10*/
						else if(event.motion.y >= 2* *W + 5*dlar3b + 4*dlar4 && event.motion.y <= 2* *W + 5*dlar3b + 5*lar4){
							*MouseOver=18;
						}
					}
					/**test si la souris est sur le bouton retour*/
					else if((event.motion.x >= 3* *H - lonRet - dlonRet && event.motion.x <= 3* *H - dlonRet) && (event.motion.y >= 2* *W + dlonRet && event.motion.y <= 2* *W + dlonRet + lonRet)){
						*MouseOver=29;
					}
					/** regarde si la souris est dans la case de description d'objet*/
					if(*menu_combat == 5){
						if(event.motion.y >= 2* *W + dlar7 && event.motion.y <= 2* *W + dlar7 + lar9){
							/**rectangle nom de l'objet*/
							if(event.motion.x >= 3* *H + dlon9 && event.motion.x <= 3* *H + lon9 + dlon9){
								*MouseOver=24;
							}
						}
						else if(event.motion.y >= 2* *W + 2*dlar7 + lar9 && event.motion.y <= 2* *W + 2*dlar7 + lar9 + lar10){
							/**rectangle pixel art de l'objet*/
							if(event.motion.x >= 3* *H + dlon10 && event.motion.x <= 3* *H + lon10 + dlon10){
								*MouseOver=25;
							}
						}
						else if(event.motion.y >= 2* *W + 3*dlar7 + lar9 + lar10 && event.motion.y <= 2* *W + 3*dlar7 + lar9 + lar10 + lar11){
							/**rectangle description*/
							if(event.motion.x >= 3* *H + dlon11 && event.motion.x <= 3* *H + lon11 + dlon11){
								*MouseOver=26;
							}
						}
						else if(event.motion.y >= 2* *W + 4*dlar7 + lar9 + lar10 + lar11 && 2* *W + 4*dlar7 + lar9 + lar10 + lar11 + lar12){
							/**rectangle utiliser*/
							if(event.motion.x >= 3* *H + dlon12 && event.motion.x <= 3* *H + lon12 + dlon12){
								*MouseOver=27;
							}
						}
						/**test si la souris est sur le bouton retour*/
						else if((event.motion.x >= 4* *H - lonRet - dlonRet && event.motion.x <= 4* *H - dlonRet) && (event.motion.y >= 2* *W + dlonRet && event.motion.y <= 2* *W + dlonRet + lonRet)){
							*MouseOver=30;
						}
					}
					
				}
			}


			if(*menu_combat == 6){
				/** lancer l'attaque*/
				*menu_combat = 6;
			}
			if(*menu_combat == 7){
				/**utiliser l'item*/
				*menu_combat = 7;
			}
			else{
				*menu_combat = *menu_combat;
			}break;

			  
		   /** récuperation si le bouton de la sourit est lacher */
		   case SDL_MOUSEBUTTONUP:
		   
   			   /** regarde si le bouton est relacher sur un des boutons */
			   if(*MouseOver > -1 && *MouseOver <= 30){
				*MouseClick = *MouseOver;
				
				if(*MouseClick >=0 && *MouseClick <=2){
					*perso = *MouseClick;
					*menu_combat = 1;
				}
				else if (*MouseClick == 28){
					*menu_combat = 0;
				}
				else if(*MouseClick >= 3 && *MouseClick <= 4){
					*menu_combat = *MouseClick - 1;
				}
				else if(*MouseClick >= 5 && *MouseClick <= 8){
					*menu_combat = 4;
				}
				else if(*MouseClick >= 9 && *MouseClick <= 18){
					*menu_combat = 5;
				}
				else if(*MouseClick == 19){
					*menu_combat = 6;
				}
				else if(*MouseClick == 27){
					*menu_combat = 7;
				}
				else if(*MouseClick == 29){
					*menu_combat = 1;
				}
				else if(*MouseClick == 30){
					if(*menu_combat == 5){
						*menu_combat = 3;
					}
					else if(*menu_combat == 4){
						*menu_combat = 2;
					}
				}
			   }
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_ESCAPE){
					*scene = OP;
				}
          }
		  

    }
}

/**
* fonction ReactEventsInvSac qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur le menu d'inventaire sur le sac 
*/
void ReactEventsFight(int *p, int perso, int MouseClick,int MouseOver,int menu_combat ,SDL_Renderer* pRenderer,SDL_Texture* fond_combat,int w,int h,inventaire_t* inv,team_t * team, mob_t ** mobs,int H, int W){

     /** declaration de i servant au boucle for et textwidth, textheight pour les dimensions des textes */
     int i,j, textwidth, textheight, nb_pers, nb_mobs=0;
	 SDL_RenderClear(pRenderer);

	int lon1 = 0.7 * H; /**longueur du rectangle indiquant le nom des persos*/
	int lar1 = 0.25 * W; /**largeur du rectangle indiquant le nom des persos*/

	int lon2 = lon1 ; /**longueur des rectangles "attaque" et "item"*/
	int lar2 = 0.4 * lon2; /**largeur des rectangles "attaque" et "item"*/

	int lon3 = lon1; /**longueur des rectangles de chaque attaque*/
	int lar3 = 0.2 * lon3; /**largeur des rectangles de chaque attaque*/

	int lon4 = lon1/2; /**longueur des rectangles de chaque objet */
	int lar4 = 0.3 * lon4; /**largeur des rectangles de chaque objet */

	int lon5 = lon1/2; /**longueur du rectangle du nom de l'attaque*/
	int lar5 = 0.5 * lon5; /**largeur du rectangle du nom de l'attaque*/

	int lon6 = 0.3 * lon1; /**longueur des rectangles "puissance" et "precision"*/
	int lar6 = 0.4 * lon6; /**largeur des rectangles "puissance" et "precision"*/

	int lon7 = 0.3 * lon1; /**taille du carre dans lequel il y aura le logo representant le type de l'attaque*/
	int lar7 = lon7;

	int lon8 = 0.8 * H; /**longueur du rectangle de description de l'attaque*/
	int lar8 = 0.5 * lon8; /**largeur du rectangle de description de l'attaque*/

	int lon9 = 0.5 * H; /**longueur du rectangle du nom de l'objet*/
	int lar9 = 0.15 * lon9; /**largeur du rectangle du nom de l'objet*/

	int lon10 = 0.5 * W; /**taille du carre du pixel art de l'objet*/
	int lar10 = lon10;

	int lon11 = 0.8 * H; /**longueur du rectangle de description de l'objet*/
	int lar11 = 0.1 * lon11; /**largeur du rectangle de description de l'objet*/

	int lon12 = 0.25 * H; /**longueur du rectangle du bouton "utiliser"*/
	int lar12 = 0.2 * lon12; /**largeur du rectangle du bouton "utiliser"*/

	int dlar1 = (W - 3*lar1)/4; /**ecart vertical entre les boutons indiquant le nom des persos*/
	int dlon1 = (H - lon1)/2; /**ecart horizontal entre les boutons indiquant le nom des persos*/

	int dlar2 = (W - 2*lar2)/3; /**ecart vertical entre les boutons "attaque" et "item" */
	int dlon2 = dlon1; /**ecart horizontal entre les boutons "attaque" et "item" */

	int dlar3a = (W - 4*lar3)/5; /**ecart vertical entre les rectangles de chaque attaque*/
	int dlon3a = dlon1; /**ecart horizontal entre les rectangles de chaque attaque*/

	int dlar3b = (W - 5*lar4)/6; /**ecart vertical entre les rectangles de chaque objet*/
	int dlon3b = (H - 2*lon4)/3; /**ecart horizontal entre les rectangles de chaque objet*/

	int dlar4 = (W - lar5 - lar8)/3; /**ecart vertical entre les rectangles du nom de l'attaque et de description de l'attaque*/
	int dlon4 = (H - lon5 - lon6 - lon7)/4; /**ecart horizontal entre les rectangles du nom de l'attaque, de la puissance et du logo*/

	int dlar6 = (W - lon7 - lar8 - dlar4)/2; /**ecart vertical entre les rectangles du logo et de description*/

	int dlar5 = W - 3*dlar6  - lar8 - 2*lar6; /**ecart vertical entre les rectangles "puissance" et "precision"*/

	int dlar7 = (W - lar12 - lar11 - lar10 - lar9)/5; /**ecart vertical entre les rectangles du nom, du pixel art, de la description et du bouton"utiliser"de l'objet*/

	int dlon9 = (H - lon9)/2; /**ecart horizontal de chaque cote du rectangle nom de l'objet*/

	int dlon10 = (H - lon10)/2; /**ecart horizontal de chaque cote du pixel art de l'objet*/

	int dlon11 = (H - lon11)/2; /**ecart horizontal de chaque cote du rectangle description de l'objet*/

	int dlon12 = (H - lon12)/2; /**ecart horizontal de chaque cote du bouton "utiliser"*/

	int lonRet = 10; /**taille du carre du bouton retour*/
	int dlonRet = 2; /**ecart entre le bouton retour et le bord*/

	 *p = (*p)%6;
	 /** calcul du nombre de persos dans notre team ainsi que du nombre de mobs (adversaires)*/
	 if(mobs != NULL)
	 	for (nb_mobs=0;mobs[i];i++);
     

     /** chaine de caractère utiliser pour l'affichage des persos avec leur nb de pv et pm  */
     char pv[4];
     char pvm[4];
     char pm[4];
     char pmm[4];
     char personnage[40];

	 /** chaine de caracteres pour la conversion d'entiers en caractères*/

	 char chaine[5];

	 /** declaration et calcul des variables des coordonnees des carres des persos et des mobs*/

	 int x = 200; /** taille du carre du premier perso de la team*/
	 int y = 150; /** taille du carre du 2e perso de la team*/
	 int z = 100; /** taille du carre du 3e perso de la team*/
	 int delta = 21; /** ecart vertical entre les persos de la team*/
	 int a = 180; /** taille du carre du premier et deuxieme mob*/
	 int b = 130; /** taille du carre du troisieme et quatrieme mob*/
	 int c = 90; /** taille du carre du cinquieme et sixieme mob*/
	 int d = 64; /** taille du carre du septieme mob*/
	 int mu = 14; /** ecart vertical entre les mobs*/

	 int dp1 = h/4 - x; /** ecart horizontal a gauche du premier perso et a droite du troisieme perso*/
	 int dp2 = h/4; /** ecart horizontal a droite du premier perso*/
	 int dp3 = (h/2 - y)/2; /** ecart horizontal a gauche et a droite du deuxieme perso*/
	 int dp4 = h/2 - z - dp1; /** ecart horizontal a gauche du troisieme perso*/

	 int dm1 = (h/2 - 2*a)/3; /** ecart horizontal entre le premier et le deuxieme mob*/
	 int dm2 = (h/2 - 2*b)/3; /** ecart horizontal entre le troisieme et le quatrieme mob*/
	 int dm3 = dm2 + b/2; /** ecart horizontal a gauche du sixieme mob*/
	 int dm4 = (h/2 - 2*c - dm3); /** ecart horizontal entre le cinquieme et le sixieme mob*/
	 int dm5 = 2*dm3; /** ecart horizontal a gauche du septieme mob*/
	 int dm6 = h/2 - dm5 - d; /** ecart horizontal a droite du septieme mob*/

	 /**mise en place des coordonnees dans les tableaux correspondants*/
	int lon[15] = {lon1,lon2,lon3,lon4,lon5,lon6,lon7,lon8,lon9,lon10,lon11,lon12,lonRet}; 

	int lar[15] = {lar1,lar2,lar3,lar4,lar5,lar6,lar7,lar8,lar9,lar10,lar11,lar12,lonRet};

	int dlon[10] = {dlon1,dlon2,dlon3a,dlon3b,dlon4,dlon9,dlon10,dlon11,dlon12,dlonRet};

	int dlar[10] = {dlar1,dlar2,dlar3a,dlar3b,dlar4,dlar5,dlar6,dlar7,dlonRet};

	 /** declaration et initialisation des rectangles et des textures de chaque perso et de chaque mob*/
	 SDL_Rect rect_persos[team->nbPerso];
	 SDL_Rect rect_mobs[nb_mobs];

	 SDL_Texture* text_persos[team->nbPerso];
	 SDL_Texture* text_mobs[nb_mobs];

	 SDL_Rect IdleAnim[6] = {{0,0,32,32},{32,0,32,32},{32*2,0,32,32},{32*3,0,32,32},{32*4,0,32,32},{32*5,0,32,32}};

	 switch(team->nbPerso){ /** chaque 'case' represente le n-ieme perso. S'il y a 3 persos, je cree le rectangle des 3 persos, s'il y en a 2 j'en crée que 2 etc*/
	 	 				    /** de meme pour les textures, je charge leur IdleAnim (lorsque le perso bouge sur lui-meme)*/
		case 3: 
			rect_persos[2].x = dp4;
			rect_persos[2].y = delta;
			rect_persos[2].w = z;
			rect_persos[2].h = z;
			text_persos[2] = team->team[2]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_persos[2],&IdleAnim[(*p)],rect_persos + 2);
		case 2: 
			rect_persos[1].x = dp3;
			rect_persos[1].y = 2*delta + z;
			rect_persos[1].w = y;
			rect_persos[1].h = y;
			text_persos[1] = team->team[1]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_persos[1],&IdleAnim[(*p)],rect_persos + 1);
		case 1: 
			rect_persos[0].x = dp1;
			rect_persos[0].y = 3*delta + z + y;
			rect_persos[0].w = x;
			rect_persos[0].h = x;
			text_persos[0] = team->team[0]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_persos[0],&IdleAnim[(*p)],rect_persos + 0);
	 }

	 switch(nb_mobs){ /** chaque 'case' represente le n-ieme mob. S'il y a 7 mobs, je cree le rectangle des 7 mobs, s'il y en a 6 j'en crée que 6 etc*/
	 				  /** de meme pour les textures, je charge leur IdleAnim (lorsque le mob bouge sur lui-meme)*/
		case 7: 
			rect_mobs[6].x = h/2 + dm5;
			rect_mobs[6].y = mu;
			rect_mobs[6].w = d;
			rect_mobs[6].h = d;
			text_mobs[6] = mobs[6]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[6],&IdleAnim[(*p)],rect_mobs + 6);
		case 6: 
			rect_mobs[5].x = h/2 + dm3;
			rect_mobs[5].y = 2*mu + d;
			rect_mobs[5].w = c;
			rect_mobs[5].h = c;
			text_mobs[5] = mobs[5]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[5],&IdleAnim[(*p)],rect_mobs + 5);
		case 5: 
			rect_mobs[4].x = h/2 + dm3 + c + dm4;
			rect_mobs[4].y = 2*mu + d;
			rect_mobs[4].w = c;
			rect_mobs[4].h = c;
			text_mobs[4] = mobs[4]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[4],&IdleAnim[(*p)],rect_mobs + 4);
		case 4: 
			rect_mobs[3].x = h/2 + dm2;
			rect_mobs[3].y = 3*mu + d + c;
			rect_mobs[3].w = b;
			rect_mobs[3].h = b;
			text_mobs[3] = mobs[3]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[3],&IdleAnim[(*p)],rect_mobs + 3);
		case 3: 
			rect_mobs[2].x = h/2 + 2*dm2 + b;
			rect_mobs[2].y = 3*mu + d + c;
			rect_mobs[2].w = b;
			rect_mobs[2].h = b;
			text_mobs[2] = mobs[2]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[2],&IdleAnim[(*p)],rect_mobs + 2);
		case 2: 
			rect_mobs[1].x = h/2 + dm1;
			rect_mobs[1].y = 4*mu + d + c + b;
			rect_mobs[1].w = a;
			rect_mobs[1].h = a;
			text_mobs[1] = mobs[1]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[1],&IdleAnim[(*p)],rect_mobs + 1);
		case 1: 
			rect_mobs[1].x = h/2 + 2*dm1 + a;
			rect_mobs[1].y = 4*mu + d + c + b;
			rect_mobs[1].w = a;
			rect_mobs[1].h = a;
			text_mobs[0] = mobs[0]->IdleAnim;
			SDL_RenderCopy(pRenderer,text_mobs[0],&IdleAnim[(*p)],rect_mobs + 0);
	 }

	 *p += 1; /** on se decale de une image dans le sprite de l'Idle Animation de tous les persos et mobs*/
     
	 /** chargement des textures des boutons de fond et leur version hover (lorsque la souris est dessus)*/
	 SDL_Texture* fond = loadTexture("../Ressource/Sprites/Boutons/bouton_combat_vide.png",pRenderer);

	 SDL_Texture* fond_hover = loadTexture("../Ressource/Sprites/Boutons/bouton_combat_vide_hover.png",pRenderer);

	 /** chargement des textures du bouton retour et de sa version hover (lorsque la souris est dessus)*/
	 SDL_Texture* bouton_retour = loadTexture("../Ressource/Sprites/Boutons/bouton_retour.png",pRenderer);

	 SDL_Texture* bouton_retour_hover = loadTexture("../Ressource/Sprites/Boutons/bouton_retour_hover.png",pRenderer);

     SDL_Texture* fond_bleu = loadTexture("../Ressource/pnj.png",pRenderer);

     /** declaration des rect correspondant au coordonnées et dimensions d'affichage de tout l'interface de combat */

	 /**grand rectangle qui va contenir tous les rectangles ci-dessous*/
	 SDL_Rect rect_bleu = {0,2*W,w,W};

	 /**rectangles des persos*/
	 SDL_Rect pers1 = {dlon[0],2*W + dlar[0],lon[0],lar[0]};
	 SDL_Rect pers2 = {dlon[0],2*W + 2*dlar[0] + lar[0],lon[0],lar[0]};
	 SDL_Rect pers3 = {dlon[0],2*W + 3*dlar[0] + 2*lar[0],lon[0],lar[0]};

	 /**rectangles attaque et item*/
	 SDL_Rect att = {H + dlon[1],2*W + dlar[1],lon[1],lar[1]};
	 SDL_Rect item = {H + dlon[1],2*W + 2*dlar[1] + lar[1],lon[1],lar[1]};

	 /**rectangles de chaque objet*/
	 SDL_Rect item1 = {2*H + dlon[3],2*W + dlar[3],lon[3],lar[3]};
	 SDL_Rect item2 = {2*H + dlon[3],2*W + 2*dlar[3] + lar[3],lon[3],lar[3]};
	 SDL_Rect item3 = {2*H + dlon[3],2*W + 3*dlar[3] + 2*lar[3],lon[3],lar[3]};
	 SDL_Rect item4 = {2*H + dlon[3],2*W + 4*dlar[3] + 3*lar[3],lon[3],lar[3]};
	 SDL_Rect item5 = {2*H + dlon[3],2*W + 5*dlar[3] + 4*lar[3],lon[3],lar[3]};
	 SDL_Rect item6 = {2*H + 2*dlon[3] + lon[3],2*W + dlar[3],lon[3],lar[3]};
	 SDL_Rect item7 = {2*H + 2*dlon[3] + lon[3],2*W + 2*dlar[3] + lar[3],lon[3],lar[3]};
	 SDL_Rect item8 = {2*H + 2*dlon[3] + lon[3],2*W + 3*dlar[3] + 2*lar[3],lon[3],lar[3]};
	 SDL_Rect item9 = {2*H + 2*dlon[3] + lon[3],2*W + 4*dlar[3] + 3*lar[3],lon[3],lar[3]};
	 SDL_Rect item10 = {2*H + 2*dlon[3] + lon[3],2*W + 5*dlar[3] + 4*lar[3],lon[3],lar[3]};

	 /**rectangles de chaque attaque*/
	 SDL_Rect att1 = {2*H + dlon[2],2*W + dlar[2],lon[2],lar[2]};
	 SDL_Rect att2 = {2*H + dlon[2],2*W + 2*dlar[2] + lar[2],lon[2],lar[2]};
	 SDL_Rect att3 = {2*H + dlon[2],2*W + 3*dlar[2] + 2*lar[2],lon[2],lar[2]};
	 SDL_Rect att4 = {2*H + dlon[2],2*W + 4*dlar[2] + 3*lar[2],lon[2],lar[2]};

	 /**rectangles du detail de chaque attaque*/
	 SDL_Rect nom_att = {3*H + dlon[4],2*W + dlar[4],lon[4],lar[4]};
	 SDL_Rect puissance = {3*H + 2*dlon[4] + lon[4], 2*W + dlar[4], lon[5],lar[5]};
	 SDL_Rect precision = {3*H + 2*dlon[4] + lon[4], 2*W + dlar[4] + dlar[5] + lar[5], lon[5],lar[5]};
	 SDL_Rect logo = {3*H + 3*dlon[4] + lon[4] + lon[5], 2*W + dlar[6], lon[6],lar[6]};
	 SDL_Rect description_att = {3*H + dlon[4],2*W + 2*dlar[4] + lar[4], lon[7], lar[7]};

	 /**rectangles du detail de chaque objet*/
	 SDL_Rect nom_item = {3*H + dlon[5], 2*W + dlar[7], lon[8], lar[8]};
	 SDL_Rect pixelart_item = {3*H + dlon[6], 2*W + 2*dlar[7] + lar[8], lon[9], lar[9]};
	 SDL_Rect description_item = {3*H + dlon[7], 2*W + 3*dlar[7] + lar[8] + lar[9], lon[10], lar[10]};
	 SDL_Rect utiliser = {3*H + dlon[8], 2*W + 4*dlar[7] + lar[8] + lar[9] + lar[10], lon[11], lar[11]};

	 /**rectangles de retour*/
	 SDL_Rect retour1 = {2*H - dlon[9],2*W + dlar[8],lon[12],lar[12]};
	 SDL_Rect retour2 = {3*H - dlon[9],2*W + dlar[8],lon[12],lar[12]};
	 SDL_Rect retour3 = {4*H - dlon[9],2*W + dlar[8],lon[12],lar[12]};

	 /** affichage des fonds a l'ecran*/

	 SDL_RenderCopy(pRenderer,fond_combat,NULL,NULL);
	 SDL_RenderCopy(pRenderer,fond_bleu,NULL,&rect_bleu);
     
     /** declaration et initialisation des textures des noms et descriptions des objets ainsi que la couleur des texte */
	 
	 SDL_Color noir={0,0,0};


	 /** declaration et initialisation des textures des textes de chaque bouton*/

	 /** nom des persos*/
	 SDL_Texture* nomPerso[NB_TEAM_PERSOS];

	 for(i=0;i<NB_TEAM_PERSOS;i++){
		if(team->team[i] != NULL){
			nomPerso[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,team->team[i]->Nom,lar[8]*1.4,noir);
		}
		else{
			nomPerso[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,". . .",lar[8]*0.6,noir);
		}
	 }

	 /** texture erreur*/

	 SDL_Texture* erreur = loadTexture("../Ressource/Sprites/Logos/err.png",pRenderer);

	 /** textures attaque et item*/
	 SDL_Texture* attaque = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," Attaque ",lar[8]*0.6,noir);
	 SDL_Texture* items = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," Item ",lar[8]*0.6,noir);

	 /** textures de chaque attaque*/

	 /**matrices contenant les 4 attaques de chacun des persos de la team*/
	 SDL_Texture* attaques[NB_TEAM_PERSOS][NB_ATT];
	 SDL_Texture* descriptions_att[NB_TEAM_PERSOS][NB_ATT];
	 SDL_Texture* logos[NB_TEAM_PERSOS][NB_ATT];
	 SDL_Texture* puissances[NB_TEAM_PERSOS][NB_ATT];
	 SDL_Texture* precisions[NB_TEAM_PERSOS][NB_ATT];

	 for(i=0;i<NB_TEAM_PERSOS;i++){
		for(j=0;j<NB_ATT;j++){
			if(team->team[i] != NULL){
				if(team->team[i]->attaques != NULL){
					attaques[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,team->team[i]->attaques[j].nom,lar[8],noir);
					descriptions_att[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,team->team[i]->attaques[j].desc,lar[8],noir);
					if (team->team[i]->attaques[j].type_att != STA){
						sprintf(chaine,"%d",team->team[i]->attaques[j].qte_effet);
						puissances[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,chaine,lar[8],noir);
					}
					else{
						puissances[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," - ",lar[8],noir);
					}
					sprintf(chaine,"%d",team->team[i]->attaques[j].precision);
					strcat(chaine,"%");
					precisions[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,chaine,lar[8],noir);
					switch(team->team[i]->attaques[j].type_att){
						case PHY: logos[i][j] = loadTexture("../Ressource/Sprites/Logos/phy.png",pRenderer);break;
						case MAG: logos[i][j] = loadTexture("../Ressource/Sprites/Logos/mag.png",pRenderer);break;
						case STA: logos[i][j] = loadTexture("../Ressource/Sprites/Logos/sta.png",pRenderer);break;
					}
				}
				else{
					attaques[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," . . . ",lar[8],noir);
					descriptions_att[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," aucune attaque ",lar[8],noir);
					logos[i][j] = loadTexture("../Ressource/Sprites/Logos/err.png",pRenderer);
					puissances[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," - ",lar[8],noir);
					precisions[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," - ",lar[8],noir);
				}
			}
			else{
				attaques[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," . . . ",lar[8],noir);
				descriptions_att[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," aucune attaque ",lar[8],noir);
				logos[i][j] = loadTexture("../Ressource/Sprites/Logos/err.png",pRenderer);
				puissances[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," - ",lar[8],noir);
				precisions[i][j] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," - ",lar[8],noir);
			}
		}
	 }

	 /** declaration et initialisation des textures des objets*/
	 SDL_Texture* noms_obj[NB_INV_OBJETS];
	 SDL_Texture* descriptions_obj[NB_INV_OBJETS];
	 SDL_Texture* pixelarts[NB_INV_OBJETS];

	 for(i=0;i<NB_INV_OBJETS;i++){
		if(inv->sac[i] != NULL){
			noms_obj[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->sac[i]->nom,lar[8],noir);
			descriptions_obj[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer,inv->sac[i]->desc,lar[8],noir);
			pixelarts[i] = inv->sac[i]->sprite;
		}
		else{
			noms_obj[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," . . . ",lar[8],noir);
			descriptions_obj[i] = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," aucun objet ",lar[8],noir);
			pixelarts[i] = loadTexture("../Ressource/Sprites/Logos/err.png",pRenderer);
		}
	 }

	 SDL_Texture* bouton_utiliser = loadTextureFont("../Ressource/font/BlockKie.ttf",pRenderer," utiliser ",lar[8],noir);


	 /** affichage de tous les rectangles selon menu_combat*/
	 if(menu_combat == 5 || (MouseClick >= 9 && MouseClick <= 18)){
		menu_combat = 5;
		if(MouseOver == 30){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour3);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour3);
		}
		if(MouseOver == 27){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&utiliser);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&utiliser);
		}
		if(MouseOver == 26){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&description_item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&description_item);
		}
		if(MouseOver == 25){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pixelart_item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pixelart_item);
		}
		if(MouseOver == 24){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&nom_item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&nom_item);
		}
		if(MouseOver == 29){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour2);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour2);
		}
		if(MouseOver == 18){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item10);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item10);
		}
		if(MouseOver == 17){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item9);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item9);
		}
		if(MouseOver == 16){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item8);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item8);
		}
		if(MouseOver == 15){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item7);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item7);
		}
		if(MouseOver == 14){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item6);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item6);
		}
		if(MouseOver == 13){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item5);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item5);
		}
		if(MouseOver == 12){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item4);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item4);
		}
		if(MouseOver == 11){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item3);
		}
		if(MouseOver == 10){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item2);
		}
		if(MouseOver == 9){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item1);
		}
		if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}
		SDL_RenderCopy(pRenderer,bouton_utiliser,NULL,&utiliser);

		if (MouseClick >= 9 && MouseClick <= 18){
			printf("mouseclick %d\n",MouseClick);
			if (inv->sac[MouseClick-9] == NULL){
				printf("NULL\n");
			}
			SDL_RenderCopy(pRenderer,descriptions_obj[MouseClick-9],NULL,&description_item);
			SDL_RenderCopy(pRenderer,pixelarts[MouseClick-9],NULL,&pixelart_item);
			SDL_RenderCopy(pRenderer,noms_obj[MouseClick-9],NULL,&nom_item);
		}

		SDL_RenderCopy(pRenderer,noms_obj[0],NULL,&item1);
		SDL_RenderCopy(pRenderer,noms_obj[1],NULL,&item2);
		SDL_RenderCopy(pRenderer,noms_obj[2],NULL,&item3);
		SDL_RenderCopy(pRenderer,noms_obj[3],NULL,&item4);
		SDL_RenderCopy(pRenderer,noms_obj[4],NULL,&item5);
		SDL_RenderCopy(pRenderer,noms_obj[5],NULL,&item6);
		SDL_RenderCopy(pRenderer,noms_obj[6],NULL,&item7);
		SDL_RenderCopy(pRenderer,noms_obj[7],NULL,&item8);
		SDL_RenderCopy(pRenderer,noms_obj[8],NULL,&item9);
		SDL_RenderCopy(pRenderer,noms_obj[9],NULL,&item10);

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);

	 }
	 else if(menu_combat == 3 || MouseClick == 4){
		menu_combat = 3;
		if(MouseOver == 29){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour2);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour2);
		}
		if(MouseOver == 18){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item10);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item10);
		}
		if(MouseOver == 17){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item9);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item9);
		}
		if(MouseOver == 16){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item8);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item8);
		}
		if(MouseOver == 15){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item7);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item7);
		}
		if(MouseOver == 14){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item6);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item6);
		}
		if(MouseOver == 13){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item5);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item5);
		}
		if(MouseOver == 12){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item4);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item4);
		}
		if(MouseOver == 11){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item3);
		}
		if(MouseOver == 10){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item2);
		}
		if(MouseOver == 9){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item1);
		}
		if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,noms_obj[0],NULL,&item1);
		SDL_RenderCopy(pRenderer,noms_obj[1],NULL,&item2);
		SDL_RenderCopy(pRenderer,noms_obj[2],NULL,&item3);
		SDL_RenderCopy(pRenderer,noms_obj[3],NULL,&item4);
		SDL_RenderCopy(pRenderer,noms_obj[4],NULL,&item5);
		SDL_RenderCopy(pRenderer,noms_obj[5],NULL,&item6);
		SDL_RenderCopy(pRenderer,noms_obj[6],NULL,&item7);
		SDL_RenderCopy(pRenderer,noms_obj[7],NULL,&item8);
		SDL_RenderCopy(pRenderer,noms_obj[8],NULL,&item9);
		SDL_RenderCopy(pRenderer,noms_obj[9],NULL,&item10);

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);
	 }
	 else if(menu_combat == 4 || (MouseClick >= 5 && MouseClick <= 8) ){
		menu_combat = 4;
		if(MouseOver == 30){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour3);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour3);
		}
		if(MouseOver == 23){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&logo);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&logo);
		}
		if(MouseOver == 22){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&precision);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&precision);
		}
		if(MouseOver == 21){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&puissance);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&puissance);
		}
		if(MouseOver == 20){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&description_att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&description_att);
		}
		if(MouseOver == 19){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&nom_att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&nom_att);
		}
		if(MouseOver == 29){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour2);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour2);
		}
		if(MouseOver == 8){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att4);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att4);
		}
		if(MouseOver == 7){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att3);
		}
		if(MouseOver == 6){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att2);
		}
		if(MouseOver == 5){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att1);
		}
		if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,attaques[perso][MouseClick-5],NULL,&nom_att);
		SDL_RenderCopy(pRenderer,precisions[perso][MouseClick-5],NULL,&precision);
		SDL_RenderCopy(pRenderer,puissances[perso][MouseClick-5],NULL,&puissance);
		SDL_RenderCopy(pRenderer,descriptions_att[perso][MouseClick-5],NULL,&description_att);
		SDL_RenderCopy(pRenderer,logos[perso][MouseClick-5],NULL,&logo);

		SDL_RenderCopy(pRenderer,attaques[perso][0],NULL,&att1);
		SDL_RenderCopy(pRenderer,attaques[perso][1],NULL,&att2);
		SDL_RenderCopy(pRenderer,attaques[perso][2],NULL,&att3);
		SDL_RenderCopy(pRenderer,attaques[perso][3],NULL,&att4);

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);

	 }
	 else if(menu_combat == 2 || MouseClick == 3 ){
		menu_combat = 2;
		if(MouseOver == 29){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour2);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour2);
		}
		if(MouseOver == 8){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att4);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att4);
		}
		if(MouseOver == 7){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att3);
		}
		if(MouseOver == 6){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att2);
		}
		if(MouseOver == 5){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att1);
		}
		if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,attaques[perso][0],NULL,&att1);
		SDL_RenderCopy(pRenderer,attaques[perso][1],NULL,&att2);
		SDL_RenderCopy(pRenderer,attaques[perso][2],NULL,&att3);
		SDL_RenderCopy(pRenderer,attaques[perso][3],NULL,&att4);

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);
	 }
	 else if(menu_combat == 1 || (MouseClick >= 0 && MouseClick <= 2) || MouseClick == 29){
		menu_combat = 1;
		if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}if(MouseOver == 28){
			SDL_RenderCopy(pRenderer,bouton_retour_hover,NULL,&retour1);
		}
		else{
			SDL_RenderCopy(pRenderer,bouton_retour,NULL,&retour1);
		}
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);
		if(MouseOver == 4){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&item);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&item);
		}
		if(MouseOver == 3){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&att);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&att);
		}
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,items,NULL,&item);
		SDL_RenderCopy(pRenderer,attaque,NULL,&att);

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);
	 }
	 else if(menu_combat == 0 || MouseClick == 28){
		if(MouseOver == 2){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers3);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers3);
		}
		if(MouseOver == 1){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers2);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers2);
		}
		if(MouseOver == 0){
			SDL_RenderCopy(pRenderer,fond_hover,NULL,&pers1);
		}
		else{
			SDL_RenderCopy(pRenderer,fond,NULL,&pers1);
		}

		SDL_RenderCopy(pRenderer,nomPerso[0],NULL,&pers1);
		SDL_RenderCopy(pRenderer,nomPerso[1],NULL,&pers2);
		SDL_RenderCopy(pRenderer,nomPerso[2],NULL,&pers3);
	 }
     
	 /** destruction des textures*/

	 SDL_DestroyTexture(bouton_utiliser);
	 SDL_DestroyTexture(attaque);
	 SDL_DestroyTexture(items);
	 SDL_DestroyTexture(fond);
	 SDL_DestroyTexture(fond_hover);
	 SDL_DestroyTexture(bouton_retour);
	 SDL_DestroyTexture(bouton_retour_hover);
	SDL_DestroyTexture(erreur);

	 for(i=0;i<10;i++){
		SDL_DestroyTexture(noms_obj[i]);
		SDL_DestroyTexture(descriptions_obj[i]);
	 }

	 for(i=0;i<team->nbPerso;i++){
		SDL_DestroyTexture(text_persos[i]);
	 }

	 for(i=0;i<nb_mobs;i++){
		SDL_DestroyTexture(text_mobs[i]);
	 }

	 for(i=0;i<3;i++){
		SDL_DestroyTexture(nomPerso[i]);
		for(j=0;j<4;j++){
			SDL_DestroyTexture(attaques[i][j]);
			SDL_DestroyTexture(descriptions_att[i][j]);
			SDL_DestroyTexture(logos[i][j]);
			SDL_DestroyTexture(puissances[i][j]);
			SDL_DestroyTexture(precisions[i][j]);
		}
	 }
     /** delais d'affichage */
     SDL_Delay(35);
}
