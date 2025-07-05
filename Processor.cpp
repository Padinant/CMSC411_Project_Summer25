// CMSC 411 Project - Summer 2025
// File: Processor.cpp
// Desc: This class represents a processor
// Date: June 23, 2025
// Authors: Padina Nasiri Toussi and Qanita Baqibillah

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include "Processor.h"
using namespace std;

Processor::Processor(){
    // Constructor
    m_instructions;
    m_filename = "";
    m_clock = 0;
    for (int i = 0; i < 19; i++) {
        m_memory[i] = DEFAULT_MEMORY[i];
    }
}

Processor::Processor(string filename, string outputFile){
    // Overloaded Constructor
    m_instructions;
    m_filename = filename;
    m_outputFile = outputFile;
    m_clock = 0;
    for (int i = 0; i < 19; i++) {
        m_memory[i] = DEFAULT_MEMORY[i];
    }
}

Processor::~Processor(){
    // Destructor
    // todo: make sure to deallocate anything dynamically allocated such as 
    //    // m_instructions
}

// PUBLIC HELPERS FOR TESTING
int Processor::getMemoryValue(int index) {
    if (index >= 0 && index < 19) {
        return m_memory[index];
    }
    return -1;
}

// note: commented these for now, as they are out of date and they cause errors (we are no longer using m_registers)
// void Processor::setRegisterValue(string reg, int value) {
//     int reg_index = atoi(reg.substr(1).c_str());
//     if (reg_index >= 0 && reg_index < 32) {
//         m_registers[reg_index] = value;
//     }
// }

// int Processor::getRegisterValue(string reg) {
//     int reg_index = atoi(reg.substr(1).c_str());
//     if (reg_index >= 0 && reg_index < 32) {
//         return m_registers[reg_index];
//     }
//     return -1;
// }


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
    string instructions[const_len]; // will be filled with empty strings
    for (int i = 0; i < const_len; i++) {
        instructions[i] = "";  // Explicitly setting each index to "" so compiler doesn't complain 
    }

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

// note: commented these for now, as they are out of date and they cause errors (we are no longer using m_registers)
void Processor::load(string reg_address, string mem_address){
    // To convert mem_address to an actual index
    int mem_index = memoryAddressToIndex(mem_address);

    // Invalid mem index
    if(mem_index < 0 || mem_index >= 19){
        return;
    }

    // Extracting the register index
    int reg_index = registerAddressToIndex(reg_address);

    // Make sure the reg_index is valid between 0-32
    if (reg_index < 0 || reg_index >= 32) {
        return;
    }

    if(reg_address[0] == '$'){
        m_registersInt[reg_index] = m_memory[mem_index];
    }
    else if(reg_address[0] == 'F'){
        m_registersF[reg_index] = m_memory[mem_index];
    }
    else{
        // Invalid prefix for register
        return;
    }
}

void Processor::store(string reg_address, string mem_address){
    // Extracting the register index
    int reg_index = registerAddressToIndex(reg_address);

    // Invalid index
    if(reg_index < 0 || reg_index >= 32){
        return;
    }

    // Getting the value stored in the the register
    int value = 0;
    if(reg_address[0] == '$'){
        value = m_registersInt[reg_index];
    }
    else if( reg_address[0] == 'F'){
        value = m_registersF[reg_index];
    }
    else{
        //Invalid
        return;
    }

    // To convert it to an actual index
    int mem_index = memoryAddressToIndex(mem_address);

    // Make sure the index returned was valid and not -1 in case of an error
    if (mem_index < 0 || mem_index >= 19) {
        cout << "Invalid memory index returned by memoryAddressToIndex(): " << mem_index << endl;
        return;
    }

    // To store the value into memory
    m_memory[mem_index] = value;
}

int Processor::memoryAddressToIndex(string memAddress){
    if(memAddress.empty()) return -1;

    int openParen = -1;
    int closeParen = -1;
    
    // If the address is just a num precded by $
    if (memAddress.length() > 1 && memAddress[0] == '$') {
        int reg_index = atoi(memAddress.substr(1).c_str());
        return reg_index % 19;
    }

    // Checking for parantheses
    for (int i = 0; i < memAddress.length(); i++) {
        if (memAddress[i] == '(') { // Looking for the opening parantheses
            openParen = i;
        } else if (memAddress[i] == ')') { // Looking for the closing parantheses
            closeParen = i;
        }
    }

    // Checking if there are opening and closing parantheses that are not empty
    if (openParen != -1 && closeParen != -1 && closeParen > openParen + 1) {
        // Taking out contents from the parantheses
        string offsetStr = memAddress.substr(0, openParen);
        string reg = memAddress.substr(openParen + 1, closeParen - openParen - 1);

        int offset = 0;
        try {
            offset = stoi(offsetStr);
        } catch (...) {
            // Some invalid offset
            return -1;
        }

        if (!reg.empty()) {
            char prefix = reg[0];
            int index = atoi(reg.substr(1).c_str());

            if (prefix == '$' && index >= 0 && index < 32) {
                return (offset + m_registersInt[index]) % 19;
            } else if (prefix == 'F' && index >= 0 && index < 32) {
                return (offset + m_registersF[index]) % 19;
            } else if (isdigit(prefix)) {
                // Something like "10(5)" will treat 5 as literal number
                int regVal = atoi(reg.c_str());
                return (offset + regVal) % 19;
            }
        } 
    }

    // If it's just a num without preceding $ or ()
    bool is_num = true;
    for (char c: memAddress){
        if(!isdigit(c)){
            is_num = false;
            break;
        }
    }
    // If it's just a num without preceding $ or ()
    if(is_num){
        int index = atoi(memAddress.c_str());
        return index % 19;
    }

    // Something went wrong
    return -1;
}

