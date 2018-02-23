#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change = get_float("Cash owed: ");
    while (change < 0) //only accept positive values
    {
        change = get_float("Cash owed: ");
    }

    int pennies = round(change * 100); //convert to pennies and from float to int
    int total_coins = 0; //sum of coins
    int coins = 0; //temporary counter of each type of coins

    if (pennies >= 25) //count quarters
    {
        coins += pennies / 25;
        pennies -= coins * 25;
        total_coins += coins;
        coins = 0;
    }
    if (pennies >= 10) //count dimes
    {
        coins += pennies / 10;
        pennies -= coins * 10;
        total_coins += coins;
        coins = 0;
    }
    if (pennies >= 5) //count nickels
    {
        coins += (pennies / 5);
        pennies -= (coins * 5);
        total_coins += coins;
        coins = 0;
    }
    if (pennies >= 0) //convert leftover to pennies
    {
        coins += pennies / 1;
        pennies -= coins * 1;
        total_coins += coins;
        coins = 0;
    }
    printf("%d\n", total_coins);
}