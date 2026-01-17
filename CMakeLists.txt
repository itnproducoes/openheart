# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

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
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(-Wall)

# Add executable. Default name is the project name, version 0.1

add_executable(openheart main/main.cpp lib/ssd1306.c lib/ssd1306_bitmap.c)

# this ends up being overridden in the code but I think it's required
# for setting the REFDIV of the system pll
target_compile_definitions(openheart PRIVATE
        PLL_SYS_REFDIV=2
        PLL_SYS_VCO_FREQ_HZ=1074000000
        PLL_SYS_POSTDIV1=5
        PLL_SYS_POSTDIV2=2
        SYS_CLK_HZ=107400000
)

add_library(pico_st7735 INTERFACE)

target_sources(pico_st7735 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/st7735/pico_ST7735_TFT.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/st7735/pico_ST7735_TFT_graphics.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/st7735/pico_ST7735_TFT_Print.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/st7735/pico_ST7735_TFT_Font.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/st7735/pico_ST7735_TFT_Bitmap_Data.cpp
)




target_include_directories(pico_st7735 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# pull in common dependencies
target_link_libraries(openheart pico_stdlib hardware_pwm hardware_flash hardware_i2c hardware_spi pico_st7735 pico_unique_id )

# create map/bin/hex file etc.
pico_add_extra_outputs(openheart)

# add url via pico_set_program_url

# Enable usb output, disable uart output
pico_enable_stdio_usb(openheart 1)
pico_enable_stdio_uart(openheart 0)