// convert valid register address (from instructions) to a memory index between 0-31 inclusive
// Valid Example: register_address = "F24" ---> 24
// Invalid Example: register_address = "5" ---> -1
int Processor::registerAddressToIndex(string register_address){
    // CHeck to make sure not empty
    if(register_address.empty()) return -1;


    // if the first letter isn't an F, return -1
    char s1 = register_address[0]; // first character
    string s2 = register_address.substr(1); // everything else

    if (s1 == 'F' || s1 == '$'){
        // assuming that if there is an F, the rest is a valid number --> the register index
        return atoi(s2.c_str());
    }

    return -1;
}


// given a string with '(' and ')', returns the substring inside those brackets
// if unsuccessful, return ""
// precondition: text ends in the character ')'
// note: this is a helper function for these operands: offset(addr)
// Example: "100($4)" --> "$4"
string Processor::getSubstringInsideBrackets(string text){
    // Check the precondition: must end with ')' and not be empty
    if (text.empty() or text.back() != ')') {
        return "";
    }

    // Find the position of the last closing ')'
    int posClose = text.size() - 1; // index of the last char

    // Find the first '('
    int posOpen = text.find('(');
    if (posOpen == string::npos) {
        return "";  // no '(' found or nothing inside
    }

    // Get the substring between '(' and ')'
    return text.substr(posOpen + 1, posClose - posOpen - 1); // I hope this is right
}

// given a string with '(', returns the substring before reaching those
// if unsuccessful, return ""
// precondition: text ends in the character '('
// note: this is a helper function for these operands: offset(addr)
// Example: "100($4)" --> "100"
string Processor::getSubstringBeforeBrackets(string text){
    if (text.empty()) {
        return "";
    }

    // Find the first '('
    int posOpen = text.find('(');
    if (posOpen == string::npos) {
        return "";  // no '(' found or nothing inside
    }

    // Get the substring before '('
    return text.substr(0, posOpen);
}

  // given an int value and an addrLocation (), returns a string representation for the address
  // Precondition: addrLocation is in ["MEMORY", "R_INT", "R_F"]
  // Examples:
  // (5, "MEMORY") --> "5"
  // (5, "R_INT") --> "$5"
  // (5, "R_F") --> "F5"
  // unexpected: --> ""
  string Processor::getIndexToAddressWithoutOffset(int value, string addrLocation){
    if (addrLocation == "MEMORY"){
        return to_string(value);
    }
    if (addrLocation == "R_INT"){
        return ("$" + to_string(value));
    }
    if (addrLocation == "R_F"){
        return ("F" + to_string(value));
    }
    return ""; // unexpected
  }

// PIPELINING IMPLEMENTATION FUNCTIONS:

