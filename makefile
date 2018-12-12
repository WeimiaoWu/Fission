CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11 -g3

Fission: fussions.o baseboard.o fussionboard.o piece.o fussion.o king.o math.o
	${CXX} -o $@ ${CXXFLAGS} $^
