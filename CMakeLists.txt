# Define project
cmake_minimum_required(VERSION 3.0)
project(aim_trainer)

# Set the source directory
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/project/src")

# Include directories
include_directories("${SOURCE_DIR}")

# Define source files
set(SOURCE_FILES
    "${SOURCE_DIR}/Entities/CircleTarget.cpp"
    "${SOURCE_DIR}/Entities/CircleTarget.h"
    "${SOURCE_DIR}/Entities/Entity.cpp"
    "${SOURCE_DIR}/Entities/Entity.h"
    "${SOURCE_DIR}/Entities/HitBox.cpp"
    "${SOURCE_DIR}/Entities/HitBox.h"
    "${SOURCE_DIR}/Screens/Screen.h"
    "${SOURCE_DIR}/Screens/RangeScreen.h"
    "${SOURCE_DIR}/Screens/RangeScreen.cpp"
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/Spawners/Spawner.h"
    "${SOURCE_DIR}/Spawners/Spawner.cpp"
    "${SOURCE_DIR}/Logger.h"
    "${SOURCE_DIR}/Logger.cpp"
)

# Define the executable target
add_executable(my_executable ${SOURCE_FILES})

# Get SFML
set(SFML_DIR "/home/rjlam55/Aim-Trainer/SFML/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add spdlog subdirectory
add_subdirectory(external/spdlog)

target_link_libraries(my_executable sfml-graphics sfml-window sfml-system spdlog::spdlog)

