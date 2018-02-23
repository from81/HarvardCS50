#include <cs50.h> /*Library*/
#include <stdio.h>

int main(void)
{
    printf("Height: ");
    int height = get_int(); //ask for height

    while (height < 0 || height > 23) //set constraint
    {
        printf("Height: ");
        height = get_int();
    }

    char block = '#'; //initialize block
    for (int i = 1; i <= height; i++) //each line
    {
        for (int pad = height - i; pad > 0; pad--) //whitespaces
        {
            printf(" ");
        }
        for (int g = 0; g <= i; g++) //blocks
        {
            printf("%c", block);
        }
        printf("\n");
    }
}