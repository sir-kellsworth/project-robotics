#include "Utils/Semaphore.h"


//*****************************************************************************
Utils::Semaphore::Semaphore
(
	int count
)
:m_count(count)
{

}


//*****************************************************************************
void Utils::Semaphore::signal()
{
		std::unique_lock<std::mutex> lock(m_mtx);
		m_count++;

		m_cv.notify_one();
}


//*****************************************************************************
void Utils::Semaphore::wait()
{
		std::unique_lock<std::mutex> lock(m_mtx);
		while(m_count == 0)
		{
				m_cv.wait(lock);
		}
		m_count = 0;
}


//*****************************************************************************
void Utils::Semaphore::waitFor
(
	int countToWaitFor
)
{
	std::unique_lock<std::mutex> lock(m_mtx);
	while(m_count != countToWaitFor)
	{
		m_cv.wait(lock);
	}
	m_count = 0;
}
