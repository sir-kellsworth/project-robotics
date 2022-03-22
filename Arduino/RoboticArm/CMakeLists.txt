cmake_minimum_required(VERSION 3.15)
project(RoboticSim)

option(USE_DEBUG "Enter debug mode" OFF)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(ARDUINO_CONTROL_CODE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ACTION_MESSAGE_DIR ${BASE_DIR}/ActionMessage)
set(UTILS_DIR ${BASE_DIR}/Utils)
set(PATHING_DIR ${BASE_DIR}/Pathing)
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


set(SOURCE_ARDUINO_CONTROL_CODE
  ${ARDUINO_CONTROL_CODE_DIR}/SerialLogger.cpp
  ${ARDUINO_CONTROL_CODE_DIR}/SerialLogger.h
  ${ARDUINO_CONTROL_CODE_DIR}/RemoteInterface.cpp
  ${ARDUINO_CONTROL_CODE_DIR}/RemoteInterface.h
  ${ARDUINO_CONTROL_CODE_DIR}/RoboticArm.cpp
  ${ARDUINO_CONTROL_CODE_DIR}/RoboticArm.h
)

set(SOURCE_UTILS
  ${UTILS_DIR}/TrigEquations.cpp
  ${UTILS_DIR}/TrigEquations.h
  ${UTILS_DIR}/SafeQueue.h
  ${UTILS_DIR}/shared_ptr.h
  ${UTILS_DIR}/vector.h
)

set(SOURCE_PATHING
  ${PATHING_DIR}/Path.cpp
  ${PATHING_DIR}/Path.h
  ${PATHING_DIR}/Point.cpp
  ${PATHING_DIR}/Point.h
)

set(SOURCE_VENDOR_ACCEL_STEPPER
  ${VENDOR_DIR}/AccelStepper/AccelStepper.cpp
  ${VENDOR_DIR}/AccelStepper/AccelStepper.h
)

add_compile_definitions(FIXMATH_NO_CACHE)
file(GLOB SOURCE_VENDOR_LIBFIXMATH ${VENDOR_DIR}/libfixmath/source/libfixmath/*.h ${VENDOR_DIR}/libfixmath/source/libfixmath/*.hpp ${VENDOR_DIR}/libfixmath/source/libfixmath/*.c)

set(SOURCE_VENDOR
  ${SOURCE_VENDOR_ACCEL_STEPPER}
  ${SOURCE_VENDOR_LIBFIXMATH}
)

set(SOURCE_ALL
  ${SOURCE_ARDUINO_CONTROL_CODE}
  ${SOURCE_ACTION_MESSAGE}
  ${SOURCE_UTILS}
  ${SOURCE_PATHING}
  ${SOURCE_VENDOR}
)

if(USE_DEBUG)
  add_definitions(-DARDUINO_DEBUG)
endif()

include_directories(
  "${BASE_DIR}/"
  "${CMAKE_CURRENT_LIST_DIR}/"
  "${VENDOR_ARDUINO_DIR}/"
  "${VENDOR_DIR}/libfixmath/api/"
  "${VENDOR_DIR}/AccelStepper/"
)

add_executable(RoboticArm ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${SOURCE_ALL})
target_link_arduino_libraries(RoboticArm AUTO_PUBLIC)
target_link_arduino_libraries(RoboticArm PRIVATE core)
target_enable_arduino_upload(RoboticArm)
