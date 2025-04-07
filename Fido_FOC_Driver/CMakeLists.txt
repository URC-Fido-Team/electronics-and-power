# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initializing the Pico SDK
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(fido_tmc C CXX ASM)

pico_sdk_init()

# Add executable
add_executable(fido_tmc
        fido_tmc.c
        )

pico_set_program_name(fido_tmc "fido_tmc")
pico_set_program_version(fido_tmc "0.1")

# Disable stdout over UART/USB
pico_enable_stdio_uart(fido_tmc 0)
pico_enable_stdio_usb(fido_tmc 0)

# Include the standard library
target_link_libraries(fido_tmc
        pico_stdlib
        hardware_spi
        TMC4671
        )

# Include directories for your external library
target_include_directories(fido_tmc PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/TMC4671)

pico_enable_stdio_usb(fido_tmc 1)
pico_enable_stdio_uart(fido_tmc 0)

pico_add_extra_outputs(fido_tmc)
