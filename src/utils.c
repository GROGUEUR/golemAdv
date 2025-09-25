/**
* \file utils.c
* \brief programme gérant le menu pour rentrer un pseudo, ainsi que les sauvegardes.
* \author Un mec random.
* \version 1.9.8
* \date 12 Avril 2024.
*/

#include "../lib/utils.h"

/** Fonction de détection de chaque touche utile du clavier pour entrer un nom : 
  * condition qui permet de vérifier si la longueur est bien inférieure à la taille du nom maximale (TAILLE_NOM - 1) pour pouvoir insérer un caractère
  * condition qui permet de vérifier si la longueur est bien supérieure à 0 pour pouvoir supprimer un caractère
  * condition qui permet de vérifier si la longueur est bien supérieure à 1 pour pouvoir valider le nom
  * si et seulement si l'indice pointe sur le début de la chaîne, la lettre sera en majuscule
  */

void entrerLettre(SDL_Event event, char * name, int * indice,  SDL_Color color, int * quit){
	switch(event.key.keysym.sym){
		case SDLK_a:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'A' : 'a'; 
				(*indice)++;
			}
			break;
		case SDLK_b:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'B' : 'b'; 
				(*indice)++;
			}
			break;
		case SDLK_c:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'C' : 'c'; 
				(*indice)++;
			}
			break;
		case SDLK_d:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'D' : 'd'; 
				(*indice)++;
			}
			break;
		case SDLK_e:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'E' : 'e'; 
				(*indice)++;
			}
			break;
		case SDLK_f:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'F' : 'f'; 
				(*indice)++;
			}
			break;
		case SDLK_g:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'G' : 'g'; 
				(*indice)++;
			}
			break;
		case SDLK_h:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'H' : 'h'; 
				(*indice)++;
			}
			break;
		case SDLK_i:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'I' : 'i'; 
				(*indice)++;
			}
			break;
		case SDLK_j:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'J' : 'j'; 
				(*indice)++;
			}
			break;
		case SDLK_k:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'K' : 'k'; 
				(*indice)++;
			}
			break;
		case SDLK_l:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'L' : 'l'; 
				(*indice)++;
			}
			break;
		case SDLK_m:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'M' : 'm'; 
				(*indice)++;
			}
			break;
		case SDLK_n:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'N' : 'n'; 
				(*indice)++;
			}
			break;
		case SDLK_o:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'O' : 'o'; 
				(*indice)++;
			}
			break;
		case SDLK_p:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'P' : 'p'; 
				(*indice)++;
			}
			break;
		case SDLK_q:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'Q' : 'q'; 
				(*indice)++;
			}
			break;
		case SDLK_r:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'R' : 'r'; 
				(*indice)++;
			}
			break;
		case SDLK_s:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'S' : 's'; 
				(*indice)++;
			}
			break;
		case SDLK_t:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'T' : 't'; 
				(*indice)++;
			}
			break;
		case SDLK_u:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'U' : 'u'; 
				(*indice)++;
			}
			break;
		case SDLK_v:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'V' : 'v'; 
				(*indice)++;
			}
			break;
		case SDLK_w:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'W' : 'w'; 
				(*indice)++;
			}
			break;
		case SDLK_x:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'X' : 'x'; 
				(*indice)++;
			}
			break;
		case SDLK_y:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'Y' : 'y'; 
				(*indice)++;
			}
			break;
		case SDLK_z:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = *indice == 0 ? 'Z' : 'z'; 
				(*indice)++;
			}
			break;
		case SDLK_SPACE:
			if((*indice) < TAILLE_NOM - 1){
				name[*indice] = ' '; 
				(*indice)++;
			}
			break;
		case SDLK_BACKSPACE:
			if((*indice) > 0){
				(*indice)--;
				if((*indice) == 0)
					name[*indice] = '_';
				else
					name[*indice] = '\0';
			}
			break;
		case SDLK_RETURN:
			if((*indice) > 0)
				(*quit) = 1;
			break;
		case SDLK_ESCAPE:
			(*quit) = -1;
			break;
	}
}

/** Fonction d'entrée du nom */

