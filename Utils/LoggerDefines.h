#ifndef UTILS_LOGGERDEFINES_H
#define UTILS_LOGGERDEFINES_H

#include "Utils/Logger.h"

#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG(domain, message) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.debugLog(domain, message); \
}
#endif

#ifndef LOGGER_ERROR
#define LOGGER_ERROR(domain, message) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.errorLog(domain, message); \
}
#endif

#ifndef LOGGER_INFO
#define LOGGER_INFO(domain, message) \
{ \
Utils::Logger& logger = Utils::Logger::loggerGet(); \
logger.infoLog(domain, message); \
}
#endif

#endif
