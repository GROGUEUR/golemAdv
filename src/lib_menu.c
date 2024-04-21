/**
* \file lib_menu.c
* \brief programme gérant les Menus.
* \author Warrick Bonga.
* \version 1.8.6
* \date 12 Avril 2024.
*/

#include "../lib/init_menu.h"

/** Lecture du nom d'une sauvegarde */
void readSaveName(char name[20], FILE * save){
        int i, nameStart, n;
        char c;
        
        for(i = n = 0; n < 5; i++){
                c = fgetc(save);
                if(c == '\n' || c == '_')
                        n++;
                else if(c != '_' && c != '\n' && n == 4)
                        name[i - nameStart] = c;
                if(c == '\n' && n == 4)
                        nameStart = i + 1;
        }
        name[i - nameStart - 1] = '\0';
}

/** Menu principal */
int menuPrincipal(SDL_Renderer *renderer) {
	SDL_Event event;
	bool quit = false;
	int hover = NOTHING, clicked = NOTHING;
	SDL_Texture * title=loadTexture("../Ressource/Menu/GameTitle.png", renderer);
	SDL_Rect titleDest={(WINDOW_WIDTH - 425)/2,25,425,313};
	SDL_Texture * bg = loadTexture("../Ressource/Menu/bgName.png", renderer);
	/** Chargement de l'image Play par defaut */
	Image defaultPlayImage;
	defaultPlayImage.rect.w = 300;
	defaultPlayImage.rect.h = 100;
	
	defaultPlayImage.texture = loadTexture("../Ressource/Menu/defaultPlay.png", renderer);
	if (!defaultPlayImage.texture) {
		quit = true;
	}
	defaultPlayImage.rect.x = (WINDOW_WIDTH - defaultPlayImage.rect.w) / 2;
	defaultPlayImage.rect.y = 370;

	/** Chargement de l'image Settings par defaut */
	Image defaultSettingsImage;
	defaultSettingsImage.rect.w = 300;
	defaultSettingsImage.rect.h = 100;
	SDL_Rect dtest={WINDOW_WIDTH/2-defaultPlayImage.rect.w/2,370,300,100};
	defaultSettingsImage.texture = loadTexture("../Ressource/Menu/defaultSettings.png", renderer);
	if (!defaultSettingsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		quit = true;
	}
	defaultSettingsImage.rect.x = (WINDOW_WIDTH - defaultSettingsImage.rect.w) / 2;
	defaultSettingsImage.rect.y = 495;

	/** Chargement de l'image Credits par defaut */
	Image defaultCreditsImage;
	defaultCreditsImage.rect.w = 300;
	defaultCreditsImage.rect.h = 100;
	
	defaultCreditsImage.texture = loadTexture("../Ressource/Menu/defaultCredits.png", renderer);
	if (!defaultCreditsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		quit = true;
	}
	defaultCreditsImage.rect.x = (WINDOW_WIDTH - defaultCreditsImage.rect.w) / 2;
	defaultCreditsImage.rect.y = 620;

	/** Chargement de l'image Play du survol */
	Image hoverPlayImage;
	hoverPlayImage.rect.w = 300;
	hoverPlayImage.rect.h = 100;
	
	hoverPlayImage.texture = loadTexture("../Ressource/Menu/hoverPlay.png", renderer);
	if (!hoverPlayImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		quit = true;
	}
	hoverPlayImage.rect.x = (WINDOW_WIDTH - hoverPlayImage.rect.w) / 2;
	hoverPlayImage.rect.y = 370;

	/** Chargement de l'image Settings du survol */
	Image hoverSettingsImage;
	hoverSettingsImage.rect.w = 300;
	hoverSettingsImage.rect.h = 100;
	
	hoverSettingsImage.texture = loadTexture("../Ressource/Menu/hoverSettings.png", renderer);
	if (!hoverSettingsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		SDL_DestroyTexture(hoverPlayImage.texture);
		quit = true;
	}
	hoverSettingsImage.rect.x = (WINDOW_WIDTH - hoverSettingsImage.rect.w) / 2;
	hoverSettingsImage.rect.y = 495;

	/** Chargement de l'image Credits du survol */
	Image hoverCreditsImage;
	hoverCreditsImage.rect.w = 300;
	hoverCreditsImage.rect.h = 100;
	
	hoverCreditsImage.texture = loadTexture("../Ressource/Menu/hoverCredits.png", renderer);
	if (!hoverCreditsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		SDL_DestroyTexture(hoverPlayImage.texture);
		SDL_DestroyTexture(hoverSettingsImage.texture);
		quit = true;
	}
	hoverCreditsImage.rect.x = (WINDOW_WIDTH - hoverCreditsImage.rect.w) / 2;
	hoverCreditsImage.rect.y = 620;

	/** Chargement de l'image Play lors du clic */
	Image clickedPlayImage;
	clickedPlayImage.rect.w = 300;
	clickedPlayImage.rect.h = 100;
	
	clickedPlayImage.texture = loadTexture("../Ressource/Menu/clickedPlay.png", renderer);
	if (!clickedPlayImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		SDL_DestroyTexture(hoverPlayImage.texture);
		SDL_DestroyTexture(hoverSettingsImage.texture);
		SDL_DestroyTexture(hoverCreditsImage.texture);
		quit = true;
	}
	clickedPlayImage.rect.x = (WINDOW_WIDTH - clickedPlayImage.rect.w) / 2;
	clickedPlayImage.rect.y = 370;

	/** Chargement de l'image Settings lors du clic */
	Image clickedSettingsImage;
	clickedSettingsImage.rect.w = 300;
	clickedSettingsImage.rect.h = 100;
	
	clickedSettingsImage.texture = loadTexture("../Ressource/Menu/clickedSettings.png", renderer);
	if (!clickedSettingsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		SDL_DestroyTexture(hoverPlayImage.texture);
		SDL_DestroyTexture(hoverSettingsImage.texture);
		SDL_DestroyTexture(hoverCreditsImage.texture);
		SDL_DestroyTexture(clickedPlayImage.texture);
		quit = true;
	}
	clickedSettingsImage.rect.x = (WINDOW_WIDTH - clickedSettingsImage.rect.w) / 2;
	clickedSettingsImage.rect.y = 495;

	/** Chargement de l'image Credits lors du clic */
	Image clickedCreditsImage;
	clickedCreditsImage.rect.w = 300;
	clickedCreditsImage.rect.h = 100;
	
	clickedCreditsImage.texture = loadTexture("../Ressource/Menu/clickedCredits.png", renderer);
	if (!clickedCreditsImage.texture) {
		SDL_DestroyTexture(defaultPlayImage.texture);
		SDL_DestroyTexture(defaultSettingsImage.texture);
		SDL_DestroyTexture(defaultCreditsImage.texture);
		SDL_DestroyTexture(hoverPlayImage.texture);
		SDL_DestroyTexture(hoverSettingsImage.texture);
		SDL_DestroyTexture(hoverCreditsImage.texture);
		SDL_DestroyTexture(clickedPlayImage.texture);
		SDL_DestroyTexture(clickedSettingsImage.texture);
		quit = true;
	}
	clickedCreditsImage.rect.x = (WINDOW_WIDTH - clickedCreditsImage.rect.w) / 2;
	clickedCreditsImage.rect.y = 620;
	
	/** condition d'arret : choix d'un menu */
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					clicked = NOTHING;
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.x >= defaultPlayImage.rect.x && event.motion.x <= defaultPlayImage.rect.x + defaultPlayImage.rect.w &&
					event.motion.y >= defaultPlayImage.rect.y && event.motion.y <= defaultPlayImage.rect.y + defaultPlayImage.rect.h) {
						hover = PLAY;
					}
					else if (event.motion.x >= defaultSettingsImage.rect.x && event.motion.x <= defaultSettingsImage.rect.x + defaultSettingsImage.rect.w &&
					event.motion.y >= defaultSettingsImage.rect.y && event.motion.y <= defaultSettingsImage.rect.y + defaultSettingsImage.rect.h) {
						hover = SETTINGS;
					}
					else if (event.motion.x >= defaultCreditsImage.rect.x && event.motion.x <= defaultCreditsImage.rect.x + defaultCreditsImage.rect.w &&
					event.motion.y >= defaultCreditsImage.rect.y && event.motion.y <= defaultCreditsImage.rect.y + defaultCreditsImage.rect.h) {
						hover = GAMECREDITS;
					}
					else {
						hover = NOTHING;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					clicked = hover;
					break;
				case SDL_MOUSEBUTTONUP:
					if(hover == PLAY){
						quit = true;
						/** INSERER ACTIONS DU CLIC ICI */
					}
					else if(hover == SETTINGS){
						quit = true;
						/** INSERER ACTIONS DU CLIC ICI */
					}
					else if(hover == GAMECREDITS){
						quit = true;
						/** INSERER ACTIONS DU CLIC ICI */
					}
					break;
			}
		}
		
		/** Effacement de l'cran */
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer,bg, NULL,NULL);
		/** Affichage de l'image appropriée */
		if (clicked == PLAY)
			SDL_RenderCopy(renderer, clickedPlayImage.texture, NULL, &clickedPlayImage.rect);
		else if (hover == PLAY)
			SDL_RenderCopy(renderer, hoverPlayImage.texture, NULL, &hoverPlayImage.rect);
		else if (clicked != PLAY && hover != PLAY)
			SDL_RenderCopy(renderer, defaultPlayImage.texture, NULL, &defaultPlayImage.rect);
		if (clicked == SETTINGS)
			SDL_RenderCopy(renderer, clickedSettingsImage.texture, NULL, &clickedSettingsImage.rect);
		else if (hover == SETTINGS)
			SDL_RenderCopy(renderer, hoverSettingsImage.texture, NULL, &hoverSettingsImage.rect);
		else if (clicked != SETTINGS && hover != SETTINGS)
			SDL_RenderCopy(renderer, defaultSettingsImage.texture, NULL, &defaultSettingsImage.rect);
		if (clicked == GAMECREDITS)
			SDL_RenderCopy(renderer, clickedCreditsImage.texture, NULL, &clickedCreditsImage.rect);
		else if (hover == GAMECREDITS)
			SDL_RenderCopy(renderer, hoverCreditsImage.texture, NULL, &hoverCreditsImage.rect);
		else if (clicked != GAMECREDITS && hover != GAMECREDITS)
			SDL_RenderCopy(renderer, defaultCreditsImage.texture, NULL, &defaultCreditsImage.rect);
		SDL_RenderCopy(renderer,title, NULL, &titleDest);
		/** Affichage sur l'cran */
		SDL_RenderPresent(renderer);
	}
	
	/** Libration des ressources */
	SDL_DestroyTexture(title);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(defaultPlayImage.texture);
	SDL_DestroyTexture(hoverPlayImage.texture);
	SDL_DestroyTexture(clickedPlayImage.texture);
	SDL_DestroyTexture(defaultSettingsImage.texture);
	SDL_DestroyTexture(hoverSettingsImage.texture);
	SDL_DestroyTexture(clickedSettingsImage.texture);
	SDL_DestroyTexture(defaultCreditsImage.texture);
	SDL_DestroyTexture(hoverCreditsImage.texture);
	SDL_DestroyTexture(clickedCreditsImage.texture);
	
	return clicked;
}

