# CMSC411 Summer 2025 Multi Cycle Pipeline Simulator Project
### Project Contributers: Padina Nasiri Toussi and Qanita Baqibillah
### CMSC 411 Project - Summer 2025
### Date: June 23, 2025

## Project Description

This project was created as the final project for the UMBC CMSC 411(Computer Architecture) course in Summer 2025. 

## Files
- Processor.cpp: This file contains the main processor logic as well as all of the instruction decoding, memory and register operations, and pipelining done in the project
- Processor.h: This file is the header file for the Processor class
- Instruction.cpp/h: These files define the Instruction class used for data on individual instructions as well as pipline stage tracking
- BranchPredictor.cpp: 
- driver.cpp: This is the executable that runs the entire program
- testFile.cpp: Custom test file created to test individual function within the Processor class
- InstructionText.txt: Custom txt file containing different instructions for testing
- Makefile

## How it Works



## How to Run and Dependencies
- Requires C++ compiler
- An IDE or terminal
- Optional: Git on local host if cloning repositry

1. Clone the repository or download the files as a ZIP and open in an IDE
2. Compile the program typing the ``make`` command in the terminal
3. Run the program by either typing ``make run`` or ``./driver`` in the terminal after compiling
    - To run the custom test file (testFile.cpp), please type ``./testFile`` to run the program
4. After running, you may use the ``make clean`` command to remove any .o files created

### What to Expect as Output

- INSERT SCREEN SHOT OF SAMPLE OUTPUT AND VERY BRIEFLY EXPLAIN

- A text file named "spreadsheet1.txt" will be created as an output file that contains the data from the 2d spreadsheet array

### To Customize
- Either edit the given instruction file (``Instruction.txt``) or create new custom file
    - If using custom file, then please change the instructionFile variable in the ``driver.cpp`` file to the name of your custom file
    - This line is what you want to change: ``string instructionFile = "CUSTOM_FILE.txt";`` (Located on line 16)
- If you would like the output to be put in a file other than the given ``spreadsheet1.txt`` file,
    - Please change the ``outputFile`` variable in the ``driver.cpp`` file to the name of your custom file
    - This line is what you want to change: ``string outputFile = "CUSTOM_FILE.txt";`` (Located on line 17)

## Features and Notes




