#pragma once
struct CollisionMessage
{
	CollisionMessage(int entityOneIndex, int entityTwoIndex)
	{
		this->entityOneIndex = entityOneIndex;
		this->entityTwoIndex = entityTwoIndex;
	};
	int entityOneIndex;
	int entityTwoIndex;
};