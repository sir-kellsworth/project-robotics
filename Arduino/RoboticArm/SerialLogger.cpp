#include "SerialLogger.h"

#include <Arduino.h>
#include <stdarg.h>


namespace
{
  const uint16_t LOG_HEADER_LENGTH  (7);
  const char* LOG_HEADER            ("##log##");
}

//*****************************************************************************
SerialLogger::SerialLogger()
{

}


//*****************************************************************************
SerialLogger::~SerialLogger()
{

}


//*****************************************************************************
void SerialLogger::log
(
  const char* domain,
  const char* format,
  ...
)
{
  va_list args;
  va_start(args, format);
  char message[500];
  uint16_t messageLength = vsnprintf(message, 500, format, args);
  uint16_t totalLength = LOG_HEADER_LENGTH + messageLength;
  Serial.write((uint8_t*)&totalLength, 2);
  Serial.write(LOG_HEADER);
  Serial.write(message, messageLength);
  Serial.flush();
  va_end(args);
}


//*****************************************************************************
SerialLogger& SerialLogger::loggerGet()
{
  static SerialLogger logger;

  return logger;
}
