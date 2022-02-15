#ifndef UTILS_SHARED_PTR_H
#define UTILS_SHARED_PTR_H

#ifdef __linux__
#include <memory>
template <typename T>
using shared_ptr = std::shared_ptr<T>;
#else

template<class T>
class shared_ptr
{
    struct aux
    {
        unsigned count;

        aux() :count(1) {}
        virtual void destroy()=0;
        virtual ~aux() {} //must be polymorphic
    };

    template<class U, class Deleter>
    struct auximpl: public aux
    {
        U* p;
        Deleter d;

        auximpl(U* pu, Deleter x) :p(pu), d(x) {}
        virtual void destroy() { d(p); }
    };

    template<class U>
    struct default_deleter
    {
        void operator()(U* p) const { delete p; }
    };

    aux* pa;
    T* pt;

    void inc() { if(pa) interlocked_inc(pa->count); }

    void dec()
    {
        if(pa && !interlocked_dec(pa->count))
        {  pa->destroy(); delete pa; }
    }

    bool interlocked_inc(unsigned& c)
    {
      if(c > 0)
      {
        ++c;
        return true;
      }

      return false;
    }

    bool interlocked_dec(unsigned& c)
    {
      if(c > 0)
      {
        --c;
        return true;
      }

      return false;
    }

public:

    shared_ptr() :pa(), pt() {}

    template<class U, class Deleter>
    shared_ptr(U* pu, Deleter d) :pa(new auximpl<U,Deleter>(pu,d)), pt(pu) {}

    template<class U>
    explicit shared_ptr(U* pu) :pa(new auximpl<U,default_deleter<U> >(pu,default_deleter<U>())), pt(pu) {}

    shared_ptr(const shared_ptr& s) :pa(s.pa), pt(s.pt) { inc(); }

    template<class U>
    shared_ptr(const shared_ptr<U>& s) :pa(s.pa), pt(s.pt) { inc(); }

    ~shared_ptr() { dec(); }

    shared_ptr& operator=(const shared_ptr& s)
    {
        if(this!=&s)
        {
            dec();
            pa = s.pa; pt=s.pt;
            inc();
        }
        return *this;
    }

    bool operator()()
    {
      return pt == 0;
    }

    T* operator->() const { return pt; }
    T* get() const { return pt; }
    T& operator*() const { return *pt; }
};

#endif
#endif
