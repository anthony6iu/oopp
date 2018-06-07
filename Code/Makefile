p12 : main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
	g++ -std=c++11 -o p12 main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
main.o : main.cpp tools.hpp CList.hpp
	g++ -std=c++11 -c main.cpp CList.hpp
tools.o : tools.cpp tools.hpp
	g++ -std=c++11 -c tools.cpp
dice.o : dice.cpp dice.hpp
	g++ -std=c++11 -c dice.cpp
enums.o : enums.cpp enums.hpp
	g++ -std=c++11 -c enums.cpp
Player.o : Player.cpp Player.hpp
	g++ -std=c++11 -c Player.cpp
column.o : column.cpp column.hpp
	g++ -std=c++11 -c column.cpp
game.o : game.cpp game.hpp
	g++ -std=c++11 -c game.cpp
board.o : board.cpp board.hpp
	g++ -std=c++11 -c board.cpp
scoreboard.o : Scoreboard.cpp Scoreboard.hpp
	g++ -std=c++11 -c Scoreboard.cpp
score.o : Score.cpp Score.hpp
	g++ -std=c++11 -c Score.cpp
.PHONY : clean
clean :
	rm p12 main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
