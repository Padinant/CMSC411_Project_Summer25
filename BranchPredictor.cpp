// CMSC 411 Project - Summer 2025
// File: BranchPredictor.cpp
// Desc: This class represents a (0, 1) branch predictor
// Date: June 28, 2025
// Authors: Qanita Baqibillah and Padina Toussi

using namespace std;

class BranchPredictor{
public:
    // Constructor and Destructor
    Instruction();
    ~Instruction();
    // get or update prediction
    getPrediction();
    updatePrediction();

    // Function Definitions
    Instruction(){
        m_prediction = true;    // prediction is initially true
    }

    ~Instruction(){}
    
    getPrediction(){
        // returns prediction of the branch predictor
        return m_prediction;
    }
    
    updatePrediction(){
        // Precondition: call this only when the prediction was not correct
        m_prediction = !m_prediction;
    }

private:
    bool m_prediction;

}
