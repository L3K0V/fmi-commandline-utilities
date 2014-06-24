CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=main.cc filter.cc filter_chain.cc filter_word.cc filter_capitalize.cc filter_encode.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=cmdutils

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm *.seri
	rm out*
	rm $(EXECUTABLE)


