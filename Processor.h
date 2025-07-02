// CMSC 411 Project - Summer 2025
// File: Processor.h
// Desc: This class represents a processor
// Date: June 23, 2025
// Authors: Padina Nasiri Toussi and Qanita Baqibillah

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include "Instruction.h"
using namespace std;

// Constants corresponding to instruction categories and types
// const array<string, 3> INSTRUCTION_CATEGORIES = {"ALU", "MEMORY", "CONTROL"};
// const array<string, 5> MEMORY_INSTRUCTIONS = {"L.D", "L.I", "SD", "LW", "SW"};
// const array<string, 7> ALU_INSTRUCTIONS = {"ADD", "ADDI", "ADD.D", "SUB.D", "SUB", "MUL.D", "DIV.D"};
// const array<string, 3> CONTROL_INSTRUCTIONS = {"BEQ", "BNE", "J ADDR"};
const array<int, 19> DEFAULT_MEMORY = {45, 12, 0, 92, 10, 135, 254, 127, 18, 4,55, 8, 2, 98, 13, 5, 233, 158, 167};

 
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
  void load(string regAddress, string memAddress);
  
  // NEW (not yet in Processor.cpp)
  // loads data from register into memory
  // 19 --> 19%(18+1) = 0
  // 20 --> 20%19 = 1
  void store(string regAddress, string memAddress);

  // NEW 
  // convert memory address (from instructions) to a memory index between 0-18 inclusive
  // Example: mem_address = "0($1)" ---> 1
  // Example: mem_address = "$7" ---> 7
  int memoryAddressToIndex(string memAddress);



  // PIPELINING IMPLEMENTATION FUNCTIONS:
  // KEY FUNCTION: 
  // This function would be called to start the simulated pipeline
  // Postcondition: when done, would also save the pipeline results into a new file
  void startProcessor();



  // NEW (not yet in Processor.cpp)
  // fetches the next instruction from m_instructions (corresponds to the IF stage)
  // creates instruction object + update pointer (+ todo later: figure out branch prediction at this stage)
  Instruction instructionFetch();

  // NEW (not yet in Processor.cpp)
  // decode a given instruction object and load the values of all delivarables (corresponds to the ID stage)
  // also check if we should stall (ie repeat this stage)
  // would interpret its dependencies, and other relevant details not already known
  void instructionDecode(Instruction inst);

  // NEW (not yet in Processor.cpp)
  // finds the names of the dependencies for a given instruction (is helper to instructionDecode())
  // todo: implement a way to return the dependencies (either member attributes, or return a list of register names)
  void getDependencies(Instruction x);






  // DISPLAY RELATED FUNCTIONS:
  // TODO LATER

  //Export spreadsheet to file
    // takes 2d array of strings
    // using filename
  void exportSpreadsheet(string filename, string** spreadsheet, int rows, int cols);



  // HELPER FUNCTIONS
  
  // trims any extra whitespace from before and after from the line
  string trimExtraWhiteSpace(string s1);

  // given a valid plaintext line of code, checks whether there is a label and removes it if there is
  // Examples:
  // "Loop1: ADD F1, F2, F3" ---> "ADD F1, F2, F3"
  // "ADD F1, F2, F3" ---> "ADD F1, F2, F3"
  string removeLabel(string plaintext);

  // given a plaintext line of code, returns "" if there is no label or the label name if there is a label
  // Examples:
  // "Loop1: ADD F1, F2, F3" ---> "Loop1"
  // "ADD F1, F2, F3" ---> ""
  string getLabel(string plaintext);


private:
  // program instruction related attributes
  string* m_instructions; // this corresponds to the plaintext instructions
  int m_instructions_len; // how many instructions in m_instructions (and the instruction file)
  string m_filename;
  int m_instruction_pointer = 0;  // points at the place in m_instruction, where the next instruction is supposed to be
  
  // memory and registers
  int m_memory[19] = {0};   // when initializing the processor, set as memory values from the writeup (0-18 inclusive)
  map<string, int> m_registers = {};  // represents registers and the values stored in them

  // logistics attributes about pipelining
  vector<Instruction> m_pipeline; // This vector represents all the instructions within the pipeline, in order of being fetched
  int m_clock = 0; // corresponds to the current cycle within the entire pipeline (pipeline starts at clock cycle 1)
  int m_first_alive_instruction_ptr = 0; // points at the place in pipeline, with the first alive instruction to start on
  //                                     // if this is the same as the pipeline size, it probably means there isn't any alive instructions

};
 
#endif
