
CC=gcc
CFLAGS=-c -Wall -fPIC
GDBFLAGS=-g
LDFLAGS=-lm
RM=rm -f
SOURCES=centroidDecomp.c utils.c
TESTMAIN=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=runme
EXEC_OPTS=input.txt 20 10
RESULTS=Ltest.txt Rtest.txt
ARCHIVER=ar
ARFLAGS=-cvq
LIBNAME=libcentroiddecomposition.so

lib: clean test $(OBJECTS)
	$(CC) -shared -o $(LIBNAME) $(OBJECTS)

test: $(SOURCES) $(EXECUTABLE)
	./$(EXECUTABLE) $(EXEC_OPTS)
	if cmp -s "Ltest.txt" "Ltrg.txt" && cmp -s "Rtest.txt" "Rtrg.txt"; then echo "-> Results match"; else echo "\n\n\t\tERROR: RESULTS DO NOT MATCH!!\n\n\n"; fi

$(EXECUTABLE): $(TESTMAIN) $(OBJECTS)
	# Switch the next row to inject gdb markers in the executable
	# $(CC) $(GDBFLAGS) $(OBJECTS) $(TESTMAIN) -o $@ $(LDFLAGS)
	$(CC) $(OBJECTS) $(TESTMAIN) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) $(RESULTS) $(LIBNAME)
