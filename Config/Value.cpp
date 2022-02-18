#include "Config/Value.h"

#include "Pathing/Point.h"
#include "Utils/StringUtils.h"

#include <iostream>

//*****************************************************************************
Config::Value::Value
(
  const std::string& str
)
:m_data(Utils::strip(str))
{

}


//*****************************************************************************
Config::Value::Value()
{

}


//*****************************************************************************
Config::Value::~Value()
{

}


//*****************************************************************************
Config::Value& Config::Value::operator[]
(
  const std::string& key
)
{
  return m_subkeys[key];
}


//*****************************************************************************
void Config::Value::subAdd
(
  const std::string& key,
  const Value& value
)
{
  m_subkeys.emplace(std::pair<std::string, Value>(key, value));
}


//*****************************************************************************
template<>
Pathing::Point Config::Value::valueGet()
{
  //removes <, >
  m_data.erase(m_data.begin());
  m_data.erase(m_data.end()-1);


  std::vector<std::string> split = Utils::split(m_data, ',');
  return Pathing::Point(
    std::stof(Utils::strip(split[0])),
    std::stof(Utils::strip(split[1])),
    std::stof(Utils::strip(split[2])));
}


//*****************************************************************************
template<>
uint16_t Config::Value::valueGet()
{
  return std::stoi(m_data);
}


//*****************************************************************************
template<>
uint32_t Config::Value::valueGet()
{
  return std::stoi(m_data);
}


//*****************************************************************************
template<>
float Config::Value::valueGet()
{
  return std::stof(m_data);
}


//*****************************************************************************
template<>
std::string Config::Value::valueGet()
{
  return m_data;
}
