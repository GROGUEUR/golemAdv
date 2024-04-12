#include <string.h>
#include "../lib/fmap.h"

SDL_Surface* loadTileset(const char* filename) {
    return IMG_Load(filename);
}

int saveSurfaceAsPNG(SDL_Surface* surface, const char* filename) {
    
    if (!surface) {
        SDL_Log("Surface invalide.");
        return -1;
    }

    int success = IMG_SavePNG(surface, filename);
    if (success == -1) {
        SDL_Log("Erreur lors de l'enregistrement de l'image : %s", IMG_GetError());
        return -1;
    }

    return 0;
}

int * charger_map(char * CARTE_LIGNE,char * CARTE_TXT,char * nom_carte){

    /** Ouverture du fichier */
    FILE *fichier = fopen(CARTE_TXT, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    /** Ouvre le fichier tuiles_plaine qui contient les tuiles */
    SDL_Surface* tileset = loadTileset(CARTE_LIGNE);
    if (!tileset) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }


    /** Variables pour stocker les nombres */
    int nombre;

    /** Définir la portion de l'image à afficher */
    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 32;  /** Largeur de la portion à afficher */
    sourceRect.h = 32;  /** Hauteur de la portion à afficher */

    /** Définir le rectangle de destination */
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = sourceRect.w;  /** Utiliser la même largeur que la source */
    destRect.h = sourceRect.h;  /** Utiliser la même hauteur que la source */

    int hauteur;
    int largeur;

    int i,j;
    
    /** Recuperation de la largeur det de la hauteur*/
    fscanf(fichier, "%d", &largeur);
    fscanf(fichier, "%d", &hauteur);

    int tab[hauteur][largeur];

    /** Creation de la variable qui va creer le .png contenant l'image de la map*/
    SDL_Surface* combinedSurface = SDL_CreateRGBSurface(0, largeur*32, hauteur*32, 32, 0, 0, 0, 0);

    /** Parcours du fichier contenant la carte en numéro de tuile*/
    for(j=0;j<hauteur;j++)
    {
        destRect.y = j*32;
        for(i=0;i<largeur;i++)
        {
            fscanf(fichier, "%d", &nombre);

            /** Decalage de l'affichage (x et y) sur la map pour pouvoir afficher toute la map */
            sourceRect.x=32*nombre;
            destRect.x=i*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(tileset, &sourceRect, combinedSurface, &destRect);

            /** On va pour chaque tuile enregistrer dans un tableau */
            switch(nombre)
            {
                case 2:tab[j][i]=2;
                        break;
                case 3:tab[j][i]=0;
                        break;
                case 4:tab[j][i]=0;
                        break;
                case 14:tab[j][i]=0;
                        break;
                case 29:tab[j][i]=0;
                        break;
                case 30:tab[j][i]=0;
                        break;
                case 31:tab[j][i]=3;
                        break;
                case 32:tab[j][i]=0;
                        break;
                case 33:tab[j][i]=0;
                        break;
                case 34:tab[j][i]=0;
                        break;
                case 35:tab[j][i]=0;
                        break;
                case 36:tab[j][i]=0;
                        break;
                case 37:tab[j][i]=0;
                        break;
                case 38:tab[j][i]=0;
                        break;
                case 39:tab[j][i]=0;
                        break;
                case 40:tab[j][i]=0;
                        break;
                case 41:tab[j][i]=0;
                        break;
                case 42:tab[j][i]=0;
                        break;
                case 43:tab[j][i]=0;
                        break;
                case 44:tab[j][i]=0;
                        break;
                case 45:tab[j][i]=0;
                        break;
                default:tab[j][i]=1;
                        break;
            }
        }
    }
    
    /** Fermeture du fichier*/
    fclose(fichier);

    /** Sauvegarde de la carte en png*/
    saveSurfaceAsPNG(combinedSurface, nom_carte);

    return tab;
}

int afficher_map(int coordo_x,int coordo_y,SDL_Renderer* renderer,char * MAP){

    /** Chargement de l'image */
    SDL_Surface* imageSurface = IMG_Load(MAP);
    if (!imageSurface) {
        printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return 1;
    }

    /** Conversion de l'image en texture */
    SDL_Texture* texture_carte = SDL_CreateTextureFromSurface(renderer, imageSurface);

    /** Libération de la surface de l'image*/
    SDL_FreeSurface(imageSurface);

    /** Définir la portion de l'image à afficher */
    SDL_Rect sourceRect;
    sourceRect.x = coordo_x-(WINDOW_WIDTH/2);
    sourceRect.y = coordo_y-(WINDOW_HEIGHT/2);
    sourceRect.w = WINDOW_WIDTH;  /** Largeur de la portion à afficher */
    sourceRect.h = WINDOW_HEIGHT;  /** Hauteur de la portion à afficher */

    /** Définir le rectangle de destination */
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = sourceRect.w;  /** Utiliser la même largeur que la source */
    destRect.h = sourceRect.h;  /** Utiliser la même hauteur que la source */

    SDL_RenderCopy(renderer, texture_carte, &sourceRect, &destRect);
}