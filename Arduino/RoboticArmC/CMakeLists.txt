cmake_minimum_required(VERSION 3.15)
project(RoboticSim)

set(CMAKE_BUILD_TYPE Debug)

set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(ACTION_MESSAGE_DIR ${BASE_DIR}/ActionMessage)
set(COMMAND_INTERFACE_DIR ${BASE_DIR}/ControlInterface)
set(UTILS_DIR ${BASE_DIR}/Utils)
set(PATHING_DIR ${BASE_DIR}/Pathing)
set(REMOTE_DIR ${BASE_DIR}/Remote)
set(ARDUINO_CONTROL_CODE_DIR CMAKE_CURRENT_LIST_DIR)


set(SOURCE_ALL

)

include_directories(
  "${BASE_DIR}/"
  "${CMAKE_CURRENT_LIST_DIR}/"
)

add_executable(RoboticArm ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${SOURCE_ALL})
target_link_arduino_libraries(RoboticArm AUTO_PUBLIC)
target_link_arduino_libraries(RoboticArm PRIVATE core)
#target_enable_arduino_upload(RoboticArm)
