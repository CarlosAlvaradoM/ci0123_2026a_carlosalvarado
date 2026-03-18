CXX = g++
CXXFLAGS = -Wall -g
TARGETS = servidor cliente

all: $(TARGETS)

servidor: VSocket.o Socket.o ipv4-udp-server.o
	$(CXX) $(CXXFLAGS) -o $@ $^

cliente: VSocket.o Socket.o ipv4-udp-client.o
	$(CXX) $(CXXFLAGS) -o $@ $^

VSocket.o: VSocket.cc VSocket.h
	$(CXX) $(CXXFLAGS) -c VSocket.cc

Socket.o: Socket.cc Socket.h VSocket.h
	$(CXX) $(CXXFLAGS) -c Socket.cc

ipv4-udp-server.o: ipv4-udp-server.cc VSocket.h Socket.h
	$(CXX) $(CXXFLAGS) -c ipv4-udp-server.cc

ipv4-udp-client.o: ipv4-udp-client.cc VSocket.h Socket.h
	$(CXX) $(CXXFLAGS) -c ipv4-udp-client.cc

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean