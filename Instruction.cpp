// CMSC 411 Project - Summer 2025
// File: Instruction.cpp
// Desc: This class represents an instruction
// Date: June 23, 2025
// Authors: Qanita Baqibillah and Padina Toussi

#include <iostream>
#include <string>
#include <fstream>
#include <array>
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

