#ifndef UTILS_UNIQUE_PTR_H
#define UTILS_UNIQUE_PTR_H

#ifdef __linux__
#include <memory>
template <typename T>
using unique_ptr = std::unique_ptr<T>;
#else

template<class T>
class unique_ptr
{
public:
  unique_ptr() :pt(0) {}

  template<class U>
  unique_ptr(U* pu) :pt(pu) {}

  unique_ptr(const unique_ptr& s) :pt(s.release()) {}

  template<class U>
  unique_ptr(const unique_ptr<U>& s) :pt(s.release()) {}

  ~unique_ptr()
  {
    if(pt != 0)
    {
      delete pt;
    }
  }

  unique_ptr& operator=
  (
    const unique_ptr& s
  )
  {
      if(get()!=s.get())
      {
          pt = s.release();
      }
      return *this;
  }

  template<class U>
  unique_ptr& operator=
  (
    const unique_ptr<U>& s
  )
  {
    if(get()!=s.get())
    {
        pt = s.release();
    }
    return *this;
  }

  T* operator->() const { return pt; }
  T* get() const { return pt; }
  T& operator*() const { return *pt; }
  T* release() { T* tmp = pt; pt = 0; return tmp; }

private:
  T* pt;
};

#endif
#endif
