#include <iostream>
#include <string>
#include <cstdlib> 
#include "Loan.h"

/**
 * @brief Removed GUI Library and made the App completely console-based
 */
using namespace std;

int main(int argc, char* argv[]) {
    // 1. Create the object
    LoanCalculator loan;

    long double amount = 0.0;
    long double rate = 0.0;
    int months = 0;
    bool inputsProvided = false;

    // 2. Parse Command Line Arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-a" && i + 1 < argc) {
            amount = std::stold(argv[++i]);
            loan.setAmount(amount);
            inputsProvided = true;
        } 
        else if (arg == "-i" && i + 1 < argc) {
            rate = std::stold(argv[++i]);
            loan.setInterest(rate);
        } 
        else if (arg == "-n" && i + 1 < argc) {
            months = std::stoi(argv[++i]);
            loan.setPeriodTotal(months);
        }
    }

    // 3. Validation & Calculation
    if (!inputsProvided) {
        cout << "Usage: ./calc -a [amount] -i [interest_rate] -n [months]" << endl;
        cout << "Example: ./calc -a 50000 -i 5.5 -n 12" << endl;
        return 0; // Exit cleanly
    }

    // Perform Calculation
    long double monthlyPayment = loan.calculatePayment();

    // 4. Output the Result
    cout << "-----------------------------------" << endl;
    cout << "LOAN CALCULATOR RESULTS" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Principal: " << amount << endl;
    cout << "Interest:  " << rate << "%" << endl;
    cout << "Months:    " << months << endl;
    cout << "-----------------------------------" << endl;
    cout << "Monthly EMI: " << monthlyPayment << endl;
    cout << "-----------------------------------" << endl;

    return 0;
}


/**
 * @author Ghulam Muhammad
 */