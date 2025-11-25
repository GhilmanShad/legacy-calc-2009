#include <iostream>
#include <string>
#include <cstdlib> // for atof/atoi
#include "Loan.h"  // We assume your file is named Loan.h

using namespace std;

int main(int argc, char* argv[]) {
    // 1. Create the object
    LoanCalculator loan;

    long double amount = 0.0;
    long double rate = 0.0;
    int months = 0;
    bool inputsProvided = false;

    // 2. Parse Command Line Arguments
    // Example usage: ./calc -a 100000 -i 6.5 -n 360
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-a" && i + 1 < argc) {
            amount = std::stold(argv[++i]);
            loan.setAmount(amount);
            inputsProvided = true;
        } 
        else if (arg == "-i" && i + 1 < argc) {
            rate = std::stold(argv[++i]);
            loan.setInterest(rate); // Your header says this takes annual % (e.g. 6.75)
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

    // Optional: If you implemented toString() in Loan.cpp, you can uncomment this:
    // cout << loan.toString() << endl;

    return 0;
}