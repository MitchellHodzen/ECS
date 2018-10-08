#pragma once
#include <SDL.h>
struct Rect;
struct Position;
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
	void ApplyHorizontalPhysics();
	void ApplyVerticalPhysics();
	void GetUserInput();
	void HandleUserInput();
	void CheckCollisions();
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
	bool RectsColliding(Rect rect1, Position pos1, Rect rect2, Position pos2);
	static void Test();
	bool quit;
};

