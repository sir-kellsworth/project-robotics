#include "Config/Config.h"

#include "Config/Value.h"
#include "Pathing/Point.h"
#include "Utils/StringUtils.h"

#include <iostream>
#include <fstream>
#include <vector>

//*****************************************************************************
Config::ConfigMap Config::configGet
(
  const std::string& file
)
{
  std::ifstream reader(file, std::ifstream::in);
  Config::ConfigMap map;

  std::string next;
  while(std::getline(reader, next))
  {
    if(next.rfind('#', 0) != 0 && next.length() > 0)
    {
      std::vector<std::string> split = Utils::split(next, '=');

      //This is a sub option and needs to be added to the parent option
      std::vector<std::string> keySplit = Utils::split(split[0], '_');
      if(keySplit.size() > 1)
      {
        subAdd(
          map[keySplit[0]],
          keySplit.begin()+1,
          keySplit.end()-1,
          split[1]);
      }
      else
      {
        map[Utils::strip(split[0])] = Config::Value(split[1]);
      }
    }
  }

  return std::move(map);
}


//*****************************************************************************
void Config::subAdd
(
  Config::Value& parent,
  std::vector<std::string>::iterator keyIt,
  std::vector<std::string>::iterator keyEnd,
  const std::string& value
)
{
  if(keyIt == keyEnd)
  {
    parent.subAdd(Utils::strip(*keyIt), Config::Value(value));
  }
  else
  {
    parent.subAdd(
      Utils::strip(*keyIt),
      Config::Value("NULL"));
    subAdd(
      parent[Utils::strip(*keyIt)],
      keyIt+1,
      keyEnd,
      value);
  }
}
