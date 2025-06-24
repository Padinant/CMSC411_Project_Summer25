// CMSC 411 Project - Summer 2025
// File: Instruction.cpp
// Desc: This class represents an instruction
// Date: June 23, 2025

Instruction::Instruction(){
    // Constructor
    SetType("");
    // m_myType = "";
}

Instruction::~Instruction(){
    // Destructor
}


// getType() - returns myType
// Preconditions: myType is initialized
// Postconditions: None
string Instruction::GetType(){
    return m_myType;
}

// setType() - sets value of myType
// Preconditions: None
// Postconditions: None
void Instruction::SetType(string type){
    m_myType = type;
}
