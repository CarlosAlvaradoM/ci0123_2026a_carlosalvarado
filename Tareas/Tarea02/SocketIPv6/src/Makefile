CXX = g++
CXXFLAGS = -Wall -g
TARGETS = servidor-ipv6 cliente-ipv6

all: $(TARGETS)

servidor-ipv6: VSocket.o Socket.o ipv6-udp-server.o
	$(CXX) $(CXXFLAGS) -o $@ $^

cliente-ipv6: VSocket.o Socket.o ipv6-udp-client.o
	$(CXX) $(CXXFLAGS) -o $@ $^

VSocket.o: VSocket.cc VSocket.h
	$(CXX) $(CXXFLAGS) -c VSocket.cc

Socket.o: Socket.cc Socket.h VSocket.h
	$(CXX) $(CXXFLAGS) -c Socket.cc

ipv6-udp-server.o: ipv6-udp-server.cc Socket.h
	$(CXX) $(CXXFLAGS) -c ipv6-udp-server.cc

ipv6-udp-client.o: ipv6-udp-client.cc Socket.h
	$(CXX) $(CXXFLAGS) -c ipv6-udp-client.cc

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean