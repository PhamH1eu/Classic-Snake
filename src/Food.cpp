#include "Food.h"
#include "SDL_utils.h" 

void Food::move() 
{
		x = rand() % ( WIDTH / 16 -2 ) + 1;
		y = rand() % ( HEIGHT / 16 -2 ) + 1;
}

void Food::draw(SDL_Window* window, SDL_Renderer* renderer) 
{
		char* filename=imgDirectory("./gallery/apple.bmp");
		SDL_Texture* texture = loadTexture(renderer,filename);
		SDL_Rect r{ 16 * x, 16 * y, 16, 16 };
		blit(renderer,texture,r);
		SDL_DestroyTexture(texture);
}
