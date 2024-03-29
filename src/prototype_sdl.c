#include <stdio.h>
#include "../lib/EventOp.h"
#include "../lib/texture.h"

int main(int argc, char** argv){
    /** initialisation de x pour les coordonnée src et i pour les boucles  */
    int i,x=0;
    /** Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    else{
        /** Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,
                                                                  SDL_WINDOWPOS_CENTERED,
                                                                  1280,
                                                                  720,
                                                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        /** Initialisation de SDL_Image */
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        	fprintf(stderr, "Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        	SDL_Quit();
        	return 1;
    	}
        if( pWindow )
        {
            SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); /** Création d'un SDL_Renderer utilisant l'accélération matérielle */
            if ( pRenderer )
            {
            SDL_Texture* pTexture=loadTexture("./Ressource/scorpion.png",pRenderer);
            SDL_Texture* pSol=loadTexture("./Ressource/navigateZone.png",pRenderer);
            SDL_Texture* pBlock=loadTexture("./Ressource/blockZone.png",pRenderer);
                    if ( pTexture != NULL && pSol != NULL)
                    {
                        SDL_Rect dest = { 1280/2 - 64/2,720/2 - 64/2, 64,64};
                        SDL_Rect map = { 0,0, 1280,720};
                        SDL_Rect block = { 1000,360, 64,256};
                        /**
                        * création et initialisation d'un tableau selectionnant tout les sprites de l'animation de marche
                        */
                        SDL_Rect marcheHori[6];
                        for (i=0;i<6;i++){
                            marcheHori[i].x=x;
                            marcheHori[i].y=0;
                            marcheHori[i].w=32;
                            marcheHori[i].h=32;
                            x+=32;
                        }
             
                        /**
                        * declaration de quit etant la variable booleen qui met fin a la boucle
                        * declaration keyPressed pour gérer si une touche est maintenu ou relacher
                        */
                        int quit = 0, KeyIsPressed=0;
                        
                        /** boucle du jeux */
                        while (!quit) {
                            /** détection des évènements */
                            DetectEventsOp(&KeyIsPressed,&quit);
                            /** réaction aux évènements */
                            ReactEventsOp(KeyIsPressed,pRenderer,pTexture,pSol,pBlock,marcheHori,&dest,&i,&block,&map);
                            SDL_RenderPresent(pRenderer);
                            
                        }
                        /** Libération de la mémoire associée aux texture */
                        SDL_DestroyTexture(pTexture); 
                        SDL_DestroyTexture(pSol);
                        SDL_DestroyTexture(pBlock);
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
            SDL_Delay(1000); /** Attendre trois secondes, que l'utilisateur voie la fenêtre */
            SDL_DestroyWindow(pWindow);
        }
     else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}

