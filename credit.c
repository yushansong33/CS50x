#include <stdio.h>
#include <cs50.h>
#include <math.h>

int every_other_digit(long creditcard);
int multiplyAndSum(int lastdigit);
int number_of_digit(long creditcard);
bool isValidAmex(long creditcard, int numDigit);
bool isValidMaster(long creditcard, int numDigit);
bool isValidVisa(long creditcard, int numDigit);

int main(void)
{
    long credit_card = get_long("Credit Card: ");
    int sum_every_other_digit = every_other_digit(credit_card);
    int num_digits = number_of_digit(credit_card);
    bool amex = isValidAmex(credit_card, num_digits);
    bool master = isValidMaster(credit_card, num_digits);
    bool visa = isValidVisa(credit_card, num_digits);

    if(sum_every_other_digit % 10 != 0){
        printf("INVALID\n");
        return 0;
    }
    else if(amex == true){
        printf("AMEX\n");
    }
    else if(master == true){
        printf("MASTERCARD\n");
    }
    else if(visa == true){
        printf("VISA\n");
    }
    else{
        printf("INVALID\n");
        return 0;
    }
}

// tell whether Amex
bool isValidAmex(long creditcard, int numDigit){
    int first_two_digits = creditcard / pow(10, 13);
    if((numDigit == 15) && (first_two_digits == 34 || first_two_digits == 37)){
        return true;
    }
    else{
        return false;
    }
}

//tell whether MasterCard
bool isValidMaster(long creditcard, int numDigit){
    int first_two_digits = creditcard / pow(10, 14);
    if((numDigit == 16) && (first_two_digits > 50 && first_two_digits < 56)){
        return true;
    }
    else{
        return false;
    }
}

//tell whether Visa
bool isValidVisa(long creditcard, int numDigit){
    int first_digit = creditcard / pow(10, 15);
    if(first_digit == 0){
        first_digit = creditcard / pow(10, 12);
    }

    if((numDigit == 16 || numDigit == 13) && (first_digit == 4)){
        return true;
    }
    else{
        return false;
    }

}


// count the number of digits
int number_of_digit(long creditcard){
    int n = 0;
    while(creditcard > 0){
        n++;
        creditcard = creditcard / 10;
    }
    return n;
}

// sum algorithm
int every_other_digit(long creditcard){
    int sum = 0;
    bool isAlternateDigit = false;
    while(creditcard > 0){
        if(isAlternateDigit == true){
            int last_digit = creditcard % 10;
            int product = multiplyAndSum(last_digit);
            sum += product;
        }
        else{
            int last_digit = creditcard % 10;
            sum += last_digit;
        }
        isAlternateDigit = !isAlternateDigit;
        creditcard = creditcard / 10;
    }
    return sum;
}


int multiplyAndSum(int lastdigit){
    int multiply = lastdigit * 2;
    int sum = 0;
    while(multiply > 0){
        int last_digit_multiply = multiply % 10;
        sum += last_digit_multiply;
        multiply = multiply / 10;
    }
    return sum;
}

