CXX = g++
CXXFLAGS = -Wall

proj2: 	Shop.o Game.o Ingredient.h proj2.cpp
	$(CXX) $(CXXFLAGS) Shop.o Ingredient.h Game.o proj2.cpp -o proj2

Game.o: Shop.o Ingredient.h Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Shop.o: Shop.h Shop.cpp Ingredient.h
	$(CXX) $(CXXFLAGS) -c Shop.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2
