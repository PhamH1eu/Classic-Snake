#include "Snake.h"
#include "Food.h" 
#include "SDL_utils.h"

Point operator+ (const Point& a, const Point& b) 
{
	return Point{ a.x + b.x, a.y + b.y };
}
void operator+= (Point& a, const Point& b) 
{
	a.x += b.x;
	a.y += b.y;
}
bool operator== (Point& a, Point& b)
{
	return (a.x==b.x && a.y==b.y);
}

int Snake::checkBody(Point dot, Point preDot, Point nextDot)
{
	#define I 1
	#define II 2
	#define III 3
	#define IV 4
	#define vertical 5
	#define horizontal 6

	if ( (dot.x==(nextDot.x-1) && dot.y==nextDot.y  &&  dot.x==preDot.x && dot.y==(preDot.y+1))
	  || (dot.x==(preDot.x-1) && dot.y==preDot.y  &&  dot.x==nextDot.x && dot.y==(nextDot.y+1)) ) return I;

	if ( (dot.x==nextDot.x && dot.y==(nextDot.y+1)  &&  dot.x==(preDot.x+1) && dot.y==preDot.y)
 	  || (dot.x==preDot.x && dot.y==(preDot.y+1)  &&  dot.x==(nextDot.x+1) && dot.y==nextDot.y) ) return II;

	if ( (dot.x==nextDot.x && dot.y==(nextDot.y-1)  &&  dot.x==(preDot.x+1) && dot.y==preDot.y)
 	  || (dot.x==preDot.x && dot.y==(preDot.y-1)  &&  dot.x==(nextDot.x+1) && dot.y==nextDot.y) ) return III;
	
	if ( (dot.x==nextDot.x && dot.y==(nextDot.y-1)  &&  dot.x==(preDot.x-1) && dot.y==preDot.y)
 	  || (dot.x==preDot.x && dot.y==(preDot.y-1)  &&  dot.x==(nextDot.x-1) && dot.y==nextDot.y) ) return IV;

	if (dot.y==(preDot.y+nextDot.y)/2 && dot.x==preDot.x ) return vertical;

	if (dot.x==(preDot.x+nextDot.x)/2) return horizontal;
}
int Snake::checkHead(Point prevDirection)
{
	#define head_up 1
	#define head_down 2
	#define head_left 3
	#define head_right 4
	Point up={0,-1},down={0,1},left={-1,0},right={1,0};

	if ( prevDirection == up ) return head_up;
	if ( prevDirection == down ) return head_down;
	if ( prevDirection == left ) return head_left;
	if ( prevDirection == right ) return head_right;
}
int Snake::checkTail(Point tail, Point afterTail)
{
	#define tail_up 1
	#define tail_down 2
	#define tail_left 3
	#define tail_right 4

	if ( tail.x==afterTail.x-1 && tail.y==afterTail.y) return tail_left;
	if ( tail.x==afterTail.x+1 && tail.y==afterTail.y) return tail_right;
	if ( tail.x==afterTail.x && tail.y==afterTail.y+1) return tail_down;
	if ( tail.x==afterTail.x && tail.y==afterTail.y-1) return tail_up;
}

void Snake::reset()
{
	head={WIDTH/16/2,HEIGHT/16/2};
	snake = { {WIDTH/16/2,HEIGHT/16/2} };
	nextDirection={0,0};
	prevDirection={0,0};
	SDL_Delay(300);
}

void Snake::check_eat_food(struct Food& food, Mix_Chunk* chunk)
{
	if ( snake[0].x==food.x && snake[0].y==food.y ) 
	{
		snake.push_back(sub_tails);
		food.move();
		score++;
		Mix_PlayChannel(-1, chunk, 0);
	}
}

bool Snake::check_collision_wall(Mix_Chunk* chunk)
{
	if ( snake[0].x==0 || snake[0].x==WIDTH/16-1 || snake[0].y==0 || snake[0].y== HEIGHT/16-1) 
	{
		Mix_PlayChannel(-1, chunk, 0);
		reset();
		return true;
	}
	return false;
}

