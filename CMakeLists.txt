# Define project
cmake_minimum_required(VERSION 3.0)
project(aim_trainer)

set(CMAKE_BUILD_TYPE Debug)

# Set the source directory
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/project/src")

# Include directories
include_directories("${SOURCE_DIR}")

# Define source files
set(SOURCE_FILES
    "${SOURCE_DIR}/Entities/CircleTarget.cpp"
    "${SOURCE_DIR}/Entities/CircleTarget.h"
    "${SOURCE_DIR}/Entities/Entity.h"
    "${SOURCE_DIR}/Entities/HitBox.cpp"
    "${SOURCE_DIR}/Entities/HitBox.h"
    "${SOURCE_DIR}/Screens/Screen.h"
    "${SOURCE_DIR}/Screens/GameScreen.h"
    "${SOURCE_DIR}/Screens/GameScreen.cpp"
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/Spawners/Spawner.h"
    "${SOURCE_DIR}/Spawners/Spawner.cpp"
    "${SOURCE_DIR}/Logger.h"
    "${SOURCE_DIR}/Logger.cpp"
    "${SOURCE_DIR}/GameData.h"
    "${SOURCE_DIR}/GameData.cpp"
    "${SOURCE_DIR}/Button.h"
    "${SOURCE_DIR}/Button.cpp"
    "${SOURCE_DIR}/Screens/MenuScreen.h"
    "${SOURCE_DIR}/Screens/MenuScreen.cpp"
    "${SOURCE_DIR}/ScreenManager.h"
    "${SOURCE_DIR}/ScreenManager.cpp"
    "${SOURCE_DIR}/Screens/PauseScreen.h"
    "${SOURCE_DIR}/Screens/PauseScreen.cpp"
    "${SOURCE_DIR}/Screens/SettingsScreen.h"
    "${SOURCE_DIR}/Screens/SettingsScreen.cpp"
    "${SOURCE_DIR}/Settings.h"
    "${SOURCE_DIR}/Crosshair.h"
    "${SOURCE_DIR}/Crosshair.cpp"
    "${SOURCE_DIR}/Velocity.h"
    "${SOURCE_DIR}/SpatialHash.h"
    "${SOURCE_DIR}/ScreenState.h"
)

# Add AddressSanitizer flags
#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
#endif()

# Define the executable target
add_executable(my_executable ${SOURCE_FILES})

# Get SFML
set(SFML_DIR "/home/rjlam55/Aim-Trainer/SFML/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add spdlog subdirectory
add_subdirectory(external/spdlog)

target_link_libraries(my_executable sfml-graphics sfml-window sfml-system spdlog::spdlog)

