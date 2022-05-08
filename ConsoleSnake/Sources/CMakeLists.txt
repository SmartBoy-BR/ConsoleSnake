# CMakeList.txt: projeto de CMake para ConsoleSnake, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Adicione a origem ao executável deste projeto.
add_executable (ConsoleSnake "Main.cpp" "Game.cpp" "Timer.cpp" "Stage.cpp" "Point.cpp" "TitleScreen.cpp" "UI.cpp" "GridMap.cpp" "Snake.cpp" "BodyPiece.cpp" "Food.cpp")

# TODO: Adicione testes e instale destinos, se necessário.
