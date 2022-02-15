#ifndef CONTROLINTERFACE_COMMANDLINEINTERFACE_H
#define CONTROLINTERFACE_COMMANDLINEINTERFACE_H

#include "ControlInterface/Device.h"

#include <vector>

namespace ControlInterface
{

class CommandLineInterface
{
public:
  CommandLineInterface();

  ~CommandLineInterface();

  std::shared_ptr<ActionMessage::Action> commandParse(
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
