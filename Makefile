CPP=g++
FLAGS=-Wall
FILES=src/main.cpp src/Game.cpp
LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -pthread

Game: src/main.cpp
	$(CPP) $(FLAGS) -o release/pac $(FILES) $(LIBS)