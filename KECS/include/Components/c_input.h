#pragma once
#include <stack>
#include <vector>
struct UserInput
{
	enum InputType { LEFT, RIGHT, UP, DOWN, CLOSE};

	UserInput()
	{
		for (int i = 0; i < 4; ++i)
		{
			keyStates[i] = false;
		}
	}

	bool keyStates[4];

};