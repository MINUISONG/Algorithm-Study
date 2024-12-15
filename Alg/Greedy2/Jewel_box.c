/*
202135784 Song Minui
Assignment: Jewel Box
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void min_cost(int, int, int, int, int);

int main(void)
{
    FILE *fp;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("input.txt could not be opened");
        exit(1);
    }

    int pear;

    while (fscanf(fp, "%d", &pear) != EOF)
    {
        if (pear == 0)
            break;

        int c1, n1, c2, n2;
        fscanf(fp, "%d %d", &c1, &n1);
        fscanf(fp, "%d %d", &c2, &n2);

        if (pear < 1 || pear >= MAX || c1 < 1 || c1 >= MAX || c2 < 1 || c2 >= MAX || n1 < 1 || n1 >= MAX || n2 < 1 || n2 >= MAX)
        {
            puts("input value isn't correct");
            continue;
        }

        min_cost(pear, c1, n1, c2, n2);
    }

    fclose(fp);
    return 0;
}

void min_cost(int pear, int c1, int n1, int c2, int n2) // calculate the minimum total cost
{
    int cost = -1;
    int best_m1 = -1, best_m2 = -1;

    // greedy approach: prioritize based on cost per pearl
    if (n1 / (double)c1 < n2 / (double)c2)
    {
        // Fill with type 1 boxes first
        for (int m1 = 0; m1 * n1 <= pear; ++m1)
        {
            int remaining_pear = pear - m1 * n1;
            if (remaining_pear % n2 == 0)
            {
                int m2 = remaining_pear / n2;
                int total_cost = m1 * c1 + m2 * c2;
                if (cost == -1 || total_cost < cost)
                {
                    cost = total_cost;
                    best_m1 = m1;
                    best_m2 = m2;
                }
            }
        }
    }
    else
    {
        // Fill with type 2 boxes first
        for (int m2 = 0; m2 * n2 <= pear; ++m2)
        {
            int remaining_pear = pear - m2 * n2;
            if (remaining_pear % n1 == 0)
            {
                int m1 = remaining_pear / n1;
                int total_cost = m1 * c1 + m2 * c2;
                if (cost == -1 || total_cost < cost)
                {
                    cost = total_cost;
                    best_m1 = m1;
                    best_m2 = m2;
                }
            }
        }
    }

    if (cost != -1)
    {
        printf("%d %d\n", best_m1, best_m2);
    }
    else
    {
        printf("failed\n");
    }
}
