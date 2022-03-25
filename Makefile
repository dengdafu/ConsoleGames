CC=g++

consoleGames: main.o dummyGame.o
	$(CC) -o consoleGames main.o dummyGame.o

main.o: main.cpp
	$(CC) -c main.cpp

dummyGame.o: DummyGame/dummyGame.h DummyGame/dummyGame.cpp game.h
	$(CC) -c DummyGame/dummyGame.cpp

clean:
	rm *.o consoleGames