#ifndef UTILS_SEMAPHORE_H
#define UTILS_SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <iostream>

namespace Utils
{

class Semaphore {
public:
    Semaphore(
      int count = 0);


    void signal();

    void wait();

		void waitFor(
      int countToWaitFor);
private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    int m_count;
};

}

#endif
