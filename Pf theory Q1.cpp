#include <stdio.h>

//usage of a  Recursive function
double calculateRepayment(double loan, double interestRate,
                          int years, double annualPayment, int year)
{
    // Base case: loan repaid or no years left
    if (loan <= 0 || years == 0)
        return 0;

    // Applying interest
    double loanWithInterest = loan * (1 + interestRate);

    //  payments
    double remaining = loanWithInterest - annualPayment;
    if (remaining < 0)
        remaining = 0;

    // Print schedule
    printf("Year %d: Remaining loan = %.2f\n", year, remaining);

    // Recursive call for next year
    return annualPayment +
           calculateRepayment(remaining, interestRate,
                               years - 1, annualPayment, year + 1);
}

int main()
{
    double loan = 100000;       
    double interestRate = 0.05;  
    int years = 3;               
    double annualPayment = 40000; 

    printf("Repayment Schedule:\n");
    double totalPaid = calculateRepayment(loan, interestRate, years,
                                          annualPayment, 1);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalPaid);

    return 0;
}


