# Simple-Aim-Trainer

## Author:
**Robert Lam**  
Email: [rjlam2004@gmail.com](mailto:rjlam2004@gmail.com)

## Product Description:
An aim trainer, built using C++, SFML, and CMake. Designed to help improve users' aiming skills with a mouse.

## Learning Objectives:
- Develop basic game mechanics such as target spawning & movement, screen state management, and collision detection.
- Design a graphical user interface (GUI) for a smooth user experience.
- Apply design patterns, good abstraction & OOP to make the product maintainable and scalable.
- Learn **C++**, **CMake**, and **SFML**.

## How to Play

```bash
# 1. Clone the Repository:
git clone <repository-url>
cd Aim-Trainer

# 2. Install Dependencies:
sudo apt update
sudo apt install cmake
sudo apt install libsfml-dev
git submodule update --init --recursive

# 3. Create a Build Directory in the Top Level:
mkdir build
cd build

# 4. Compile and Run:
cmake ..
make
./my_executable
