#ifndef CONTROLLER_COMMANDLINEINTERFACE_H
#define CONTROLLER_COMMANDLINEINTERFACE_H

#include "ControlInterface/Device.h"

#include <vector>

namespace Controller
{

class CommandLineInterface
{
public:
  CommandLineInterface();

  ~CommandLineInterface();

  void commandParse(
    const std::string& command);

  void deviceSet(
    std::shared_ptr<ControlInterface::Device> device);

  void run();

  void usagePrint();
private:
  std::shared_ptr<ControlInterface::Device> m_device;
  bool m_running;
};

}

#endif
