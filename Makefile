
CC=g++
CFLAGS=-c -Wall -std=c++0x
GDBFLAGS=-g
LDFLAGS=
RM=rm
SOURCES=centroidDecomp.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test
EXEC_OPTS=input.txt 20 10

all: $(SOURCES) $(EXECUTABLE)
	./$(EXECUTABLE) $(EXEC_OPTS)

$(EXECUTABLE): $(OBJECTS)
	# Switch the next row to inject gdb markers in the executable
	# $(CC) $(LDFLAGS) $(GDBFLAGS) $(OBJECTS) -o $@
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
