/*
 * ftoa.c
 *
 *  Created on: Oct 12, 2016
 *      Author: vidur
 */
#include "ftoa.h"

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char *str, int d)
{
    int i = 0;
    while (x)
    {
        *(str+i) = (x%10) + '0';
        i++;
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d){
        *(str+i) = '0';
        i++;
    }

    my_reverse(str, i);
    *(str+i) = '\0';
    return i;
}

// Converts a floating point number to string.
void my_ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        *(res+i) = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}


