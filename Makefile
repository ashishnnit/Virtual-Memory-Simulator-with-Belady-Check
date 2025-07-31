CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = src/main.cpp src/FIFO.cpp src/LRU.cpp src/LFU.cpp src/Optimal.cpp src/Utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = pager

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
