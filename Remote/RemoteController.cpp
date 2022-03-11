#include "Remote/RemoteController.h"

#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "Network/ServerTcp.h"

#include <iostream>
#include <memory>


namespace
{
  const uint16_t MAX_DATA_SIZE_DEFAULT(50);
}

//*****************************************************************************
Remote::RemoteController::RemoteController
(
  std::unique_ptr<ControlInterface::Device>& sim,
  unsigned short port
)
:m_sim(std::move(sim)),
 m_running(true)
{
  std::cout << "waiting for connection" << std::endl;
  Network::ServerTcp server("127.0.0.1", port);
  m_socket = server.accept();
  std::cout << "received valid connection" << std::endl;

  m_thread = std::thread(&Remote::RemoteController::backgroundHandle, this);
}


//*****************************************************************************
Remote::RemoteController::~RemoteController()
{
  m_running = false;
  m_thread.join();
}


//*****************************************************************************
void Remote::RemoteController::backgroundHandle()
{
  while(m_running)
  {
    std::vector<uint8_t> data(MAX_DATA_SIZE_DEFAULT);
    if(m_socket->read(data) > 0)
    {
      for(uint8_t& next : data){
        std::cout << (int)next << " ";
      }
      std::cout << std::endl;
      std::shared_ptr<ActionMessage::Action> nextAction(
        ActionMessage::ActionFactory::messageGenerate(data));

      std::shared_ptr<ActionMessage::Action> reply
        = m_sim->actionSendReply(nextAction);

      std::shared_ptr<ActionMessage::ActionEncoder> encoder
        = ActionMessage::ActionFactory::encoderGet(reply);
      encoder->actionEncode(data);
      m_socket->send(data);
    }
  }
}