// KEY FUNCTION: startProcessor()
// This function would be called to start and run the simulated pipeline
// Precondition: loadInstructions() has been called to load the instructions
// Postcondition: when done, would also save the pipeline results into a new file
void Processor::startProcessor(){
    /* How the processor works:
    - Precondition: load instructions (should be done before calling startProcessor)
    - start pipeline loop (main portion) - 1 iteration corresponds to 1 clock cycle:
        - update forwarding related vectors for the new cycle
        - look at every (alive) instruction already in the pipeline and have them progress by 1 step
            - if any is stalling, everything after would also stall, and we'd skip the IF part    
            - otherwise, instruction fetch from the next line (if not empty line), and increment the m_instruction_pointer
            - incremeny clock cycle by 1
    - when the loop is done, and no active instruction is left in the pipeline, convert the pipeline into 2D array
    - export the array into a text file
    */ 

    // The Pipeline Loop
    bool pipeline_active = true;

    // reset some variables just in case
    m_clock = 0;
    m_instruction_pointer = 0;
    m_first_alive_instruction_ptr = 0;

    while(pipeline_active){
        // Each Iteration is a cycle
        bool stall_all_the_way_down = false;    // when this is true, every instruction below stalls

        // Clear m_availableNextCycle vectors (used to avoid RAW hazards) for the new cycle
        m_availableNextCycleRead.clear();
        m_availableNextCycleWrite.clear();
        registerRAW_WriteTracker.clear();
        registerRAW_ReadTracker.clear();

        // TODO: deal with instructions already in m_pipeline
        if (not m_pipeline.empty()){
            // ADD CODE HERE LATER
            bool deactivateRestOfBranch = false;    // useful boolean for branch selection

            // for each instruction in the pipeline...
            for (int i = 0; i < m_pipeline.size(); i++){
                Instruction currInst = m_pipeline[i];   // (hopefully)this should be a shallow copy
                // check if stalling
                // check if not breaking any rules/hazards for forwarding
                    // potentially update stall_all_the_way_down
                // apply instruction if 
                // update the two forwarding queues
                // end instruction if we are done
                // update pointer if we had a branch prediction or branch decision
                

                // TODO check for inactivity (add logic for that and check it before the stall stage)
                // for the actual branch selection prediction/determination, that would happen later on
                // todo Section Description: add a section + boolean that if a previous branch selection had been wrong, deactivate everything until loop's end
                if (deactivateRestOfBranch and currInst.getIsAlive()){
                    currInst.deActivate(m_clock);
                    
                    // also update all the vectors so it doesn't cause issues (update based on the previous stage and prevRelevant stage)
                    // not sure if it would help with keeping the vectors straight, if we move this section to slightly later??? thought prob not
                    // vectors // TODO
                }


                if (currInst.getIsAlive()){ // skip over anything that is inactive or dead
                    // STALL - we are stalling
                    if (stall_all_the_way_down){
                        // set instruction to stall - note: we do not need to modify the forwarding queues in this version
                        currInst.pushToStageLog(STALL_NAME);

                        // SOME EXTRA STEPS DEPENDING ON THE PREVIOUS RELEVANT (non-stall) STAGE:
                        string prevRelevantStage = currInst.getLatestNonStallStageLog();
                        // IF - none
                        if (prevRelevantStage == "IF"){
                            // nothing here
                        }
                        // ID - update the operator values again
                        else if (prevRelevantStage == "ID"){
                            instructionDecode(currInst);

                            // Section Description: update the forwarding vectors based on the instruction type and operators
                            // Note: this section is based on the one used during the ID stage, but slightly different
                            // update forwarding vectors (note: since we are stalling, don't modify m_heldUpRead and m_heldUpWrite, ONLY availableNextCycle)
                            // Basically, we are just refilling the forwarding vectors that get automatically cleared at every cycle
                            string type = currInst.getType();
                            string category = currInst.getCategory();
                            
                            string dest = currInst.getDest();
                            string s1 = currInst.getS1();
                            string s2 = currInst.getS2();

                            // CONTROL
                            if (type == "J"){
                                // skip for now - dest is a label, s1 and s2 are nonexistant
                                // no need for any forwarding
                            } else if (category == INSTRUCTION_CATEGORIES[2]) {
                                // rest of "CONTROL" category - ie: BEQ or BNE
                                // dest and s1 ARE BOTH READ FROM (not written to), s2 is a label
                                m_availableNextCycleRead.push_back(s1);
                                m_availableNextCycleRead.push_back(dest);  
                            } 
                            // ALU
                            else if (type == "ADDI"){
                                // add immediate - dest and s1 are normal registers, s2 is a immediate
                                m_availableNextCycleRead.push_back(s1);
                            } else if (category == INSTRUCTION_CATEGORIES[0]){
                                // rest of the ALU categories - dest, s1, s2 are normal registers
                                // update forwarding for all three
                                m_availableNextCycleRead.push_back(s1);
                                m_availableNextCycleRead.push_back(s2);
                            }
                            // MEMORY
                            // L.D Fa, Offset(addr)
                            // S.D Fa, Offset(addr)
                            // LI $d, IMM64 -Integer Immediate Load
                            // LW $d, Offset(addr)
                            // SW $s, Offset(addr)
                            // A memory instruction has dest and s1 only
                            // for LI, only dest would go to heldUp
                            // for loads, dest and (if applicable) s1 would go to heldUp
                            // for stores, dest would go to heldUp, s1 would go to availableNextCycle
                            else {
                                // MEMORY
                                // we don't need to do anything, unless it's a store instruction
                                if(type == "S.D" or type == "SW"){       // every other load
                                    m_availableNextCycleRead.push_back(s1);
                                }
                            }

                        } 
                        // Other stages: EX, MEM, WB - also none
                        else {
                            // nothing here         // todo: potentially add more stuff to this later if needed
                        }
                    } 
                    
                    // VALID STAGE - take a valid stage between ID-WB (if allowed through forwarding)
                    else {
                        string prevStage = currInst.getLatestStageLog();
                        string expectedStage = currInst.getNextExpectedStageLog(prevStage);

                        // ID - load operands, update forwarding(most cases), update mem-specific forwarding
                        if (expectedStage == DEFAULT_PIPELINE_STAGES[1]){                        
                            
                            // call ID stage (load all operands)
                            instructionDecode(currInst);
                            currInst.pushToStageLog("ID");


                            // IGNORE:
                            // todo: check whether everything is available or if we should stall
                            // update forwarding (register mem-specific forwarding) (only if MEMORY instruction, and reading from register memory which was written to on this cycle)


                            // Note: only do this section if we can successfully continue
                            // update forwarding (heldUp R + W)
                            // update forwarding (availableNextCycle R)
                            // update forwarding (register mem-specific forwarding) - (Note: This will now be done at the beginning of EX and end of MEM)

                            // update the forwarding vectors based on the instruction type and operators
                            string type = currInst.getType();
                            string category = currInst.getCategory();
                            
                            string dest = currInst.getDest();
                            string s1 = currInst.getS1();
                            string s2 = currInst.getS2();

                            // CONTROL
                            if (type == "J"){
                                // skip for now - dest is a label, s1 and s2 are nonexistant
                                // no need for any forwarding
                            } else if (category == INSTRUCTION_CATEGORIES[2]) {
                                // rest of "CONTROL" category - ie: BEQ or BNE
                                // dest and s1 ARE BOTH READ FROM (not written to), s2 is a label
                                // update forwarding for dest and s1 only
                                // m_heldUpRead.push_back(s1);  // NOPE
                                m_availableNextCycleRead.push_back(s1);
                                m_availableNextCycleRead.push_back(dest);
                            } 
                            // ALU
                            else if (type == "ADDI"){
                                // add immediate - dest and s1 are normal registers, s2 is a immediate
                                // update forwarding for dest and s1 only
                                m_availableNextCycleRead.push_back(s1);
                                m_heldUpWrite.push_back(dest);
                            } else if (category == INSTRUCTION_CATEGORIES[0]){
                                // rest of the ALU categories - dest, s1, s2 are normal registers
                                // update forwarding for all three
                                m_availableNextCycleRead.push_back(s1);
                                m_availableNextCycleRead.push_back(s2);
                                m_heldUpWrite.push_back(dest);
                            }
                            // MEMORY
                            // L.D Fa, Offset(addr)
                            // S.D Fa, Offset(addr)
                            // LI $d, IMM64 -Integer Immediate Load
                            // LW $d, Offset(addr)
                            // SW $s, Offset(addr)
                            // A memory instruction has dest and s1 only
                            // for LI, only dest would go to heldUp
                            // for loads, dest and (if applicable) s1 would go to heldUp
                            // for stores, dest would go to heldUp, s1 would go to availableNextCycle
                            else {
                                // MEMORY
                                if (type == "LI"){      // Load Immediate
                                    m_heldUpWrite.push_back(dest);
                                } else if(type == "L.D" or type == "LW"){       // every other load
                                    m_heldUpRead.push_back(s1);
                                    m_heldUpWrite.push_back(dest);
                                } else { // stores
                                    m_availableNextCycleRead.push_back(s1);
                                    m_heldUpWrite.push_back(dest);
                                }
                            }
                        } else if (expectedStage == DEFAULT_PIPELINE_STAGES[2] or expectedStage == DOUBLE_ADD_EXECUTE_PREFIX 
                            or expectedStage == DOUBLE_MULT_EXECUTE_PREFIX or expectedStage == DOUBLE_DIV_EXECUTE_PREFIX){
                            // It's the FIRST execute stage! A lot to break down
                            string type = currInst.getType();
                            string category = currInst.getCategory();
                            string unit = currInst.getUnit();
                            
                            string dest = currInst.getDest();
                            string s1 = currInst.getS1();
                            string s2 = currInst.getS2();


                            // STOP: check if we have to end up stalling all the way down
                            // if so, skip the rest of this section's code
                            // note: todo use isExecuteAllowed function
                            bool executeIsAllowed = isExecuteAllowed(currInst);



                            // No: We are NOT completing the first EX stage on this cycle
                            if (!executeIsAllowed){
                                currInst.pushToStageLog(STALL_NAME);    // Push "STALL" to the instruction's stage log
                                stall_all_the_way_down = true;          // stall ripples down
                            } 
                            // Yes: We are completing the first EX stage on this cycle
                            else {
                                // Push the correct EX stage name to the instruction's stage log
                                currInst.pushToStageLogDefault();


                                // Cases to deal with
                                // CONTROL EXECUTE - branch determination + ending the instruction + potentially deactivating later remaining instructions in the loop this round
                                // MEMORY EXECUTE - the only execute stage - mostly nothing, although there might be some forwarding?
                                // ALU Integer EXECUTE - the only execute stage
                                // ALU FP EXECUTE - the first execute stage

                                // CONTROL EXECUTE
                                if (category == "CONTROL"){
                                    // todo: update forwarding 


                                    // make branch determination
                                    int determination = getBranchActual(currInst);
                                    int prediction = currInst.getBranchingInt("m_predicted_taken");

                                    // If prediction was wrong
                                    if (determination != prediction){
                                        m_bp.updatePrediction();    // let the predictor know that it was wrong

                                        // update m_instruction_pointer to what it should have been
                                        if (determination == 1){
                                            // determination is taken
                                            m_instruction_pointer = currInst.getBranchingInt("m_ptr_to_taken");
                                        } else if (determination == 0) {
                                            // determination is not taken
                                            m_instruction_pointer = currInst.getBranchingInt("m_ptr_to_not_taken");
                                        }
                                    }

                                    // end the instruction
                                    currInst.endInstruction(m_clock);

                                    // If prediction was wrong: deactivate any instruction in the pipeline right now after currInst
                                    if (determination != prediction){
                                        deactivateRestOfBranch = true;
                                    }
                                    

                                } 
                                // MEMORY EXECUTE
                                else if (...){}
                            }





                        }


















                        // NOTE: these are old code remnants, I will get rid of them                            
                        // } else if (prevStage == DEFAULT_PIPELINE_STAGES[4]){
                        //     // WB stage - don't worry about dependencies being met at this stage
                        //     // 
                        //     // end the instruction

                        //     // and update the forwarding vectors based on operators
                        // }
                }










                }





                // old version // todo: DETELE
                if (stall_all_the_way_down){
                    // set instruction to stall - note: we do not need to modify the forwarding queues in this version
                    currInst.pushToStageLog(STALL_NAME);
                    // if previous (non-stall) stage was ID, update the operator values again
                    string prevRelevantStage = currInst.getLatestNonStallStageLog();
                    if (prevRelevantStage == "ID"){
                        instructionDecode(currInst);
                    }

                    // todo: potentially add more stuff to this if needed

                } else {
                    // progress instruction by 1 stage (if possible) - OR start to stall_all_the_way_down
                    // Figure out what the expected stage would be
                    // string expectedStage = currInst.getNextExpectedStageLog(getLatestStageLog());
                    string prevStage = currInst.getLatestStageLog();
                    if (prevStage == DEFAULT_PIPELINE_STAGES[0]){
                        // IF stage - don't worry about dependencies being met at this stage
                        // instead call ID stage 
                        instructionDecode(currInst);
                        // and update the forwarding vectors based on operators
                        string type = currInst.getType();
                        if (type == "J"){
                            // skip for now - s1 is a label
                        } 
                        // else if (type == ...)
                        
                        // // destination
                        // m_heldUpRead.push_back
                        // m_heldUpWrite.push_back(currInst.getDestVal())
                        
                    } else if (prevStage == DEFAULT_PIPELINE_STAGES[4]){
                        // WB stage - don't worry about dependencies being met at this stage
                        // 
                        // end the instruction

                        // and update the forwarding vectors based on operators
                    }
                }
            }
        
        
        
        
        
        
        
        
        
        
        
        
        
        }

        bool deactivateRestOfBranch = false;    // reset this boolean for branch selection so it is false again


        // fetch the next instruction if we are not stalling AND there are more instructions left to fetch
        if (!stall_all_the_way_down and (m_instruction_pointer >= m_instructions_len)){
            Instruction newInst = instructionFetch();

            // update the stage log in newInst
            newInst.pushToStageLog("IF");    // pushes "IF" to the back of the stage log

            // add newInst to the end of the pipeline
            m_pipeline.push_back(newInst);


            // NEW SECTION: BRACNH PREDICTION
            if (newInst.getType() == "CONTROL"){
                // make prediction using m_bp
                int prediction = getBranchPrediction(newInst);

                // set the instruction_pointer to the address we predicted it would take
                if (prediction){
                    m_instruction_pointer = newInst.getBranchingInt("m_ptr_to_taken");
                } else {
                    m_instruction_pointer += 1;
                }

            } else {
                // update the pointer as normal
                m_instruction_pointer += 1;
            }
        }

        // update some pipeline-related variable to update the cycle
        m_clock += 1;   // clock cycle

        // EXIT CONDITIONS: check if we are done - 
        // ie: if every instruction in pipeline is dead, and there is no instructions left to fetch
        if (m_instruction_pointer >= m_instructions_len){
            if (m_pipeline.empty()){
                pipeline_active = false;
            } else {
                // check every pipeline instruction to see that it's not alive 
                // using a lambda expression, none_of(), and getIsAlive()
                if (none_of(m_pipeline.begin(), m_pipeline.end(), 
                [](Instruction &x) { return x.getIsAlive(); })){
                    pipeline_active = false;
                }
            }
        }
    }

    // We have exited the while loop

    // Step: convert the pipeline into 2D array
    // Step: export the array into a text file


    // We are done!
}


