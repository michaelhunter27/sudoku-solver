CXX = g++
SRCS = cell.cpp puzzle.cpp solver.cpp
OBJS =  cell.o puzzle.o solver.o
HEADERS = cell.h puzzle.h

solver: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o solver -municode

${OBJS}: ${SRCS}
	${CXX} -c $(@:.o=.cpp)