#ifndef UTILS_MESSAGEQUEUE_H
#define UTILS_MESSAGEQUEUE_H

#include "Utils/Semaphore.h"

#include <queue>
#include <mutex>

namespace Utils{

template <class T>
class MessageQueue{
public:
	MessageQueue();
	int size();
	void push(T *newMsg);
	T *pop();
private:
	std::mutex mutex;
	Utils::Semaphore semaphore;
	std::queue<T *> queue;
};

}


//*****************************************************************************
template <class T>
Utils::MessageQueue<T>::MessageQueue()
{

}


//*****************************************************************************
template <class T>
int Utils::MessageQueue<T>::size()
{
	return queue.size();
}


//*****************************************************************************
template <class T>
void Utils::MessageQueue<T>::push
(
  T *newMessage
)
{
	mutex.lock();
	queue.push(newMessage);
	mutex.unlock();
	semaphore.signal();
}


//*****************************************************************************
template <class T>
T *Utils::MessageQueue<T>::pop()
{
	semaphore.wait();
	mutex.lock();
	T *next = queue.front();
	queue.pop();
	mutex.unlock();

	return next;
}

#endif
