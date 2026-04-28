CXX = g++
CXXFLAGS = -Wall -pthread -std=c++11

SRC = main.cc Cliente.cc Interceptor.cc Servidor.cc IPC.cc
OBJ = $(SRC:.cc=.o)

TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(CXXFLAGS)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)
