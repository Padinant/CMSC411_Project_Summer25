// CMSC 411 Project - Summer 2025
// File: Instruction.cpp
// Desc: This class represents an instruction
// Date: June 23, 2025
// Authors: Padina Nasiri Toussi and Qanita Baqibillah

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include "Instruction.h"
using namespace std;

Instruction::Instruction(){
    // Constructor
    setType("");
    setPlaintext("");
}

Instruction::Instruction(string plaintext, int initial_cycle){
    // Overloaded Constructor
    // Preconditions: give valid plaintext instruction (without any labels)
    // Postconditions: type, destination, s1, s2, have been updated based on plaintext
    
    // set up pipeline related attributes
    m_initial_cycle = initial_cycle;
    m_final_cycle = -1;
    m_isActive = true;
    m_hasEnded = false;

    // set up instruction related attributes
    setPlaintext(plaintext);
}

Instruction::~Instruction(){
    // Destructor
}

// getPlaintext() - returns plaintext
// Preconditions: plaintext is initialized
// Postconditions: None
string Instruction::getPlaintext(){
    return m_plaintext;
}

// setPlaintext() - sets value of plaintext
// Preconditions: None
// Postconditions: None
void Instruction::setPlaintext(string text){
    m_plaintext = text;
}

// getType() - returns myType
// Preconditions: myType is initialized
// Postconditions: None
string Instruction::getType(){
    return m_myType;
}

// setType() - sets value of myType
// Preconditions: None
// Postconditions: None
void Instruction::setType(string type){
    m_myType = type;
}

// getCategory() - returns category (if m_category is "", calculates it first then returns)
// Preconditions: myType is initialized
string Instruction::getCategory(){
    // get category if it is one of ("ALU", "MEMORY", "CONTROL")
    if (m_category == "ALU" or m_category == "MEMORY" or m_category == "CONTROL"){
        return m_category;
    }

    // otherwise, calculate it then return category
    setCategory();
    return m_category;
}

// setCategory() - calculates and sets category based on the type
// Preconditions: myType is initialized
void Instruction::setCategory(){
    // set category
    // check if m_myType in ALU_INSTRUCTIONS
    for (int i = 0; i < 7; i++){
        if (m_myType == ALU_INSTRUCTIONS[i]){
            m_category = "ALU";
            return;
        }
    }

    for (int i = 0; i < 5; i++){
        if (m_myType == MEMORY_INSTRUCTIONS[i]){
            m_category = "MEMORY";
            return;
        }
    }
    
    for (int i = 0; i < 3; i++){
        if (m_myType == CONTROL_INSTRUCTIONS[i]){
            m_category = "CONTROL";
            return;
        }
    }

    // the unexpected scenario (m_myType == "")
    m_category = "";

}

// getUnit() - returns unit (if m_unit is "", calculates it first then returns)
// Preconditions: myType is initialized
string Instruction::getUnit(){
    // get unit if it is one of ("INT", "D.ADD", "D.MULT", "D.DIV")
    if (m_unit == "INT" or m_unit == "D.ADD" or m_unit == "D.MULT" or m_unit == "D.DIV"){
        return m_unit;
    }

    // otherwise, calculate it then return unit
    setUnit();
    return m_unit;
}

// setUnit() - calculates and sets unit based on the type
// Preconditions: myType is initialized
void Instruction::setUnit(){
    // set unit
    // check if category is memory or control --> INT
    string category = getCategory();    // resets category
    if (category == "CONTROL" or category == "MEMORY"){
        m_unit = "INT";
        return;
    }

    // actually check the unit for ALU instructions
    if (m_myType == "ADD" or m_myType == "ADDI" or m_myType == "SUB"){
        m_unit = "INT";
        return;
    }
    if (m_myType == "ADD.D" or m_myType == "SUB.D"){
        m_unit = "D.ADD";
        return;
    }
    if (m_myType == "MUL.D"){
        m_unit = "D.MULT";
        return;
    }
    if (m_myType == "DIV.D"){
        m_unit = "D.DIV";
        return;
    }

    // the unexpected scenario (m_myType == "", etc.)
    m_unit = "";

}


// More getters and setters
string Instruction::getDest(){
    return m_dest;
}
void Instruction::setDest(string dest){
    m_dest = dest;
}

string Instruction::getS1(){
    return m_s1;
}
void Instruction::setS1(string s1){
    m_s1 = s1;
}

string Instruction::getS2(){
    return m_s2;
}
void Instruction::setS2(string s2){
    m_s2 = s2;
}



