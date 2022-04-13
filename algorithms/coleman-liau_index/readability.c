#include <string.h>
#include <stdio.h>
#include <math.h>

// Prototypes
int index_compute(const char*);
int is_letter(char);

// Important things to remember:
// the space character is of decimal 32
// the null character is of decimal 0
// Uppercase letters are in range 65 - 90
// Lowercase letters are in range 97 - 122
// ! = 33
// ? = 63
// . = 46
int main(int argc, char *argv[])
{
    const char *user_input = argv[1];
    // string user_input = "One fish. Two fish. Red fish. Blue fish.";
    int index = index_compute(user_input);

    if (index > 16.0)
    {
        printf("Grade 16+\n");
        return 0;
    }
    if (index < 1.0)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    printf("Grade %d\n", index);
    return 0;
}

int index_compute(const char* text)
{

    // Average number of letters per 100 words in the text
    float L = 0;
    // Average number of sentences per 100 words
    float S = 0;

    // Bookeeping numbers
    float letter_count = 0, sentence_count = 0;
    float word_count = 1;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (is_letter(text[i]))
        {
            letter_count++;
        }
        // if the cur_letter is one of the following: `.?!`
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence_count++;
        }
        // if there is a space
        if (text[i] == 32)
        {
            // this still works at new sentences because of punctuation magic!
            // After a sentence, there is always a space after the period. Like in this sentece!
            word_count++;
        }
    }

    L = (letter_count / word_count) * 100;
    S = (sentence_count / word_count) * 100;

    int index = (int)round((0.0588 * L) - (0.296 * S) - 15.8);

    return index;
}

// checks if it is a chracter, using ascii table
int is_letter(char character)
{
    // checks ascii range for uppercase and lowercase letters
    if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
    {
        return 1;
    }
    return 0;
}

// These functions might help you understand the above code better... or not
// int compute_L(string text)
// {
//     int letter_count = 0;
//     int length = strlen(text);
//     for (int i = 0; i < length; i++)
//     {
//         if (is_letter(text[i]))
//         {
//             letter_count++;
//         }
//     }

//     return (letter_count / word_count) * 100;
// }

// int compute_S(string text)
// {
//     int word_count = 1;
//     int sentence_count = 0;
//     int length = strlen(text);
//     for (int i = 0; i < length; i++)
//     {
//         if (text[i] == 33 || text[i] == 46 || text[i] == 63)
//         {
//             sentence_count++;
//         }
//         if (text[i] == 32)
//         {
//             word_count++;
//         }
//     }

//     return (sentence_count / word_count) * 100;
// }
