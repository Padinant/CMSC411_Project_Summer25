// CMSC 411 Project - Summer 2025
// File: Processor.cpp
// Desc: This class represents a processor
// Date: June 23, 2025
// Authors: Qanita Baqibillah and Padina Toussi

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include "Processor.h"
using namespace std;

Processor::Processor(){
    // Constructor
    m_instructions;
    m_filename = "";
    m_clock = 0;
}

Processor::Processor(string filename){
    // Overloaded Constructor
    m_instructions;
    m_filename = filename;
    m_clock = 0;
}

Processor::~Processor(){
    // Destructor
    // todo: make sure to deallocate anything dynamically allocated such as 
    //    // m_instructions
}

// loads instructions from the given file name into m_instructions
// Preconditions: filename contains the load instructions
// Note: currently, only loads plaintext instructions
void Processor::loadInstructions(string filename){

    // loop 1: find out the count of instructions (this is so we don't have to use vectors instead of arrays)
    ifstream infile(filename);
    string result;
    string line;
    int len = 0;
    int count = 0;  // used in loop 2
    if (infile.is_open()) {
        while(getline(infile, result)){
            len++;
        }
        infile.close();
    } else {
        cout << "Error opening instructions file";
    }
    // Update the length of m_instructions
    m_instructions_len = len;
    const int const_len = len;  // need a constant
    string instructions[const_len] = {""}; // filled with empty strings
    m_instructions = instructions;

    // loop 2: For each instruction in the file, create an object and load it into the m_instructions array
    infile.open(filename);

    if (infile.is_open()) {
        while(getline(infile, line)){
            // set the var result equal to the line but with the beginning and end whitespaces removed


            // // create the corresponding Instruction object
            // Instruction* newInstruction = new Instruction();
            // newInstruction->setPlaintext(result);    // plaintext

            // add instruction into m_instructions
            // m_instructions[count] = newInstruction;
            result = trimExtraWhiteSpace(line);
            m_instructions[count] = result;
            cout << "result: " << result << endl;
            count++;
        }
        infile.close();
        cout << count << " instructions loaded." << endl;
    } else {
        cout << "Error opening instructions file";
    }
}


// PIPELINING IMPLEMENTATION FUNCTIONS:

// fetches the next instruction from m_instructions (corresponds to the IF stage)
// creates instruction object + update pointer (+ todo later: figure out branch prediction at this stage)
// Instruction Processor::instructionFetch(){
//     // Loads instruction plaintext (if any exist at address)
//     // Creates instruction class and loads relevant attributes (ignore any labels at the beginning)
//     // Updates instruction pointer (todo: this is currently just pointer +1)

//     // part 0
//     if (m_instruction_pointer >= m_instructions_len){
//         // pointer out of range - we've reached the end of the program
//         return;
//     }
//     // part 1
//     string plaintext = m_instructions[m_instruction_pointer];
    
//     // part 2
//     Instruction myInst;
//     // todo: [CONTINUE CODE]


//     // part 4
//     return myInst;


// }

// NEW (not yet implemented in Processor.cpp)
// decode a given instruction object and load the values of all delivarables (corresponds to the ID stage)
// also check if we should stall (ie repeat this stage)
// would interpret its dependencies, and other relevant details not already known
void Processor::instructionDecode(Instruction inst){
    //
}

// NEW (not yet implemented in Processor.cpp)
// finds the names of the dependencies for a given instruction (is helper to instructionDecode())
// todo: implement a way to return the dependencies (either member attributes, or return a list of register names)
void Processor::getDependencies(Instruction x){
    //
}



// HELPER FUNCTIONS

string Processor::trimExtraWhiteSpace(string s1){
    // trims any extra whitespace from before and after from the line
    // example input: "       ADD F1, F2, F3  "
    // example output: "ADD F1, F2, F3"
    if (s1.empty()) return s1;

    return s1.substr(s1.find_first_not_of(" \t\n\r"), s1.find_last_not_of(" \t\n\r") - s1.find_first_not_of(" \t\n\r") + 1);
}



