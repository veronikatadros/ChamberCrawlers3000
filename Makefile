CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = cc3k
CCFILES = $(wildcard *.cc)
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}
LDFLAGS = -L/usr/local/opt/ncurses/lib -lncursesw -lncurses

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f ${EXEC} ${OBJECTS} ${DEPENDS}
