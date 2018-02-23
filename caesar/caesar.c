#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//argc is number of arguments passed
//argv is the input string
int main(int argc, string argv[])
{
    if (argc != 2) //exit if more than 1 command line arg entered
    {
        printf("Usage: %s k\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[1]); //initialize key
    if (k > 26) //adjust to k <= 26
    {
        k = k % 26;
    }

    string plaintxt = get_string("plaintext: "); //take user input
    int length = strlen(plaintxt); //input string length
    for (int i = 0; i < length; i++) //iterate over each char in string
    {
        if (isalpha(plaintxt[i]) != 0)
        {
            for (int g = 0; g < k; g++)
            {
                if ((plaintxt[i] == 'Z') || (plaintxt[i] == 'z'))
                {
                    plaintxt[i] -= 25;
                }
                else if ((plaintxt[i] >= 'A') && (plaintxt[i] < 'Z'))
                {
                    plaintxt[i] += 1;
                }
                else if ((plaintxt[i] >= 'a') && (plaintxt[i] < 'z'))
                {
                    plaintxt[i] += 1;
                }
            }
        }
    }
    printf("ciphertext: %s\n", plaintxt);
    return 0;
}