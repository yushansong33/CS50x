#include<stdio.h>
#include<cs50.h>

int main (void)
{
    // Prompt for users to enter positive heights
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 1);

    // Find number of 25 cents
    int a = n / 25;

    n = n - 25 * a;

    // Find the number of 10 cents
    int b = n / 10;

    n = n - 10 * b;

    // Find the number of 5 cents
    int c = n / 5;

    n = n - 5 * c;

    // Find the number of 1 cent
    int d = n;

    printf("%i\n", a + b + c + d);

}




