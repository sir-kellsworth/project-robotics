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

  unique_ptr(const unique_ptr& s) :pt(s.pt) { }

  template<class U>
  unique_ptr(unique_ptr<U>& s) :pt(s.pt) {  }

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
      if(this!=&s)
      {
          pt=s.pt;
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
        pt=s.get();
    }
    return *this;
  }

  T* operator->() const { return pt; }
  T* get() const { return pt; }
  T& operator*() const { return *pt; }

private:
  T* pt;
};

#endif
#endif
