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
		messageQueue<Message>->push(message);
	}

	template<typename Message> static Message PopMessage()
	{
		Message message = messageQueue<Message>->front();
		messageQueue<Message>->pop();
		return message;
	}

	template<typename Message> static void ClearMessages()
	{
		//std::queue<Message, std::vector<Message>>().swap(messageQueue<Message>);
	}

	template<typename Message> static bool NotEmpty()
	{
		return !messageQueue<Message>->empty();
	}
	
private:
	MessageManager() {};
	~MessageManager() {};
	//static inline std::queue<int, std::vector<int>> messageQueue;
	template<typename T> static inline std::queue<T>* messageQueue = new std::queue<T>;
	//template<typename T> static inline std::vector<T> messageVector;
};