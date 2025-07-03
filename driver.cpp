// CMSC 411 Project - Summer 2025
// File: driver.cpp
// Desc: This is the driver for the project (ie. the file to run)
// Date: June 23, 2025
//Authors: Padina Nasiri Toussi

#include "Instruction.h"
#include "Processor.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// main
int main(){
    string instructionFile = "InstructionText.txt";
    string outputFile = "spreadsheet1.txt";
    Processor myComputer(instructionFile, outputFile);
    myComputer.loadInstructions(instructionFile);
    myComputer.startProcessor();

    return 0;

}