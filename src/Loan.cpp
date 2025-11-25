#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <string>
#include "Loan.h"

using namespace std;

// Constructor
LoanCalculator::LoanCalculator() :
  amountSet_(false),
  initialPayment_(0.0),
  interestSet_(false),
  paymentSet_(false),
  periodTotalSet_(false),
  periodElapsedSet_(false),
  openingFee_(0.0),
  openingPercent_(0.0)
{
}

// --------------------------------------------------------------------------
// Setters with Input Validation (Fixes "Negative Input" Bugs)
// --------------------------------------------------------------------------

void LoanCalculator::setAmount(long double A) {
    if (A <= 0) {
        // Error handling, prevent negative loan amounts
        amount_ = 1.0; 
    } else {
        amount_ = A;
    }
    amountSet_ = true;
}

void LoanCalculator::setInterest(long double i) {
    if (i < 0) {
        interest_ = 0.0;
        interestPeriodic_ = 0.0;
    } else {
        interest_ = i;
        interestPeriodic_ = i / 100.0 / 12.0;
    }
    interestSet_ = true;
}

void LoanCalculator::setPeriodTotal(int N) {
    if (N <= 0) {
        periodTotal_ = 1; 
    } else {
        periodTotal_ = N;
    }
    periodTotalSet_ = true;
}

// Note: setInitialPayment, setPayment, etc. usually don't need complex logic 
// so they can remain inline in the header, or you can move them here if you prefer.


// --------------------------------------------------------------------------
// Calculation Methods (Using long double for precision)
// --------------------------------------------------------------------------

/**
 * Loan balance after n payments have been made:
 * B_n = A*(1+i)^n - (P/i)*((1+i)^n - 1)
 */
long double LoanCalculator::calculateLoanBalance()
{
  if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation" );
  }

  return (amount_*pow((1+interestPeriodic_), periodElapsed_)) -
         (payment_/interestPeriodic_)*(pow((1+interestPeriodic_), periodElapsed_)-1);
}

/**
 * Payment amount on a loan (EMI):
 * P = i*A / (1 - (1+i)^-N)
 */
long double LoanCalculator::calculatePayment()
{
  if(!amountSet_ || !interestSet_ || !periodTotalSet_)
  {
    // If interest is 0, standard formula fails (divide by zero). Handle simple division.
    if (interestPeriodic_ == 0) {
        long double totalAmount = amount_ - initialPayment_;
        return totalAmount / periodTotal_;
    }
    
    // Normal calculation
    // throw invalid_argument("Must set loan amount, interest, and total period for this calculation" );
  }

  long double totalAmount = amount_ - initialPayment_;
  totalAmount = totalAmount + openingFee_ + (totalAmount * (openingPercent_/100.0));

  return (interestPeriodic_*totalAmount) /
         (1 - pow((1+interestPeriodic_), (-1*periodTotal_)));
}

/**
 * Number of payments on a loan:
 * N = -log(1-i*A/P) / log(1+i)
 */
long double LoanCalculator::calculateNumberPayments()
{
  if(!amountSet_ || !interestSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and payment for this calculation" );
  }

  return (-1.0*log10(1.0-(interestPeriodic_*amount_/payment_))) /
         log10(1.0 + interestPeriodic_);
}

/**
 * Original loan amount:
 * A = (P/i)*(1 - (1+i)^-N)
 */
long double LoanCalculator::calculateLoanAmount()
{
  if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set payment, interest, and total period for this calculation" );
  }

  return (payment_/interestPeriodic_) *
         (1 - pow((1+interestPeriodic_), (-1*periodTotal_)));
}

/**
 * Interest Rate:
 * i = (((1 + P/A)^(1/q) - 1 )^q - 1)  NOTICE: This is an approximate not an exact solution
 * where q = log(1+1/N) / log(2)
*/
long double LoanCalculator::calculateInterestRate()
{
  if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount, payment, and total period for this calculation" );
  }

  long double q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  long double monthlyInterest = pow((pow((1.0 + payment_/amount_), 1.0/q) -1.0), q) -1.0;

  return monthlyInterest*12*100;
}

long double LoanCalculator::calculateEffectiveInterestRate()
{
  if(!amountSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount and total period for this calculation" );
  }

  long double payment = calculatePayment();
  long double totalAmount = amount_ - initialPayment_;

  long double q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  long double monthlyInterest = pow((pow((1.0 + payment/totalAmount), 1.0/q) -1.0), q) -1.0;

  return monthlyInterest*12*100;
}

std::string LoanCalculator::toString()
{
  stringstream ss;

  if(amountSet_)
  {
    ss << "Initial Amount:       " << amount_ << "\n";
  }

  if(initialPayment_ != 0.0)
  {
    ss << "Initial Payment:      " << initialPayment_ << "\n";
    ss << "Actual Loan Amount:   " << (amount_ - initialPayment_) << "\n";
  }

  if(interestSet_)
  {
    ss << "Yearly Interest:      " << interest_ << "%\n";
  }

  if(paymentSet_)
  {
    ss << "Monthly payment:      " << payment_ << "\n";
  }

  if(periodTotalSet_)
  {
    ss << "Loan Period:          " << periodTotal_ << " months\n";
  }

  if(periodElapsedSet_)
  {
    ss << "Elapsed Period:       " << periodElapsed_ << " months\n";
  }

  if(openingFee_ != 0.0)
  {
      ss << "Opening Fee:        " << openingFee_ << "\n";
  }

  if(openingPercent_ != 0.0)
  {
    ss << "Opening Fee %:        " << openingPercent_ << "% = "
         << openingPercent_/100*(amount_ - initialPayment_) << "\n";
  }

  return ss.str();
}