// CMSC 411 Project - Summer 2025
// File: Instruction.cpp
// Desc: This class represents an instruction
// Date: June 23, 2025
#include <iostream>
#include <string>
#include <fstream>
#include "Instruction.h"
using namespace std;

Instruction::Instruction(){
    // Constructor
    setType("");
    setPlaintext("");
}

Instruction::~Instruction(){
    // Destructor
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
