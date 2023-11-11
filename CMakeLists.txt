cmake_minimum_required(VERSION 3.24)
project(G_lab_sim)

set(CMAKE_CXX_STANDARD 17)

add_executable(G_lab_sim main.cpp CPU_sim/sim.c)
