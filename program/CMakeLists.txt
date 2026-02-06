cmake_minimum_required(VERSION 3.13)

# Définir explicitement la carte comme Pico W
set(PICO_BOARD pico_w)
if(NOT DEFINED PICO_BOARD)
    add_definitions(-DPICO_BOARD=${PICO_BOARD})
endif()

include(pico_sdk_import.cmake)

project(controller C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(controller
  src/main.c
  src/controller.c
  src/wifi/wifi_operator.c
  src/wifi/udp_server.c
  src/wifi/dhcp_server.c
)

target_include_directories(controller PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/wifi/headers/
  ${CMAKE_CURRENT_LIST_DIR}/src/
)

target_link_libraries(controller
  pico_stdlib
  hardware_i2c
  hardware_pwm
  hardware_uart
  pico_cyw43_arch_lwip_poll
)

pico_enable_stdio_usb(controller 1)
pico_enable_stdio_uart(controller 1)

pico_add_extra_outputs(controller)

add_custom_target(Flash
    DEPENDS controller

    COMMAND sudo picotool load -f ${PROJECT_BINARY_DIR}/controller.uf2
)
