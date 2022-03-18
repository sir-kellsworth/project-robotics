#include "Utils/Logger.h"

#include <iostream>
#include <stdarg.h>


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
  const char* format...
)
{
  if(m_logLevel >= DEBUG_LEVEL)
  {
    va_list args;
    va_start(args, format);
    messageLog(ERROR_LOG_TAG, domain, format, args);
    va_end(args);
  }
}


//*****************************************************************************
void Utils::Logger::errorLog
(
  const std::string& domain,
  const char* format...
)
{
  if(m_logLevel >= ERROR_LEVEL)
  {
    va_list args;
    va_start(args, format);
    messageLog(ERROR_LOG_TAG, domain, format, args);
    va_end(args);
  }
}


//*****************************************************************************
void Utils::Logger::infoLog
(
  const std::string& domain,
  const char* format...
)
{
  if(m_logLevel >= INFO_LEVEL)
  {
    va_list args;
    va_start(args, format);
    messageLog(ERROR_LOG_TAG, domain, format, args);
    va_end(args);
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
Utils::Logger& Utils::Logger::loggerGet()
{
  static Logger logger;

  return logger;
}


//*****************************************************************************
void Utils::Logger::messageLog
(
  const std::string& logLevel,
  const std::string& domain,
  const char* format...
)
{
  std::time_t currentTime = std::time(0);
  char time[100];
  strftime(time, 100, "%H:%M:%S", localtime(&currentTime));

  va_list args;
  va_start(args, format);
  char message[500];
  vsprintf(message, format, args);
  va_end(args);

  std::lock_guard<std::mutex> lock(m_mutex);
  std::cout << time
    << logLevel << "\t"
    << "-" << domain << "- -" << message << std::endl;
}
