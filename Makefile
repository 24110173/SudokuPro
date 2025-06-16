CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = src/main.cpp src/sudoku.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sudoku

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(TARGET).exe
