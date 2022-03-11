#include "Config/Config.h"
#include "Controller/CommandLineInterface.h"
#include "Network/SocketSerial.h"
#include "Network/SocketTcp.h"
#include "Remote/RemoteInterface.h"


namespace
{
  const char* CONFIG_FILE                   ("config.txt");

  const char* CONFIG_KEY_ARM_LENGTH         ("armLength");
  const char* CONFIG_KEY_AVAILABLE          ("available");
  const char* CONFIG_KEY_BAUD_RATE          ("baudRate");
  const char* CONFIG_KEY_BASE_MOTOR         ("baseMotor");
  const char* CONFIG_KEY_DEGREES_PER_SECOND ("degreesPerSecond");
  const char* CONFIG_KEY_DEVICE_NAME        ("deviceName");
  const char* CONFIG_KEY_ELBOW_MOTOR        ("elbowMotor");
  const char* CONFIG_KEY_FORARM_LENGTH      ("forarmLength");
  const char* CONFIG_KEY_INTERFACE_TYPE     ("interfaceType");
  const char* CONFIG_KEY_IP_ADDRESS         ("ipAddress");
  const char* CONFIG_KEY_HOME_POINT         ("homePoint");
  const char* CONFIG_KEY_MAX_ANGLE          ("maxAngle");
  const char* CONFIG_KEY_MIN_ANGLE          ("minAngle");
  const char* CONFIG_KEY_PORT               ("port");
  const char* CONFIG_KEY_REMOTE_CONTROLLER  ("remoteController");
  const char* CONFIG_KEY_SERIAL_INTERFACE   ("serial");
  const char* CONFIG_KEY_SHOULDER_MOTOR     ("shoulderMotor");
  const char* CONFIG_KEY_START_POINT        ("startPoint");
  const char* CONFIG_KEY_TCP_INTERFACE      ("tcp");
}


//*****************************************************************************
int main
(
  int argc,
  char* argv[]
)
{
  Config::ConfigMap map = Config::configGet(CONFIG_FILE);
  Controller::CommandLineInterface interface;
  std::unique_ptr<Network::Socket> socket;
  if(map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_INTERFACE_TYPE].valueGet<std::string>() == CONFIG_KEY_TCP_INTERFACE)
  {
    std::string remoteIp = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_TCP_INTERFACE][CONFIG_KEY_IP_ADDRESS].valueGet<std::string>();
    unsigned short port = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_TCP_INTERFACE][CONFIG_KEY_PORT].valueGet<unsigned short>();
    socket = std::unique_ptr<Network::Socket>(new Network::SocketTcp(remoteIp, port));
  }
  else if(map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_INTERFACE_TYPE].valueGet<std::string>() == CONFIG_KEY_SERIAL_INTERFACE)
  {
    std::string deviceName = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_SERIAL_INTERFACE][CONFIG_KEY_DEVICE_NAME].valueGet<std::string>();
    uint16_t baudRate = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_SERIAL_INTERFACE][CONFIG_KEY_BAUD_RATE].valueGet<uint16_t>();
    socket = std::unique_ptr<Network::Socket>(new Network::SocketSerial(deviceName, baudRate));
  }
  std::shared_ptr<Remote::RemoteInterface> remoteInterface(
    new Remote::RemoteInterface(socket));

  interface.deviceSet(remoteInterface);
  interface.run();

  return 0;
}
