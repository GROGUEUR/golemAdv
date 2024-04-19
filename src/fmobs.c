/**
* \file fmobs.c
* \brief programme gérant les mobs
* \author François Lépine.
* \version 1.9.5
* \date 16 Avril 2024.
*/
#include <string.h>
#include "../lib/type.h"
#include "../lib/fmobs.h"
#include "../lib/fmap.h"

int copie_fichier_mob_txt(char * fichier_mob_origine,char* fichier_mob_destination){
    /** Ouvrir le fichier destination en mode lecture */
    FILE * source = fopen(fichier_mob_origine, "r");

    char caractere;

    if (source == NULL) {
        printf("Erreur lors de l'ouverture du fichier source.");
        return 1;
    }

    /** Ouvrir le fichier destination en mode écriture */
    FILE * destination = fopen(fichier_mob_destination, "w");

    if (destination == NULL) {
        printf("Erreur lors de l'ouverture du fichier destination.");
        fclose(source);
        return 1;
    }

    /** Copier le contenu du fichier source vers le fichier destination */
    while ((caractere = fgetc(source)) != EOF) {
        fputc(caractere, destination);
    }

    /** Fermer les fichiers */
    fclose(source);
    fclose(destination);

    return 0;
}

int charger_map_mobs(char * MOBS_LIGNE,char * MOBS_TXT,char * MOBS_TXT2,char * MAP,int collisions[125][250]){

    /** Ouvre le fichier mobs_ligne qui contient les créatures */
    SDL_Surface* MOBS = loadTileset(MOBS_LIGNE);
    if (!MOBS) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE1 = loadTileset(MAP);
    if (!CARTE1) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE2 = loadTileset(MAP);
    if (!CARTE2) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE3 = loadTileset(MAP);
    if (!CARTE3) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE4 = loadTileset(MAP);
    if (!CARTE4) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE5 = loadTileset(MAP);
    if (!CARTE5) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Ouvre le fichier de la carte du jeu pour y ajouter les pnj */
    SDL_Surface* CARTE6 = loadTileset(MAP);
    if (!CARTE6) {
        /** Gestion de l'erreur */
        SDL_Log("Impossible de charger le tileset : %s", SDL_GetError());
        return 0;
    }

    /** Variables pour stocker les nombres */
    int quel_mob,coordo_mob_x,coordo_mob_y;

    /** Définir la portion de l'image à afficher */
    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 32;  /** Largeur de la portion à afficher */
    /** Les monstres ont un sprite contenant 6 animations */
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
    
    /** Ouverture du fichier */
    FILE *fichier2 = fopen(MOBS_TXT2, "r");
    if (fichier2 == NULL) {
        FILE *fichier = fopen(MOBS_TXT, "r");
        if(fichier==NULL){
            printf("Impossible de charger le fichier.\n");

            SDL_FreeSurface(CARTE1);
            SDL_FreeSurface(CARTE2);
            SDL_FreeSurface(CARTE3);
            SDL_FreeSurface(CARTE4);
            SDL_FreeSurface(CARTE5);
            SDL_FreeSurface(CARTE6);
            SDL_FreeSurface(MOBS);

            return 0;
        }
        /** Recuperation de la largeur det de la hauteur*/
        fscanf(fichier, "%d", &largeur);
        fscanf(fichier, "%d", &hauteur);

        /** Parcours du fichier contenant la carte en numéro de tuile*/
        for(j=0;j<hauteur;j++)
        {

            for(i=0;i<largeur;i++)
            {
                fscanf(fichier, "%d", &quel_mob);
                fscanf(fichier, "%d", &coordo_mob_x);
                fscanf(fichier, "%d", &coordo_mob_y);

                /** Dans le tableau de collisions il y aura 3 créatures, chacune d'elles auront une seule et même configuration */
                if(quel_mob==0){
                    collisions[coordo_mob_y][coordo_mob_x]=8;
                }
                else if(quel_mob==1){
                    collisions[coordo_mob_y][coordo_mob_x]=9;
                }
                else if(quel_mob==2){
                    collisions[coordo_mob_y][coordo_mob_x]=10;
                }

                sourceRect.x=0;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE1, &destRect);

                sourceRect.x=32;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE2, &destRect);

                sourceRect.x=32*2;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE3, &destRect);

                sourceRect.x=32*3;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE4, &destRect);

                sourceRect.x=32*4;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE5, &destRect);

                sourceRect.x=32*5;
                sourceRect.y=quel_mob*32;
                destRect.x=coordo_mob_x*32;
                destRect.y=coordo_mob_y*32;

                /** Affichage de la tuile */
                SDL_BlitSurface(MOBS, &sourceRect,CARTE6, &destRect);
            }
        }
        
        /** Fermeture du fichier*/
        fclose(fichier);

        /** Sauvegarde de la carte en png*/
        saveSurfaceAsPNG(CARTE1, "../Ressource/Mapping/map/map1.png");
        saveSurfaceAsPNG(CARTE2, "../Ressource/Mapping/map/map2.png");
        saveSurfaceAsPNG(CARTE3, "../Ressource/Mapping/map/map3.png");
        saveSurfaceAsPNG(CARTE4, "../Ressource/Mapping/map/map4.png");
        saveSurfaceAsPNG(CARTE5, "../Ressource/Mapping/map/map5.png");
        saveSurfaceAsPNG(CARTE6, "../Ressource/Mapping/map/map6.png");

        SDL_FreeSurface(CARTE1);
        SDL_FreeSurface(CARTE2);
        SDL_FreeSurface(CARTE3);
        SDL_FreeSurface(CARTE4);
        SDL_FreeSurface(CARTE5);
        SDL_FreeSurface(CARTE6);
        SDL_FreeSurface(MOBS);

        return 0;
    }

    /** Recuperation de la largeur det de la hauteur*/
    fscanf(fichier2, "%d", &largeur);
    fscanf(fichier2, "%d", &hauteur);

    /** Parcours du fichier contenant la carte en numéro de tuile*/
    for(j=0;j<hauteur;j++)
    {

        for(i=0;i<largeur;i++)
        {
            fscanf(fichier2, "%d", &quel_mob);
            fscanf(fichier2, "%d", &coordo_mob_x);
            fscanf(fichier2, "%d", &coordo_mob_y);

            /** Dans le tableau de collisions il y aura 3 créatures, chacune d'elles auront une seule et même configuration */
            if(quel_mob==0){
                collisions[coordo_mob_y][coordo_mob_x]=8;
            }
            else if(quel_mob==1){
                collisions[coordo_mob_y][coordo_mob_x]=9;
            }
            else if(quel_mob==2){
                collisions[coordo_mob_y][coordo_mob_x]=10;
            }

            sourceRect.x=0;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE1, &destRect);

            sourceRect.x=32;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE2, &destRect);

            sourceRect.x=32*2;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE3, &destRect);

            sourceRect.x=32*3;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE4, &destRect);

            sourceRect.x=32*4;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE5, &destRect);

            sourceRect.x=32*5;
            sourceRect.y=quel_mob*32;
            destRect.x=coordo_mob_x*32;
            destRect.y=coordo_mob_y*32;

            /** Affichage de la tuile */
            SDL_BlitSurface(MOBS, &sourceRect,CARTE6, &destRect);
        }
    }
    
    /** Fermeture du fichier*/
    fclose(fichier2);

    /** Sauvegarde de la carte en png*/
    saveSurfaceAsPNG(CARTE1, "../Ressource/Mapping/map/map1.png");
    saveSurfaceAsPNG(CARTE2, "../Ressource/Mapping/map/map2.png");
    saveSurfaceAsPNG(CARTE3, "../Ressource/Mapping/map/map3.png");
    saveSurfaceAsPNG(CARTE4, "../Ressource/Mapping/map/map4.png");
    saveSurfaceAsPNG(CARTE5, "../Ressource/Mapping/map/map5.png");
    saveSurfaceAsPNG(CARTE6, "../Ressource/Mapping/map/map6.png");

    SDL_FreeSurface(CARTE1);
    SDL_FreeSurface(CARTE2);
    SDL_FreeSurface(CARTE3);
    SDL_FreeSurface(CARTE4);
    SDL_FreeSurface(CARTE5);
    SDL_FreeSurface(CARTE6);
    SDL_FreeSurface(MOBS);
    return 0;
}

