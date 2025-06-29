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

const string INSTRUCTION_CATEGORIES = {"ALU", "MEMORY", "CONTROL"};
const string MEMORY_INSTRUCTIONS = {"L.D", "L.I", "SD", "LW", "SW"};
const string ALU_INSTRUCTIONS = {"ADD", "ADDI", "ADD.D", "SUB.D", "SUB", "MUL.D", "DIV.D"};
const string CONTROL_INSTRUCTIONS = {"BEQ", "BNE", "J ADDR"};

 
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
