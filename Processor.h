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

private:
  Instruction* m_instructions;
  string m_filename;
};
 
#endif