char * entrerNom(SDL_Renderer * renderer){
	
	/** Déclarations des variables d'event et d'arrêt de la boucle */
	
	SDL_Event event;
	int quit = 0;
	
	/** Déclarations des chaînes de caractères de la fenêtre (en-tête et règles d'entrée du nom) */
	
	const char header[] = "Entrez le nom du golem :";
	const char rule1[] = "- Nom compris entre 1 et 19 caracteres";
	const char rule2[] = "- Appuyer sur Entree pour valider";
	const char rule3[] = "- Appuyer sur Echap pour entrer";
	const char rule4[] = "  un nom par defaut";
	
	/** Déclaration de la couleur blanche avec le type personalisé de SDL */
	
	const SDL_Color white = {255, 255, 255};
	
	/** Création des textures des textes déclarés plus haut */
	
	SDL_Texture * bgT = loadTexture("../Ressource/Menu/bgName.png", renderer);
	SDL_Texture * nameWindowT = loadTexture("../Ressource/Menu/nameWindow.png", renderer);
	SDL_Texture * headerT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, header, LETTER_HEIGHT, white);
	SDL_Texture * rule1T = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, rule1, LETTER_HEIGHT, white);
	SDL_Texture * rule2T = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, rule2, LETTER_HEIGHT, white);
	SDL_Texture * rule3T = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, rule3, LETTER_HEIGHT, white);
	SDL_Texture * rule4T = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, rule4, LETTER_HEIGHT, white);
	SDL_Texture * nameT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "_", LETTER_HEIGHT, white);
	
	/** Création et allocation des zones des textures + copie dans renderer */
	
	SDL_Rect bgR;
	bgR.w = WINDOW_WIDTH;
	bgR.h = WINDOW_HEIGHT;
	bgR.x = 0;
	bgR.y = 0;
	SDL_RenderCopy(renderer, bgT, NULL, &bgR);
	
	SDL_Rect nameWindowR;
	nameWindowR.w = 800;
	nameWindowR.h = 450;
	nameWindowR.x = (WINDOW_WIDTH - nameWindowR.w) / 2;
	nameWindowR.y = (WINDOW_HEIGHT - nameWindowR.h) / 2;
	SDL_RenderCopy(renderer, nameWindowT, NULL, &nameWindowR);
	
	SDL_Rect headerR;
	headerR.w = LETTER_WIDTH * strlen(header);
	headerR.h = LETTER_HEIGHT;
	headerR.x = nameWindowR.x + 30;
	headerR.y = nameWindowR.y + 20;
	SDL_RenderCopy(renderer, headerT, NULL, &headerR);
	
	SDL_Rect rule1R;
	rule1R.w = LETTER_WIDTH * strlen(rule1);
	rule1R.h = LETTER_HEIGHT;
	rule1R.x = nameWindowR.x + 30;
	rule1R.y = headerR.y + 60;
	SDL_RenderCopy(renderer, rule1T, NULL, &rule1R);
	
	SDL_Rect rule2R;
	rule2R.w = LETTER_WIDTH * strlen(rule2);
	rule2R.h = LETTER_HEIGHT;
	rule2R.x = nameWindowR.x + 30;
	rule2R.y = rule1R.y + 60;
	SDL_RenderCopy(renderer, rule2T, NULL, &rule2R);
	
	SDL_Rect rule3R;
	rule3R.w = LETTER_WIDTH * strlen(rule3);
	rule3R.h = LETTER_HEIGHT;
	rule3R.x = nameWindowR.x + 30;
	rule3R.y = rule2R.y + 60;
	SDL_RenderCopy(renderer, rule3T, NULL, &rule3R);
	
	SDL_Rect rule4R;
	rule4R.w = LETTER_WIDTH * strlen(rule4);
	rule4R.h = LETTER_HEIGHT;
	rule4R.x = nameWindowR.x + 30;
	rule4R.y = rule3R.y + 60;
	SDL_RenderCopy(renderer, rule4T, NULL, &rule4R);
	
	SDL_Rect nameR;
	nameR.w = LETTER_WIDTH;
	nameR.h = headerR.h;
	nameR.x = (WINDOW_WIDTH - LETTER_WIDTH) / 2;
	nameR.y = headerR.y + 360;
	
	/** Déclaration du nom et de l'indice d'écriture dans le nom */
	
	char * name = malloc(TAILLE_NOM * sizeof(char));
	int i;
	
	/** Premier bourrage de la chaîne du nom pour éviter un affichage de caractères aléatoires */
	
	name[0] = '_';
	for(i = 1; i < TAILLE_NOM; i++)
		name[i] = '\0';
	i = 0;
	
	/** Boucle d'entrée du nom */
	
	while(!quit){
		while(SDL_PollEvent(&event)){
			
			/** L'entrée de lettres s'activera au moment de l'appui sur une des touches disponibles (cf. fonction entrerLettre) */
			
			if(event.type == SDL_KEYUP){
				entrerLettre(event, name, &i, white, &quit);
				SDL_DestroyTexture(nameT);
				
				/** Pour éviter une erreur lorsque la largeur de la texture vaut 0, le premier caractère du nom vaut '_' lorsque celui-ci est vide */
				
				if(i == 0){
					name[0] == '_';
					nameR.w = LETTER_WIDTH;
					nameR.x = (WINDOW_WIDTH - LETTER_WIDTH) / 2;
				}
				else{
					nameR.w =  i * LETTER_WIDTH;
					nameR.x = (WINDOW_WIDTH - i * LETTER_WIDTH) / 2;
				}
				
				/** Écriture du nom sur l'écran */
				
				nameT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, name, LETTER_HEIGHT, white);
			}
		}
		
		/** Rafraîchissement de l'écran */
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgT, NULL, &bgR);
		SDL_RenderCopy(renderer, nameWindowT, NULL, &nameWindowR);
		SDL_RenderCopy(renderer, headerT, NULL, &headerR);
		SDL_RenderCopy(renderer, rule1T, NULL, &rule1R);
		SDL_RenderCopy(renderer, rule2T, NULL, &rule2R);
		SDL_RenderCopy(renderer, rule3T, NULL, &rule3R);
		SDL_RenderCopy(renderer, rule4T, NULL, &rule4R);
		SDL_RenderCopy(renderer, nameT, NULL, &nameR);
		SDL_RenderPresent(renderer);
	}
	
	/** Libération en mémoire des textures */
	
	SDL_DestroyTexture(headerT);
	SDL_DestroyTexture(rule1T);
	SDL_DestroyTexture(rule2T);
	SDL_DestroyTexture(rule3T);
	SDL_DestroyTexture(rule4T);
	SDL_DestroyTexture(nameT);
	SDL_DestroyTexture(nameWindowT);
	SDL_DestroyTexture(bgT);
	
	/** Appuyer sur échap retourne le nom "Golem" par défaut */
	
	if(quit == -1){
		for(i = 0; i < TAILLE_NOM; i++)
			name[i] = '\0';
		
		name[0] = 'G';
		name[1] = 'o';
		name[2] = 'l';
		name[3] = 'e';
		name[4] = 'm';
	}
	
	/** Bourrage de la place allouée non utilisée */
	
	for(int j = TAILLE_NOM - 1; j > i; j--)
			name[j] = '\0';
	
	/** Renvoi de l'adresse du nom */
	
	return name;
}

