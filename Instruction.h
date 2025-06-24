// CMSC 411 Project - Summer 2025
// File: Instruction.h
// Desc: This class represents an instruction
// Date: June 23, 2025
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <string>
#include <fstream>
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
  string getType();
 
  // setType() - sets value of myType
  // Preconditions: None
  // Postconditions: None
  void setType(string type);

  // getPlaintext() - returns plaintext
  // Preconditions: plaintext is initialized
  // Postconditions: None
  string getPlaintext();
 
  // setPlaintext() - sets value of plaintext
  // Preconditions: None
  // Postconditions: None
  void setPlaintext(string text);

private:
  string m_myType;
  string m_plaintext;
};
 
#endif
