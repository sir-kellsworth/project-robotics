#ifndef UTILS_STRINGUTILS_H
#define UTILS_STRINGUTILS_H

#include <string>
#include <vector>

namespace Utils
{
  std::vector<std::string> split(
    const std::string& string,
    const char& delimiator);

  std::string strip(
    const std::string& str);
}

#endif