/** Fonction de sauvegarde de la progression */
void sauvegarder(int nb_save, int idMap, int x, int y, team_t team, inventaire_t inv,int lorePos, objet_t allPot[ALL_OBJETS], equipement_t allStuff[ALL_EQUIPEMENTS][3], arme_t allArmes[ALL_ARMES][3], SDL_Renderer * renderer, SDL_Texture * Map, SDL_Rect dest){
	
	/** Déclaration de l'image pour la fenêtre de la sauvegarde */
	
	SDL_Texture * saveWindowT = loadTexture("../Ressource/saveWindow.png", renderer);
	SDL_Rect saveWindowR;
	SDL_QueryTexture(saveWindowT, NULL, NULL, &saveWindowR.w, &saveWindowR.h);
	saveWindowR.x = (WINDOW_WIDTH - saveWindowR.w) / 2;
	saveWindowR.y = (WINDOW_HEIGHT - saveWindowR.h) / 2;
	
	/** Déclaration des images textuelles pendant et après la sauvegarde */
	
	const SDL_Color white = {255,255,255};
	
	SDL_Texture * savingT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "Sauvegarde en cours...", 50, white);
	SDL_Rect savingR;
	savingR.w = 460;
	savingR.h = 50;
	savingR.x = (WINDOW_WIDTH - savingR.w) / 2;
	savingR.y = (WINDOW_HEIGHT - savingR.h) / 2;
	
	SDL_Texture * savedT = loadTextureFont("../Ressource/font/BlockKie.ttf", renderer, "Progression sauvegardee.", 50, white);
	SDL_Rect savedR;
	savedR.w = 500;
	savedR.h = 50;
	savedR.x = (WINDOW_WIDTH - savedR.w) / 2;
	savedR.y = (WINDOW_HEIGHT - savedR.h) / 2;
	
	/** Ouverture du fichier contenant la sauvegarde */
	
	char path[20];
	sprintf(path, "../.saves/save%d.txt", nb_save);
	FILE * save = fopen(path, "w");
	
	/** Déclaration des indices */
	
	int i, j;
	
	/** Affichage du texte pendant la sauvegarde */
	
	SDL_RenderClear(renderer);
	afficher_map(dest.x,dest.y,renderer,Map);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, NULL);
	SDL_RenderCopy(renderer, saveWindowT, NULL, &saveWindowR);
	SDL_RenderCopy(renderer, savingT, NULL, &savingR);
	SDL_RenderPresent(renderer);
	
	/** Sauvegarde de la dernière carte du monde chargée ainsi que la position du personnage dessus */
	
	fprintf(save, "%d_%d_%d\n", idMap, x, y);
	
	/** Sauvegarde des personnages et de leurs statistiques */
	
	fprintf(save, "%d\n", team.nbPerso);
	for(i = 0; i < team.nbPerso; i++)
		fprintf(save, "%s_%s_%d_%d_%d_%d_%.1f_%.1f_%.1f_%.1f_%.1f_%.1f_%.1f_%.1f_%.1f_#\n", team.team[i] -> Nom, team.team[i] -> Classe, team.team[i] -> lvl, team.team[i] -> Xplvl, team.team[i] -> Xp, team.team[i] -> PtComp, team.team[i] -> PvMax, team.team[i] -> Pv, team.team[i] -> ManaMax, team.team[i] -> Mana, team.team[i] -> Def, team.team[i] -> Res, team.team[i] -> For, team.team[i] -> Int, team.team[i] -> Vit);
        
        /** Sauvegarde des objets de l'inventaire (potions) */
        
        fprintf(save, "%d\n", inv.nbObjActu);
	for(i = 0; i < inv.nbObjActu; i++){
	        for(j = 0; strcmp(inv.sac[i] -> nom, allPot[j].nom); j++);
	        fprintf(save, "%d_", j);
	}
	fprintf(save, "-1_%d_#\n", inv.bourse);
	
	/** Sauvegarde de l'équipement de l'inventaire (armure) et de la bourse (montant de la monnaie du jeu) */
	
	fprintf(save, "%d\n", inv.nbEquActu);
	for(i = 0; i < inv.nbEquActu; i++){
	        for(j = 0; strcmp(inv.equipements[i] -> nom, allStuff[j] -> nom); j++);
	        fprintf(save, "%d_", j);
        }
        fprintf(save, "-1_#\n");
	
	/** Sauvegarde des armes de l'inventaire */
	
	fprintf(save, "%d\n", inv.nbArmActu);
	for(i = 0; i < inv.nbArmActu; i++){
	        for(j = 0; strcmp(inv.armes[i] -> nom, allArmes[j] -> nom); j++);
	        fprintf(save, "%d_", j);
	}
	fprintf(save, "-1_#\n");
	
	/** Sauvegarde de l'avancement dans l'histoire du jeu */
	
	fprintf(save, "%d", lorePos);
	
	/** Affichage du texte après la sauvegarde */
	
	SDL_RenderClear(renderer);
	afficher_map(dest.x,dest.y,renderer,Map);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
	SDL_RenderFillRect(renderer, NULL);
	SDL_RenderCopy(renderer, saveWindowT, NULL, &saveWindowR);
	SDL_RenderCopy(renderer, savedT, NULL, &savedR);
	SDL_RenderPresent(renderer);
	
	/** Affichage du texte jusqu'à qu'un clic de souris soit détecté */
	
	SDL_Event event;
	while(event.type != SDL_MOUSEBUTTONUP)
	        SDL_PollEvent(&event);
	
	/** Destruction des textures */
	
	SDL_DestroyTexture(savingT);
	SDL_DestroyTexture(savedT);
	SDL_DestroyTexture(saveWindowT);
	
	/** Fermeture du fichier contenant la sauvegarde */
	
	fclose(save);
}