// fetches the next instruction from m_instructions (corresponds to the IF stage)
// creates and returns instruction object
// new: also sets m_ptr_to_taken and m_ptr_to_not_taken in "CONTROL" instructions
Instruction Processor::instructionFetch(){
    // Loads instruction plaintext (if any exist at address)
    // Creates instruction class and loads relevant attributes (ignore any labels at the beginning)

    // NOTE: things this function no longer does:
    // Updates instruction pointer (this is currently just pointer +1)

    // // part 0 - would be done before the function was called
    // if (m_instruction_pointer >= m_instructions_len){
    //     // pointer out of range - we've reached the end of the program
    //     return;
    // }
    // part 1
    string plaintext = m_instructions[m_instruction_pointer];

    // part 1.5 remove label from beginning if any
    char labelSignifier = ':';
    int posLabelSignifier = plaintext.find(labelSignifier); // position of the ':' character
    if (posLabelSignifier != string::npos) {
        // There IS a label --> remove it
        // string labelName = plaintext.substr(0, posLabelSignifier); // doesn't include ':' // code is here for reference
        string theRest = plaintext.substr(posLabelSignifier + 1);
        plaintext = trimExtraWhiteSpace(theRest); // update the plaintext
    }

    
    // part 2 - creating an instruction object
    Instruction myInst(plaintext, m_clock);
    
    // detrmine type, dest, source1, source2
    // Some Valid Examples:
    // "ADD.D F2,F0,F1"
    // "S.D F2,0($2)
    // "LI $7,0"
    // "J Loop1"
    // "BNE $1,$2,Loop1"

    // find first word until space --> type
    int space_pos = plaintext.find(' ');  // position of the first space
    string text1 = plaintext.substr(0, space_pos); // first chunk (before the space) --> the instruction type!
    string text2 = plaintext.substr(space_pos + 1); // The rest of the string (after the space)
    
    myInst.setType(text1);

    // NEW SECTION: WE'LL DO THE CODE SEPARATELY FOR A J INSTRUCTION (only has dest)
    if (text1 == "J"){
        // s1 and s2 are ""
        text2 = trimExtraWhiteSpace(text2);

        myInst.setDest(text2);
        myInst.setS1("");
        myInst.setS2("");
        
        return myInst; // early return
    }

    
    // split string by commas: dest, source1, source2(optional)
    string text_a, text_b, text_c;
    int first_comma = plaintext.find(',');
    int second_comma = plaintext.find(',', first_comma + 1);

    if (second_comma == -1){    // note: npos should be converted into -1 since we saved second_comma as int
        // there is only 1 comma
        text_a = plaintext.substr(0, first_comma);
        text_b = plaintext.substr(first_comma + 1, second_comma - first_comma - 1);
        text_c = plaintext.substr(second_comma + 1);
    } else {
        // there are 2 commas
        text_a = plaintext.substr(0, first_comma);
        text_b = plaintext.substr(first_comma + 1);
        text_c = "";
    }

    text_a = trimExtraWhiteSpace(text_a);
    text_b = trimExtraWhiteSpace(text_b);
    text_c = trimExtraWhiteSpace(text_c);   // check this doesn't cause an error

    myInst.setDest(text_a);
    myInst.setS1(text_b);
    myInst.setS2(text_c);

    // NOTE: parts 3 and 4 are no longer done inside the function
    // // part 3 - update instruction pointer  (TODO: add branch prediction)
    // if (1){
    //     // default case
    //     m_instruction_pointer += 1;
    // } else {
    //     // Use Branch Prediction To Figure Where to Point Next?
    //     // todo: add a member attr to keep track of prev pointers if prediction is wrong
    // }

    // // part 4
    // m_pipeline.push_back(myInst); // Note: this should now be done in startProcessor

    // New Section: If it is a control instruction, also add m_ptr_to_taken and m_ptr_to_not_taken
    if(myInst.getCategory() == "CONTROL"){
        int posTaken;
        int posNotTaken;

        // posTaken is the position of the label at dest
        posTaken = findLabelIndex(myInst.getDest());

        // posNotTaken is the currentptr + 1 (ie: the next line as the branch instruction)
        posNotTaken = m_instruction_pointer + 1;

        myInst.setBranchingInt("m_ptr_to_taken", posTaken);
        myInst.setBranchingInt("m_ptr_to_not_taken", posNotTaken);
    }

    return myInst;  
}

