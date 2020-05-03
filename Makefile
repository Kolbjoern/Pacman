CPP=g++
FLAGS=-Wall -Iinclude -Llibs
FILES=src/main.cpp src/Game.cpp src/Server.cpp src/Client.cpp
LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

Game: src/main.cpp
	$(CPP) $(FLAGS) -o release/pac $(FILES) $(LIBS)