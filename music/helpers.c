// Helper functions for music
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = atoi(&fraction[0]); //parse fraction
    int denominator = atoi(&fraction[2]);

    if (denominator == 8)
    {
        return numerator;
    }
    else
    {
        return (pow(denominator, -1) * 8);
    }
}

// Calculates frequency (in Hz) of a note and return as int
int frequency(string note)
{
    int len = strlen(note);
    char mnote = 'A';
    char accidentals = ' ';
    int octave = 4;
    float hertz = 440; //start with 440
    int i = 0;

    if (len == 3) //if accidentals
    {
        mnote = note[0];
        accidentals = note[1];
        octave = atoi(&note[2]) - octave;
    }
    else if (len == 2) //if no accidentals
    {
        mnote = note[0];
        octave = atoi(&note[1]) - octave;
    }

    if (octave != 0) //adjust hertz for octave: 2^(4-octave)
    {
        hertz *= pow(2, octave);
    }

    char notes[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
    int a[] = {9, 7, 5, 4, 2, 0, 2};
    float n = 0;
    for (i = 0; i < 7; i++) //iterate to find corresponding multiplier
    {
        if (mnote == notes[i])
        {
            n = (float) a[i] / 12; //exponent
            if (i > 4) //if A or B
            {
                hertz *= pow(2, n);
            }
            else if (i <= 4) //if C - G
            {
                hertz *= 1 / pow(2, n);
            }
        }
    }

    float adjust = (float)1 / 12;
    if (accidentals == '#') //adjust for #
    {
        hertz *= pow(2, adjust);
    }
    else if (accidentals == 'b') //adjust for b
    {
        hertz *= 1 / pow(2, adjust);
    }

    hertz = round(hertz); //round the hertz
    int frequency = (int)hertz; //type casting to integer
    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // return True if blank line. else return false
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}