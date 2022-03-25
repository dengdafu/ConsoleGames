CC=g++

consoleGames: main.o dummyGame.o wordle.o
	$(CC) -o consoleGames main.o dummyGame.o wordle.o

main.o: main.cpp
	$(CC) -c main.cpp

dummyGame.o: DummyGame/dummyGame.h DummyGame/dummyGame.cpp game.h
	$(CC) -c DummyGame/dummyGame.cpp

wordle.o: Wordle/wordle.h Wordle/wordle.cpp game.h
	$(CC) -c Wordle/wordle.cpp

clean:
	rm *.o consoleGames