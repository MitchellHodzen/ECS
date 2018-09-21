#pragma once
#include <stack>
#include <vector>
struct UserInput
{
	enum InputType { LEFT, RIGHT, UP, DOWN, CLOSE};

	UserInput()
	{
		inputStack = std::stack<int, std::vector<int>>();
	}

	std::stack<int, std::vector<int>> inputStack;

};