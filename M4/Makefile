.default: all

all: car

clean:
	rm -f car *.o

car: board.o carboard.o helper.o player.o game.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
