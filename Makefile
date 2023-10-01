CXX = g++
CXXFLAGS = -Wall

main: 	Shop.o Game.o main.o
	$(CXX) $(CXXFLAGS) Shop.o Game.o main.o -o main

main.o: main.cpp Ingredient.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Ingredient.h Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Shop.o: Shop.h Shop.cpp Ingredient.h
	$(CXX) $(CXXFLAGS) -c Shop.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./main
