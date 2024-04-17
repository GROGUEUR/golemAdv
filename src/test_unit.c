/**
* \file test_unit.c
* \brief programme faisant les test unitaires.
* \author Cognard Luka.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "../lib/EventOp.h"
#include "../lib/texture.h"
#include "../lib/type.h"
#include "../lib/init_menu.h"

/** test la fonction de création de texture */
void test_creer_texture() {
    SDL_Window* pWindow = SDL_CreateWindow("Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1360,780,SDL_WINDOW_SHOWN);
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
    int *succes=NULL; int suc=0;
    // Charger les textures pour le test
    SDL_Texture* vendeurDialoTexture[5]={loadTexture("../Ressource/pnj/dialogue/shopFirstDialogue.png",pRenderer),
                                           loadTexture("../Ressource/pnj/dialogue/shopBiyDialogue.png",pRenderer),
                                           loadTexture("../Ressource/pnj/dialogue/shopSellDialogue.png",pRenderer),
                                           loadTexture("../Ressource/pnj/dialogue/shopQuitDialogue.png",pRenderer),
                                           loadTexture("../Ressource/pnj/dialogue/shopSecondDialogue.png",pRenderer)};
    for(int i=0;i<5;i++){
    	if(vendeurDialoTexture[i]!=NULL){
    		suc++;
    	}
        SDL_DestroyTexture(vendeurDialoTexture[i]);
        vendeurDialoTexture[i]=NULL;
    }
    
    if(suc==5){
    	succes=malloc(sizeof(int));
    }
    CU_ASSERT_PTR_NOT_NULL(succes);
    free(succes);
    succes=NULL;
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
}

void test_creer_texture_texte() {
    SDL_Window* pWindow = SDL_CreateWindow("Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1360,780,SDL_WINDOW_SHOWN);
    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
    SDL_Color blanc={255,255,255};
    // Charger les textures pour le test
    SDL_Texture* texte=loadTextureFont("../Ressource/font/LifeCraft.ttf",pRenderer,"test",34,blanc);
    
    CU_ASSERT_PTR_NOT_NULL(texte);
    SDL_DestroyTexture(texte);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
}

/** test la fonction d'initialisation de la team */
void test_init_team(){
	team_t team;
	init_reinit__team(&team);
	int * succes=NULL; int suc=0;
	if(team.nbPerso==0){
		for(int i=0;i<3;i++){
			if(team.team[i]==NULL){
				suc++;
			}
		}
	}
	
	if(suc==3){
	    succes=malloc(sizeof(int));
	}
	CU_ASSERT_PTR_NOT_NULL(succes);
	free(succes);
        succes=NULL;
}

/** test la fonction d'initialisation de l'inventaire */
void test_init_inv(){
	inventaire_t inv;
	init_and_reinit_inv(&inv);
	int * succes=NULL; int suc=0;
	if(inv.nbObjActu==0 && inv.nbEquActu==0 && inv.nbArmActu==0 && inv.bourse==0){
		for(int i=0;i<NB_INV_OBJETS;i++){
			if(inv.sac[i]==NULL){
				suc++;
			}
		}
		if(suc==NB_INV_OBJETS){
			suc=0;
			for(int i=0;i<NB_INV_EQUIPEMENTS;i++){
				if(inv.equipements[i]==NULL){
					suc++;
				}
			}
			if(suc==NB_INV_EQUIPEMENTS){
				suc=0;
				for(int i=0;i<NB_INV_ARMES;i++){
					if(inv.armes[i]==NULL){
						suc++;
					}
				}
				if(suc==NB_INV_ARMES){
					suc=3;
				}
			}
		}
	}
	
	if(suc==3){
	    succes=malloc(sizeof(int));
	}
	CU_ASSERT_PTR_NOT_NULL(succes);
	free(succes);
        succes=NULL;
}

/** programme principale effectuant tout les tests */
int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS );
    TTF_Init();
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite de tests pour EventOp", NULL, NULL);
    
    CU_add_test(suite, "test_creer_texture", test_creer_texture);
    CU_add_test(suite, "test_init_team", test_init_team);
    CU_add_test(suite, "test_init_inventaire", test_init_inv);
    CU_add_test(suite, "test_creer_texture_texte", test_creer_texture_texte);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return CU_get_error();
}
