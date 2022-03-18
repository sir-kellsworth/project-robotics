#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <mutex>

namespace Utils
{

class Logger
{
public:
  enum LOG_LEVEL
  {
    ERROR_LEVEL = 0,
    INFO_LEVEL,
    DEBUG_LEVEL,
  };

  ~Logger();

  void debugLog(
    const std::string& domain,
    const std::string& message);

  void errorLog(
    const std::string& domain,
    const std::string& message);

  void infoLog(
    const std::string& domain,
    const std::string& message);

  void levelSet(
    LOG_LEVEL level);

  static Logger& loggerGet();

  void messageLog(
    const std::string& logLevel,
    const std::string& domain,
    const std::string& message);
private:
  Logger();

  LOG_LEVEL m_logLevel;
  std::mutex m_mutex;
};

}

#endif
