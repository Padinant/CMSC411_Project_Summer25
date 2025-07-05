# CMSC 411 Summer 2025 Multi Cycle Pipeline Simulator Project
### Project Contributers: Padina Nasiri Toussi and Qanita Baqibillah
### CMSC 411 Project - Summer 2025
### Date: June 23, 2025

## Project Description

This project was created as the final project for the UMBC CMSC 411(Computer Architecture) course in Summer 2025. This project is a 5 stage pipilined processor simulator that includes instruction level parallelism, full forwarding, and branch prediction.

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

1. The program begins by loading the instruction. The processor reads the ``.txt`` file (``InstructionText.txt``) line by line, strips the whitespace, and then loads each instruction into m_instructions
2. Next the main processor starts. When ``startProcessor()`` is called a loop will being and each loop iteration is representative of 1 clock cycle
    - In this loop, the existing instructions in the pipeline move to the next stage unless something is invalid
    - Hazards are checked for and stall are applied where needed
    - New instructions are then fetched if there isn't any stall
    - Branches are predicted and carrected as needed
3. The next step is the actual execution of the instructions. Each instruction is parsed into its respective type, destination, source1, and source2, and the relevant operands are soreted out usinf registors or memory
4. The next step is the forwarding and hazard detection step. It checks for RAW hazards (read/write conlficts) and are mitigated by using forwarding and tracking vectors like ``m_heldUpRead`` and ``m_heldUpWrite``
5. Next is the branch prediction step. For control instructions such as ``BEQ``, ``BNE``, or J the processor wil predict the outcome. If the prediction was wrong, then it invalidates wrong path instructions
6. Last is the ending exectuion step. When the pipeline is empty and there are no new instructions left, the processor will convert the pipline history into a 2D strimg array and export the data to a spreadsheet file (``spreadsheet1.txt``)

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
    - This line is that you want to change: ``string instructionFile = "CUSTOM_FILE.txt";`` (Located on line 16)
- If you would like the output to be put in a file other than the given ``spreadsheet1.txt`` file,
    - Please change the ``outputFile`` variable in the ``driver.cpp`` file to the name of your custom file
    - This line is that you want to change: ``string outputFile = "CUSTOM_FILE.txt";`` (Located on line 17)

## Features and Notes




