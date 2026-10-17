CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: calculator_app

libcalculator.a: calculator.o
	ar rcs libcalculator.a calculator.o

calculator.o: calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c calculator.cpp

calculator_app: main.o libcalculator.a
	$(CXX) $(CXXFLAGS) main.o -L. -lcalculator -o calculator_app

main.o: main.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o *.a calculator_app