// NEW (not yet implemented in Processor.cpp)
// decode a given instruction object and load the values of all delivarables (corresponds to the ID stage)
// What it doesn't do now: also check if we should stall (ie repeat this stage)
// What it doesn't do: push "ID to stage log"
// would interpret its dependencies, and other relevant details not already known
// if we have a memory function, replace offset(addr) with string(int(offset + addr))
//      // Example: m_s1 = "10($5)" ----> m_s1 = "$15"
//      // Example: m_s1 = "32($1)" ----> m_s1 = "$1"
void Processor::instructionDecode(Instruction &inst){
    // call getOperandVals to find operand values
    getOperandVals(inst);

    // in case of mem functions where an operand name ends in brackets
    // for S1
    if (inst.getS1().back() == ')'){
        int value = inst.getS1Val();

        int intLoc = inst.getS1().find('$'); // location of '$' sign
        int fLoc = inst.getS1().find('F'); // location of 'F'
        // if both are -1, we can assume it's a memory address

        if (intLoc != -1){
            // int register $
            int num = value % 32;
            inst.setS1(getIndexToAddressWithoutOffset(num, "R_INT"));
        } else if (fLoc != -1){
            // float register F
            int num = value % 32;
            inst.setS1(getIndexToAddressWithoutOffset(num, "R_F"));
        } else {
            // mem address
            int num = value % 19;
            inst.setS1(getIndexToAddressWithoutOffset(num, "MEMORY"));
        }
    }


    // for S2
    if (inst.getS2().back() == ')'){
        int value = inst.getS2Val();

        int intLoc = inst.getS2().find('$'); // location of '$' sign
        int fLoc = inst.getS2().find('F'); // location of 'F'
        // if both are -1, we can assume it's a memory address

        if (intLoc != -1){
            // int register $
            int num = value % 32;
            inst.setS2(getIndexToAddressWithoutOffset(num, "R_INT"));
        } else if (fLoc != -1){
            // float register F
            int num = value % 32;
            inst.setS2(getIndexToAddressWithoutOffset(num, "R_F"));
        } else {
            // mem address
            int num = value % 19;
            inst.setS2(getIndexToAddressWithoutOffset(num, "MEMORY"));
        }
    }
}

