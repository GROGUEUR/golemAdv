#ifndef EVENTOP_H
#define EVENTOP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/**
* déclaration des fonctions DetectEventsOp et ReactEventsOp
*/
void DetectEventsOp(int* , int* );
void ReactEventsOp(int,SDL_Renderer* ,SDL_Texture* ,SDL_Rect*,SDL_Rect* ,int*);
#endif

