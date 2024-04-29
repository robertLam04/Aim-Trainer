# Define project
cmake_minimum_required(VERSION 3.0)
project(aim_trainer)

# Define the executable target
add_executable(my_executable src/learn.cpp)

# Include SFML
set(SFML_DIR "/home/rjlam55/Simple-Aim-Trainer/project/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics window system REQUIRED)
target_include_directories(my_executable PRIVATE ${SFML_DIR})
target_link_libraries(my_executable sfml-graphics sfml-window sfml-system)
set_target_properties(my_executable PROPERTIES
    INSTALL_RPATH "$ORIGIN"
)