// NOTE: DUE TO REGISTER ISSUES, THIS IS POTENTIALLY INCOMPLETE
// finds the int values of the dependencies for a given instruction (is helper to instructionDecode())
// if s2 doesn't exist, save the value as -1
// if something is an immediate, save the value as itself
// Precondition: IF stage has been called so we do know the names of the operands
void Processor::getOperandVals(Instruction &x){
    // find the register/memory values per operand
    string dest = x.getDest();
    string s1 = x.getS1();
    string s2 = x.getS2();
    // Destination - always a register
    int destRegisterNum = registerAddressToIndex(dest);
    if (dest[0] == '$'){
        // int register
        x.setDestVal(m_registersInt[destRegisterNum]);

    } else if (dest[0] == 'F') {
        // float register
        x.setDestVal(m_registersF[destRegisterNum]);
    } else {
        // unexpected
        x.setDestVal(-1);
    }

    // S1 - might be: register, imediate, memory address --> (as in: offset(addr)), label
    string p1 = s1.substr(0, 1);  // first character
    string p2 = s1.substr(1);     // everything else

    if (p1 == "F"){ // assume it's a register name
        int s1Val = m_registersInt[registerAddressToIndex(s1)];
        x.setS1Val(s1Val);
    } else if (p1 == "$"){ // also assume it's a register
        int s1Val = m_registersF[registerAddressToIndex(s1)];
        x.setS1Val(s1Val);
    } else {
        // If there it ends in ')' assume it's offset(addr) - otherwise, it's an immediate
        string pf = s1.substr(s1.size() - 1); // the final character
        if (pf == ")"){
            // memory address or int register address or F register address + offset
            string addr = getSubstringInsideBrackets(s1);
            int offset = stoi(getSubstringBeforeBrackets(s1)); // assuming that this can be converted to a num
            
            string subp1 = addr.substr(0, 1);  // first character
            string subp2 = addr.substr(1);     // everything else
            if (subp1 == "$"){ // assume addr is an int register name
                int s1Val = m_registersInt[(registerAddressToIndex(addr) + offset) % 32];
                x.setS1Val(s1Val);
            } else if (subp1 == "F"){ // also assume addr is a Float register name
                int s1Val = m_registersF[(registerAddressToIndex(addr) + offset) % 32];
                x.setS1Val(s1Val);
            } else { // assume addr is an immediate (representing the memory location)
                int s1Val = m_memory[(stoi(addr) + offset) % 19];
                x.setS1Val(s1Val);
            }

        } else {
            // valid integer immediate (if we can convert to int) OR label (if we can't convert to int)
            
            try {
                // immediate
                int number = stoi(s1);
                x.setS1Val(number);
            } catch (const invalid_argument& e) {
                // label name
                x.setS1Val(-1);
            }
        }
    }

    // S2 - potentially non-existant --> -1
    if (s2 == ""){
        x.setS2Val(-1);
    } else {
        // otherwise, mostly the same as S1
        // S2 - might be: register, imediate, memory address --> (as in: offset(addr))
        string p1 = s2.substr(0, 1);  // first character
        string p2 = s2.substr(1);     // everything else

        if (p1 == "F"){ // assume it's a register name
            int s2Val = m_registersInt[registerAddressToIndex(s2)];
            x.setS2Val(s2Val);
        } else if (p1 == "$"){ // also assume it's a register
            int s2Val = m_registersF[registerAddressToIndex(s2)];
            x.setS2Val(s2Val);
        } else {
            // If there it ends in ')' assume it's offset(addr) - otherwise, it's an immediate
            string pf = s2.substr(s2.size() - 1); // the final character
            if (pf == ")"){
                // memory address or int register address or F register address + offset
                string addr = getSubstringInsideBrackets(s2);
                int offset = stoi(getSubstringBeforeBrackets(s2)); // assuming that this can be converted to a num
                
                string subp1 = addr.substr(0, 1);  // first character
                string subp2 = addr.substr(1);     // everything else
                if (subp1 == "$"){ // assume addr is an int register name
                    int s2Val = m_registersInt[(registerAddressToIndex(addr) + offset) % 32];
                    x.setS2Val(s2Val);
                } else if (subp1 == "F"){ // also assume addr is a Float register name
                    int s2Val = m_registersF[(registerAddressToIndex(addr) + offset) % 32];
                    x.setS2Val(s2Val);
                } else { // assume addr is an immediate (representing the memory location)
                    int s2Val = m_memory[(stoi(addr) + offset) % 19];
                    x.setS2Val(s2Val);
                }

            } else {
                // valid integer immediate (if we can convert to int)
                try {
                    // immediate
                    int number = stoi(s2);
                    x.setS2Val(number);
                } catch (const invalid_argument& e) {
                    // I don't think it might be a label name, but this is still a good catch for exceptions
                    x.setS2Val(-1);
                }
            }
        }
    }
}

