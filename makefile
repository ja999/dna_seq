CXXFLAGS += -std=c++0x -fopenmp
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

tests: testWord testGraph testScx

testWord: word.cpp tests/testWord.cpp
	$(CXX) $(CXXFLAGS) word.cpp tests/testWord.cpp -o $(DIR)testWord

testScx: word.cpp tests/testScx.cpp wordsGraph.cpp specimen.cpp
	$(CXX) $(CXXFLAGS) word.cpp tests/testScx.cpp wordsGraph.cpp specimen.cpp -o $(DIR)testScx

testGraph: word.cpp tests/testGraph.cpp wordsGraph.cpp
	$(CXX) $(CXXFLAGS) word.cpp tests/testGraph.cpp wordsGraph.cpp -o $(DIR)testGraph

clean:
	rm -rf bin/*
