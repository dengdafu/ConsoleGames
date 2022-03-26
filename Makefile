CC=g++

PROGRAM_NAME=consoleGames

OBJ=main.o
OBJ+=utils.o
OBJ+=dummyGame.o
OBJ+=wordle.o
OBJ+=snake.o

FLAGS=-lncurses

consoleGames: main.o utils.o dummyGame.o wordle.o snake.o
	$(CC) -o $(PROGRAM_NAME) $(OBJ) $(FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp

utils.o: utils/utils.h utils/utils.cpp
	$(CC) -c utils/utils.cpp

dummyGame.o: DummyGame/dummyGame.h DummyGame/dummyGame.cpp game.h
	$(CC) -c DummyGame/dummyGame.cpp

wordle.o: Wordle/wordle.h Wordle/wordle.cpp game.h
	$(CC) -c Wordle/wordle.cpp

snake.o: Snake/snake.h Snake/snake.cpp game.h
	$(CC) -c Snake/snake.cpp

clean:
	rm *.o consoleGames