/*
202135784 Song Minui
Assignment: Euclid Problem
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000001 // Define the maximum limit for input values as 1,000,000,001

long long Extended_Euclid(long long, long long, long long *, long long *);
void adjust_solution(long long, long long, long long *, long long *, long long);

int main(void)
{
    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL) // Check if the file opened successfully
    {
        puts("input.txt could not be opened");
        exit(1);
    }

    long long a, b; // Use the long long type because a and b can grow up to 1,000,000,000,000
    long long x, y;
    long long gcd;

    while (fscanf(fp, "%lld %lld", &a, &b) != EOF)
    {
        if (a >= MAX || b >= MAX)
        {
            puts("input value ERROR");
            exit(1);
        }

        gcd = Extended_Euclid(a, b, &x, &y);
        adjust_solution(a, b, &x, &y, gcd);

        printf("%lld %lld %lld\n", x, y, gcd);
    }
    fclose(fp);
    return 0;
}

/*
Because of the recursive nature of the extended Euclidean algorithm,
the algorithm naturally establishes that |x| + |y| is a minimum
*/
long long Extended_Euclid(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = Extended_Euclid(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

/*
This function adjusts the values of x and y to minimize X <= Y.
*/
void adjust_solution(long long a, long long b, long long *x, long long *y, long long gcd)
{
    long long d = gcd;

    while (*x > *y)
    {
        *x = *x - b / d;
        *y = *y + a / d;
    }
}
