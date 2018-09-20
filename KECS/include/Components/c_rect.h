#pragma once
struct Rect
{
	Rect()
	{
		offsetX = 0;
		offsetY = 0;
		width = 0; 
		height = 0;
	};
	int offsetX;
	int offsetY;
	int width;
	int height;
};