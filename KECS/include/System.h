#pragma once
#include <functional>
#include <iostream>
class System
{
public:
	template<typename... Components> static void Run(std::function<void(int)> systemFunction)
	{
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (ComponentManager::HasComponent<Components...>(i))
			{
				systemFunction(i);
			}
		}
	}
private:
	System() {};
	~System() {};
};