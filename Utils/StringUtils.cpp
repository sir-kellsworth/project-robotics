#include "Utils/StringUtils.h"

#include <algorithm>
#include <functional>


//*****************************************************************************
std::vector<std::string> Utils::split
(
  const std::string& str,
  const char& delimiator
)
{
  std::vector<std::string> result;

  std::string::const_iterator wordStart = str.begin();
  std::string::const_iterator it = str.begin();
  std::string::const_iterator end = str.end();
  while(it != end)
  {
    if(*it == delimiator)
    {
      result.push_back(std::string(wordStart, it));
      wordStart = it+1;
    }

    ++it;
  }
  result.push_back(std::string(wordStart, it));

  return std::move(result);
}


//*****************************************************************************
std::string Utils::strip
(
  const std::string& str
)
{
  std::string result(str);

  std::string::iterator end_pos = std::remove(result.begin(), result.end(), ' ');
  result.erase(end_pos, result.end());

  return std::move(result);
}
