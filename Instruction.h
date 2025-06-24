// CMSC 411 Project - Summer 2025
// File: Instruction.h
// Desc: This class represents an instruction
// Date: June 23, 2025
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
using namespace std;
 
class Instruction{
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Instruction();
 
  // Destructor
  // Preconditions: None
  // Postconditions: None
  ~Instruction();
 
  // getType() - returns myType
  // Preconditions: myType is initialized
  // Postconditions: None
  string GetType();
 
  // setType() - sets value of myType
  // Preconditions: None
  // Postconditions: None
  void SetType(string type);

private:
  string m_myType;
};
 
#endif
