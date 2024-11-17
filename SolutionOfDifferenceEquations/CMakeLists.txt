cmake_minimum_required(VERSION 3.23)
project(SolutionOfDifferentialEquations)

set(CMAKE_CXX_STANDARD 20)

add_library(System1 test/system1.cpp test/system1.h)

add_library(Border BoundaryValueProblem.cpp BoundaryValueProblem.h)

add_executable(SolutionOfDifferentialEquations main.cpp BoundaryValueProblem.cpp BoundaryValueProblem.h test/system1.cpp test/system1.h)
