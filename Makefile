CPP=g++
FLAGS=-Wall -Iinclude -Llibs
FILES=src/main.cpp src/Game.cpp src/Server.cpp src/Client.cpp src/utils/Console.cpp src/net/NetManager.cpp
LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

Game: src/main.cpp
	$(CPP) $(FLAGS) -o release/pac $(FILES) $(LIBS)