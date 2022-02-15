#include "Config/Config.h"
#include "ControlInterface/CommandLineInterface.h"
#include "Remote/RemoteInterface.h"


namespace
{
  const char* CONFIG_FILE("config.txt");

  const char* CONFIG_KEY_ARM_LENGTH("armLength");
  const char* CONFIG_KEY_AVAILABLE("available");
  const char* CONFIG_KEY_BASE_MOTOR("baseMotor");
  const char* CONFIG_KEY_DEGREES_PER_SECOND("degreesPerSecond");
  const char* CONFIG_KEY_ELBOW_MOTOR("elbowMotor");
  const char* CONFIG_KEY_FORARM_LENGTH("forarmLength");
  const char* CONFIG_KEY_IP_ADDRESS("ipAddress");
  const char* CONFIG_KEY_HOME_POINT("homePoint");
  const char* CONFIG_KEY_MAX_ANGLE("maxAngle");
  const char* CONFIG_KEY_MIN_ANGLE("minAngle");
  const char* CONFIG_KEY_REMOTE_CONTROLLER("remoteController");
  const char* CONFIG_KEY_SHOULDER_MOTOR("shoulderMotor");
  const char* CONFIG_KEY_SIM("sim");
  const char* CONFIG_KEY_START_POINT("startPoint");
  const char* CONFIG_KEY_PORT("port");
}

int main(int argc, char* argv[])
{
  Config::ConfigMap map = Config::configGet(CONFIG_FILE);
  ControlInterface::CommandLineInterface interface;
  std::string remoteIp = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_IP_ADDRESS].valueGet<std::string>();
  unsigned short port = map[CONFIG_KEY_REMOTE_CONTROLLER][CONFIG_KEY_PORT].valueGet<unsigned short>();
  std::shared_ptr<Remote::RemoteInterface> remoteInterface(
    new Remote::RemoteInterface(remoteIp, port));

  interface.deviceSet(remoteInterface);
  interface.run();

  return 0;
}
