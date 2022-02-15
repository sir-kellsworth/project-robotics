#include "ControlInterface/CommandLineInterface.h"

#include "ActionMessage/KillAction.h"
#include "ActionMessage/HomeAction.h"
#include "ActionMessage/MoveAction.h"
#include "ActionMessage/NoAction.h"
#include "Pathing/Point.h"

#include <iostream>

namespace
{
  const std::string COMMAND_HOME("home");
  const std::string COMMAND_MOVE_TO("moveTo");
  const std::string COMMAND_QUIT("quit");
  const std::string COMMAND_POWER_DOWN("powerDown");
  const std::string COMMAND_POWER_UP("powerUp");

  const uint8_t MOVE_TO_NUM_ARGS(3);

  //*****************************************************************************
  std::vector<std::string> split
  (
    std::string const &str, char dil
  )
  {
  	std::vector<std::string> split;
  	std::string buff = "";

  	int begining = 0;
  	for(int i = 0; i < str.length(); i++){
  		if(str[i] == dil){
  			split.push_back(buff);
  			buff = "";
  		}else{
  			buff += str[i];
  		}
  	}
  	split.push_back(buff);

  	return split;
  }
}

//*****************************************************************************
ControlInterface::CommandLineInterface::CommandLineInterface()
:m_running(true)
{

}


//*****************************************************************************
ControlInterface::CommandLineInterface::~CommandLineInterface()
{

}


//*****************************************************************************
std::shared_ptr<ActionMessage::Action> ControlInterface::CommandLineInterface::commandParse
(
  const std::string& commandString
)
{
  std::vector<std::string> args = split(commandString, ' ');
  std::string command = args[0];
  args.erase(args.begin());

  std::shared_ptr<ActionMessage::Action> action;
  if(command == COMMAND_HOME)
  {
    action = std::shared_ptr<ActionMessage::HomeAction>(new ActionMessage::HomeAction);
  }
  else if(command == COMMAND_QUIT)
  {
    m_running = false;
    action = std::shared_ptr<ActionMessage::KillAction>(new ActionMessage::KillAction);
  }
  else if(command == COMMAND_MOVE_TO)
  {
    if(args.size() != MOVE_TO_NUM_ARGS){
      std::cout << "invalid number of args" << std::endl;
      action = std::shared_ptr<ActionMessage::NoAction>(new ActionMessage::NoAction);
    }
    else
    {
      action = std::shared_ptr<ActionMessage::MoveAction>(
        new ActionMessage::MoveAction(
          stof(args[0]),
          stof(args[1]),
          stof(args[2])
        ));
    }
  }
  else if(command == COMMAND_POWER_DOWN)
  {

  }
  else if(command == COMMAND_POWER_UP)
  {

  }
  else
  {
    action = std::shared_ptr<ActionMessage::NoAction>(new ActionMessage::NoAction);
    usagePrint();
  }

  return action;
}


//*****************************************************************************
void ControlInterface::CommandLineInterface::deviceSet
(
  std::shared_ptr<ControlInterface::Device> device
)
{
  m_device = device;
}


//*****************************************************************************
void ControlInterface::CommandLineInterface::run()
{
  usagePrint();
  while(m_running)
  {
    std::string command;
    std::getline(std::cin, command);

    m_device->actionSend(commandParse(command));
  }
}


//*****************************************************************************
void ControlInterface::CommandLineInterface::usagePrint()
{
  std::cout << "commands:" << std::endl;
  std::cout << "\thome" << std::endl;
  std::cout << "\tmoveTo x y z" << std::endl;
  std::cout << "\tpowerDown" << std::endl;
  std::cout << "\tpowerUp" << std::endl;
  std::cout << "\tquit" << std::endl;
}
