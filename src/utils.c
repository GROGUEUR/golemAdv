/**
* \file utils.c
* \brief programme gérant le menu pour rentrer un pseudo.
* \author Warrick Bonga.
* \version 1.8.6
* \date 12 Avril 2024.
*/

#include "../lib/type.h"
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
			
			if(event.type == SDL_KEYDOWN){
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
