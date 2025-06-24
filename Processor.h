// CMSC 411 Project - Summer 2025
// File: Processor.h
// Desc: This class represents a processor
// Date: June 23, 2025
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include "Instruction.h"
using namespace std;
 
class Processor{
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Processor();
 
  // Destructor
  // Preconditions: None
  // Postconditions: None
  ~Processor();

  // loads instructions from the given file name into m_instructions
  // Preconditions: file_name contains the load instructions
  loadInstructions(file_name);

private:
  string m_instructions;
};
 
#endif
