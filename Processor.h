// CMSC 411 Project - Summer 2025
// File: Processor.h
// Desc: This class represents a processor
// Date: June 23, 2025

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include <string>
#include <fstream>
#include "Instruction.h"
using namespace std;
 
class Processor{
public:

  // Constructor
  // Preconditions: None
  // Postconditions: None
  Processor();

  // Overloaded Constructor
  // Preconditions: None
  // Postconditions: None
  Processor(string filename);
 
  // Destructor
  // Preconditions: None
  // Postconditions: None
  ~Processor();

  // loads instructions from the given file name into m_instructions
  // Preconditions: filename contains valid instructions
  void loadInstructions(string filename);


  // MEMORY FUNCTIONS:

  // NEW (not yet in Processor.cpp)
  // loads data from memory into register
  void load(string register_address, string memory_address);
  
  // NEW (not yet in Processor.cpp)
  // loads data from register into memory
  void store(string register_address, string memory_address);



  // PIPELINING IMPLEMENTATION FUNCTIONS:

  // NEW (not yet in Processor.cpp)
  // decode a given instruction, (this would correspond to the ID stage)
  // would interpret the instruction type, its dependencies, and other relevant details
  void instructionDecode(Instruction x);

  // NEW (not yet in Processor.cpp)
  // finds the names of the dependencies for a given instruction (is helper to instructionDecode())
  // todo: implement a way to return the dependencies (either member attributes, or return a list of register names)
  void getDependencies(Instruction x);




  // DISPLAY RELATED FUNCTIONS:
  // TODO LATER



private:
  Instruction* m_instructions[0];
  string m_filename;
  // NEW (not yet in Processor.cpp)
  int memory[18] = {0};   // when initializing the processor, set as memory values from the writeup
  //                            // OR: replace this with a global constant

};
 
#endif
