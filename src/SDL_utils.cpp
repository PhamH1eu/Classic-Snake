#include "SDL_utils.h"

void quitSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, Mix_Music*& music, Mix_Chunk*& chunk)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	
    window = SDL_CreateWindow("Classic Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );

	if (TTF_Init() < 0)	
		SDL_Log("%s", TTF_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		printf("%s", Mix_GetError());

	music = Mix_LoadMUS("./gallery/background_music.mp3");
	if (music == NULL)
		printf("%s", Mix_GetError());
	
	chunk = Mix_LoadWAV("./gallery/eat_sound.wav");
	if (chunk == NULL)
		printf("%s", Mix_GetError());
	
}

char* imgDirectory(std::string s)
{
	return &s[0];
}

SDL_Texture* loadTexture(SDL_Renderer* renderer,char* filename)
{
	SDL_Texture* texture;
	texture = IMG_LoadTexture(renderer, filename);
	return texture;
}

void blit(SDL_Renderer* renderer ,SDL_Texture* texture, SDL_Rect dest)
{
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void draw_Wall(SDL_Window* window, SDL_Renderer* renderer)
{
	for (int i=0;i<WIDTH/16;i++) 
	{
		SDL_Rect r_top{ 32*i, 0, 32, 16};
		SDL_Rect r_bot{ 32*i, HEIGHT-16, 32, 16};
		char* filename_horizontal=imgDirectory("./gallery/wall_horizontal.bmp");
		SDL_Texture* texture_horizontal = loadTexture(renderer,filename_horizontal);
		blit(renderer,texture_horizontal,r_top);
		blit(renderer,texture_horizontal,r_bot);
		SDL_DestroyTexture(texture_horizontal);
	}
	
	for (int i=0;i<HEIGHT/16;i++)
	{ 
		SDL_Rect r_left{ 0, 32*i, 16, 32};
		SDL_Rect r_right{ WIDTH-16, 32*i, 16, 32};
		char* filename_vertical=imgDirectory("./gallery/wall_vertical.bmp");
		SDL_Texture* texture_vertical = loadTexture(renderer,filename_vertical);
		blit(renderer,texture_vertical,r_left);
		blit(renderer,texture_vertical,r_right);
		SDL_DestroyTexture(texture_vertical);
	}
}

void draw_Background(SDL_Window* window, SDL_Renderer* renderer)
{
	char* s=imgDirectory("./gallery/background.bmp");
	SDL_Texture* texture=loadTexture(renderer,s);
	SDL_RenderCopy(renderer,texture,NULL,NULL);
	SDL_DestroyTexture(texture);
}

void show_score(SDL_Renderer* renderer, std::string s)
{
	TTF_Font* font = TTF_OpenFont("./fonts/gameFonts.ttf", 50);
	SDL_Color color = { 0, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, &s[0], color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { WIDTH/2-100, HEIGHT/2, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void show_endGame(SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("./fonts/gameFonts.ttf", 50);
	SDL_Color color = { 0, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, "Game Over!", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { WIDTH/2-100, HEIGHT/2-50, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
