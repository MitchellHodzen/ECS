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
	SDL_Rect fillRect = { rect.posX, rect.posY, rect.width, rect.height }; 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF ); 
	SDL_RenderFillRect( renderer, &fillRect );
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
		Rect rect;
		rect.posX = 200;
		rect.posY = 200;
		rect.width = 50;
		rect.height = 50;
		ComponentManager::SetComponent<Rect>(ent0, rect);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if( e.type == SDL_QUIT )
				{ 
					quit = true; 
				}
			}
			//Clear screen 
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear( renderer ); 
			//Render texture to screen 
			//SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
			//Update screen
			//System::Run<Position, Rect>(std::bind(&Example::Draw, this));
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