/** Fonction de chargement de la sauvegarde */
void chargerSave(int nb_save, int * idMap, int * x, int * y, team_t * team, inventaire_t * inv, int * lorePos, objet_t allPot[ALL_OBJETS], equipement_t allStuff[ALL_EQUIPEMENTS][3], perso_t allPerso[NB_TEAM_PERSOS], arme_t allArmes[ALL_ARMES][3], float stats[NB_TEAM_PERSOS][8], SDL_Renderer * renderer){
	
	/** Ouverture du fichier contenant la sauvegarde */
	
	char path[20];
	sprintf(path, "../.saves/save%d.txt", nb_save);
	FILE * save = fopen(path, "r");
	
	/** Déclaration des indices, de l'élément courant et du caractère courant lors de la lecture du fichier */
	
	int i, j, ec = 0;
	char cc = '\0';
	
	/** Déclaration des variables provisoires permettant la lecture des statistiques */
	
	char nom[TAILLE_NOM];
	char classe[20];
	int lvl, xp, xplvl, ptcomp,nb;
	float pvmax, pv, manamax, mana, def, res, For, Int, vit;
	
	/** Chargement de la dernière carte du monde sauvegardée ainsi que la position du personnage dessus */
	
	fscanf(save, "%d_%d_%d\n", idMap, x, y);
	
	/** Chargement des personnages et de leurs statistiques */
	
	fscanf(save, "%d\n", &nb);
	for(i = 0; i < nb; i++){
		for(j = 0; j < 20; j++){
		        nom[j] = '\0';
		        classe[j] = '\0';
		}
        	cc = '\0';
		for(j = 0; cc != '_'; j++){
		        cc = fgetc(save);
		        if(cc != '_')
        		        nom[j] = cc;
        	}
        	
        	cc = '\0';
		for(j = 0; cc != '_'; j++){
		        cc = fgetc(save);
		        if(cc != '_')
        		        classe[j] = cc;
        	}
		fscanf(save, "%d_%d_%d_%d_%f_%f_%f_%f_%f_%f_%f_%f_%f_#\n", &lvl, &xplvl, &xp, &ptcomp, &pvmax, &pv, &manamax, &mana, &def, &res, &For, &Int, &vit);
		creer_perso(&allPerso[i], nom, classe, renderer, stats[i]);
		allPerso[i].lvl=lvl;
		allPerso[i].Xplvl=xplvl;
		allPerso[i].PvMax=stats[i][0] = pvmax;
		allPerso[i].Pv=pv;
		allPerso[i].ManaMax=stats[i][1] = manamax;
		allPerso[i].Mana=mana;
		allPerso[i].For=stats[i][2] = For;
		allPerso[i].Def=stats[i][3] = def;
		allPerso[i].Int=stats[i][4] = Int;
		allPerso[i].Res=stats[i][5] = res;
		allPerso[i].Vit=stats[i][6] = vit;
		allPerso[i].PtComp=stats[i][7] = ptcomp;
		join_team(team, allPerso);
	}
	
	/** Chargement des objets de l'inventaire (potions) */
	
	fscanf(save, "%d\n", &nb);
	for(i = 0; i <= nb; i++){
	        fscanf(save, "%d_", &ec);
	        if(ec != -1)
	                ajouter_obj(inv, allPot, ec);
	}
	fscanf(save, "%d_#\n", &(inv -> bourse));
	
	/** Chargement de l'équipement de l'inventaire (armure) et de la bourse (montant de la monnaie du jeu) */
	
	fscanf(save, "%d\n", &nb);
	for(i = 0; i <= nb; i++){
	        fscanf(save, "%d_", &ec);
	        if(ec != -1)
	                ajouter_stuff(allStuff, inv, ec);
        }
        
        /** Chargement des armes de l'inventaire */
        
        fscanf(save, "#\n%d\n", &nb);
	for(i = 0; i <= nb; i++){
	        fscanf(save, "%d_", &ec);
	        if(ec != -1)
	                ajouter_arme(allArmes, inv, ec);
        }
        
        /** Chargement de l'avancement dans l'histoire du jeu */
        
        fscanf(save, "#\n%d", lorePos);
        
        /** Fermeture du fichier contenant la sauvegarde */
        
	fclose(save);
}

