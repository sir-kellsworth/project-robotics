#ifndef UTILS_LOGGERDEFINES_H
#define UTILS_LOGGERDEFINES_H

#include "Utils/Logger.h"

#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG(domain, format, ...) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.debugLog(domain, format __VA_OPT__(,) __VA_ARGS__); \
}
#endif

#ifndef LOGGER_ERROR
#define LOGGER_ERROR(domain, format, ...) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.errorLog(domain, format __VA_OPT__(,) __VA_ARGS__); \
}
#endif

#ifndef LOGGER_INFO
#define LOGGER_INFO(domain, format, ...) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.infoLog(domain, format __VA_OPT__(,) __VA_ARGS__); \
}
#endif

#ifndef LOGGER_MSG
#define LOGGER_MSG(domain, format, ...) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.messageLog(domain, format __VA_OPT__(,) __VA_ARGS__); \
}
#endif

#endif
