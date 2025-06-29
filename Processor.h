// CMSC 411 Project - Summer 2025
// File: Processor.h
// Desc: This class represents a processor
// Date: June 23, 2025

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Instruction.h"
using namespace std;

// const string INSTRUCTION_CATEGORIES = {"ALU", "MEMORY", "CONTROL"};
// const string MEMORY_INSTRUCTIONS = {"L.D", "L.I", "SD", "LW", "SW"};
// const string ALU_INSTRUCTIONS = {"ADD", "ADDI", "ADD.D", "SUB.D", "SUB", "MUL.D", "DIV.D"};
// const string CONTROL_INSTRUCTIONS = {"BEQ", "BNE", "J ADDR"};

 
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
  // fetches the next instruction from m_instructions (corresponds to the IF stage)
  // todo: return the instruction plaintext
  void instructionFetch();

  // NEW (not yet in Processor.cpp)
  // decode a given plaintext instruction and create an instruction object, (corresponds to the ID stage)
  // would interpret the instruction type, its dependencies, and other relevant details
  Instruction instructionDecode(string instructionText);

  // NEW (not yet in Processor.cpp)
  // finds the names of the dependencies for a given instruction (is helper to instructionDecode())
  // todo: implement a way to return the dependencies (either member attributes, or return a list of register names)
  void getDependencies(Instruction x);






  // DISPLAY RELATED FUNCTIONS:
  // TODO LATER






  // HELPER FUNCTIONS
  
  // trims any extra whitespace from before and after from the line
  string trimExtraWhiteSpace(string s1);



private:
  // Instruction* m_instructions[0]; // this corresponds to the rows
  string m_instructions[0]; // this corresponds to the plaintext instructions
  string m_filename;
  // NEW (not yet in Processor.cpp)
  int instruction_pointer = 0;  // points at the place in m_instruction, where the next instruction is supposed to be
  int memory[18] = {0};   // when initializing the processor, set as memory values from the writeup
  map<string, int> registers = {};  // represents registers and the values stored in them
};
 
#endif
