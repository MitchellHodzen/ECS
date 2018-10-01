#pragma once
#include <SDL.h>
class Example
{
public:
	Example(int screenWidth, int screenHeight);
	void Run();
	~Example();
private:
	int screenWidth;
	int screenHeight;
	bool InitSDL();
	void CloseSDL();
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr; 
	SDL_Texture* texture = nullptr;
	void Draw();
	void Physics();
	void GetUserInput();
	void HandleUserInput();
	void CheckCollisions();
	void HandleCollisions();
	static void Test();
	bool quit;
};