int detruire_mob(int coordo_x_mob_suppr,int coordo_y_mob_suppr,char * MOBS_TXT,int collisions[125][250]){

	 /** Ouverture du fichier */

	 FILE *source = fopen(MOBS_TXT, "r");

	 if (source == NULL) {

		 perror("Erreur lors de l'ouverture du fichier");

		 return 0;

	 }

	 int hauteur,largeur;

	 fscanf(source,"%d %d",&largeur,&hauteur);

	 int type_mob;

	 /** Ouvrir un fichier temporaire en mode écriture */

	 FILE *temp = fopen("temp.txt", "w");

	 if (temp == NULL) {

		 printf("Erreur lors de l'ouverture du fichier temporaire.");

		 fclose(source);

		 return 1;

	 }

	 fprintf(temp,"%d %d\n",largeur,hauteur-1);

	 /** Lire chaque ligne du fichier source */

	 for (int i=0;i<hauteur;i++) {

		 int coordo1, coordo2;

		 /** Extraire les deux derniers chiffres de la ligne */

		 fscanf(source, "%d %d %d",&type_mob ,&coordo1, &coordo2);

		 /** Si les deux derniers chiffres ne correspondent pas à ceux spécifiés, écrire la ligne dans le fichier temporaire */

		 if (coordo1 != coordo_x_mob_suppr || coordo2!= coordo_y_mob_suppr) { 

			 fprintf(temp,"%d %d %d\n",type_mob,coordo1,coordo2);

		 }
	 }

	 collisions[coordo_y_mob_suppr][coordo_x_mob_suppr]=1;

	 /** Fermer les fichiers */

	 fclose(source);

	 fclose(temp);

	 /** Supprimer le fichier source */

	 remove(MOBS_TXT);

	 /** Renommer le fichier temporaire pour qu'il devienne le nouveau fichier source */

	 rename("temp.txt", MOBS_TXT);

	 return 0;

}