/** Menu PLAY */
int menuPlay(SDL_Renderer *renderer) {
	SDL_Event event;
	FILE *save1 = fopen("../.saves/save1.txt", "r");
	FILE *save2 = fopen("../.saves/save2.txt", "r");
	FILE *save3 = fopen("../.saves/save3.txt", "r");
	Image saveName1, saveName2, saveName3;
	char * nameString1 = malloc(20 * sizeof(char));
	char * nameString2 = malloc(20 * sizeof(char));
	char * nameString3 = malloc(20 * sizeof(char));
	const SDL_Color white = {255,255,255};
	
	if(save1 == NULL){
	        saveName1.rect.w = 300;
	        saveName1.rect.h = 50;
	        saveName1.rect.x = 125;
	        saveName1.rect.y = 125;
	        saveName1.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "Nouvelle partie", saveName1.rect.h, white);
	}
	else{
	        readSaveName(nameString1, save1);
	        saveName1.rect.w = strlen(nameString1) * 20;
	        saveName1.rect.h = 50;
	        saveName1.rect.x = 125;
	        saveName1.rect.y = 125;
	        saveName1.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, nameString1, saveName1.rect.h, white);
	}
	
	if(save2 == NULL){
	        saveName2.rect.w = 300;
	        saveName2.rect.h = 50;
	        saveName2.rect.x = 125;
	        saveName2.rect.y = 335;
	        saveName2.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "Nouvelle partie", saveName2.rect.h, white);
	}
	else{
	        readSaveName(nameString2, save2);
	        saveName2.rect.w = strlen(nameString2) * 20;
	        saveName2.rect.h = 50;
	        saveName2.rect.x = 125;
	        saveName2.rect.y = 335;
	        saveName2.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, nameString2, saveName2.rect.h, white);
	}
	
	if(save3 == NULL){
	        saveName3.rect.w = 300;
	        saveName3.rect.h = 50;
	        saveName3.rect.x = 125;
	        saveName3.rect.y = 545;
	        saveName3.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "Nouvelle partie", saveName3.rect.h, white);
	}
	else{
	        readSaveName(nameString3, save3);
	        saveName3.rect.w = strlen(nameString3) * 20;
	        saveName3.rect.h = 50;
	        saveName3.rect.x = 125;
	        saveName3.rect.y = 545;
	        saveName3.texture = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, nameString3, saveName3.rect.h, white);
	}
	
	int saveSelect = NOTHING;
	bool quit = false;
	int hover = NOTHING, clicked = NOTHING;
	
	/** Chargement du fond du menu play */
	Image bgPlay;
	bgPlay.texture = loadTexture("../Ressource/Menu/bgPlay.png", renderer);
	bgPlay.rect.w = WINDOW_WIDTH;
	bgPlay.rect.h = WINDOW_HEIGHT;
	bgPlay.rect.x = 0;
	bgPlay.rect.y = 0;

	/** Chargement de l'image de la sauvegarde 1 par défaut */
	Image defaultSave1Image;
	defaultSave1Image.rect.w = 800;
	defaultSave1Image.rect.h = 150;
	
	defaultSave1Image.texture = loadTexture("../Ressource/objDefault.png", renderer);
	if (!defaultSave1Image.texture) {
		quit = true;
	}
	defaultSave1Image.rect.x = 75;
	defaultSave1Image.rect.y = 75;
	
	/** Chargement de l'image de la sauvegarde 2 par défaut */
	Image defaultSave2Image;
	defaultSave2Image.rect.w = 800;
	defaultSave2Image.rect.h = 150;
	
	defaultSave2Image.texture = loadTexture("../Ressource/objDefault.png", renderer);
	if (!defaultSave2Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		quit = true;
	}
	defaultSave2Image.rect.x = 75;
	defaultSave2Image.rect.y = 285;
	
	/** Chargement de l'image de la sauvegarde 3 par défaut */
	Image defaultSave3Image;
	defaultSave3Image.rect.w = 800;
	defaultSave3Image.rect.h = 150;
	
	defaultSave3Image.texture = loadTexture("../Ressource/objDefault.png", renderer);
	if (!defaultSave3Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		quit = true;
	}
	defaultSave3Image.rect.x = 75;
	defaultSave3Image.rect.y = 495;
	
	/** Chargement de l'image de la sauvegarde 1 au survol */
	Image hoverSave1Image;
	hoverSave1Image.rect.w = 800;
	hoverSave1Image.rect.h = 150;
	
	hoverSave1Image.texture = loadTexture("../Ressource/objHover.png", renderer);
	if (!hoverSave1Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		quit = true;
	}
	hoverSave1Image.rect.x = 75;
	hoverSave1Image.rect.y = 75;
	
	/** Chargement de l'image de la sauvegarde 2 au survol */
	Image hoverSave2Image;
	hoverSave2Image.rect.w = 800;
	hoverSave2Image.rect.h = 150;
	
	hoverSave2Image.texture = loadTexture("../Ressource/objHover.png", renderer);
	if (!hoverSave2Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		quit = true;
	}
	hoverSave2Image.rect.x = 75;
	hoverSave2Image.rect.y = 285;
	
	/** Chargement de l'image de la sauvegarde 3 au survol */
	Image hoverSave3Image;
	hoverSave3Image.rect.w = 800;
	hoverSave3Image.rect.h = 150;
	
	hoverSave3Image.texture = loadTexture("../Ressource/objHover.png", renderer);
	if (!hoverSave3Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		quit = true;
	}
	hoverSave3Image.rect.x = 75;
	hoverSave3Image.rect.y = 495;
	
	/** Chargement de l'image de la sauvegarde 1 au clic */
	Image clickedSave1Image;
	clickedSave1Image.rect.w = 800;
	clickedSave1Image.rect.h = 150;
	
	clickedSave1Image.texture = loadTexture("../Ressource/objSelect.png", renderer);
	if (!clickedSave1Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		quit = true;
	}
	clickedSave1Image.rect.x = 75;
	clickedSave1Image.rect.y = 75;
	
	/** Chargement de l'image de la sauvegarde 2 au clic */
	Image clickedSave2Image;
	clickedSave2Image.rect.w = 800;
	clickedSave2Image.rect.h = 150;
	
	clickedSave2Image.texture = loadTexture("../Ressource/objSelect.png", renderer);
	if (!clickedSave2Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		quit = true;
	}
	clickedSave2Image.rect.x = 75;
	clickedSave2Image.rect.y = 285;
	
	/** Chargement de l'image de la sauvegarde 3 au clic */
	Image clickedSave3Image;
	clickedSave3Image.rect.w = 800;
	clickedSave3Image.rect.h = 150;
	
	clickedSave3Image.texture = loadTexture("../Ressource/objSelect.png", renderer);
	if (!clickedSave3Image.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		quit = true;
	}
	clickedSave3Image.rect.x = 75;
	clickedSave3Image.rect.y = 495;
	
	/** Chargement de l'image de l'option lancement par défaut */
	Image defaultStartImage;
	defaultStartImage.rect.w = 255;
	defaultStartImage.rect.h = 150;
	
	defaultStartImage.texture = loadTexture("../Ressource/Menu/defaultStart.png", renderer);
	if (!defaultStartImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		quit = true;
	}
	defaultStartImage.rect.x = WINDOW_WIDTH-defaultStartImage.rect.w*1.15;
	defaultStartImage.rect.y = 75;
	
	/** Chargement de l'image de l'option écrasement par défaut */
	Image defaultOverwriteImage;
	defaultOverwriteImage.rect.w = 255;
	defaultOverwriteImage.rect.h = 150;
	
	defaultOverwriteImage.texture = loadTexture("../Ressource/Menu/defaultOverwrite.png", renderer);
	if (!defaultOverwriteImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		quit = true;
	}
	defaultOverwriteImage.rect.x = WINDOW_WIDTH-defaultOverwriteImage.rect.w*1.15;
	defaultOverwriteImage.rect.y = 285;
	
	/** Chargement de l'image de l'option retour par défaut */
	Image defaultBackImage;
	defaultBackImage.rect.w = 255;
	defaultBackImage.rect.h = 150;
	
	defaultBackImage.texture = loadTexture("../Ressource/Menu/defaultBack.png", renderer);
	if (!defaultBackImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		quit = true;
	}
	defaultBackImage.rect.x = WINDOW_WIDTH-defaultBackImage.rect.w*1.15;
	defaultBackImage.rect.y = 495;
	
	/** Chargement de l'image de l'option lancement au survol */
	Image hoverStartImage;
	hoverStartImage.rect.w = 255;
	hoverStartImage.rect.h = 150;
	
	hoverStartImage.texture = loadTexture("../Ressource/Menu/hoverStart.png", renderer);
	if (!hoverStartImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		quit = true;
	}
	hoverStartImage.rect.x = WINDOW_WIDTH-hoverStartImage.rect.w*1.15;
	hoverStartImage.rect.y = 75;
	
	/** Chargement de l'image de l'option écrasement au survol */
	Image hoverOverwriteImage;
	hoverOverwriteImage.rect.w = 255;
	hoverOverwriteImage.rect.h = 150;
	
	hoverOverwriteImage.texture = loadTexture("../Ressource/Menu/hoverOverwrite.png", renderer);
	if (!hoverOverwriteImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverStartImage.texture);
		quit = true;
	}
	hoverOverwriteImage.rect.x = WINDOW_WIDTH-hoverOverwriteImage.rect.w*1.15;
	hoverOverwriteImage.rect.y = 285;
	
	/** Chargement de l'image de l'option retour au survol */
	Image hoverBackImage;
	hoverBackImage.rect.w = 255;
	hoverBackImage.rect.h = 150;
	
	hoverBackImage.texture = loadTexture("../Ressource/Menu/hoverBack.png", renderer);
	if (!hoverBackImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverStartImage.texture);
		SDL_DestroyTexture(hoverOverwriteImage.texture);
		quit = true;
	}
	hoverBackImage.rect.x = WINDOW_WIDTH-hoverBackImage.rect.w*1.15;
	hoverBackImage.rect.y = 495;
	
	/** Chargement de l'image de l'option lancement au clic */
	Image clickedStartImage;
	clickedStartImage.rect.w = 255;
	clickedStartImage.rect.h = 150;
	
	clickedStartImage.texture = loadTexture("../Ressource/Menu/clickedStart.png", renderer);
	if (!clickedStartImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverStartImage.texture);
		SDL_DestroyTexture(hoverOverwriteImage.texture);
		SDL_DestroyTexture(hoverBackImage.texture);
		quit = true;
	}
	clickedStartImage.rect.x = WINDOW_WIDTH-clickedStartImage.rect.w*1.15;
	clickedStartImage.rect.y = 75;
	
	/** Chargement de l'image de l'option écrasement au clic */
	Image clickedOverwriteImage;
	clickedOverwriteImage.rect.w = 255;
	clickedOverwriteImage.rect.h = 150;
	
	clickedOverwriteImage.texture = loadTexture("../Ressource/Menu/clickedOverwrite.png", renderer);
	if (!clickedOverwriteImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverStartImage.texture);
		SDL_DestroyTexture(hoverOverwriteImage.texture);
		SDL_DestroyTexture(hoverBackImage.texture);
		SDL_DestroyTexture(clickedStartImage.texture);
		quit = true;
	}
	clickedOverwriteImage.rect.x = WINDOW_WIDTH-clickedOverwriteImage.rect.w*1.15;
	clickedOverwriteImage.rect.y = 285;
	
	/** Chargement de l'image de l'option retour au clic */
	Image clickedBackImage;
	clickedBackImage.rect.w = 255;
	clickedBackImage.rect.h = 150;
	
	clickedBackImage.texture = loadTexture("../Ressource/Menu/clickedBack.png", renderer);
	if (!clickedBackImage.texture) {
		SDL_DestroyTexture(defaultSave1Image.texture);
		SDL_DestroyTexture(defaultSave2Image.texture);
		SDL_DestroyTexture(defaultSave3Image.texture);
		SDL_DestroyTexture(hoverSave1Image.texture);
		SDL_DestroyTexture(hoverSave2Image.texture);
		SDL_DestroyTexture(hoverSave3Image.texture);
		SDL_DestroyTexture(clickedSave1Image.texture);
		SDL_DestroyTexture(clickedSave2Image.texture);
		SDL_DestroyTexture(clickedSave3Image.texture);
		SDL_DestroyTexture(defaultStartImage.texture);
		SDL_DestroyTexture(defaultOverwriteImage.texture);
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverStartImage.texture);
		SDL_DestroyTexture(hoverOverwriteImage.texture);
		SDL_DestroyTexture(hoverBackImage.texture);
		SDL_DestroyTexture(clickedStartImage.texture);
		SDL_DestroyTexture(clickedOverwriteImage.texture);
		quit = true;
	}
	clickedBackImage.rect.x = WINDOW_WIDTH-clickedBackImage.rect.w*1.15;
	clickedBackImage.rect.y = 495;
	
	/** condition d'arret : chargement d'une sauvegarde (vide ou commencée) */
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					saveSelect = NOTHING;
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.x >= defaultSave1Image.rect.x && event.motion.x <= defaultSave1Image.rect.x + defaultSave1Image.rect.w &&
					event.motion.y >= defaultSave1Image.rect.y && event.motion.y <= defaultSave1Image.rect.y + defaultSave1Image.rect.h)
						hover = SAVE1;
					else if (event.motion.x >= defaultSave2Image.rect.x && event.motion.x <= defaultSave2Image.rect.x + defaultSave2Image.rect.w &&
					event.motion.y >= defaultSave2Image.rect.y && event.motion.y <= defaultSave2Image.rect.y + defaultSave2Image.rect.h)
						hover = SAVE2;
					else if (event.motion.x >= defaultSave3Image.rect.x && event.motion.x <= defaultSave3Image.rect.x + defaultSave3Image.rect.w &&
					event.motion.y >= defaultSave3Image.rect.y && event.motion.y <= defaultSave3Image.rect.y + defaultSave3Image.rect.h)
						hover = SAVE3;
					else if (event.motion.x >= defaultStartImage.rect.x && event.motion.x <= defaultStartImage.rect.x + defaultStartImage.rect.w &&
					event.motion.y >= defaultStartImage.rect.y && event.motion.y <= defaultStartImage.rect.y + defaultStartImage.rect.h){
						if((saveSelect == SAVE1 && save1 != NULL) || (saveSelect == SAVE2 && save2 != NULL) || (saveSelect == SAVE3 && save3 != NULL))
							hover = saveSelect + LOAD;
						else if((saveSelect == SAVE1 && save1 == NULL) || (saveSelect == SAVE2 && save2 == NULL) || (saveSelect == SAVE3 && save3 == NULL))
							hover = saveSelect + NEWGAME;
					}
					else if (event.motion.x >= defaultOverwriteImage.rect.x && event.motion.x <= defaultOverwriteImage.rect.x + defaultOverwriteImage.rect.w &&
					event.motion.y >= defaultOverwriteImage.rect.y && event.motion.y <= defaultOverwriteImage.rect.y + defaultOverwriteImage.rect.h) {
						if((saveSelect == SAVE1 && save1 != NULL) || (saveSelect == SAVE2 && save2 != NULL) || (saveSelect == SAVE3 && save3 != NULL))
							hover = saveSelect + ERASE;
					}
					else if (event.motion.x >= defaultBackImage.rect.x && event.motion.x <= defaultBackImage.rect.x + defaultBackImage.rect.w &&
					event.motion.y >= defaultBackImage.rect.y && event.motion.y <= defaultBackImage.rect.y + defaultBackImage.rect.h)
						hover = BACK;
					else
						hover = NOTHING;
					break;
				case SDL_MOUSEBUTTONDOWN:
					clicked = hover;
					break;
				case SDL_MOUSEBUTTONUP:
					if(clicked%10==ERASE){
						saveSelect = saveSelect + NEWGAME;
					}
					else{
						saveSelect = clicked;
					}
					if(clicked != SAVE1 && clicked != SAVE2 && clicked != SAVE3 && clicked != NOTHING)
						quit = true;
					break;
			}
		}

		/** Effacement de l'cran */
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer,bgPlay.texture,NULL,&(bgPlay.rect));

		/** Affichage de l'image appropriée */
		if (clicked == SAVE1)
			SDL_RenderCopy(renderer, clickedSave1Image.texture, NULL, &clickedSave1Image.rect);
		else if (hover == SAVE1)
			SDL_RenderCopy(renderer, hoverSave1Image.texture, NULL, &hoverSave1Image.rect);
		else if (clicked != SAVE1 && hover != SAVE1)
			SDL_RenderCopy(renderer, defaultSave1Image.texture, NULL, &defaultSave1Image.rect);
		if (clicked == SAVE2)
			SDL_RenderCopy(renderer, clickedSave2Image.texture, NULL, &clickedSave2Image.rect);
		else if (hover == SAVE2)
			SDL_RenderCopy(renderer, hoverSave2Image.texture, NULL, &hoverSave2Image.rect);
		else if (clicked != SAVE2 && hover != SAVE2)
			SDL_RenderCopy(renderer, defaultSave2Image.texture, NULL, &defaultSave2Image.rect);
		if (clicked == SAVE3)
			SDL_RenderCopy(renderer, clickedSave3Image.texture, NULL, &clickedSave3Image.rect);
		else if (hover == SAVE3)
			SDL_RenderCopy(renderer, hoverSave3Image.texture, NULL, &hoverSave3Image.rect);
		else if (clicked != SAVE3 && hover != SAVE3)
			SDL_RenderCopy(renderer, defaultSave3Image.texture, NULL, &defaultSave3Image.rect);
		if ((clicked % 10 == LOAD || clicked % 10 ==NEWGAME) && saveSelect != NOTHING)
			SDL_RenderCopy(renderer, clickedStartImage.texture, NULL, &clickedStartImage.rect);
		else if ((hover % 10 == LOAD || hover % 10 == NEWGAME) && saveSelect != NOTHING)
			SDL_RenderCopy(renderer, hoverStartImage.texture, NULL, &hoverStartImage.rect);
		else if ((clicked % 10 != LOAD || clicked % 10 !=NEWGAME) && (hover % 10 != LOAD || hover % 10 !=NEWGAME) && saveSelect != NOTHING)
			SDL_RenderCopy(renderer, defaultStartImage.texture, NULL, &defaultStartImage.rect);
		if (clicked % 10 == ERASE && saveSelect != NOTHING)
			SDL_RenderCopy(renderer, clickedOverwriteImage.texture, NULL, &clickedOverwriteImage.rect);
		else if (hover % 10 == ERASE && saveSelect != NOTHING)
			SDL_RenderCopy(renderer, hoverOverwriteImage.texture, NULL, &hoverOverwriteImage.rect);
		else if (clicked % 10 != ERASE && hover % 10 != ERASE && saveSelect != NOTHING && ((saveSelect == SAVE1 && save1 != NULL) || (saveSelect == SAVE2 && save2 != NULL) || (saveSelect == SAVE3 && save3 != NULL)))
			SDL_RenderCopy(renderer, defaultOverwriteImage.texture, NULL, &defaultOverwriteImage.rect);
		if (clicked == BACK)
			SDL_RenderCopy(renderer, clickedBackImage.texture, NULL, &clickedBackImage.rect);
		else if (hover == BACK)
			SDL_RenderCopy(renderer, hoverBackImage.texture, NULL, &hoverBackImage.rect);
		else if (clicked != BACK && hover != BACK)
			SDL_RenderCopy(renderer, defaultBackImage.texture, NULL, &defaultBackImage.rect);
		
		SDL_RenderCopy(renderer, saveName1.texture, NULL, &saveName1.rect);
		SDL_RenderCopy(renderer, saveName2.texture, NULL, &saveName2.rect);
		SDL_RenderCopy(renderer, saveName3.texture, NULL, &saveName3.rect);
                
		/** Affichage sur l'cran */
		SDL_RenderPresent(renderer);
	}

	/** Libration des ressources */
	SDL_DestroyTexture(saveName1.texture);
	SDL_DestroyTexture(saveName2.texture);
	SDL_DestroyTexture(saveName3.texture);
	SDL_DestroyTexture(defaultSave1Image.texture);
	SDL_DestroyTexture(hoverSave1Image.texture);
	SDL_DestroyTexture(clickedSave1Image.texture);
	SDL_DestroyTexture(defaultSave2Image.texture);
	SDL_DestroyTexture(hoverSave2Image.texture);
	SDL_DestroyTexture(clickedSave2Image.texture);
	SDL_DestroyTexture(defaultSave3Image.texture);
	SDL_DestroyTexture(hoverSave3Image.texture);
	SDL_DestroyTexture(clickedSave3Image.texture);
	SDL_DestroyTexture(defaultStartImage.texture);
	SDL_DestroyTexture(hoverStartImage.texture);
	SDL_DestroyTexture(clickedStartImage.texture);
	SDL_DestroyTexture(defaultOverwriteImage.texture);
	SDL_DestroyTexture(hoverOverwriteImage.texture);
	SDL_DestroyTexture(clickedOverwriteImage.texture);
	SDL_DestroyTexture(defaultBackImage.texture);
	SDL_DestroyTexture(hoverBackImage.texture);
	SDL_DestroyTexture(clickedBackImage.texture);
	SDL_DestroyTexture(bgPlay.texture);
	if(saveSelect % 10 == LOAD){
		switch(saveSelect / 10){
			case SAVE1:
				saveSelect -= (save1 == NULL);
				break;
			case SAVE2:
				saveSelect -= (save2 == NULL);
				break;
			case SAVE3:
				saveSelect -= (save3 == NULL);
				break;
		}
	}
	free(nameString1);
	free(nameString2);
	free(nameString3);
	
	if(save1 != NULL)
		fclose(save1);
	if(save2 != NULL)
		fclose(save2);
	if(save3 != NULL)
		fclose(save3);
	
	return saveSelect;
}

