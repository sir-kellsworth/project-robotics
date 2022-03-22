#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG(domain, format, ...) \
{ \
SerialLogger& logger = SerialLogger::loggerGet(); \
logger.log(domain, format __VA_OPT__(,) __VA_ARGS__); \
}
#endif

class SerialLogger
{
public:
  ~SerialLogger();

  void log(
    const char* domain,
    const char* format,
    ...);

  SerialLogger& loggerGet();
private:
  SerialLogger();
};

#endif
