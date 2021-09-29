cmake_minimum_required(VERSION 3.20)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY") # needed for cmake to stop complaining when compiler failed to compile a "standard" test program
#these two lines are alternative to the line above
#set(CMAKE_C_COMPILER_WORKS 1)
#set(CMAKE_CXX_COMPILER_WORKS 1)
project(game_dev_maths
  VERSION 0.0.0.1
  LANGUAGES C CXX
)

add_executable(main
  main.cpp
 "vector/vector.hpp")

set_target_properties(main
  PROPERTIES
  CXX_STANDARD 20
)