/** Menu SETTINGS */
int menuSettings(SDL_Renderer *renderer) {
	SDL_Event event;
	bool quit = false;
	int hover = NOTHING, clicked = NOTHING;

	/** Chargement de l'image du bouton retour par defaut */
	Image defaultBackImage;
	defaultBackImage.rect.w = 255;
	defaultBackImage.rect.h = 150;
	
	defaultBackImage.texture = loadTexture("../Ressource/Menu/defaultBack.png", renderer);
	if (!defaultBackImage.texture) {
		quit = true;
	}
	defaultBackImage.rect.x = 975;
	defaultBackImage.rect.y = 520;
	
	/** Chargement de l'image du bouton retour du survol */
	Image hoverBackImage;
	hoverBackImage.rect.w = 255;
	hoverBackImage.rect.h = 150;
	
	hoverBackImage.texture = loadTexture("../Ressource/Menu/hoverBack.png", renderer);
	if (!hoverBackImage.texture) {
		SDL_DestroyTexture(defaultBackImage.texture);
		quit = true;
	}
	hoverBackImage.rect.x = 975;
	hoverBackImage.rect.y = 520;
	
	/** Chargement de l'image du bouton retour lors du clic */
	Image clickedBackImage;
	clickedBackImage.rect.w = 255;
	clickedBackImage.rect.h = 150;
	
	clickedBackImage.texture = loadTexture("../Ressource/Menu/clickedBack.png", renderer);
	if (!clickedBackImage.texture) {
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverBackImage.texture);
		quit = true;
	}
	clickedBackImage.rect.x = 975;
	clickedBackImage.rect.y = 520;
	
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.x >= defaultBackImage.rect.x && event.motion.x <= defaultBackImage.rect.x + defaultBackImage.rect.w &&
					event.motion.y >= defaultBackImage.rect.y && event.motion.y <= defaultBackImage.rect.y + defaultBackImage.rect.h) {
						hover = BACK;
					}
					else {
						hover = NOTHING;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT && hover == BACK)
						clicked = hover;
					break;
				case SDL_MOUSEBUTTONUP:
					if(clicked == BACK){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					break;
			}
		}

		/** Effacement de l'cran */
		SDL_RenderClear(renderer);

		/** Affichage de l'image appropriée */
		if (clicked == BACK)
			SDL_RenderCopy(renderer, clickedBackImage.texture, NULL, &clickedBackImage.rect);
		else if (hover == BACK)
			SDL_RenderCopy(renderer, hoverBackImage.texture, NULL, &hoverBackImage.rect);
		else if (clicked != BACK && hover != BACK)
			SDL_RenderCopy(renderer, defaultBackImage.texture, NULL, &defaultBackImage.rect);

		/** Affichage sur l'cran */
		SDL_RenderPresent(renderer);
	}
	
	/** Libration des ressources */
	SDL_DestroyTexture(defaultBackImage.texture);
	SDL_DestroyTexture(hoverBackImage.texture);
	SDL_DestroyTexture(clickedBackImage.texture);
	
	return clicked;
}

