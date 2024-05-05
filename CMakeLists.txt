cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME swift-test)

if(NOT PICO_SDK_PATH)
    message(WARNING "PICO_SDK_PATH not specified. Forcing fetch from git!")
    set(PICO_SDK_FETCH_FROM_GIT true)
endif()

# Import PICO SDK.
include(pico_sdk_import.cmake)

# Set up proejct.
project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK.
pico_sdk_init()

# Find the PicoSystem library.
include(picosystem_sdk_import.cmake)

# Set up the Swift target.
execute_process(COMMAND xcrun -f swiftc OUTPUT_VARIABLE SWIFTC OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(${PROJECT_NAME})
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/_swiftcode.o
    COMMAND
        ${SWIFTC}
        -target armv6m-none-none-eabi -Xcc -mfloat-abi=soft -Xcc -fshort-enums
        -Xfrontend -function-sections -enable-experimental-feature Embedded -wmo -parse-as-library
        -cxx-interoperability-mode=default
        -Xcc -fno-exceptions
        -Xcc -std=c++17
        $$\( echo '$<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES>' | tr '\;' '\\n' | sed -e 's/\\\(.*\\\)/-Xcc -I\\1/g' \)
        $$\( echo '${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}'              | tr ' '  '\\n' | sed -e 's/\\\(.*\\\)/-Xcc -I\\1/g' \)
        ${CMAKE_CURRENT_LIST_DIR}/Main.swift
        -c -o ${CMAKE_CURRENT_BINARY_DIR}/_swiftcode.o
    DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/Main.swift
)
add_custom_target(swift-test-swiftcode DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/_swiftcode.o)

# Link the Swift object with the `picosys_c` library.
target_link_libraries(${PROJECT_NAME}
  picosys_c
  ${CMAKE_CURRENT_BINARY_DIR}/_swiftcode.o
)

add_dependencies(${PROJECT_NAME} swift-test-swiftcode)
pico_add_extra_outputs(${PROJECT_NAME})
pico_set_linker_script(${PROJECT_NAME} ${PICOSYSTEM_LINKER_SCRIPT})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.uf2 DESTINATION .)

# PicoSystem build options.
pixel_double(${PROJECT_NAME})          # 120x120 resolution game, pixel-doubled to 240x240
disable_startup_logo(${PROJECT_NAME})  # Skip the PicoSystem splash
#no_font(${PROJECT_NAME})              # Omit the default font
#no_spritesheet(${PROJECT_NAME})       # Omit the default spritesheet
#no_overclock(${PROJECT_NAME})         # Don't overclock