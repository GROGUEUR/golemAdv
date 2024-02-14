#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/**
* déclaration de la fonction loadTexture qui prend en parametre le chemin de l'image et le renderer
*/
SDL_Texture* loadTexture(const char* , SDL_Renderer* );

#endif

