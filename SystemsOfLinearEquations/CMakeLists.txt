cmake_minimum_required(VERSION 3.23)
project(SystemsOfLinearEquations)

set(CMAKE_CXX_STANDARD 20)

add_library(Fraction Fraction.cpp Fraction.h)
add_library(Matrix Matrix.h Matrix.cpp)
add_library(GaussMethod GaussMethod.cpp GaussMethod.h)
add_library(RelaxationMethod RelaxationMethod.cpp RelaxationMethod.h)

add_executable(SystemsOfLinearEquations main.cpp)
add_executable(test_fraction test_fraction.cpp)