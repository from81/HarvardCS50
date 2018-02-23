#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//argc is number of arguments passed
//argv is the input string
int main(int argc, string argv[])
{
    int i = 0, counter = 0;
    if (argc != 2) //check if more than 2 command line args were entered
    {
        printf("Usage: %s k\n", argv[0]);
        return 1;
    }

    string k = argv[1]; //assign command line argument key (string) to k
    int keylen = strlen(k); //key length
    int key[keylen]; //create int array to use as key array
    for (i = 0; i < keylen; i++) //check if argv[1] was all alpha
    {
        if (isalpha(k[i]) == 0)
        {
            printf("Usage: %s k\n", argv[0]);
            return 1;
        }
    }

    string plaintxt = get_string("plaintext: "); //user input
    for (i = 0; i < keylen; i++) //convert each char to int 0-25 and assign to key[]
    {
        if ((k[i] >= 'a') && (k[i] <= 'z'))
        {
            key[i] = ((int)k[i]) - 97;
        }
        else if ((k[i] >= 'A') && (k[i] <= 'Z'))
        {
            key[i] = ((int)k[i]) - 65;
        }
    }

    int inputlen = strlen(plaintxt); //plaintext length
    for (i = 0; i < inputlen; i++) //encipher each alpha char in string
    {
        if (isalpha(plaintxt[i]) != 0) //if alpha
        {
            if (counter == keylen)
            {
                counter = 0; //reset counter when it reaches keylen
            }
            if (key[counter] > 0) //if key[counter] is greater than 0
            {
                for (int g = 0; g < key[counter]; g++) //encipher key[counter] times
                {
                    if ((plaintxt[i] == 'Z') || (plaintxt[i] == 'z'))
                    {
                        plaintxt[i] -= 25;
                    }
                    else if ((plaintxt[i] >= 'A') && (plaintxt[i] < 'Z'))
                    {
                        plaintxt[i]++;
                    }
                    else if ((plaintxt[i] >= 'a') && (plaintxt[i] < 'z'))
                    {
                        plaintxt[i]++;
                    }
                }
            }
            counter++;
        }
    }
    printf("ciphertext: %s\n", plaintxt);
    return 0;
}