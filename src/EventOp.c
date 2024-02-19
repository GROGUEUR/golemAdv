#include "../lib/EventOp.h"

/**
* fonction DetectEventsOp qui s'occupera de gérer la détection
* des évènement quand nous somme sur l'openWorld 
*/
void DetectEventsOp(int* KeyIsPressed, int* quit){
    /** création de la variable event qui récupère les évènements */
    SDL_Event event;
    /** boucle d'attente d'évènements */
    while (SDL_PollEvent(&event) != 0) {
    	  /** regarde le bouton pour quitter la fenètre si appuyer met quit a 1 ce qui va arrêter la boucle de jeux */
          if (event.type == SDL_QUIT) {
             *quit = 1;
          }
          /** récuperation des touche enfoncer */
          if (event.type == SDL_KEYDOWN) {
          /** regarde qu'elle touche est enfoncer */
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
                 
          }                 
          /** récuperation des touche relacher changement de KeyIsPressed */
          else if (event.type == SDL_KEYUP) {
               /** regarde qu'elle touche a été relacher 
               * et change la variable KeyIsPressed en fonction de la touche 
               */
               switch(event.key.keysym.sym){
               	case SDLK_d:*KeyIsPressed = 0;break;
               	case SDLK_q:*KeyIsPressed = -1;break;
               	case SDLK_z:*KeyIsPressed = -2;break;
               	case SDLK_s:*KeyIsPressed = -3;break;
               }
         }
                                
    }
}

/**
* fonction ReactEventsOp qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur l'openWorld
*/
void ReactEventsOp(int KeyIsPressed,SDL_Renderer* pRenderer,SDL_Texture* pTexture,SDL_Texture* pSol,SDL_Texture* pBlock,SDL_Rect* marcheHori,SDL_Rect* dest,int* i,SDL_Rect* block,SDL_Rect* map){
     SDL_RenderClear(pRenderer);/** nettoyage de l'écran */
     SDL_RenderCopy(pRenderer,pSol,NULL,map); /** placemet de la map */
     SDL_RenderCopy(pRenderer,pBlock,NULL,block);/** placement d'un block de collision */
     switch(KeyIsPressed){
        /** déplacement vers la gauche */
        case 1:
        	dest->x-=5;
		SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+((++*i)%6),dest, 0, NULL, SDL_FLIP_HORIZONTAL);break;
	/** déplacement vers la droite */
        case 2:
        	dest->x+=5;
        	SDL_RenderCopy(pRenderer,pTexture,marcheHori+((++*i)%6),dest);break;
        /** déplacement vers le haut */
        case 3:
        	dest->y-=5;
        	SDL_RenderCopy(pRenderer,pTexture,marcheHori+((++*i)%6),dest);break;
        /** déplacement vers le bas */
        case 4:
        	dest->y+=5;
        	SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+((++*i)%6),dest, 0, NULL, SDL_FLIP_HORIZONTAL);break;
        	
        case 0:SDL_RenderCopy(pRenderer,pTexture,marcheHori+0,dest);break;
        
        case -1:SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+0,dest, 0, NULL, SDL_FLIP_HORIZONTAL);break;
        
        case -3:SDL_RenderCopy(pRenderer,pTexture,marcheHori+0,dest);break;
        
        case -2:SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+0,dest, 0, NULL, SDL_FLIP_HORIZONTAL);break;
        
     }
     /** réinitialisation du i pour éviter qu'il dépasse la valeur max d'un int
     */
     if(*i%6==0){
     	*i=0;
     }
     
     /**
     * detection des hitbox d'un obstacle qui bloque le personnage
     */
     if ((dest->x>=936 && dest->x<=1064)&&(dest->y>=300 && dest->y<=615)){
     	switch(KeyIsPressed){
     		case 1:dest->x=1065;break;
     		case 2:dest->x=935;break;
     		case 3:dest->y=616;break;
     		case 4:dest->y=299;break;
   
     	}
     }
     /** 
     * test si le personnage est sur le point de sortir de l'écran
     * si oui le place du coté opposer de l'écran
     */
     if(dest->x<=-13 ||dest->x>=1230 ||dest->y<=-13  ||dest->y>=660 ){
     	switch(KeyIsPressed){
     		case 1:dest->x=1229;break;
     		case 2:dest->x=-12;break;
     		case 3:dest->y=659;break;
     		case 4:dest->y=-12;break;

     	}
     }
     /** delais d'affichage et mise a jour de l'écran */
     SDL_Delay(35);
     SDL_RenderPresent(pRenderer);
}
