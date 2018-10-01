#pragma once
#include <type_traits>
#include <iostream>
#include <vector>

class MessageManager
{
public:
	//Template function to get the current vector of the message
	template<typename Message> static std::vector<Message> GetMessageVector()
	{
		return messageVector<Message>;
	}

	template<typename Message> static void AddMessage(Message message)
	{
		messageVector<Message>.push_back(message);
	}

	template<typename Message> static void ClearMessages()
	{
		messageVector<Message>.clear();
	}
private:
	MessageManager() {};
	~MessageManager() {};
	template<typename T> static inline std::vector<T> messageVector;
};