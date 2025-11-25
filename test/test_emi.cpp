#include <gtest/gtest.h>
#include "../src/Loan.h" 

// TEST 1: Normal Calculation
// We use known values , Loan 1000, Rate 10%, 1 Year 

TEST(LoanTest, CalculatesStandardEMI) {
    LoanCalculator loan;
    loan.setAmount(1000.0);
    loan.setInterest(10.0);
    loan.setPeriodTotal(12);

    // Allow a tiny error margin
    EXPECT_NEAR(loan.calculatePayment(), 87.91, 0.01); 
}

// TEST 2: Invalid Input Handling
// Assignment Requirement
TEST(LoanTest, HandlesNegativeInput) {
    LoanCalculator loan;
    
    // Try to set negative amount
    loan.setAmount(-5000.0);
    
    
    // Adjust this expectation based on YOUR Loan.cpp logic.
   
    EXPECT_GT(loan.getAmount(), 0); 
}

// TEST 3: Large Tenure (Overflow Check)

TEST(LoanTest, HandlesLargeTenure) {
    LoanCalculator loan;
    
    // 10 Million Dollar loan for 100 years Max
    loan.setAmount(10000000.0); 
    loan.setInterest(5.0);
    loan.setPeriodTotal(1200); 

    long double emi = loan.calculatePayment();
    
    // We just want to ensure it calculates a valid number
    EXPECT_GT(emi, 0);
    EXPECT_LT(emi, 10000000.0); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
