#pragma once
#include "SDL_utils.h"
#include <vector>
struct Point 
{
	int x, y;
};

struct Snake
{
	std::vector<Point> snake ={ {1,1} };
	Point head={WIDTH/2/16,HEIGHT/2/16},sub_tails;
	Point prevDirection, nextDirection;
	bool dead;
	int score=0;

	int checkBody(Point dot, Point preDot, Point nextDot);
	int checkHead(Point prevDirection);
	int checkTail(Point tail, Point afterTail);
	
    void update(struct Food& food, Mix_Chunk* chunk, SDL_Renderer* renderer);
	void changeDirection(SDL_Event event);
	void reset();
	void check_eat_food(struct Food& food, Mix_Chunk* chunk);
	
	bool check_collision_wall(Mix_Chunk* chunk);
	bool check_eatSelf(Mix_Chunk* chunk);

	void insertIMG(SDL_Renderer* renderer, Point snake, std::string imgLocate );
	void draw(SDL_Window* window, SDL_Renderer* renderer);
};
