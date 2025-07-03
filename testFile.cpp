// CMSC 411 Project - Summer 2025
// File: testFile.cpp
// Desc: The Test File
// Date: June 28, 2025
//Author: Qanita Baqibillah

#include <iostream>
#include <string>
#include <fstream>
#include "Processor.h"
#include "Instruction.h"
using namespace std;

class Tester{

    public:
        void testLoadInstructions(const string& filename);
        void testExportSpreadsheet();
        void testAddressToIndex();
        void testStore();
        void testLoad();
        void testConvertPipline();
    private:

};

int main(){
    string testFilename = "InstructionText.txt";
    Tester test;
    test.testLoadInstructions(testFilename);
    test.testExportSpreadsheet();
    test.testAddressToIndex();
    test.testStore();
    test.testLoad();
    test.testConvertPipline();
    return 0;
}

void Tester::testLoadInstructions(const string& filename){
    Processor proc;
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

void Tester::testAddressToIndex(){
    Processor p;
    // Last four are error cases and should return -1
    string testCases[] = {"$0", "$5", "$18", "$19", "$20", "0($0)", "4($1)", "16($18)", "100($19)","($2)",
        "1", "18", "100", "( $3 )", "invalid", "", "$"};

    cout << "Testing memoryAddressToIndex: " << endl;
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        int index = p.memoryAddressToIndex(testCases[i]);
        cout << "memAddress: " << testCases[i] << "-> Index: " << index << endl;
    }
}

void Tester::testStore(){
    Processor p;
    p.setRegisterValue("$5", 101);
    p.store("$5", "0($2)");

    int expectedIndex = p.memoryAddressToIndex("0($2)");
    int actualValue = p.getMemoryValue(expectedIndex);

    cout << "Testing store(): " << endl;
    cout << "Expected memory[" << expectedIndex << "] = 101. Got: " << actualValue << endl;
}

void Tester::testLoad(){
    Processor p;
    int expectedValue = 101;
    int memoryIndex = 5;

    p.setRegisterValue("$1", expectedValue);
    p.store("$1", "$5");

    p.load("$10", "$5");

    int actual = p.getRegisterValue("$10");

    cout << "Testing load(): " << endl;
    cout << "Register $10 contains " << actual << ". Expected: " << expectedValue << endl;
}

void Tester::testConvertPipline(){
    Processor p;

    
}