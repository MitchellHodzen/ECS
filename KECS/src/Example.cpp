#include "Example.h"
#include <iostream>
#include "ECS.h"
#include "Components/c_position.h"
#include "Components/c_velocity.h"
#include "Components/c_rect.h"
#include "Tags.h"
#include "Components/c_input.h"
#include "Components/c_friction.h"
#include "Time.h"
void Example::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, Rect>();

	for (int entityIndex : entities)
	{
		//Render red filled quad 
		Rect rect = EntityManager::GetComponent<Rect>(entityIndex);
		Position pos = EntityManager::GetComponent<Position>(entityIndex);
		SDL_Rect fillRect = { pos.x + rect.offsetX, pos.y + rect.offsetY, rect.width, rect.height };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);
	}
	SDL_RenderPresent(renderer);
}

void Example::Physics()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, Velocity, Friction>();
	for (int entityIndex : entities)
	{
		Position pos = EntityManager::GetComponent<Position>(entityIndex);
		Velocity vel = EntityManager::GetComponent<Velocity>(entityIndex);
		Friction frict = EntityManager::GetComponent<Friction>(entityIndex);
		if (vel.dx > 0)
		{
			vel.dx -= frict.amountX * Time::GetDeltaTime();
			if (vel.dx < 0)
			{
				vel.dx = 0;
			}
		}
		else if (vel.dx < 0)
		{
			vel.dx += frict.amountX * Time::GetDeltaTime();
			if (vel.dx > 0)
			{
				vel.dx = 0;
			}
		}

		if (vel.dy > 0)
		{
			vel.dy -= frict.amountY * Time::GetDeltaTime();
			if (vel.dy < 0)
			{
				vel.dy = 0;
			}
		}
		else if (vel.dy < 0)
		{
			vel.dy += frict.amountY * Time::GetDeltaTime();
			if (vel.dy > 0)
			{
				vel.dy = 0;
			}
		}
		pos.x += vel.dx * Time::GetDeltaTime();
		pos.y += vel.dy * Time::GetDeltaTime();
		//std::cout << vel.dx << ", " << vel.dy << std::endl;
		EntityManager::SetComponent<Position>(entityIndex, pos);
		EntityManager::SetComponent<Velocity>(entityIndex, vel);
	}
}

void Example::GetUserInput()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<UserInput>();

	//For every entity which captures user input, record user input
	for (int entityIndex : entities)
	{
		UserInput uin = EntityManager::GetComponent<UserInput>(entityIndex);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); 
		if (currentKeyStates[SDL_SCANCODE_UP]) 
		{
			uin.keyStates[UserInput::InputType::UP] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::UP] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{ 
			uin.keyStates[UserInput::InputType::DOWN] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::DOWN] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_LEFT]) 
		{ 
			uin.keyStates[UserInput::InputType::LEFT] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::LEFT] = false;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) 
		{ 
			uin.keyStates[UserInput::InputType::RIGHT] = true;
		}
		else
		{
			uin.keyStates[UserInput::InputType::RIGHT] = false;
		}
		EntityManager::SetComponent<UserInput>(entityIndex, uin);
	}
		

}
void Example::HandleUserInput()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Velocity, UserInput>();
	
	for (int entityIndex : entities)
	{
		Velocity vel = EntityManager::GetComponent<Velocity>(entityIndex);
		UserInput uin = EntityManager::GetComponent<UserInput>(entityIndex);
		float speed = 100.0f;
		if (uin.keyStates[UserInput::InputType::UP])
		{
			vel.dy -= speed * Time::GetDeltaTime();
		}
		if (uin.keyStates[UserInput::InputType::DOWN])
		{
			vel.dy += speed * Time::GetDeltaTime();
		}
		if (uin.keyStates[UserInput::InputType::LEFT])
		{
			vel.dx -= speed * Time::GetDeltaTime();
		}
		if (uin.keyStates[UserInput::InputType::RIGHT])
		{
			vel.dx += speed * Time::GetDeltaTime();
		}

		EntityManager::SetComponent<Velocity>(entityIndex, vel);
		EntityManager::SetComponent<UserInput>(entityIndex, uin);


	}
	
}
void Example::Test()
{
	std::vector<int> entities = EntityManager::GetEntitiesWithComponent<Position, Velocity>();
	for (int entityIndex : entities)
	{
		std::cout << "Test funtion " << entityIndex << std::endl;
	}
}

