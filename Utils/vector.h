//      g++ -std=c++11 -g3 test.cpp -o test
// OR:  clang -std=c++11 -g3 -Wall test.cpp -lstdc++ -o test
//
// valgrind --leak-check=yes ./test
#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H

#ifdef __linux__
#include <vector>
template <typename T>
using vector = std::vector<T>;
#else

#include <stdio.h>      // printf
#include <string.h>     /* memcpy */

#define min(a,b) (a < b) ? a : b

template <typename T>
class vector {
public:
  //***************************************************************************
  vector()
  :capacity_(0),
   count_(0),
   data_(nullptr)
  {

  }


  //***************************************************************************
  vector
  (
    uint32_t size
  )
  :capacity_(size),
   count_(0), //count_(size),
   data_(new T[count_])
  {

  }

  //***************************************************************************
  vector
  (
    const vector& rhs
  )
  :capacity_(rhs.capacity_),
   count_(rhs.count_),
   data_(new T[rhs.capacity_])
  {
    memcpy (data_, rhs.data_, sizeof (T) * count_);
  }

  //***************************************************************************
  vector& operator=
  (
    const vector& rhs
  )
  {
    // gracefully handle self-assignment (eg. a = a;)
    if (this == &rhs )
      return *this;

    data_ = new T [rhs.capacity_];
    capacity_ = rhs.capacity_;
    count_ = rhs.count_;
    memcpy (data_, rhs.data_, sizeof (T) * count_);
    return *this;
  }

  //***************************************************************************
  ~vector()
  {
      clear ();
  }


  //***************************************************************************
  const T& operator[]
  (
    unsigned int idx
  ) const
  {
     return data_[idx];
  }


  //***************************************************************************
  T& operator[]
  (
    unsigned int idx
  )
  {
     return data_[idx];
  }


  //***************************************************************************
  const T* begin()
  {
    return data_[0];
  }


  //***************************************************************************
  const T* end()
  {
    return data_[count_];
  }


  //***************************************************************************
  void resize_to_fit()
  {
      resize(count_);
  }


  //***************************************************************************
  T& pop_back()
  {
      return data_[--count_];
  }


  //***************************************************************************
  void push_back
  (
    const T& obj
  )
  {
    if (capacity_ == count_)
    {
        resize(capacity_ + 1);
    }

    data_[count_++] = obj;
  }


  //***************************************************************************
  bool isempty()
  {
      return count_ == 0;
  }


  //***************************************************************************
  void clear()
  {
    delete [] data_;
    data_ = nullptr;
    count_ = 0;
    capacity_ = 0;
  }

  T* data()
  {
      return data_;
  }


  //***************************************************************************
  unsigned int size()
  {
      return count_;
  }


  //***************************************************************************
  unsigned int capacity()
  {
      return capacity_;
  }


  //***************************************************************************
  void resize
  (
    int capacity
  )
  {
    if (data_ == nullptr)
    {
        data_ = new T[capacity];
        count_ = 0;
        capacity_ = capacity;
    }
    else if (capacity > capacity_)
    {
      // allocate new memory
      T* data = new T[capacity];
      // count can't be higher than capacity
      count_ = min(count_, capacity);
      capacity_ = capacity;
      // copy data across to new pointer
      memcpy(data, data_, sizeof(T) * count_);
      // delete old pointer
      delete [] data_;
      // now remember the new pointer
      data_ = data;
    }
    else if(capacity > 0)
    {
      count_ = capacity;
    }
  }
protected:
  unsigned int capacity_;
  unsigned int count_;
  T* data_;
};

#endif
#endif
