/**
* \file texture.h
* \brief programme gérant les fonctions pour le chargement des textures
* \author Luka Cognard.
* \version 1.9.5
* \date 16 Avril 2024.
*/

#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/**
* déclaration de la fonction loadTexture qui prend en parametre le chemin de l'image et le renderer
* déclaration de la fonction loadTextureFont qui prend en parametre le chemin de la police d'écriture,
* le renderer, le texte a afficher, la taille de police et la couleur du texte
*/
SDL_Texture* loadTexture(const char* , SDL_Renderer* );
SDL_Texture* loadTextureFont(const char* , SDL_Renderer* ,const char*,int,SDL_Color);
#endif

