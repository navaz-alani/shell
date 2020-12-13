CXX=gcc
CXXFLAGS=-Wall -Werror
SOURCES=$(wildcard *.c)
OBJECTS=${SOURCES:.c=.o}
EXEC=shell

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)
	rm -rf *.o

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf *.o $(EXEC)
