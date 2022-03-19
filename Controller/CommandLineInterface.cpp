#include "Controller/CommandLineInterface.h"

#include "ActionMessage/KillAction.h"
#include "ActionMessage/HomeAction.h"
#include "ActionMessage/MoveAction.h"
#include "ActionMessage/NoAction.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerUpAction.h"
#include "ActionMessage/SuccessAction.h"
#include "Pathing/Point.h"
#include "Utils/LoggerDefines.h"

#include <iostream>
#include <sstream>

namespace
{
  const char* LOGGER_DOMAIN       ("Main");

  const char* COMMAND_HOME        ("home");
  const char* COMMAND_MOVE_TO     ("moveTo");
  const char* COMMAND_QUIT        ("quit");
  const char* COMMAND_POWER_DOWN  ("powerDown");
  const char* COMMAND_POWER_UP    ("powerUp");

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
Controller::CommandLineInterface::CommandLineInterface()
:m_running(true)
{

}


//*****************************************************************************
Controller::CommandLineInterface::~CommandLineInterface()
{

}


//*****************************************************************************
void Controller::CommandLineInterface::commandParse
(
  const std::string& commandString
)
{
  std::vector<std::string> args = split(commandString, ' ');
  std::string command = args[0];
  args.erase(args.begin());

  if(command == COMMAND_HOME)
  {
    std::shared_ptr<ActionMessage::Action> action
      = std::shared_ptr<ActionMessage::HomeAction>();

    std::shared_ptr<ActionMessage::Action> reply = m_device->actionSendReply(action);
    if(reply->messageTypeGet() == ActionMessage::SuccessAction::TYPE_ID)
    {
      LOGGER_INFO(LOGGER_DOMAIN, "success");
    }
    else
    {
      LOGGER_INFO(LOGGER_DOMAIN, "failed to move to home");
    }
  }
  else if(command == COMMAND_QUIT)
  {
    m_running = false;
    std::shared_ptr<ActionMessage::Action>action = std::shared_ptr<ActionMessage::KillAction>(new ActionMessage::KillAction);
  }
  else if(command == COMMAND_MOVE_TO)
  {
    if(args.size() != MOVE_TO_NUM_ARGS)
    {
      LOGGER_ERROR(LOGGER_DOMAIN, "invalid number of args");
    }
    else
    {
      std::shared_ptr<ActionMessage::Action> action
        = std::shared_ptr<ActionMessage::MoveAction>(
          new ActionMessage::MoveAction(
            stof(args[0]),
            stof(args[1]),
            stof(args[2])));

      std::shared_ptr<ActionMessage::Action> reply = m_device->actionSendReply(action);
      if(reply.get() != 0)
      {
        if(reply->messageTypeGet() == ActionMessage::SuccessAction::TYPE_ID)
        {
          LOGGER_INFO(LOGGER_DOMAIN, "success");
        }
        else
        {
          LOGGER_INFO(LOGGER_DOMAIN, "failed to move");
        }
      }
      else
      {
        LOGGER_INFO(LOGGER_DOMAIN, "received invalid message");
      }
    }
  }
  else if(command == COMMAND_POWER_DOWN)
  {
    std::shared_ptr<ActionMessage::Action> action
      = std::shared_ptr<ActionMessage::PowerDownAction>();

    std::shared_ptr<ActionMessage::Action> reply = m_device->actionSendReply(action);
    if(reply->messageTypeGet() == ActionMessage::SuccessAction::TYPE_ID)
    {
      LOGGER_INFO(LOGGER_DOMAIN, "success");
    }
    else
    {
      LOGGER_INFO(LOGGER_DOMAIN, "failed to power arm");
    }
  }
  else if(command == COMMAND_POWER_UP)
  {
    std::shared_ptr<ActionMessage::Action> action
      = std::shared_ptr<ActionMessage::PowerUpAction>();

    std::shared_ptr<ActionMessage::Action> reply = m_device->actionSendReply(action);
    if(reply->messageTypeGet() == ActionMessage::SuccessAction::TYPE_ID)
    {
      LOGGER_INFO(LOGGER_DOMAIN, "success");
    }
    else
    {
      LOGGER_INFO(LOGGER_DOMAIN, "failed to power arm down");
    }
  }
  else
  {
    usagePrint();
  }
}


//*****************************************************************************
void Controller::CommandLineInterface::deviceSet
(
  std::shared_ptr<ControlInterface::Device> device
)
{
  m_device = device;
}


//*****************************************************************************
void Controller::CommandLineInterface::run()
{
  usagePrint();
  while(m_running)
  {
    std::string command;
    std::getline(std::cin, command);

    commandParse(command);
  }
}


//*****************************************************************************
void Controller::CommandLineInterface::usagePrint()
{
  std::stringstream ss;
  ss << "commands:\n";
  ss << "\thome\n";
  ss << "\tmoveTo x y z\n";
  ss << "\tpowerDown\n";
  ss << "\tpowerUp\n";
  ss << "\tquit";

  std::cout << ss.str() << std::endl;
}