// return a boolean on whether we are allowed to move forward to the beginning of the execute stage, for the current instruction
// this function also references the forwarding vectors and the instruction type and category
bool Processor::isExecuteAllowed(Instruction &x){
    // We need to check the heldUp stuff for everything other than J and Loads
        // L.D Fa, Offset(addr)
        // S.D Fa, Offset(addr)
        // LI $d, IMM64 -Integer Immediate Load
        // LW $d, Offset(addr)
        // SW $s, Offset(addr)

    vector<string> myV = m_heldUpRead;
    string type = x.getType();

    if (type == "J" or type == "L.D" or type == "LI" or type == "LW"){
        return true;
    }
    // find out if there is more than 1 instances of any of the (READ) operators within the vector --> if there are: return false
    
    string dest = x.getDest();
    string s1 = x.getS1();
    string s2 = x.getS2();
    string category = x.getCategory();

    if (category == "CONTROL"){
        return (!moreThanOneInstanceInVector(myV, dest));
    }
    if (category == "MEMORY"){
        // stores
        return (!moreThanOneInstanceInVector(myV, s1));
    }
    // category == "ALU"
    if (type == "ADDI"){
        // add immediate
        return !moreThanOneInstanceInVector(myV, s1); 
    }

    // account for s1 and s2 being same register

    int cnt1 = count(myV.begin(), myV.end(), s1);
    int cnt2 = count(myV.begin(), myV.end(), s2);

    if (s1!=s2) {
        return (cnt1<2 and cnt2<2);
    } else {
        return (cnt1<3);
    }

}


void Processor::removeInstanceFromVector(vector<string> myVec, string operandName){
    // part 1: find the first occurrence – using iterator type
    vector<string>::iterator it = find(myVec.begin(), myVec.end(), operandName);

    // part 2: if found, erase it
    if (it != myVec.end()) {
        myVec.erase(it);
    }

}

bool Processor::moreThanOneInstanceInVector(vector<string> myVec, string operandName){
    // Find if operandName appears in vector more than once
    // count how many times operandName appears
    int cnt = count(myVec.begin(), myVec.end(), operandName);

    if (cnt >= 2) {
        return true;
    } else {
        return false;
    }
}


