/**
* \file texture.c
* \brief programme gérant les fonction de chargement de texture.
* \author Luka Cognard.
* \version 1.8.6
* \date 12 Avril 2024.
*/

#include "../lib/texture.h"
/**
* fonction loadTexture qui s'occupera de charger l'image avec une surface
* puis d'utiliser cet surface pour créer une texture
* la fonction renvoie NULL si il y a une erreur sinon renvoie la texture créer
*/
SDL_Texture* loadTexture(const char* chemin, SDL_Renderer* renderer) {
    /** créer la surface de l'image si ça na pas marcher renvoie NULL avec une erreur */
    SDL_Surface* surface = IMG_Load(chemin);
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return NULL;
    }

    /** créer la texture de l'image a partir de ça surface puis libère la surface inutiliser 
    * si la texture n'est pas créer renvoie NULL avec une erreur 
    */
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        fprintf(stderr, "Erreur 1 lors de la création de la texture : %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

/**
* fonction loadTextureFont qui s'occupera de charger le texte avec une surface
* puis d'utiliser cet surface pour créer une texture
* la fonction renvoie NULL si il y a une erreur sinon renvoie la texture créer
*/
SDL_Texture* loadTextureFont(const char* chemin, SDL_Renderer* renderer,const char* text,int h,SDL_Color color){
    /** charge la police d'écriture via le chemin entré en paramètre 
    * si ça n'as pas marcher renvoie NULL avec une erreur
    */
    SDL_RWops* rw = SDL_RWFromFile(chemin, "rb");
    TTF_Font* font = TTF_OpenFontIndexRW(rw, 1, h, 0);
    if (!font) {
        fprintf(stderr, "Impossible de charger la police : %s\n", TTF_GetError());
        return NULL;
    }
    
    /** créer la surface du texte via le text entrée en paramètre 
    * libère la police charger inutiliser
    * si ça na pas marcher renvoie NULL avec une erreur 
    */
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,text,color);
    TTF_CloseFont(font);
    if (!textSurface) {
        fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
        printf("de %s\n",text);
        return NULL;
    }
    
    /** créer la texture du texte a partir de ça surface puis libère la surface inutiliser 
    * si la texture n'est pas créer renvoie NULL avec une erreur 
    */
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
        return NULL;
    }
    return textTexture;
}
