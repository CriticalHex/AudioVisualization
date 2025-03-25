TARGET = AudioVisualization.exe
SRC_FILES = main.cpp Lattice.cpp Rectangle.cpp ../WASAPI/Listener.cpp

OBJECTS = $(SRC_FILES:.cpp=.o)

INCLUDE_PATH = -I"C:\mingw64\include" -I"..\WASAPI"

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lole32 -lfftw3f
LIB_PATH = 
CXX = g++

all: $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CXX) -o $@ $^ $(LIB_PATH) $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(INCLUDE_PATH)

clean:
	@$(RM) $(OBJECTS) $(TARGET)

run:
	@$(TARGET)

.PHONY: clean run

main.o: main.cpp Lattice.o Listener.o Rectangle.o
Lattice.o: Lattice.cpp
Rectangle.o: Rectangle.cpp
Listener.o: ../WASAPI/Listener.cpp