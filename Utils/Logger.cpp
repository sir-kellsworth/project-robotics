#include "Utils/Logger.h"

#include <iostream>


namespace
{
  const std::string BLUE_COLOR_FG("\033[34m");
  const std::string DEFAULT_COLOR_FG("\033[39m");
  const std::string RED_COLOR_FG("\033[31m");
  const std::string YELLOW_COLOR_FG("\033[93m");

  const std::string DEBUG_LOG_TAG(YELLOW_COLOR_FG + "[debug]" + DEFAULT_COLOR_FG);
  const std::string ERROR_LOG_TAG(RED_COLOR_FG + "[error]" + DEFAULT_COLOR_FG);
  const std::string INFO_LOG_TAG(BLUE_COLOR_FG + "[info]" + DEFAULT_COLOR_FG);
}

//*****************************************************************************
Utils::Logger::Logger()
:m_logLevel(INFO_LEVEL)
{

}


//*****************************************************************************
Utils::Logger::~Logger()
{

}


//*****************************************************************************
void Utils::Logger::debugLog
(
  const std::string& domain,
  const std::string& message
)
{
  if(m_logLevel >= DEBUG_LEVEL)
  {
    messageLog(DEBUG_LOG_TAG, domain, message);
  }
}


//*****************************************************************************
void Utils::Logger::errorLog
(
  const std::string& domain,
  const std::string& message
)
{
  if(m_logLevel >= ERROR_LEVEL)
  {
    messageLog(ERROR_LOG_TAG, domain, message);
  }
}


//*****************************************************************************
void Utils::Logger::infoLog
(
  const std::string& domain,
  const std::string& message
)
{
  if(m_logLevel >= INFO_LEVEL)
  {
    messageLog(INFO_LOG_TAG, domain, message);
  }
}


//*****************************************************************************
void Utils::Logger::levelSet
(
  LOG_LEVEL level
)
{
  m_logLevel = level;
}


//*****************************************************************************
void Utils::Logger::messageLog
(
  const std::string& logLevel,
  const std::string& domain,
  const std::string& message
)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  std::time_t currentTime = std::time(0);
  char time[100];
  strftime(time, 100, "%H:%M:%S", localtime(&currentTime));

  std::cout << time
    << logLevel << "\t"
    << domain << "- -" << message << std::endl;
}
