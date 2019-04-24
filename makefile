CXX=g++
CXXFLAGS=-std=c++11 -fno-stack-protector
OBJ=Accounting_system.o data_manipulation.o user_interface.o
all: Accounting_system
Accounting_system: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
data_manipulation.o: data_manipulation.cpp
	$(CXX) $(CXXFLAGS) -c $<
user_interface.o: user_interface.cpp
	$(CXX) $(CXXFLAGS) -c $<
Accounting_system.o: Accounting_system.cpp
	$(CXX) $(CXXFLAGS) -c $<