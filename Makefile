P1-Hongchi : main.o tools.o dice.o
	g++ -o P1-Hongchi main.o tools.o dice.o
main.o : main.cpp tools.hpp dice.hpp
	g++ -c main.cpp
tools.o : tools.cpp tools.hpp
	g++ -c tools.cpp
dice.o : dice.cpp dice.hpp
	g++ -c dice.cpp
.PHONY : clean
clean :
	rm P1-Hongchi main.o tools.o dice.o
