# CMSC 411 Project - Summer 2025
# File: makefile
# Desc: The makefile for the project
# Date: June 23, 2025

CXX = g++
CXXFLAGS = -Wall

driver: Instruction.o Processor.o driver.cpp
	$(CXX) $(CXXFLAGS) Instruction.o Processor.o driver.cpp -o driver

Processor.o: Processor.h Processor.cpp Instruction.o
	$(CXX) $(CXXFLAGS) -c Processor.cpp

Instruction.o: Instruction.cpp Instruction.h
	$(CXX) $(CXXFLAGS) -c Instruction.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver
