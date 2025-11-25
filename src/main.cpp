#include <iostream>
#include <string>
#include <cstdlib>
#include "Loan.h"
#include <fstream>


/**
 * @brief Removed GUI Library and made the App completely console-based
 */
using namespace std;

/**
 * @param readConfig defining the parameters of function
 */

/**
 * @brief Explaining readConfig from reading values with file handling from config.txt
 */

void readConfig(long double &amount, long double &rate, int &months) {
    std::ifstream file("config.txt");

    if (!file.is_open()) {
        std::cout << "config.txt not found. Using defaults.\n";
        return;
    }

    std::string name;
    std::string value;

    // Each line should look like:  Name=Value
    while (std::getline(file, name, '=') && std::getline(file, value)) {
        if (name == "Amount") {
            amount = std::stold(value);
        }
        else if (name == "Interest") {
            rate = std::stold(value);
        }
        else if (name == "Years") {
            months = std::stoi(value) * 12;
        }
    }

    std::cout << "Configuration loaded.\n";
}

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