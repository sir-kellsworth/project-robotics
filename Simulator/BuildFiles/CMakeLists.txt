cmake_minimum_required(VERSION 3.15)
project(RoboticSim)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(ACTION_MESSAGE_DIR ${BASE_DIR}/ActionMessage)
set(CONFIG_DIR ${BASE_DIR}/Config)
set(COMMAND_INTERFACE_DIR ${BASE_DIR}/ControlInterface)
set(NETWORK_DIR ${BASE_DIR}/Network)
set(UTILS_DIR ${BASE_DIR}/Utils)
set(PATHING_DIR ${BASE_DIR}/Pathing)
set(REMOTE_DIR ${BASE_DIR}/Remote)
set(SIMULATOR_DIR ${BASE_DIR}/Simulator)
set(VENDOR_DIR ${BASE_DIR}/vendor)

set(SOURCE_ACTION_MESSAGE
  ${ACTION_MESSAGE_DIR}/Action.cpp
  ${ACTION_MESSAGE_DIR}/Action.h
  ${ACTION_MESSAGE_DIR}/ActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/ActionEncoder.h
  ${ACTION_MESSAGE_DIR}/FailedAction.cpp
  ${ACTION_MESSAGE_DIR}/FailedAction.h
  ${ACTION_MESSAGE_DIR}/FailedActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/FailedActionDecoder.h
  ${ACTION_MESSAGE_DIR}/FailedActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/FailedActionEncoder.h
  ${ACTION_MESSAGE_DIR}/HomeAction.cpp
  ${ACTION_MESSAGE_DIR}/HomeAction.h
  ${ACTION_MESSAGE_DIR}/HomeActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/HomeActionDecoder.h
  ${ACTION_MESSAGE_DIR}/HomeActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/HomeActionEncoder.h
  ${ACTION_MESSAGE_DIR}/KillAction.cpp
  ${ACTION_MESSAGE_DIR}/KillAction.h
  ${ACTION_MESSAGE_DIR}/KillActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/KillActionDecoder.h
  ${ACTION_MESSAGE_DIR}/KillActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/KillActionEncoder.h
  ${ACTION_MESSAGE_DIR}/MoveAction.cpp
  ${ACTION_MESSAGE_DIR}/MoveAction.h
  ${ACTION_MESSAGE_DIR}/MoveActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/MoveActionDecoder.h
  ${ACTION_MESSAGE_DIR}/MoveActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/MoveActionEncoder.h
  ${ACTION_MESSAGE_DIR}/NoAction.cpp
  ${ACTION_MESSAGE_DIR}/NoAction.h
  ${ACTION_MESSAGE_DIR}/NoActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/NoActionDecoder.h
  ${ACTION_MESSAGE_DIR}/NoActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/NoActionEncoder.h
  ${ACTION_MESSAGE_DIR}/PowerDownAction.cpp
  ${ACTION_MESSAGE_DIR}/PowerDownAction.h
  ${ACTION_MESSAGE_DIR}/PowerDownActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/PowerDownActionDecoder.h
  ${ACTION_MESSAGE_DIR}/PowerDownActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/PowerDownActionEncoder.h
  ${ACTION_MESSAGE_DIR}/PowerUpAction.cpp
  ${ACTION_MESSAGE_DIR}/PowerUpAction.h
  ${ACTION_MESSAGE_DIR}/PowerUpActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/PowerUpActionDecoder.h
  ${ACTION_MESSAGE_DIR}/PowerUpActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/PowerUpActionEncoder.h
  ${ACTION_MESSAGE_DIR}/SuccessAction.cpp
  ${ACTION_MESSAGE_DIR}/SuccessAction.h
  ${ACTION_MESSAGE_DIR}/SuccessActionDecoder.cpp
  ${ACTION_MESSAGE_DIR}/SuccessActionDecoder.h
  ${ACTION_MESSAGE_DIR}/SuccessActionEncoder.cpp
  ${ACTION_MESSAGE_DIR}/SuccessActionEncoder.h
  ${ACTION_MESSAGE_DIR}/ActionFactory/ActionFactory.cpp
  ${ACTION_MESSAGE_DIR}/ActionFactory/ActionFactory.h
)

set(SOURCE_CONFIG
  ${CONFIG_DIR}/Config.cpp
  ${CONFIG_DIR}/Config.h
  ${CONFIG_DIR}/Value.cpp
  ${CONFIG_DIR}/Value.h
)

set(SOURCE_COMMAND_INTERFACE
  ${COMMAND_INTERFACE_DIR}/CommandLineInterface.cpp
  ${COMMAND_INTERFACE_DIR}/CommandLineInterface.h
  ${COMMAND_INTERFACE_DIR}/Device.h
)

set(SOURCE_NETWORK
  ${NETWORK_DIR}/Socket.cpp
  ${NETWORK_DIR}/Socket.h
  ${NETWORK_DIR}/ServerTcp.cpp
  ${NETWORK_DIR}/ServerTcp.h
  ${NETWORK_DIR}/SocketTcp.cpp
  ${NETWORK_DIR}/SocketTcp.h
)

set(SOURCE_UTILS
  ${UTILS_DIR}/TrigEquations.cpp
  ${UTILS_DIR}/TrigEquations.h
  ${UTILS_DIR}/SafeQueue.h
  ${UTILS_DIR}/Semaphore.cpp
  ${UTILS_DIR}/Semaphore.h
  ${UTILS_DIR}/StringUtils.cpp
  ${UTILS_DIR}/StringUtils.h
)

set(SOURCE_PATHING
  ${PATHING_DIR}/Path.cpp
  ${PATHING_DIR}/Path.h
  ${PATHING_DIR}/Point.cpp
  ${PATHING_DIR}/Point.h
)

set(SOURCE_REMOTE
  ${REMOTE_DIR}/RemoteController.cpp
  ${REMOTE_DIR}/RemoteController.h
  ${REMOTE_DIR}/RemoteInterface.cpp
  ${REMOTE_DIR}/RemoteInterface.h
)

set(SOURCE_SIMULATOR
  ${SIMULATOR_DIR}/SimulatorArm.cpp
  ${SIMULATOR_DIR}/SimulatorArm.h
  ${SIMULATOR_DIR}/SimulatorMotor.cpp
  ${SIMULATOR_DIR}/SimulatorMotor.h
)

set(SOURCE_ALL
  ${SOURCE_ACTION_MESSAGE}
  ${SOURCE_CONFIG}
  ${SOURCE_COMMAND_INTERFACE}
  ${SOURCE_NETWORK}
  ${SOURCE_UTILS}
  ${SOURCE_PATHING}
  ${SOURCE_REMOTE}
  ${SOURCE_SIMULATOR}
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

include_directories(
  "${BASE_DIR}/"
  "${VENDOR_DIR}/libfixmath/api/"
)

add_executable(RoboticSim ${CMAKE_CURRENT_LIST_DIR}/../main.cpp ${SOURCE_ALL})
target_link_libraries(RoboticSim Threads::Threads)
target_link_libraries(RoboticSim ${VENDOR_DIR}/libfixmath/lib/liblibfixmath.a)


add_custom_target(
    configCopy ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/__header.h
)

add_custom_command(
  COMMAND cp
    ${CMAKE_CURRENT_LIST_DIR}/../config.txt
    ${CMAKE_CURRENT_BINARY_DIR}/config.txt
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/__header.h
)
