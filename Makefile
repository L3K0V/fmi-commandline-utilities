CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cc filter.cc filter_chain.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=cmdutils

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)


