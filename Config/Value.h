#ifndef CONFIG_VALUE_H
#define CONFIG_VALUE_H

#include <map>
#include <string>

namespace Config
{

class Value
{
public:
  Value(
    const std::string& str);

  Value();

  ~Value();

  template<typename t>
  t valueGet();

  void subAdd(
    const std::string& key,
    const Value& value);

  Value& operator[](
    const std::string& key);
private:
  std::string m_data;
  std::map<std::string, Value> m_subkeys;
};

}

#endif
