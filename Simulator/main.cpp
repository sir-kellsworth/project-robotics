#include "Config/Config.h"
#include "Pathing/Point.h"
#include "Simulator/SimulatorArm.h"
#include "Utils/TrigEquations.h"
#include "Utils/StringUtils.h"
#include "Remote/RemoteController.h"
#include "Remote/RemoteInterface.h"

#include <iostream>
#include <unistd.h>


namespace
{
  const char* CONFIG_FILE("config.txt");

  const char* CONFIG_KEY_ARM_LENGTH         ("armLength");
  const char* CONFIG_KEY_AVAILABLE          ("available");
  const char* CONFIG_KEY_BASE_MOTOR         ("baseMotor");
  const char* CONFIG_KEY_DEGREES_PER_SECOND ("degreesPerSecond");
  const char* CONFIG_KEY_ELBOW_MOTOR        ("elbowMotor");
  const char* CONFIG_KEY_FORARM_LENGTH      ("forarmLength");
  const char* CONFIG_KEY_IP_ADDRESS         ("ipAddress");
  const char* CONFIG_KEY_HOME_POINT         ("homePoint");
  const char* CONFIG_KEY_MAX_ANGLE          ("maxAngle");
  const char* CONFIG_KEY_MIN_ANGLE          ("minAngle");
  const char* CONFIG_KEY_REMOTE_CONTROLLER  ("remoteController");
  const char* CONFIG_KEY_SHOULDER_MOTOR     ("shoulderMotor");
  const char* CONFIG_KEY_SIM                ("sim");
  const char* CONFIG_KEY_START_POINT        ("startPoint");
  const char* CONFIG_KEY_PORT               ("port");
}


std::shared_ptr<Remote::RemoteController> simulatorArmMake
(
  Config::ConfigMap& map
)
{
  Pathing::Point home = map[CONFIG_KEY_SIM][CONFIG_KEY_HOME_POINT].valueGet<Pathing::Point>();
  Pathing::Point startPoint = map[CONFIG_KEY_SIM][CONFIG_KEY_START_POINT].valueGet<Pathing::Point>();
  uint32_t armLength_mm = map[CONFIG_KEY_SIM][CONFIG_KEY_ARM_LENGTH].valueGet<uint32_t>();
  uint32_t forarmLength_mm = map[CONFIG_KEY_SIM][CONFIG_KEY_FORARM_LENGTH].valueGet<uint32_t>();
  uint32_t degreesPerSecond = map[CONFIG_KEY_SIM][CONFIG_KEY_DEGREES_PER_SECOND].valueGet<uint32_t>();

  float baseMotorStartAngle(0);
  float shoulderMotorStartAngle(0);
  float elbowMotorStartAngle(0);
  Utils::anglesCalculate(
    startPoint.xGet(),
    startPoint.yGet(),
    startPoint.zGet(),
    armLength_mm,
    forarmLength_mm,
    baseMotorStartAngle,
    shoulderMotorStartAngle,
    elbowMotorStartAngle);

  float baseMotorMinAngle = map[CONFIG_KEY_BASE_MOTOR][CONFIG_KEY_MIN_ANGLE].valueGet<float>();
  float baseMotorMaxAngle = map[CONFIG_KEY_BASE_MOTOR][CONFIG_KEY_MAX_ANGLE].valueGet<float>();
  std::shared_ptr<Simulator::SimulatorMotor> baseMotor(
    new Simulator::SimulatorMotor(
      baseMotorStartAngle,
      baseMotorMinAngle,
      baseMotorMaxAngle,
      degreesPerSecond));
  float shoulderMotorMinAngle = map[CONFIG_KEY_SHOULDER_MOTOR][CONFIG_KEY_MIN_ANGLE].valueGet<float>();
  float shoulderMotorMaxAngle = map[CONFIG_KEY_SHOULDER_MOTOR][CONFIG_KEY_MAX_ANGLE].valueGet<float>();
  std::shared_ptr<Simulator::SimulatorMotor> shoulderMotor(
    new Simulator::SimulatorMotor(
      shoulderMotorStartAngle,
      shoulderMotorMinAngle,
      shoulderMotorMaxAngle,
      degreesPerSecond));
  float elbowMotorMinAngle = map[CONFIG_KEY_ELBOW_MOTOR][CONFIG_KEY_MIN_ANGLE].valueGet<float>();
  float elbowMotorMaxAngle = map[CONFIG_KEY_ELBOW_MOTOR][CONFIG_KEY_MAX_ANGLE].valueGet<float>();
  std::shared_ptr<Simulator::SimulatorMotor> elbowMotor(
    new Simulator::SimulatorMotor(
      elbowMotorStartAngle,
      elbowMotorMinAngle,
      elbowMotorMaxAngle,
      degreesPerSecond));

  std::unique_ptr<ControlInterface::Device> sim = std::unique_ptr<Simulator::SimulatorArm>(
    new Simulator::SimulatorArm(
      home,
      startPoint,
      armLength_mm,
      forarmLength_mm,
      baseMotor,
      shoulderMotor,
      elbowMotor));

  unsigned short port = map[CONFIG_KEY_SIM][CONFIG_KEY_PORT].valueGet<unsigned short>();
  return std::shared_ptr<Remote::RemoteController>(
    new Remote::RemoteController(
      sim,
      port));
}


//*****************************************************************************
int main(int argc, char* argv[])
{
  Config::ConfigMap map = Config::configGet(CONFIG_FILE);
  std::shared_ptr<Remote::RemoteController> sim = simulatorArmMake(map);

  while(true)
  {
    sleep(100);
  }

  return 0;
}
