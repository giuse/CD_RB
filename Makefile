
CC=g++
CFLAGS=-c -Wall -std=c++0x
GDBFLAGS=-g
LDFLAGS=
RM=rm -f
SOURCES=centroidDecomp.cpp utils.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test
EXEC_OPTS=input.txt 20 10
RESULTS=Ltest.txt Rtest.txt

# all: $(SOURCES) $(EXECUTABLE)
all: clean $(SOURCES) $(EXECUTABLE)
	./$(EXECUTABLE) $(EXEC_OPTS)
	if cmp -s "Ltest.txt" "Ltrg.txt" && cmp -s "Rtest.txt" "Rtrg.txt"; then echo "Results match"; else echo "\n\n\t\tERROR: RESULTS DO NOT MATCH!!\n\n\n"; fi

$(EXECUTABLE): $(OBJECTS)
	# Switch the next row to inject gdb markers in the executable
	# $(CC) $(LDFLAGS) $(GDBFLAGS) $(OBJECTS) -o $@
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) $(RESULTS)
