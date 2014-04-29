CXXFLAGS += "-std=c++11"
CXX = g++-4.8
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -DDEBUG
else
	CXXFLAGS +=-DNDEBUG
endif
DIR = bin/
main: word.cpp wordsGraph.cpp specimen.cpp population.cpp main.cpp
	$(CXX) $(CXXFLAGS) word.cpp wordsGraph.cpp specimen.cpp population.cpp main.cpp -o $(DIR)GacekSequencer

tests: testWord testGraph

testWord: word.cpp tests/testWord.cpp
	$(CXX) $(CXXFLAGS) word.cpp tests/testWord.cpp -o $(DIR)testWord

testGraph: word.cpp tests/testGraph.cpp wordsGraph.cpp
	$(CXX) $(CXXFLAGS) word.cpp tests/testGraph.cpp wordsGraph.cpp -o $(DIR)testGraph

clean:
	rm -rf bin/*
