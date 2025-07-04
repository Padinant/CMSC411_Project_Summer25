# CMSC 411 Project - Summer 2025
# File: makefile
# Desc: The makefile for the project
# Date: June 23, 2025
# Authors: Padina Nasiri Toussi and Qanita Baqibillah

CXX = g++
CXXFLAGS = -Wall

testFile: Instruction.o Processor.o testFile.cpp
	$(CXX) $(CXXFLAGS) Instruction.o Processor.o testFile.cpp -o testFile

driver: Instruction.o Processor.o driver.cpp
	$(CXX) $(CXXFLAGS) Instruction.o Processor.o BranchPredictor.o driver.cpp -o driver

Processor.o: Processor.h Processor.cpp Instruction.o BranchPredictor.o
	$(CXX) $(CXXFLAGS) -c Processor.cpp

Instruction.o: Instruction.cpp Instruction.h
	$(CXX) $(CXXFLAGS) -c Instruction.cpp

BranchPredictor.o: BranchPredictor.cpp
	$(CXX) $(CXXFLAGS) -c BranchPredictor.cpp


clean:
	rm *.o*
	rm *~ 

run:
	./driver