int Processor::getBranchPrediction(Instruction cInst) {
    // New: don't call this for "J" instructions, because they are always taken
    // This returns 1 for taken, 0 for not taken, or -1 for something wrong
    // New: Also, updates m_predicted_taken in cInst
    int prediction = m_bp.getPrediction();
    cInst.setBranchingInt("m_predicted_taken", prediction);
    return prediction;
}

int Processor::getBranchActual(Instruction cInst) { // todo: also potentially update the predictor
    // New: Also, updates m_actual_taken in cInst (but only if we are successful)
    // New: what to use: cInst.setBranchingInt("m_actual_taken", ...);
    string type = cInst.getType();

    // Something wrong
    if (type != "BEQ" && type != "BNE" && type != "J") {
        return -1;
    }

    // Jump is always taken
    if (type == "J") {
        cInst.setBranchingInt("m_actual_taken", 1);
        return 1;
    }

    int s1 = cInst.getS1Val();
    int s2 = cInst.getS2Val();

    if (type == "BEQ") {
        if(s1 == s2) {
            cInst.setBranchingInt("m_actual_taken", 1);
            return 1;
        } else {
            cInst.setBranchingInt("m_actual_taken", 0);
            return 0;
        }
    }

    if (type == "BNE") {
        if(s1 != s2) {
            cInst.setBranchingInt("m_actual_taken", 1);
            return 1;
        } else {
            cInst.setBranchingInt("m_actual_taken", 0);
            return 0;
        }
    }

    // Something went wrong if it makes it here
    return -1;
}

int Processor::findLabelIndex(string labelName){
    if(labelName.empty()) return -1;
    
    // Decided to add a : at the end to match the format of "Label:" since it wasn't working otherwise
    string targetLabel = labelName + ":";

    // Loop through all instructions to search for label
    for (int i = 0; i < m_instructions_len; ++i) {
        string trimmed = trimExtraWhiteSpace(m_instructions[i]);

        // Check if the instruction starts with the label followed by :
        if (trimmed.find(targetLabel) == 0) {
            return i;
        }
    }
    // Something wrong
    return -1;

}

void Processor::convertPipline(){
    int num_instructions = m_pipeline.size();

    // FInding the num colums/ max ending cycle across all of the instructions
    int max_cycle = 0;
    for (int i = 0; i < num_instructions; ++i) {
        int end;
        if (m_pipeline[i].getIsActive()) {
            end = m_clock;
        } else {
            end = m_pipeline[i].getStageLog().size() + m_pipeline[i].getInitialCycle();
        }

        if (end > max_cycle) {
            max_cycle = end;
        }
    }

    // Creating and intializing 2D array of empty strings
    string** spreadsheet = new string*[num_instructions];
    for (int i = 0; i < num_instructions; ++i) { // num_instructions are the ros
        spreadsheet[i] = new string[max_cycle];
        for (int j = 0; j < max_cycle; ++j) { // max_cycle are the columns
            spreadsheet[i][j] = "";
        }
    }

    // Populating each instructions row based on its stage log
    for (int i = 0; i < num_instructions; ++i) {
        Instruction inst = m_pipeline[i];

        int endCycle;
        // If its still active then it then it uses current clock as end cylce
        if (inst.getIsActive()) {
            endCycle = m_clock;
        } else { // If its inactive then it calculates the end based on how many stages were completed when started
            endCycle = inst.getStageLog().size() + inst.getInitialCycle();
        }

        // Using the initial cycle find the starting column for the instructions row
        int start_cycle = inst.getInitialCycle();

        const vector<string>& stages = inst.getStageLog();
        // Looping through each stage and putting it in the column it belongs is
        for (int j = 0; j < stages.size(); ++j) {
                int col = start_cycle + j - 1;
                if (col < max_cycle) {
                    spreadsheet[i][col] = stages[j];
                }
            }
        }
}


// HELPER FUNCTIONS

void Processor::exportSpreadsheet(string filename, string** spreadsheet, int rows, int cols){
    // open new txt file
    ofstream outfile(filename);

    // iterate 2d array spreadsheet
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outfile << spreadsheet[i][j]; // add contents to file
            if (j < cols - 1) {
                outfile << "\t"; // add tab between valus for clean visualization
            }
        }
        outfile << endl; // add new line after each row
    }

    outfile.close();
}

// Display/print main memory
void Processor::displayMemory(){
    cout << "Memory Contents from indices 0-18:" << endl;
    for (int i = 0; i < 19; ++i) {
        cout << "m_memory[" << i << "] = " << m_memory[i] << endl;
    }
    cout << endl;
}

 // Display/print int registers
void Processor::displayRegistersInt(){
    cout << "Integer Registers from $0 - $31:" << endl;
    for (int i = 0; i < 32; ++i) {
        cout << "$" << i << " = " << m_registersInt[i] << endl;
    }
    cout << endl;
}

// Display/print F registers
void Processor::displayRegistersF(){
    cout << "Float Registers from F0-F31:" << endl;
    for (int i = 0; i < 32; ++i) {
        cout << "F" << i << " = " << m_registersF[i] << endl;
    }
    cout << endl;
}

string Processor::trimExtraWhiteSpace(string s1){
    // trims any extra whitespace from before and after from the line
    // example input: "       ADD F1, F2, F3  "
    // example output: "ADD F1, F2, F3"
    if (s1.empty()) return s1;

    return s1.substr(s1.find_first_not_of(" \t\n\r"), s1.find_last_not_of(" \t\n\r") - s1.find_first_not_of(" \t\n\r") + 1);
}



