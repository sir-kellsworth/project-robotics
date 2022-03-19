#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

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