/** Menu CREDITS */
int menuCredits(SDL_Renderer *renderer) {
	system("wget -P .. https://github.com/GROGUEUR/golemAdv/raw/main/credits.txt");
	system("gedit ../credits.txt");
	SDL_Event event;
	bool quit = false;
	int hover = NOTHING, clicked = NOTHING;

	/** Chargement de l'image du bouton retour par defaut */
	Image defaultBackImage;
	defaultBackImage.rect.w = 255;
	defaultBackImage.rect.h = 150;
	
	defaultBackImage.texture = loadTexture("../Ressource/Menu/defaultBack.png", renderer);
	if (!defaultBackImage.texture) {
		quit = true;
	}
	defaultBackImage.rect.x = 975;
	defaultBackImage.rect.y = 520;
	
	/** Chargement de l'image du bouton retour du survol */
	Image hoverBackImage;
	hoverBackImage.rect.w = 255;
	hoverBackImage.rect.h = 150;
	
	hoverBackImage.texture = loadTexture("../Ressource/Menu/hoverBack.png", renderer);
	if (!hoverBackImage.texture) {
		SDL_DestroyTexture(defaultBackImage.texture);
		quit = true;
	}
	hoverBackImage.rect.x = 975;
	hoverBackImage.rect.y = 520;
	
	/** Chargement de l'image du bouton retour lors du clic */
	Image clickedBackImage;
	clickedBackImage.rect.w = 255;
	clickedBackImage.rect.h = 150;
	
	clickedBackImage.texture = loadTexture("../Ressource/Menu/clickedBack.png", renderer);
	if (!clickedBackImage.texture) {
		SDL_DestroyTexture(defaultBackImage.texture);
		SDL_DestroyTexture(hoverBackImage.texture);
		quit = true;
	}
	clickedBackImage.rect.x = 975;
	clickedBackImage.rect.y = 520;
	
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					exit(0);
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.x >= defaultBackImage.rect.x && event.motion.x <= defaultBackImage.rect.x + defaultBackImage.rect.w &&
					event.motion.y >= defaultBackImage.rect.y && event.motion.y <= defaultBackImage.rect.y + defaultBackImage.rect.h) {
						hover = BACK;
					}
					else {
						hover = NOTHING;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT && hover == BACK)
						clicked = hover;
					break;
				case SDL_MOUSEBUTTONUP:
					if(clicked == BACK){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					break;
			}
		}

		/** Effacement de l'cran */
		SDL_RenderClear(renderer);

		/** Affichage de l'image appropriée */
		if (clicked == BACK)
			SDL_RenderCopy(renderer, clickedBackImage.texture, NULL, &clickedBackImage.rect);
		else if (hover == BACK)
			SDL_RenderCopy(renderer, hoverBackImage.texture, NULL, &hoverBackImage.rect);
		else if (clicked != BACK && hover != BACK)
			SDL_RenderCopy(renderer, defaultBackImage.texture, NULL, &defaultBackImage.rect);

		/** Affichage sur l'cran */
		SDL_RenderPresent(renderer);
	}
	
	/** Libration des ressources */
	SDL_DestroyTexture(defaultBackImage.texture);
	SDL_DestroyTexture(hoverBackImage.texture);
	SDL_DestroyTexture(clickedBackImage.texture);
	
	return clicked;
}

