cmake_minimum_required(VERSION 3.10)
project(BoardGames)

set(CMAKE_CXX_STANDARD 11)

add_executable(BoardGames main.cpp Plateau.cpp Plateau.h Case.cpp Case.h Pion.cpp Pion.h PlateauDamierInternational.cpp PlateauDamierInternational.h PlateauStratego.cpp PlateauStratego.h PlateauEchiquier.cpp PlateauEchiquier.h PlateauDamier.cpp PlateauDamier.h PlateauDamierAnglais.cpp PlateauDamierAnglais.h PlateauCombinatoireAbstrait.cpp PlateauCombinatoireAbstrait.h)