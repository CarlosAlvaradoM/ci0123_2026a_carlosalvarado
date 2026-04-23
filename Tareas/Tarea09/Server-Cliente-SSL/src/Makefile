CXX = g++
CXXFLAGS = -Wall -std=c++20
LIBS = -lssl -lcrypto -pthread

# Archivos comunes
COMMON = SSLSocket.cc Socket.cc VSocket.cc

all: server_thread server_fork client

# 🔹 Servidor con hilos
server_thread:
	$(CXX) $(COMMON) SSLServerThread.cc -o server_thread $(LIBS)

# 🔹 Servidor con fork
server_fork:
	$(CXX) $(COMMON) SSLServerFork.cc -o server_fork $(LIBS)

# 🔹 Cliente
client:
	$(CXX) $(COMMON) SSLClient.cc -o client $(LIBS)

clean:
	rm -f server_thread server_fork client *.o