#include "EventOp.h"

/**
* fonction DetectEventsOp qui s'occupera de gérer la détection
* des évènement quand nous somme sur l'openWorld 
*/
void DetectEventsOp(int* KeyIsPressed, int* quit){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
          if (event.type == SDL_QUIT) {
             *quit = 1;
          }
          /** récuperation des touche enfoncer */
          if (event.type == SDL_KEYDOWN) {
          /** regarde si la touche enfoncer est q */    
                   if (event.key.keysym.sym == SDLK_q) {
          /** test si la touche est maintenu change la variable KeyIsPressed */
                       if (*KeyIsPressed <= 0) {
                           *KeyIsPressed = 1;
                       }  
                   }
                                    
                   else if (event.key.keysym.sym == SDLK_d) {
                       if (*KeyIsPressed <= 0) {
                            *KeyIsPressed = 2;
                       }  
                   }
                   else if (event.key.keysym.sym == SDLK_z) {
                       if (*KeyIsPressed <= 0) {
                           *KeyIsPressed = 3;
                       }  
                   }
                                    
                   else if (event.key.keysym.sym == SDLK_s) {
                       if (*KeyIsPressed <= 0) {
                           *KeyIsPressed = 4;
                       }  
                   }
          }                 
          /** récuperation des touche relacher changement de KeyIsPressed */
          else if (event.type == SDL_KEYUP) {
          /** regarde si la touche relacher est q */
               if (event.key.keysym.sym == SDLK_d){
                  *KeyIsPressed = 0;
               }
               else if(event.key.keysym.sym == SDLK_q){
                  *KeyIsPressed = -1;
               }
               else if (event.key.keysym.sym == SDLK_z){
                  *KeyIsPressed = -2;
               }
               else if(event.key.keysym.sym == SDLK_s){
                  *KeyIsPressed = -3;
               }
         }
                                
    }
}

/**
* fonction ReactEventsOp qui s'occupe de réagire en fonction 
* des évènement quand nous somme sur l'openWorld
*/
void ReactEventsOp(int KeyIsPressed,SDL_Renderer* pRenderer,SDL_Texture* pTexture,SDL_Rect* marcheHori,SDL_Rect* dest,int* i){

     if (KeyIsPressed==1){
        dest->x-=5;
  
        /** 
        * test si le personnage est sur le point de sortir de l'écran
        * si oui le place du coté opposer de l'écran
        */
        if (dest->x<=-13){
           dest->x=1230;
        }
        SDL_RenderClear(pRenderer);
        SDL_RenderCopy(pRenderer,pTexture,marcheHori+((++*i)%6),dest);
        SDL_Delay(50);
        SDL_RenderPresent(pRenderer);
     }
     else if(KeyIsPressed==2){
        dest->x+=5;
        if (dest->x>=1230){
           dest->x=-13;
        }
        SDL_RenderClear(pRenderer);
        SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+((++*i)%6),dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_Delay(50);
        SDL_RenderPresent(pRenderer); 
     }
     else if (KeyIsPressed==3) {
        dest->y-=5;
        if (dest->y<=-13){
           dest->y=660;
        }
        SDL_RenderClear(pRenderer);
        SDL_RenderCopy(pRenderer,pTexture,marcheHori+((++*i)%6),dest);
        SDL_Delay(50);
        SDL_RenderPresent(pRenderer);
     }
     else if (KeyIsPressed==4){
        dest->y+=5;
        if (dest->y>=660){
           dest->y=-13;
        }
        SDL_RenderClear(pRenderer);
        SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+((++*i)%6),dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_Delay(50);
        SDL_RenderPresent(pRenderer);
                               
     }
     else if(KeyIsPressed==0){
        SDL_RenderClear(pRenderer);
        SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+0,dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(pRenderer); 
     }
     else if(KeyIsPressed==-1){
        SDL_RenderClear(pRenderer);
        SDL_RenderCopy(pRenderer,pTexture,marcheHori+0,dest);
        SDL_RenderPresent(pRenderer); 
     }
     else if(KeyIsPressed==-3){
        SDL_RenderClear(pRenderer);
        SDL_RenderCopyEx(pRenderer,pTexture,marcheHori+0,dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(pRenderer); 
                            }
     else{
        SDL_RenderClear(pRenderer);
        SDL_RenderCopy(pRenderer,pTexture,marcheHori+0,dest);
        SDL_RenderPresent(pRenderer); 
     }
     if(*i%6==0){
     	*i=0;
     }
}
