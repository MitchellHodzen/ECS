#include "Example.h"
#include <iostream>
#include "ECS.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include "Components/c_rect.h"


void Example::Draw(int entityIndex)
{
	//Render red filled quad 
	Rect rect = ComponentManager::GetComponent<Rect>(entityIndex);
	Position pos = ComponentManager::GetComponent<Position>(entityIndex);
	SDL_Rect fillRect = { pos.x, pos.y, rect.width, rect.height }; 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF ); 
	SDL_RenderFillRect( renderer, &fillRect );
}

void Example::Physics(int entityIndex)
{
	Position pos = ComponentManager::GetComponent<Position>(entityIndex);
	Velocity vel = ComponentManager::GetComponent<Velocity>(entityIndex);
	pos.x += vel.dx;
	pos.y += vel.dy;
	ComponentManager::SetComponent<Position>(entityIndex, pos);
}

Example::Example(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	ComponentManager::SetUpComponents<Position, Velocity, Rect>();
}


Example::~Example()
{
}

void Example::Run()
{
	//Run tests
	if (InitSDL())
	{
		bool quit = false;
		SDL_Event e;
		EntityManager em(5);
		ComponentManager::em = &em;
		int ent0 = em.CreateEntity();
		ComponentManager::AddComponent<Position>(ent0);
		ComponentManager::AddComponent<Rect>(ent0);
		ComponentManager::AddComponent<Velocity>(ent0);
		Rect rect;
		rect.posX = 200;
		rect.posY = 200;
		rect.width = 50;
		rect.height = 50;
		ComponentManager::SetComponent<Rect>(ent0, rect);

		while (!quit)
		{
			int dx = 0;
			int dy = 0;
			while (SDL_PollEvent(&e) != 0)
			{
				if( e.type == SDL_QUIT )
				{ 
					quit = true; 
				}
				else if( e.type == SDL_KEYDOWN ) 
				{ 
					//Select surfaces based on key press 
					switch( e.key.keysym.sym ) 
					{ 
						case SDLK_UP: 
							dy -= 5;
							break; 
						case SDLK_DOWN: 
							dy += 5;
							break; 
						case SDLK_LEFT: 
							dx -= 5;
							break; 
						case SDLK_RIGHT: 
							dx += 5;
							break; 
						default: 
							break; 
					}
				}
			}
			//Clear screen 
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear( renderer ); 
			Velocity newVelocity;
			newVelocity.dx = dx;
			newVelocity.dy = dy;
			ComponentManager::SetComponent<Velocity>(ent0, newVelocity);
			System::Run<Position, Velocity>([this](int x) {Physics(x); });
			System::Run<Position, Rect>([this](int x){Draw(x); });
			SDL_RenderPresent( renderer );
		}
		CloseSDL();
	}
}

bool Example::InitSDL()
{
	//Initialization flag 
	bool success = true; 
	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;;
		success = false;
	} 
	else 
	{ 
		//Create window 
		window = SDL_CreateWindow( "ECS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN ); 
		if( window == nullptr ) 
		{ 
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false; 
		} 
		else
		{ 
			//Create renderer for window 
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
			if( renderer == nullptr ) 
			{ 
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false; 
			}
			else 
			{ 
				//Initialize renderer color 
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
			}
		}
	}
	return success;
}

void Example::CloseSDL()
{
	//Destroy window 
	SDL_DestroyWindow( window ); 
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}