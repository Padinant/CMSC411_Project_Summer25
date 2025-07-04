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
#include "BranchPredictor.cpp"  // note: potentially remove this if it shouldn't be here
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
  Processor(string filename, string outputFile);
 
  // Destructor
  // Preconditions: None
  // Postconditions: None
  ~Processor();

  // PUBLIC HELPERS FOR TESTING
  void setRegisterValue(string reg, int value);
  int getMemoryValue(int index);
  int getRegisterValue(string reg);
  // loads instructions from the given file name into m_instructions
  // Preconditions: filename contains valid instructions
  void loadInstructions(string filename);


  // MEMORY FUNCTIONS:

  // NEW (not yet in Processor.cpp)
  // loads data from memory into register
  void load(string reg_address, string mem_address);
  
  // NEW (not yet in Processor.cpp)
  // loads data from register into memory
  // 19 --> 19%(18+1) = 0
  // 20 --> 20%19 = 1
  void store(string reg_address, string mem_address);

  // NEW 
  // convert memory address (from instructions) to a memory index between 0-18 inclusive
  // Example: mem_address = "0($1)" ---> 1
  // Example: mem_address = "$7" ---> 7
  int memoryAddressToIndex(string mem_address);

  // convert valid register address (from instructions) to a memory index between 0-31 inclusive
  // Valid Example: register_address = "F24" ---> 24
  // Invalid Example: register_address = "5" ---> -1
  int registerAddressToIndex(string register_address);

  // given a string with '(' and ')', returns the substring inside those brackets
  // if unsuccessful, return ""
  // precondition: text ends in the character ')'
  string getSubstringInsideBrackets(string text);

  // given a string with '(', returns the substring before reaching those
  // if unsuccessful, return ""
  // precondition: text ends in the character '('
  string getSubstringBeforeBrackets(string text);

  // given an int value and an addrLocation (), returns a string representation for the address
  // Precondition: addrLocation is in ["MEMORY", "R_INT", "R_F"]
  // Examples:
  // (5, "MEMORY") --> "5"
  // (5, "R_INT") --> "$5"
  // (5, "R_F") --> "F5"
  // unexpected: --> ""
  string getIndexToAddressWithoutOffset(int value, string addrLocation);




  // PIPELINING IMPLEMENTATION FUNCTIONS:
  // KEY FUNCTION: 
  // This function would be called to start the simulated pipeline
  // Postcondition: when done, would also save the pipeline results into a new file
  void startProcessor();

  // fetches the next instruction from m_instructions (corresponds to the IF stage)
  // creates instruction object + update pointer (+ todo later: figure out branch prediction at this stage)
  Instruction instructionFetch();

  // decode a given instruction object and load the values of all delivarables (corresponds to the ID stage)
  // also check if we should stall (ie repeat this stage)
  // would interpret its dependencies, and other relevant details not already known
  void instructionDecode(Instruction &inst);

  // finds the values of the dependencies for a given instruction (is helper to instructionDecode())
  // Precondition: IF stage has been called so we do know the names of the operands
  void getOperandVals(Instruction &x);

  // return a boolean on whether we are allowed to move forward to the beginning of the execute stage, for the current instruction
  // this function also references the forwarding vectors and the instruction type and category
  bool isExecuteAllowed(Instruction &x);


  // BRANCH PREDICTION RELATED FUNCTIONS
  // Precondition: Instruction is a control instruction, and is at the IF stage
  // For reference (don't modify these values)
  // if you predict taken: m_predicted_taken = 1
  // if you predict not taken: m_predicted_taken = 0
  // if something unexpected happens and no prediction is made: m_predicted_taken = -1
  // What this function does: if predict taken: 1, if you predict not taken: 0, unexpected: -1
  int getBranchPrediction(Instruction cInst);

  // Get the actual branch determination result (1 for taken, 0 for not taken) based on m_s1, m_s2, m_dest, m_myType from the Instruction
  int getBranchActual(Instruction cInst);

  // given a labelName, return the index in which that label can be access on m_instructions
  // note: if labelName is valid, it should be in the range of (0, m_instructions_len)
  // if you can't find labelName, return -1
  // Example: m_instructions = ["J Loop2", "Label1: ...", "...", "...", "Label2: ..."]
  // findLabelIndex("Label1") --> 1
  // findLabelIndex("Label2") --> 4
  int findLabelIndex(string labelName);


  // NEW
  // Converts pipline into 2D array
  void convertPipline();



  // DISPLAY RELATED FUNCTIONS:

  //Export spreadsheet to file
  // takes 2d array of strings
  // using filename
  void exportSpreadsheet(string filename, string** spreadsheet, int rows, int cols);

  // Display/print main memory
  void displayMemory();

  // Display/print int registers
  void displayRegistersInt();

  // Display/print F registers
  void displayRegistersF();


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
  string m_filename;  // input file name
  string m_outputFile; // output file name
  int m_instruction_pointer = 0;  // points at the place in m_instruction, where the next instruction is supposed to be
  
  // memory and registers
  int m_memory[19] = {0};   // when initializing the processor, set as memory values from the writeup (0-18 inclusive)
  int m_registersInt[32] = {0}; // represents the values stored in registers $0-$31. All are initialized to 0.
  int m_registersF[32] = {0}; // represents the values stored in registers F0-F31. All are initialized to 0.
  
  // branch predictor
  BranchPredictor m_bp;

  // logistics attributes about pipelining
  vector<Instruction> m_pipeline; // This vector represents all the instructions within the pipeline, in order of being fetched
  int m_clock = 0; // corresponds to the current cycle within the entire pipeline (pipeline starts at clock cycle 1)
  int m_first_alive_instruction_ptr = 0; // points at the place in pipeline, with the first alive instruction to start on
  //                                     // if this is the same as the pipeline size, it probably means there isn't any alive instructions

  // forwarding related attributes
  vector<string> m_heldUpRead;
  vector<string> m_availableNextCycleRead; // would be treated as nonexistant for forwarding between loads and stores (in case of WAR not RAW)
  vector<string> m_heldUpWrite;
  vector<string> m_availableNextCycleWrite; // would be treated as nonexistant for forwarding between loads and stores (in case of WAR not RAW)

  // note: these two are only used in case of loads and stores, where we might be able to read and write to a register on the same cycle
  vector<string> registerRAW_WriteTracker;
  vector<string> registerRAW_ReadTracker;

};
 
#endif
