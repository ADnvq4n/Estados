
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Iinclude -IC:/SFML/include

LDFLAGS = -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

TARGET = mascota_virtual
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\*.o $(TARGET).exe 2>nul || true



