#include <stdio.h>
#include <math.h>

float calcrepayment(float loan, float interestrate, int years, int installment, float extrapayment, int year)
{
    if (years == 0 || loan <= 0)
    {
        return 0;
    }

    loan = loan + (loan * interestrate);
    loan = loan - installment - extrapayment;

    if (loan < 0)
    {
        loan = 0;
    }

    printf("Year %d : Remaining loan = %.2f\n", year, loan);

    return (installment + extrapayment) + calcrepayment(loan, interestrate, years - 1, installment, extrapayment, year + 1);
    // year + 1 is form printing purpose only
}

int main()
{
    float loan = 100000;
    float interestrate = 0.05;
    int years = 3;
    int installment = 30000;
    float extraPayment = 0;

    printf("Loan Repayment Schedule:\n");
    float totalbill = calcrepayment(loan, interestrate, years, installment, extraPayment, 1);
    printf("Total repayment = %.2f\n", totalbill);

    return 0;
}