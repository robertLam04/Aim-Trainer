# Define project
cmake_minimum_required(VERSION 3.0)
project(aim_trainer)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Add compiler flags for debugging symbols
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Define source files
Set(SOURCE_FILES 
"project/src/Entities/CircleTarget.cpp"
"project/src/Entities/CircleTarget.h"
"project/src/Entities/Entity.cpp"
"project/src/Entities/Entity.h"
"project/src/Entities/HitBox.cpp"
"project/src/Entities/HitBox.h"
"project/src/main.cpp"
)

# Define the executable target
add_executable(my_executable ${SOURCE_FILES})

# Include SFML
set(SFML_DIR "/home/rjlam55/Aim-Trainer/SFML/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics window system REQUIRED)
target_include_directories(my_executable PRIVATE ${SFML_DIR})
target_link_libraries(my_executable sfml-graphics sfml-window sfml-system)
set_target_properties(my_executable PROPERTIES
    INSTALL_RPATH "$ORIGIN"
)