/** Menu PAUSE */
int menuPause(SDL_Renderer *renderer, scene_t * scene,SDL_Texture * map,SDL_Rect dest) {
	SDL_Event event;
	bool quit = false;
	int hover = NOTHING, clicked = NOTHING;
	SDL_Rect destMap={115,10,540*2+40,375};
	
	const SDL_Color black = {0,0,0};
	
	SDL_Texture * saveT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "SAUVEGARDER", 50, black);
	SDL_Rect saveR;
	saveR.w = 220;
	saveR.h = 50;
	saveR.x = 275;
	saveR.y = 420;
	
	SDL_Texture * sQuitT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "SAUVER ET QUITTER", 50, black);
	SDL_Rect sQuitR;
	sQuitR.w = 340;
	sQuitR.h = 50;
	sQuitR.x = 215;
	sQuitR.y = 570;
	
	SDL_Texture * optionsT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "OPTIONS", 50, black);
	SDL_Rect optionsR;
	optionsR.w = 140;
	optionsR.h = 50;
	optionsR.x = 895;
	optionsR.y = 420;
	
	SDL_Texture * backT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "RETOUR", 50, black);
	SDL_Rect backR;
	backR.w = 120;
	backR.h = 50;
	backR.x = 905;
	backR.y = 570;
	
	/** Chargement de l'image de sauvegarde par defaut */
	Image defaultSaveImage;
	defaultSaveImage.texture = loadTexture("../Ressource/Menu/defaultPause.png", renderer);
	if (!defaultSaveImage.texture) {
		quit = true;
	}
	SDL_QueryTexture(defaultSaveImage.texture, NULL, NULL, &defaultSaveImage.rect.w, &defaultSaveImage.rect.h);
	defaultSaveImage.rect.x = 115;
	defaultSaveImage.rect.y = 395;

	/** Chargement de l'image du bouton quitter par defaut */
	Image defaultSQuitImage;
	defaultSQuitImage.texture = loadTexture("../Ressource/Menu/defaultPause.png", renderer);
	if (!defaultSQuitImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		quit = true;
	}
	SDL_QueryTexture(defaultSQuitImage.texture, NULL, NULL, &defaultSQuitImage.rect.w, &defaultSQuitImage.rect.h);
	defaultSQuitImage.rect.x = 115;
	defaultSQuitImage.rect.y = 545;

	/** Chargement de l'image Options par defaut */
	Image defaultOptionsImage;
	defaultOptionsImage.texture = loadTexture("../Ressource/Menu/defaultPause.png", renderer);
	if (!defaultOptionsImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		quit = true;
	}
	SDL_QueryTexture(defaultOptionsImage.texture, NULL, NULL, &defaultOptionsImage.rect.w, &defaultOptionsImage.rect.h);
	defaultOptionsImage.rect.x = 695;
	defaultOptionsImage.rect.y = 395;
	
	/** Chargement de l'image du bouton retour par défaut */
	Image defaultResumeImage;
	defaultResumeImage.texture = loadTexture("../Ressource/Menu/defaultPause.png", renderer);
	if (!defaultResumeImage.texture) {
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		quit = true;
	}
	SDL_QueryTexture(defaultResumeImage.texture, NULL, NULL, &defaultResumeImage.rect.w, &defaultResumeImage.rect.h);
	defaultResumeImage.rect.x = 695;
	defaultResumeImage.rect.y = 545;
	
	/** Chargement de l'image de sauvegarde du survol */
	Image hoverSaveImage;
	hoverSaveImage.texture = loadTexture("../Ressource/Menu/hoverPause.png", renderer);
	if (!hoverSaveImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		quit = true;
	}
	SDL_QueryTexture(hoverSaveImage.texture, NULL, NULL, &hoverSaveImage.rect.w, &hoverSaveImage.rect.h);
	hoverSaveImage.rect.x = 115;
	hoverSaveImage.rect.y = 395;

	/** Chargement de l'image du bouton quitter du survol */
	Image hoverSQuitImage;
	hoverSQuitImage.texture = loadTexture("../Ressource/Menu/hoverPause.png", renderer);
	if (!hoverSQuitImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		quit = true;
	}
	SDL_QueryTexture(hoverSQuitImage.texture, NULL, NULL, &hoverSQuitImage.rect.w, &hoverSQuitImage.rect.h);
	hoverSQuitImage.rect.x = 115;
	hoverSQuitImage.rect.y = 545;

	/** Chargement de l'image Options du survol */
	Image hoverOptionsImage;
	hoverOptionsImage.texture = loadTexture("../Ressource/Menu/hoverPause.png", renderer);
	if (!hoverOptionsImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		quit = true;
	}
	SDL_QueryTexture(hoverOptionsImage.texture, NULL, NULL, &hoverOptionsImage.rect.w, &hoverOptionsImage.rect.h);
	hoverOptionsImage.rect.x = 695;
	hoverOptionsImage.rect.y = 395;
	
	/** Chargement de l'image du bouton retour du survol */
	Image hoverResumeImage;
	hoverResumeImage.texture = loadTexture("../Ressource/Menu/hoverPause.png", renderer);
	if (!hoverResumeImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		SDL_DestroyTexture(hoverOptionsImage.texture);
		quit = true;
	}
	SDL_QueryTexture(hoverResumeImage.texture, NULL, NULL, &hoverResumeImage.rect.w, &hoverResumeImage.rect.h);
	hoverResumeImage.rect.x = 695;
	hoverResumeImage.rect.y = 545;
	
	/** Chargement de l'image de sauvegarde lors du clic */
	Image clickedSaveImage;
	clickedSaveImage.texture = loadTexture("../Ressource/Menu/clickedPause.png", renderer);
	if (!clickedSaveImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		SDL_DestroyTexture(hoverOptionsImage.texture);
		SDL_DestroyTexture(hoverResumeImage.texture);
		quit = true;
	}
	SDL_QueryTexture(clickedSaveImage.texture, NULL, NULL, &clickedSaveImage.rect.w, &clickedSaveImage.rect.h);
	clickedSaveImage.rect.x = 115;
	clickedSaveImage.rect.y = 395;

	/** Chargement de l'image du bouton quitter lors du clic */
	Image clickedSQuitImage;
	clickedSQuitImage.texture = loadTexture("../Ressource/Menu/clickedPause.png", renderer);
	if (!clickedSQuitImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		SDL_DestroyTexture(hoverOptionsImage.texture);
		SDL_DestroyTexture(hoverResumeImage.texture);
		SDL_DestroyTexture(clickedSaveImage.texture);
		quit = true;
	}
	SDL_QueryTexture(clickedSQuitImage.texture, NULL, NULL, &clickedSQuitImage.rect.w, &clickedSQuitImage.rect.h);
	clickedSQuitImage.rect.x = 115;
	clickedSQuitImage.rect.y = 545;

	/** Chargement de l'image Options lors du clic */
	Image clickedOptionsImage;
	clickedOptionsImage.texture = loadTexture("../Ressource/Menu/clickedPause.png", renderer);
	if (!clickedOptionsImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		SDL_DestroyTexture(hoverOptionsImage.texture);
		SDL_DestroyTexture(hoverResumeImage.texture);
		SDL_DestroyTexture(clickedSaveImage.texture);
		SDL_DestroyTexture(clickedSQuitImage.texture);
		quit = true;
	}
	SDL_QueryTexture(clickedOptionsImage.texture, NULL, NULL, &clickedOptionsImage.rect.w, &clickedOptionsImage.rect.h);
	clickedOptionsImage.rect.x = 695;
	clickedOptionsImage.rect.y = 395;
	
	/** Chargement de l'image du bouton retour lors du clic */
	Image clickedResumeImage;
	clickedResumeImage.texture = loadTexture("../Ressource/Menu/clickedPause.png", renderer);
	if (!clickedResumeImage.texture) {
		SDL_DestroyTexture(defaultSaveImage.texture);
		SDL_DestroyTexture(defaultSQuitImage.texture);
		SDL_DestroyTexture(defaultOptionsImage.texture);
		SDL_DestroyTexture(defaultResumeImage.texture);
		SDL_DestroyTexture(hoverSaveImage.texture);
		SDL_DestroyTexture(hoverSQuitImage.texture);
		SDL_DestroyTexture(hoverOptionsImage.texture);
		SDL_DestroyTexture(hoverResumeImage.texture);
		SDL_DestroyTexture(clickedSaveImage.texture);
		SDL_DestroyTexture(clickedSQuitImage.texture);
		SDL_DestroyTexture(clickedOptionsImage.texture);
		quit = true;
	}
	SDL_QueryTexture(clickedResumeImage.texture, NULL, NULL, &clickedResumeImage.rect.w, &clickedResumeImage.rect.h);
	clickedResumeImage.rect.x = 695;
	clickedResumeImage.rect.y = 545;

	/** condition d'arret : sélection d'un choix du menu de pause OU appui sur [échap] */
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					if (event.motion.x >= defaultSaveImage.rect.x && event.motion.x <= defaultSaveImage.rect.x + defaultSaveImage.rect.w &&
					event.motion.y >= defaultSaveImage.rect.y && event.motion.y <= defaultSaveImage.rect.y + defaultSaveImage.rect.h)
						hover = SAVE;
					else if (event.motion.x >= defaultSQuitImage.rect.x && event.motion.x <= defaultSQuitImage.rect.x + defaultSQuitImage.rect.w &&
					event.motion.y >= defaultSQuitImage.rect.y && event.motion.y <= defaultSQuitImage.rect.y + defaultSQuitImage.rect.h)
						hover = SQUIT;
					else if (event.motion.x >= defaultOptionsImage.rect.x && event.motion.x <= defaultOptionsImage.rect.x + defaultOptionsImage.rect.w &&
					event.motion.y >= defaultOptionsImage.rect.y && event.motion.y <= defaultOptionsImage.rect.y + defaultOptionsImage.rect.h)
						hover = OPTIONS;
					else if (event.motion.x >= defaultResumeImage.rect.x && event.motion.x <= defaultResumeImage.rect.x + defaultResumeImage.rect.w &&
					event.motion.y >= defaultResumeImage.rect.y && event.motion.y <= defaultResumeImage.rect.y + defaultResumeImage.rect.h)
						hover = RESUME;
					else
						hover = NOTHING;
					break;
				case SDL_MOUSEBUTTONDOWN:
					clicked = hover;
					break;
				case SDL_MOUSEBUTTONUP:
					if(clicked == SAVE){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					else if(clicked == SQUIT){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					else if(clicked == OPTIONS){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					else if(clicked == RESUME){
						/** INSERER ACTIONS DU CLIC ICI */
						quit = true;
					}
					break;
				case SDL_KEYUP:
					if(event.key.keysym.sym == SDLK_ESCAPE){
						*scene = OP;
						clicked = RESUME;
						quit = true;
					}
					break;
			}
		}

		/** Effacement de l'écran */
		SDL_RenderClear(renderer);
		afficher_map(dest.x,dest.y,renderer,map);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		SDL_RenderFillRect(renderer, NULL);
		SDL_RenderCopy(renderer, map, NULL, &destMap);
		/** Affichage de l'image appropriée */
		if (clicked == SAVE)
			SDL_RenderCopy(renderer, clickedSaveImage.texture, NULL, &clickedSaveImage.rect);
		else if (hover == SAVE)
			SDL_RenderCopy(renderer, hoverSaveImage.texture, NULL, &hoverSaveImage.rect);
		else if (clicked != SAVE && hover != SAVE)
			SDL_RenderCopy(renderer, defaultSaveImage.texture, NULL, &defaultSaveImage.rect);
		if (clicked == SQUIT)
			SDL_RenderCopy(renderer, clickedSQuitImage.texture, NULL, &clickedSQuitImage.rect);
		else if (hover == SQUIT)
			SDL_RenderCopy(renderer, hoverSQuitImage.texture, NULL, &hoverSQuitImage.rect);
		else if (clicked != SQUIT && hover != SQUIT)
			SDL_RenderCopy(renderer, defaultSQuitImage.texture, NULL, &defaultSQuitImage.rect);
		if (clicked == OPTIONS)
			SDL_RenderCopy(renderer, clickedOptionsImage.texture, NULL, &clickedOptionsImage.rect);
		else if (hover == OPTIONS)
			SDL_RenderCopy(renderer, hoverOptionsImage.texture, NULL, &hoverOptionsImage.rect);
		else if (clicked != OPTIONS && hover != OPTIONS)
			SDL_RenderCopy(renderer, defaultOptionsImage.texture, NULL, &defaultOptionsImage.rect);
		if (clicked == RESUME)
			SDL_RenderCopy(renderer, clickedResumeImage.texture, NULL, &clickedResumeImage.rect);
		else if (hover == RESUME)
			SDL_RenderCopy(renderer, hoverResumeImage.texture, NULL, &hoverResumeImage.rect);
		else if (clicked != RESUME && hover != RESUME)
			SDL_RenderCopy(renderer, defaultResumeImage.texture, NULL, &defaultResumeImage.rect);
		
		SDL_RenderCopy(renderer, saveT, NULL, &saveR);
		SDL_RenderCopy(renderer, sQuitT, NULL, &sQuitR);
		SDL_RenderCopy(renderer, optionsT, NULL, &optionsR);
		SDL_RenderCopy(renderer, backT, NULL, &backR);
                
		/** Affichage sur l'cran */
		SDL_RenderPresent(renderer);
	}
	
	/** Libration des ressources */
	SDL_DestroyTexture(saveT);
	SDL_DestroyTexture(sQuitT);
	SDL_DestroyTexture(optionsT);
	SDL_DestroyTexture(backT);
	SDL_DestroyTexture(defaultSaveImage.texture);
	SDL_DestroyTexture(hoverSaveImage.texture);
	SDL_DestroyTexture(clickedSaveImage.texture);
	SDL_DestroyTexture(defaultSQuitImage.texture);
	SDL_DestroyTexture(hoverSQuitImage.texture);
	SDL_DestroyTexture(clickedSQuitImage.texture);
	SDL_DestroyTexture(defaultOptionsImage.texture);
	SDL_DestroyTexture(hoverOptionsImage.texture);
	SDL_DestroyTexture(clickedOptionsImage.texture);
	SDL_DestroyTexture(defaultResumeImage.texture);
	SDL_DestroyTexture(hoverResumeImage.texture);
	SDL_DestroyTexture(clickedResumeImage.texture);
	
	return clicked;
}
