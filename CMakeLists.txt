cmake_minimum_required(VERSION 3.10)
project(CplusProj)

set(CMAKE_CXX_STANDARD 11)

add_executable(CplusProj main.cpp Plateau.cpp Plateau.h Case.cpp Case.h Pion.cpp Pion.h PlateauDamier.cpp PlateauDamier.h PlateauStratego.cpp PlateauStratego.h)