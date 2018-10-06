#pragma once
#include <type_traits>
#include <iostream>
#include <queue>
#include <vector>
class MessageManager
{
public:
	template<typename Message> static void PushMessage(Message message)
	{
		messageQueue<Message>.push(message);
	}

	template<typename Message> static Message PopMessage()
	{
		Message message = messageQueue<Message>.top();
		messageQueue<Message>.pop();
		return message;
	}

	template<typename Message> static void ClearMessages()
	{
		std::queue<Message, std::vector<Message>>().swap(messageQueue<Message>);
	}

	template<typename Message> static bool NotEmpty()
	{
		return !messageQueue<Message>.empty();
	}
private:
	MessageManager() {};
	~MessageManager() {};
	//template<typename T> static inline std::vector<T> messageVector;
	template<typename T> static inline std::queue<T, std::vector<T>> messageQueue  = std::queue<T, std::vector<T>>();
};