/**
* \file fbibliothèque.c
* \brief programme gérant la Map de la bibliothèque
* \author François Lépine.
* \version 1.8.6
* \date 16 Avril 2024.
*/

#include <string.h>
#include "../lib/fbibliotheque.h"

int charger_map_biblio(char * CARTE_LIGNE,char * CARTE_TXT,char * nom_carte, int tab[125][250]){

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
                case 0:tab[j][i]=1;
                    break;
                case 7:tab[j][i]=3;
                    break;
                default:tab[j][i]=0;
                        break;
            }
        }
    }

    /** Fermeture du fichier*/
    fclose(fichier);

    /** Sauvegarde de la carte en png*/
    saveSurfaceAsPNG(combinedSurface, nom_carte);
    SDL_FreeSurface(combinedSurface);
    SDL_FreeSurface(tileset);
    return 0;
}

int charger_map_pnj_biblio(char * PNJ_LIGNE,char * PNJ_TXT,char * MAP,char * nom_carte,int collisions[125][250]){

    /** Ouverture du fichier */
    FILE *fichier = fopen(PNJ_TXT, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    /** Ouvre le fichier pnj_ligne qui contient les pnj */
    SDL_Surface* PNJS = loadTileset(PNJ_LIGNE);
    if (!PNJS) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE = loadTileset(MAP);
    if (!CARTE) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }


    /** Variables pour stocker les nombres */
    int quel_pnj,coordo_pnj_x,coordo_pnj_y;

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

    /** Parcours du fichier contenant la carte en numéro de tuile*/
    for(j=0;j<hauteur;j++)
    {

        for(i=0;i<largeur;i++)
        {
            fscanf(fichier, "%d", &quel_pnj);
            fscanf(fichier, "%d", &coordo_pnj_x);
            fscanf(fichier, "%d", &coordo_pnj_y);

            collisions[coordo_pnj_y][coordo_pnj_x]=15;
            

            sourceRect.x=quel_pnj*32;
            destRect.x=coordo_pnj_x*32;
            destRect.y=coordo_pnj_y*32;


            /** Affichage de la tuile */
            SDL_BlitSurface(PNJS, &sourceRect,CARTE, &destRect);
        }
    }
    
    /** Fermeture du fichier*/
    fclose(fichier);

    /** Sauvegarde de la carte en png*/
    saveSurfaceAsPNG(CARTE, nom_carte);

    SDL_FreeSurface(CARTE);
    SDL_FreeSurface(PNJS);
    return 0;
}