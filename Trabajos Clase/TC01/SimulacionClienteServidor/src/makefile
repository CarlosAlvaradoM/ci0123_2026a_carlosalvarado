# Makefile para compilar el programa
# Ubicación: src/Makefile

# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -pthread -std=c++11
TARGET = programa
SRCDIR = .
OBJDIR = obj

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

# Regla principal
all: $(TARGET)

# Crear directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilar el ejecutable
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CXXFLAGS)

# Compilar archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos generados
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Declarar reglas como phony
.PHONY: all run clean