#ifndef UTILS_QUEUE_H
#define UTILS_QUEUE_H

#include "Utils/vector.h"

namespace Utils
{

template<class T>
class Queue
{
public:
  Queue(uint8_t capacity = 20);

  ~Queue();

  bool isEmpty();

  bool isFull();

  bool push(
    shared_ptr<T> object);

  shared_ptr<T> pop();
private:
  uint8_t m_front;
  uint8_t m_end;
  uint8_t m_count;
  uint8_t m_capacity;
  vector<shared_ptr<T>> m_backend;
};

}


//*****************************************************************************
template<class T>
Utils::Queue<T>::Queue
(
  uint8_t capacity
)
:m_front(0),
 m_end(-1),
 m_count(0),
 m_capacity(capacity),
 m_backend(capacity)
{

}


//*****************************************************************************
template<class T>
Utils::Queue<T>::~Queue()
{

}


//*****************************************************************************
template<class T>
bool Utils::Queue<T>::isEmpty()
{
  return m_count == 0;
}


//*****************************************************************************
template<class T>
bool Utils::Queue<T>::isFull()
{
  return m_count == m_capacity;
}


//*****************************************************************************
template<class T>
bool Utils::Queue<T>::push
(
  shared_ptr<T> object
)
{
  bool success(false);
  if(!isFull())
  {
    m_end = (m_end + 1) % m_capacity;
    m_backend[m_end] = object;
    ++m_count;

    success = true;
  }

  return success;
}


//*****************************************************************************
template<class T>
shared_ptr<T> Utils::Queue<T>::pop()
{
  shared_ptr<T> tmp;
  if(!isEmpty())
  {
    tmp = m_backend[m_front];
    m_backend[m_front].reset(0);
    m_front = (m_front + 1) % m_capacity;
    ++m_count;
  }

  return tmp;
}

#endif