/** Fonction d'initialisation de la sauvegarde */
void nouvelleSave(int nb_save, char * nom){
	
	/** Création du dossier contenant les sauvegardes */
	
	mkdir("../.saves", 0755);
	
	/** Ouverture du fichier d'initialisation de la sauvegarde */
	
        char path[20];
	sprintf(path, "../.saves/save%d.txt", nb_save);
	FILE * save = fopen(path, "w");
	
	/** Initialisation de la première carte du monde ainsi que la position du personnage au départ */
	
	fprintf(save, "0_1056_640\n");
	
	/** Initialisation du personnage de départ et de ses statistiques */
	
	fprintf(save, "1\n");
	fprintf(save, "%s_Golem_1_20_0_0_30_30_0_0_15_5_15_0_5_#\n", nom);
	
	/** Intialisation de l'emplacement des objets de l'inventaire (potions) */
	
	fprintf(save, "0\n");
	fprintf(save, "-1_0_#\n");
	
	/** Intialisation de l'emplacement de l'équipement de l'inventaire (armure) et de la bourse (montant de la monnaie du jeu) */
	
	fprintf(save, "0\n");
	fprintf(save, "-1_#\n");
	
	/** Initialisation de l'emplacement des armes de l'inventaire */
	
	fprintf(save, "0\n");
	fprintf(save, "-1_#\n");
	
	/** Initialisation de la valeur représentant l'avancement dans l'histoire du jeu */
	
	fprintf(save, "0");
	
	/** Fermeture du fichier d'initialisation de la sauvegarde */
	
	fclose(save);
}
