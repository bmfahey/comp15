#
# Makefile for HW6
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g

hw6degrees: main.cpp hashfunc.cpp hashfunc.h ClassVec.h ClassVec.cpp Person.h\
		Person.cpp PersonHash.h PersonHash.cpp NodeVector.h \
		NodeVector.cpp
	${CXX} ${CXXFLAGS} -o hw6degrees main.cpp hashfunc.cpp ClassVec.cpp \
		Person.cpp PersonHash.cpp NodeVector.cpp

clean:
	rm -f hw6degrees *.o *.dSYM

provide:
	provide comp15 hw6 main.cpp Makefile ReadMe.md hashfunc.cpp hashfunc.h\
		ClassVec.h ClassVec.cpp Person.h Person.cpp PersonHash.h \
		PersonHash.cpp NodeVector.h NodeVector.cpp
