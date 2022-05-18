#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#define WIDTH 800	
#define HEIGHT 600

void quitSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, Mix_Music*& music, Mix_Chunk*& chunk);

char* imgDirectory(std::string s);

SDL_Texture* loadTexture(SDL_Renderer* renderer,char* filename);

void blit(SDL_Renderer* renderer ,SDL_Texture* texture, SDL_Rect dest);

void draw_Wall(SDL_Window* window, SDL_Renderer* renderer);

void draw_Background(SDL_Window* window, SDL_Renderer* renderer);

void show_score(SDL_Renderer* renderer, std::string s);
void show_endGame(SDL_Renderer* renderer);

