#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

class SerialLogger
{
public:
  ~SerialLogger();

  void log(
    const char* format,
    ...);

  static SerialLogger& loggerGet();
private:
  SerialLogger();
};


#ifdef ARDUINO_DEBUG
#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG(...) \
{ \
SerialLogger& logger = SerialLogger::loggerGet(); \
logger.log(__VA_ARGS__); \
delay(100); \
}
#endif
#else
#define LOGGER_DEBUG(format, ...) {};
#endif

#endif
