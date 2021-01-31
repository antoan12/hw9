CXX=g++
CCLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11
OBJS=main.o libfirewall.so libinput.so ip.o field.o port.o string.o
EXE=firewall.exe
RM=rm -rf *.o *so *.exe

$(EXE): main.o libfirewall.so libinput.so
	$(CCLINK) main.o libfirewall.so libinput.so -o $(EXE)

main.o: main.cpp input.h
	$(CCLINK) $(CXXFLAGS) -c main.cpp

libfirewall.so: ip.o field.o port.o string.o
	$(CCLINK) $(CXXFLAGS) -shared ip.o field.o port.o string.o -o libfirewall.so

ip.o: ip.h ip.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic ip.cpp

field.o: field.h field.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic field.cpp

port.o: port.h port.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic port.cpp

string.o: string.h string.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic string.cpp

clean:
	$(RM)