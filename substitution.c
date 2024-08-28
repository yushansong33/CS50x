#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkAlpha(string a);
int checkOnce(string c);
string check_cipher(string plain, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int length = strlen(argv[1]);

        // check valid
        if (length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (checkAlpha(argv[1]) == 1)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (checkOnce(argv[1]) == 1)
        {
            printf("Key must contain each letter exactly once.\n");
            return 1;
        }
        else
        {
            // cipher
            string plaintext = get_string("plaintext: ");
            string ciphertext = check_cipher(plaintext, argv[1]);
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
    }
}


int checkAlpha(string a)
{
    int count = 0;
    for (int i = 0; i < strlen(a); i++)
    {
        char ch = a[i];
        if (isalpha(ch) == 0)
        {
            count++;
        }
    }
    if (count != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int checkOnce(string c)
{
    int i = 0;
    int buf[26];
    int count = 0;
    for (i = 0; i < 26; i++)
    {
        buf[i] = -1;
    }

    for (i = 0; i < strlen(c); i++)
    {
        char ch = c[i];
        if (buf[tolower(ch) - 'a'] != -1)
        {
            count++;
        }
        else
        {
            buf[tolower(ch) - 'a'] = 1;
        }
    }

    if (count != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


string check_cipher(string plain, string key)
{
    int l = strlen(plain);
    string base_lower = "abcdefghijklmnopqrstuvwxyz";
    string base_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int j = 0;
    char cipher[l];
    for (j = 0; j < l; j++)
    {
        char ch = plain[j];
        if (isalpha(ch) == 0)
        {
            cipher[j] = ch;
        }
        else
        {
            if (isupper(ch) != 0)
            {
                int x = ch - 'A';
                char ch_keyupper = key[x];
                cipher[j] = toupper(ch_keyupper);
            }
            else
            {
                int y = ch - 'a';
                char ch_keylower = key[y];
                cipher[j] = tolower(ch_keylower);
            }
        }
    }

    string output = cipher;
    return output;
}


