#include "../lib/texture.h"
/**
* fonction loadTexture qui s'occupera de charger l'image en avec une surface
* puis d'utiliser cet surface pour créer une texture
* la fonction renvoie NULL si il y a une erreur sinon renvoie la texture créer
*/
SDL_Texture* loadTexture(const char* chemin, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(chemin);
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "Erreur 1 lors de la création de la texture : %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}
