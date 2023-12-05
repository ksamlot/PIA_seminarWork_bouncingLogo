#include "findLCM.h"
#include <stdlib.h>

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
static int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int FindLCM::calculateLCM(int num1, int num2)
{
    // Avoid division by zero
    if (num1 == 0 || num2 == 0) {
        return 0;
    }

    // Calculate the absolute values of num1 and num2
    int absNum1 = abs(num1);
    int absNum2 = abs(num2);

    // Calculate the LCM using the formula: LCM(a, b) = |a * b| / GCD(a, b)
    int gcd = calculateGCD(absNum1, absNum2);
    int lcm = (absNum1 / gcd) * absNum2;

    return lcm;
}
