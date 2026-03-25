# Variables de compilación
CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lssl -lcrypto
TARGET = tcp-cli.out
SOURCES = tcp-cli.cc SSLSocket.cc Socket.cc VSocket.cc

# Regla por defecto (make)
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

# Regla para ejecutar (make run)
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar (make clean)
clean:
	rm -f $(TARGET)

# Evita conflictos con archivos que se llamen igual que las reglas
.PHONY: run clean