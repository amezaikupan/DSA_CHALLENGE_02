#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX(a, b) (((a) > (b)) ? (a): (b))

int maxsuf(char *T, int reverse, int *p, int *l)
{
    int m = strlen(T);
    int cmp;
    int j = 0;
    int k = 1;
    int comparisionCount = 0;
    *p = 1;
    *l = -1;

    while (++comparisionCount && j + k < m)
    {
        cmp = T[j + k] - T[*l + k];

        if (++comparisionCount && reverse)
        {
            cmp = -cmp;
        }

        if (++comparisionCount && cmp < 0)
        {
            j += k;
            k = 1;
            *p = j - *l;
        }
        else if (++comparisionCount && cmp == 0)
        {
            if (++comparisionCount && k == *p)
            {
                j += *p;
                k = 1;
            }
            else
            {
                k++;
            }
        }
        else
        {
            *l = j;
            j++;
            *p = 1;
            k = 1;
        }
    }

    return comparisionCount;
}

int criticalFactor(char *T, int *p, int *l)
{
    int l1, p1, l2, p2;
    int comparisionCount = 0;
    comparisionCount += maxsuf(T, 0, &p1, &l1);
    comparisionCount += maxsuf(T, 1, &p2, &l2);

    if (++comparisionCount && l1 > l2)
    {
        *l = l1;
        *p = p1;
    }
    else
    {
        *l = l2;
        *p = p2;
    }

    return comparisionCount;
}

int twoWayMatch(char *T, char *P, FILE *fp1)
{
    int p, l, comparisionCount = 0;
    int n = strlen(T);
    int m = strlen(P);

    comparisionCount += criticalFactor(T, &p, &l);

    int startText = 0;
    int i; //bien chay tren text
    int j = l; //bien chay tren pattern

    while (++comparisionCount && startText <= n - m)
    {
        i = startText + l;

        while (++comparisionCount && j < m && ++comparisionCount && T[i] == P[j])
        {
            i++;
            j++;
        }

        if (++comparisionCount && j >= m)
        {
            i = startText + l;
            j = l;

            while (++comparisionCount && i - startText >= 0 && ++comparisionCount && T[i] == P[j])
            {
                i--;
                j--;
            }

            if (++comparisionCount && i - startText < 0)
            {
                fprintf(fp1, "%d ", startText);
            }

            startText += p;
        }
        else
        {
            startText += j - l + 1;
        }

        j = l;
    }

    printf("\n");

    return comparisionCount;
}

void TwoWayAlgorithm(char *inputFile, char *outputFile, int outputInfo)
{
    FILE *fp = fopen(inputFile, "r");
    FILE *fp1 = fopen(outputFile, "w");

    if (fp == NULL || fp1 == NULL)
    {
        printf("Khong mo duoc file!\n");

        if (fp)
        {
            fclose(fp);
        }

        if (fp1)
        {
            fclose(fp1);
        }

        exit(EXIT_FAILURE);
    }
    else
    {
        char T[500001];
        char P[51];

        fgets(P, 51, fp);
        fscanf(fp, "\n");
        fgets(T, 500001, fp);

        if (outputInfo == 0)
        {
            clock_t start, end;

            start = clock();
            twoWayMatch(T, P, fp1);
            end = clock();

            printf("Time: %f\n", double (end - start) / CLOCKS_PER_SEC);
        }
        else if (outputInfo == 1)
        {
            printf("Comparision: %d\n", twoWayMatch(T, P, fp1));
        }
        else if (outputInfo == 2)
        {
            int cmp;
            clock_t start, end;

            start = clock();
            cmp = twoWayMatch(T, P, fp1);
            end = clock();

            printf("Time: %f\n", double (end - start) / CLOCKS_PER_SEC);
            printf("Comparision: %d\n", cmp);
        }

        fclose(fp);
        fclose(fp1);
    }
}
