#include "SDL_utils.h"
#include "Food.h"
#include "Snake.h"

int main(int argc, char* args[]) 
{
	srand(std::time(NULL));

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL; 
	SDL_Event event;
	Mix_Music* music = NULL;
	Mix_Chunk* chunk = NULL;

	initSDL(window,renderer,music,chunk);
	
	Mix_PlayMusic(music, -1);

	bool running = true;
	Snake game_snake = {};
	Food food = {};
	food.move();
	
	while (running) 
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT) 
			{
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) game_snake.changeDirection(event);
		}

		draw_Background(window,renderer);
		draw_Wall(window,renderer);
		game_snake.update(food,chunk,renderer);
		game_snake.draw(window,renderer);
		food.draw(window,renderer);

		SDL_RenderPresent(renderer);
		if (game_snake.dead == true) SDL_Delay(3000);
	}
	
	quitSDL(window,renderer);
	return 0;
}

