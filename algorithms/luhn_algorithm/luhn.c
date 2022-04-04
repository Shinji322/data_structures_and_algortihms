#include <stdio.h>
#include <stdbool.h>

// bool checksum(long long);
int check_length(long long);
bool is_valid(long long);
void print_card(long long);
void first_two_digits(long long);

int main ()
{
    long long credit_card_number = 5555555555554444;
    // long long credit_card_number = 378282246310005;
    // long long credit_card_number = 4012888888881881;

    print_card(credit_card_number);    
}

int check_length(long long cc_num)
{
    int length = 0;
    for (long long copy = cc_num; copy != 0; copy /= 10)
    {
        length++;
    }
    return length;
}

// Validates the checksum
bool checksum(long long cc_num)
{
    long long ccn = cc_num;
    int digit_count = 0;
    // i was pulling my hair out but it turns out, 
    // like a complete joker, I forgot to initialize this variable
    // I should play Donkey in Shrek 5.
    int sum = 0; 
    int first = 0, second = 0;

    for (; ccn != 0; digit_count++, ccn /= 10)
    {
        first = ccn % 10;
        if (digit_count % 2 == 0)
        {
            sum += (ccn % 10);
        }
        else
        {
            int digit = (ccn % 10) * 2;
            sum +=  ( digit / 10 ) + ( digit % 10 );
        }
    }
    return (sum % 10) == 0;
}

// Validates the length and the checksum
bool check_validity(long long cc_num)
{
    int len = check_length(cc_num);
    return checksum(cc_num) && (len >= 13 && len <= 16);
}

// This is the real main funciton, if you think about it
void print_card(long long cc_num)
{
    long long ccn = cc_num;

    // Stuff to calculate if the number is valid
    int length = check_length(cc_num);
    int digit_count = 0;
    int first = 0, second = 0;

    // Let's get the first and second digits 
    // Ideally this would be done in another function but
    // I would need to utilize pointers
    for (; ccn > 0; digit_count++, ccn /= 10)
    {
        second = first;
        first = ccn % 10;
    }
    bool is_valid = check_validity(cc_num); 
    // Standard base 10 conversion
    int first_two_digits = first * 10 + second * 1;

    // A really long if statement
    if (first == 4 && digit_count >= 13 && digit_count <= 16 && is_valid)
    {
        printf("VISA\n");
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55 && digit_count == 16 && is_valid)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_digits == 34 || first_two_digits == 37) && digit_count == 15 && is_valid)
    {
        printf("AMEX\n");
    }
    else 
    {
        printf("INVALID\n");
    }
}
