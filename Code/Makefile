P12 : main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
	g++ -o p12 main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
main.o : main.cpp tools.hpp CList.hpp
	g++ -c main.cpp CList.hpp
tools.o : tools.cpp tools.hpp
	g++ -c tools.cpp
dice.o : dice.cpp dice.hpp
	g++ -c dice.cpp
enums.o : enums.cpp enums.hpp
	g++ -c enums.cpp
Player.o : Player.cpp Player.hpp
	g++ -c Player.cpp
column.o : column.cpp column.hpp
	g++ -c column.cpp
game.o : game.cpp game.hpp
	g++ -c game.cpp
board.o : board.cpp board.hpp
	g++ -c board.cpp
scoreboard.o : Scoreboard.cpp Scoreboard.hpp
	g++ -c Scoreboard.cpp
score.o : Score.cpp Score.hpp
	g++ -c Score.cpp
.PHONY : clean
clean :
	rm p12 main.o tools.o dice.o enums.o Player.o column.o game.o board.o scoreboard.o score.o
