// CMSC 411 Project - Summer 2025
// File: Instruction.h
// Desc: This class represents an instruction
// Date: June 23, 2025
//Authors: Padina Nasiri Toussi and Qanita Baqibillah

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
using namespace std;

// Constants corresponding to instruction categories and types
const array<string, 3> INSTRUCTION_CATEGORIES = {"ALU", "MEMORY", "CONTROL"};
const array<string, 5> MEMORY_INSTRUCTIONS = {"L.D", "L.I", "SD", "LW", "SW"};
const array<string, 7> ALU_INSTRUCTIONS = {"ADD", "ADDI", "ADD.D", "SUB.D", "SUB", "MUL.D", "DIV.D"};
const array<string, 3> CONTROL_INSTRUCTIONS = {"BEQ", "BNE", "J ADDR"};

const array<string, 4> INSTRUCTION_UNITS = {"INT", "D.ADD", "D.MULT", "D.DIV"};


const array<string, 5> DEFAULT_PIPELINE_STAGES = {"IF", "ID", "EX", "MEM", "WB"};

const int NUM_INT_EXECUTES = 1;
const int NUM_DOUBLE_ADD_EXECUTES = 2;
const int NUM_DOUBLE_MULT_EXECUTES = 10;
const int NUM_DOUBLE_DIV_EXECUTES = 40;

const string STALL_NAME = "STALL";
const string INT_EXECUTE_NAME = "EX";
const string DOUBLE_ADD_EXECUTE_PREFIX = "A";
const string DOUBLE_MULT_EXECUTE_PREFIX = "M";
const string DOUBLE_DIV_EXECUTE_PREFIX = "D";

 
class Instruction{
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Instruction();

  // Overloaded Constructor
  // Preconditions: give valid plaintext instruction (without any labels)
  // Postconditions: type, destination, s1, s2, have been updated based on plaintext
  Instruction(string plaintext, int initial_cycle);
 
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

  // getCategory() - returns category (if m_category is "", calculates it first then returns)
  // Preconditions: myType is initialized
  string getCategory();

  // setCategory() - calculates and sets category based on the type
  // Preconditions: myType is initialized
  void setCategory();

  // getUnit() - returns unit (if m_unit is "", calculates it first then returns)
  // Preconditions: myType is initialized
  string getUnit();

  // setUnit() - calculates and sets unit based on the type
  // Preconditions: myType is initialized
  void setUnit();

  // getPlaintext() - returns plaintext
  // Preconditions: plaintext is initialized
  // Postconditions: None
  string getPlaintext();
 
  // setPlaintext() - sets value of plaintext
  // Preconditions: None
  // Postconditions: None
  void setPlaintext(string text);

  // more setters and getters
  string getDest();
  void setDest(string dest);

  string getS1();
  void setS1(string s1);

  string getS2();
  void setS2(string s2);

  int getResult();
  void setResult(int result);

  // more getters and setters (int instead of string)
  int getDestVal();
  void setDestVal(int destVal);

  int getS1Val();
  void setS1Val(int s1Val);

  int getS2Val();
  void setS2Val(int s2Val);



  // functions (getters and setters) for pipeline-related attributes

  void deActivate(int currCycle); // set m_isActive to false, and save m_final_cycle 
  void endInstruction(int currCycle); // set m_hasEnded to true, and save m_final_cycle

  bool getIsAlive();  // return false if !m_isActive or m_hasEnded
  bool getIsActive();
  bool getHasEnded(); 

  // setters for initial and final cycles
  int getInitialCycle();
  int getFinalCycle();
  const vector<string>& getStageLog() const;


  // More complex pipeline-related functions

  // Pushes the given stageName into m_stageLog - very useful for pushing stalls and IF stage
  // note: it doesn't update any other variables
  // Precondition: stageName is a valid stage name
  // Examples: stageName = "STALL", "IF", "A1", "WB", etc.
  void pushToStageLog(string stageName);
  
  // Pushes the default next stage into m_stageLog based on the function type and the previous stages
  // Precondition: IF stage has already been completed
  // Example: if we have a branch instruction using int unit, and latest stage was "IF", we would push "ID"
  void pushToStageLogDefault();

  // Returns the most recently logged stage. If stage log is empty, return ""
  string getLatestStageLog();

  // Returns the most recently logged stage (that wasn't a STALL). If stage log is empty, return ""
  string getLatestNonStallStageLog();

  // Uses getLatestStageLog to predict what the next expected stage log should be
  // Precondition: IF stage has already been completed
  string getNextExpectedStageLog(string prevStage);


  // Getters and Setters for attributes relating to Branch Prediction and CONTROL category instructions
  // IMPORTANT NOTE: branchVarName has to be 1 of ["m_ptr_to_taken", "m_ptr_to_not_taken", "m_predicted_taken", "m_actual_taken"]
  // 1=yes, 0=no, -1=unexpected

  int getBranchingInt(string branchVarName);

  void setBranchingInt(string branchVarName, int branchVarValue);


private:
  string m_plaintext; // the instruction in plaintext
  
  // attributes for instruction sources, destination, etc. (things we can know from the plaintext)
  string m_dest;
  string m_s1;
  string m_s2;
  string m_myType;  // for example, "ADD" or "BNE"
  string m_category; // "ALU", "MEMORY", "CONTROL"
  string m_unit; // "INT", "D.ADD", "D.MULT", "D.DIV"
  int m_result = -1; // this represents the calculated result of the instruction --> which would be saved during WB stage

  // int attributes for values of instruction operands - (-1 implies unknow so far/irrelevant)
  // these would be updated during the ID stage (and also stall stages happening right after the ID stage)
  // note: if s1Val is -1, it might also be because it is a label, and labels cannot be represented as ints
  int m_destVal = -1;
  int m_s1Val = -1;
  int m_s2Val = -1;

  // attributes related to instruction state
  bool m_isActive; // defaults true, unless proven false by branch selection - only continue the row for active instructions
  bool m_hasEnded; // defaults false, and is set to true when instruction ends - only continue the row if !hasEnded
  
  // attributes relating to Branch Prediction and CONTROL category instructions
  // note: these are only referenced or changed for control instructions
  // in all these attributes, the value being -1 means the variable is unkown (or irrelevant)
  int m_ptr_to_taken = -1; // corresponds to an index of the instruction on m_instructions
  int m_ptr_to_not_taken = -1; // corresponds to an index of the instruction on m_instructions
  int m_predicted_taken = -1;  // 1=yes, 0=no
  int m_actual_taken = -1;  // 1=yes, 0=no

  // pipeline related attrbutes
  int m_initial_cycle;  // the cycle number where the instruction object was created on
  int m_final_cycle;  // the cycle where the last stage of the instruction happened - it is otherwise -1.
  //                  // This would be when the instruction ends, OR one cycle before when instruction became inactive
  vector<string> m_stage_log; // represents every stage done (including stall) during instruction life
  //  // This corresponds to the row in the pipelining spreadsheet starting from cycle m_init_cycle to final_cycle
};
 
#endif