Example::Example(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}


Example::~Example()
{
}

void Example::Run()
{
	//Run tests
	if (InitSDL())
	{
		EntityManager::SetUpComponents<Position, Velocity, Rect, Friction, UserInput>();
		EntityManager::SetUpTags<Player, Enemy, Wall>();

		int ent0 = EntityManager::CreateEntity();
		EntityManager::AddTag<Player>(ent0);
		EntityManager::AddComponent<Position>(ent0);
		EntityManager::AddComponent<Rect>(ent0);
		EntityManager::AddComponent<Velocity>(ent0);
		EntityManager::AddComponent<Friction>(ent0);
		EntityManager::AddComponent<UserInput>(ent0);
		Rect rect;
		rect.width = 50;
		rect.height = 50;
		rect.offsetX = -rect.width / 2;
		rect.offsetY = -rect.height / 2;
		EntityManager::SetComponent<Rect>(ent0, rect);

		Friction frict;
		frict.amountX = 20.0f;
		frict.amountY = 20.0f;
		EntityManager::SetComponent<Friction>(ent0, frict);

		int ent1 = EntityManager::CreateEntity();
		EntityManager::AddComponent<Position>(ent1);
		EntityManager::AddComponent<Rect>(ent1);
		Position pos1 = EntityManager::GetComponent<Position>(ent1);
		pos1.x = 200;
		pos1.y = 200;
		EntityManager::SetComponent<Position>(ent1, pos1);

		Rect rect1 = EntityManager::GetComponent<Rect>(ent1);
		rect1.width = 100;
		rect1.height = 75;
		EntityManager::SetComponent<Rect>(ent1, rect1);
		EntityManager::AddTag<Enemy>(ent1);
		EntityManager::AddTag<Wall>(ent1);
		EntityManager::AddComponent<Velocity>(ent1);
		EntityManager::AddComponent<UserInput>(ent1);
		Friction frict2;
		frict2.amountX = 20.0f;
		frict2.amountY = 20.0f;
		EntityManager::AddComponent<Friction>(ent1);
		EntityManager::SetComponent<Friction>(ent1, frict2);

		std::cout << "Entity " << ent0 << " is a player: " << EntityManager::HasTag<Player>(ent0) << std::endl;
		std::cout << "Entity " << ent1 << " is a player: " << EntityManager::HasTag<Player>(ent1) << std::endl;
		std::cout << "Entity " << ent0 << " is an enemy and wall: " << EntityManager::HasTag<Enemy, Wall>(ent0) << std::endl;
		std::cout << "Entity " << ent1 << " is an enemy and wall: " << EntityManager::HasTag<Enemy, Wall>(ent1) << std::endl;

		//EntityManager::DestroyEntity(ent1);
		//ent1 = EntityManager::CreateEntity();
		//std::cout << "Entity " << ent1 << " is an enemy and wall: " << EntityManager::HasTag<Enemy, Wall>(ent1) << std::endl;
		SDL_Event e;



		float deltaTime = 0.0f;
		Uint32 lastFrameTime = 0;
		Uint32 currentFrameTime = SDL_GetTicks();


		while (!quit)
		{
			lastFrameTime = currentFrameTime;
			currentFrameTime = SDL_GetTicks();
			Time::CalculateDeltaTime(lastFrameTime, currentFrameTime);

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				/*
				else if (e.type == SDL_KEYDOWN)
				{
					//Select surfaces based on key press 
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						uin.inputStack.push(UserInput::InputType::UP);
						break;
					case SDLK_DOWN:
						uin.inputStack.push(UserInput::InputType::DOWN);
						break;
					case SDLK_LEFT:
						uin.inputStack.push(UserInput::InputType::LEFT);
						break;
					case SDLK_RIGHT:
						uin.inputStack.push(UserInput::InputType::RIGHT);
						break;
					default:
						break;
					}
				}
				*/
			}
			GetUserInput();
			HandleUserInput();
			Physics();
			Draw();
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