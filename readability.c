#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int space_count = 0;
    int letter_count = 0;
    int sentence_count = 0;
    string a = ".!?";

    string input = get_string("Text: ");

    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (isalnum(input[i]) != 0)
        {
            letter_count++;
        }

        if (isspace(input[i]) != 0)
        {
            space_count++;
        }

        if (input[i] == a[0] || input[i] == a[1] || input[i] == a[2])
        {
            sentence_count++;
        }
    }

    int words = space_count + 1;

    float letter_average = letter_count / (float) words * 100;

    float sentence_average = sentence_count / (float) words * 100;

    float index = 0.0588 * letter_average - 0.296 * sentence_average - 15.8;

    int index_round = round(index);

    // print grade of the text under condition
    if (index_round < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index_round > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index_round);
    }
}
