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
        void testExportSpreadsheet();
    private:

};

int main(){
    string testFilename = "InstructionText.txt";
    Tester test;
    test.testLoadInstructions(testFilename);
    test.testExportSpreadsheet();
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

void Tester::testExportSpreadsheet(){
    int rows = 3;
    int cols = 4;

    // create the dynamic 2D array
    string** spreadsheet = new string*[rows];
    for (int i = 0; i < rows; ++i) {
        spreadsheet[i] = new string[cols];
    }

    // populate the spreadsheet with some test data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            spreadsheet[i][j] = "R" + to_string(i) + "C" + to_string(j);
        }
    }

    // create the processor instance just to use export function
    Processor proc;
    string filename = "outputSpreadsheet.txt";
    proc.exportSpreadsheet(filename, spreadsheet, rows, cols);

    // clean up memory later if needed
    // for (int i = 0; i < rows; ++i) {
    //     delete[] spreadsheet[i];
    // }
    // delete[] spreadsheet;
}