// functions (getters and setters) for pipeline-related attributes
void Instruction::deActivate(int currCycle){
    // set m_isActive to false, and save m_final_cycle 
    m_isActive = false;
    m_final_cycle = currCycle - 1;
}
void Instruction::endInstruction(int currCycle){
    // set m_hasEnded to true, and save m_final_cycle
    m_hasEnded = true;
    m_final_cycle = currCycle; 
}

bool Instruction::getIsAlive(){
    // return false if !m_isActive or m_hasEnded
    return (m_isActive and !m_hasEnded);
}
bool Instruction::getIsActive(){
    return m_isActive;
}
bool Instruction::getHasEnded(){
    return m_hasEnded;
}


// setters for initial and final cycles
int Instruction::getInitialCycle(){
    return m_initial_cycle;
}
int Instruction::getFinalCycle(){
    return m_final_cycle;
}
const vector<string>& Instruction::getStageLog() const {
    return m_stage_log;
}

// More complex pipeline-related functions

// Pushes the given stageName into m_stageLog - very useful for pushing stalls and IF stage
// note: it doesn't update any other variables
// Precondition: stageName is a valid stage name
// Examples: stageName = "STALL", "IF", "A1", "WB", etc.
void Instruction::pushToStageLog(string stageName){
    m_stage_log.push_back("stageName");
}

// Pushes the default next stage into m_stageLog based on the function type and the previous stages
// Precondition: IF stage has already been completed
// Example: if we have a branch instruction using int unit, and latest stage was "ID", we would push "IF"
void Instruction::pushToStageLogDefault(){
    string prevStage = getLatestStageLog();
    string nextStage = getNextExpectedStageLog(prevStage);
    pushToStageLog(nextStage);
}


// Returns the most recently logged stage. If stage log is empty, return ""
string Instruction::getLatestStageLog(){
    if (m_stage_log.empty()){
        return "";
    }

    return m_stage_log.back();  // returns the last element of the vector
}


// Uses getLatestStageLog to predict what the next expected stage log should be
// Precondition: IF stage has already been completed
string Instruction::getNextExpectedStageLog(string prevStage){
    // this is a helper function to pushToStageLogDefault()
    if (prevStage == ""){   // unexpected
        return "";
    }
    if (prevStage == "STALL"){     // STALL --> [depends]
        // find the latest none-stall command
        string prevRelevantStage = "";
        for (int i = m_stage_log.size() - 1; i >= 0; --i) {
            if (m_stage_log[i] != "stall") {
                prevRelevantStage = m_stage_log[i];
                break;
            }
        }

        // It get's slightly inductive here
        return getNextExpectedStageLog(prevRelevantStage);
    }
    if (prevStage == "IF"){     //IF --> ID
        return "ID";
    }
    if (prevStage == "ID"){      // ID --> EX [though the exact one depends]
        // figure out the execute stage's name
        string unit = getUnit();    // this makes sure the unit is updated

        if (m_unit == "INT"){
            return "EX";
        }
        if (m_unit == "D.ADD"){
            return (DOUBLE_ADD_EXECUTE_PREFIX + "1");
        }
        if (m_unit == "D.MULT"){
            return (DOUBLE_MULT_EXECUTE_PREFIX + "1");
        }
        if (m_unit == "D.DIV"){
            return (DOUBLE_DIV_EXECUTE_PREFIX + "1");
        }
        // unexpected
        return "";
    } 

    // skipping the execute stage for now (see below)

    if (prevStage == "MEM"){     // MEM --> WB
        return "WB";
    }
    if (prevStage == "WB"){     // WB --> ""
        return "";
    }

    // EXECUTE STAGES
    if (prevStage == "EX"){     // EX --> MEM (or "" if it's a control instruction)
        if (m_category == "CONTROL"){
            return "";
        }
        return "MEM";
    }

    string s1 = prevStage.substr(0, 1);  // first character
    string s2 = prevStage.substr(1);     // everything else
    
    if (s2 == ""){  // unexpected
        return "";
    }

    int s2_int = stoi(s2);      // the int version for s2

    if (s1 == DOUBLE_ADD_EXECUTE_PREFIX){
        if (s2_int < NUM_DOUBLE_ADD_EXECUTES){
            return (s1 + to_string(s2_int + 1));
        }
        return "MEM";
    }
    if (s1 == DOUBLE_MULT_EXECUTE_PREFIX){
        if (s2_int < NUM_DOUBLE_MULT_EXECUTES){
            return (s1 + to_string(s2_int + 1));
        }
        return "MEM";
    }
    if (s1 == DOUBLE_DIV_EXECUTE_PREFIX){
        if (s2_int < NUM_DOUBLE_DIV_EXECUTES){
            return (s1 + to_string(s2_int + 1));
        }
        return "MEM";
    }


    // anything else unexpected
    return "";
}
