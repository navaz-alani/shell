CXX=gcc
CXXFLAGS=-Wall -Werror -g
SOURCES=$(wildcard *.c)
OBJECTS=${SOURCES:.c=.o}
EXEC=shell

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.c
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf *.o $(EXEC)
