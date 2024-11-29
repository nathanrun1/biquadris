# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -Wextra

# Directories (all files in the same directory)
TARGET = biquadris
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)

# Rules
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