bool Snake::check_eatSelf(Mix_Chunk* chunk)
{
	for (int i = 1; i < snake.size(); i++) 
	{
		if ( snake[i] == head ) 
		{
			Mix_PlayChannel(-1, chunk, 0);
			reset();
			return true;
		}
	}
	return false;
}

void Snake::update(struct Food& food, Mix_Chunk* chunk, SDL_Renderer* renderer) 
{
	dead = false;
	for (int i=0;i<snake.size();i++) while ( snake[i].x==food.x && snake[i].y==food.y ) food.move();

	prevDirection=nextDirection;
	head+=prevDirection;

	sub_tails=snake[snake.size()-1];
	for ( int i=snake.size()-1; i>0; i-- )
	{
		snake[i]=snake[i-1];
	}
	snake[0] = head;

	check_eat_food(food,chunk);
	if ( check_eatSelf(chunk) || check_collision_wall(chunk) ) 
	{
		food.move(); 
		dead = true;
		show_endGame(renderer);
		show_score( renderer, "Your score: " + std::to_string( score ) );
		score=0;
	}

	SDL_Delay(70);
}

void Snake::changeDirection(SDL_Event event)
{
	switch (event.key.keysym.sym) 
	{
	case SDLK_w: if (prevDirection.y != 1) nextDirection = { 0, -1 }; break;
	case SDLK_s: if (prevDirection.y != -1) nextDirection = { 0, 1 }; break;
	case SDLK_a: if (prevDirection.x != 1) nextDirection = { -1, 0 }; break;
	case SDLK_d: if (prevDirection.x != -1) nextDirection = { 1, 0 }; break;
	}
}

void Snake::draw(SDL_Window* window, SDL_Renderer* renderer) 
{	

	for (int i = 1; i < snake.size()-1; i++)  
	{
		switch ( checkBody( snake[i], snake[(i-1)], snake[(i+1)] ) )
		{
			case I: insertIMG(renderer, snake[i], "./gallery/I.bmp"); break;

			case II: insertIMG(renderer, snake[i], "./gallery/II.bmp"); break;

			case III: insertIMG(renderer, snake[i], "./gallery/III.bmp"); break;

			case IV: insertIMG(renderer, snake[i], "./gallery/IV.bmp"); break;

			case vertical: insertIMG(renderer, snake[i], "./gallery/vertical_body.bmp"); break;

			case horizontal: insertIMG(renderer, snake[i], "./gallery/horizontal_body.bmp"); break;
		}
	}	

	switch ( checkTail(snake[snake.size()-1], snake[snake.size()-2]) )
	{
		case tail_up: insertIMG(renderer, snake[snake.size()-1], "./gallery/tail_up.bmp"); break;

		case tail_down: insertIMG(renderer, snake[snake.size()-1], "./gallery/tail_down.bmp"); break;

		case tail_left: insertIMG(renderer, snake[snake.size()-1], "./gallery/tail_left.bmp"); break;

		case tail_right: insertIMG(renderer,snake[snake.size()-1], "./gallery/tail_right.bmp"); break;
	}

	switch ( checkHead(prevDirection) )
	{
		case head_up: insertIMG(renderer, snake[0], "./gallery/head_up.bmp"); break;

		case head_down: insertIMG(renderer, snake[0], "./gallery/head_down.bmp"); break;

		case head_left: insertIMG(renderer, snake[0], "./gallery/head_left.bmp"); break;

		case head_right: insertIMG(renderer,snake[0], "./gallery/head_right.bmp"); break;
	}
	
	Point null={0,0};
	if (nextDirection==null)  insertIMG(renderer,snake[0], "./gallery/home.bmp");
}

void Snake::insertIMG(SDL_Renderer* renderer, Point snake, std::string imgLocate )
{
	SDL_Rect r{ 16 * snake.x, 16 * snake.y, 16, 16 };
	char* filename=imgDirectory(imgLocate);
	SDL_Texture* texture = loadTexture(renderer,filename);
	blit(renderer,texture,r);
	SDL_DestroyTexture(texture);
}
