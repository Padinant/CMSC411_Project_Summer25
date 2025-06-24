// CMSC 411 Project - Summer 2025
// File: Processor.cpp
// Desc: This class represents a processor
// Date: June 23, 2025

#include <iostream>
#include <string>
#include <fstream>
#include "Processor.h"
using namespace std;

Processor::Processor(){
    // Constructor
    m_instructions = {};
    m_filename = "";
}

Processor::Processor(string filename){
    // Overloaded Constructor
    m_instructions = {};
    m_filename = filename;
}

Processor::~Processor(){
    // Destructor
}

// loads instructions from the given file name into m_instructions
// Preconditions: filename contains the load instructions
// Note: currently, only loads plaintext instructions
void Processor::loadInstructions(string filename){

    // loop 1: find out the count of instructions (this is so we don't have to use vectors instead of arrays)
    ifstream infile(filename);
    string result;
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
    Instruction* m_instructions[len] = {nullptr}; // filled with nullptr

    // loop 2: For each instruction in the file, create an object and load it into the m_instructions array
    infile.open(filename);

    if (infile.is_open()) {
        while(getline(infile, result)){
            // create the corresponding Instruction object
            Instruction* newInstruction = new Instruction();
            newInstruction->setPlaintext(result);    // plaintext

            // add instruction into m_instructions
            m_instructions[count] = newInstruction;

            count++;
        }
        infile.close();
        cout << count << " instructions loaded." << endl;
    } else {
        cout << "Error opening instructions file";
    }
}


