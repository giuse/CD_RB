
CC=g++
CFLAGS=-c -Wall -std=c++0x
GDBFLAGS=-g
LDFLAGS=
RM=rm
SOURCES=centroidDecomp.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	# Switch the next row to inject gdb markers in the executable
	# $(CC) $(LDFLAGS) $(GDBFLAGS) $(OBJECTS) -o $@
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
