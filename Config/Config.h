#ifndef CONFIG_H
#define CONFIG_H

#include "Config/Value.h"

#include <map>
#include <string>
#include <vector>

namespace Config
{

typedef std::map<std::string, Config::Value> ConfigMap;

ConfigMap configGet(
  const std::string& file);

void subAdd(
  Config::Value& parent,
  std::vector<std::string>::iterator keyIt,
  std::vector<std::string>::iterator keyEnd,
  const std::string& value);
}

#endif
