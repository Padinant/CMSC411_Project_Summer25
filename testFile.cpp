// CMSC 411 Project - Summer 2025
// File: testFile.cpp
// Desc: This class represents a processor
// Date: June 23, 2025
//Authors: Qanita Baqibillah and Padina Toussi

#include <iostream>
#include <string>
#include <fstream>
#include "Processor.h"
using namespace std;

class Tester{

    public:
        void testLoadInstructions(const string& filename);
    private:

};

int main(){
    string testFilename = "InstructionText.txt";
    Tester test;
    test.testLoadInstructions(testFilename);
    return 0;
}

void Tester::testLoadInstructions(const string& filename){
    Processor proc(filename);
    proc.loadInstructions(filename);

        // To disisplay the loaded instructions
//         cout << "Loaded Instructions from txt: " << endl;
//         for (int i = 0; i < 6; i++) {
//             Instruction* instr = proc.getInstructionAt(i);
//             if (instr != nullptr) {
//                 cout << i + 1 << ": " << instr->getPlaintext() << endl;
//             }
//         }
}
