#include <stdio.h>
#include <stdlib.h>
#include <chrono>
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

    comparisionCount += criticalFactor(P, &p, &l);

    int startText = 0; //diem khoi dau cua Text match voi Pattern
    int i; //bien chay tren text
    int j = l + 1; //bien chay tren pattern

    if (memcmp(T, T + p, l + 1))
    {
        p = MAX(l + 1, m - l - 1) + 1;

        while (++comparisionCount && startText <= n - m)
        {
            i = startText + l + 1;

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
                    // fprintf(fp1, "%d ", startText);
                    fprintf(fp1, "%d %d\n", startText, startText + m - 1 );
                }

                startText += p;
            }
            else
            {
                startText += j - l + 1;
            }

            j = l + 1;
        }
    }
    else
    {
        int memory = -1;

        while (++comparisionCount && startText <= n - m)
        {
            i = startText + MAX(l, memory) + 1;

            while (++comparisionCount && j < m && ++comparisionCount && T[i] == P[j])
            {
                i++;
                j++;
            }

            if (++comparisionCount && j >= m)
            {
                i = startText + l;
                j = l;

                while (++comparisionCount && i > startText + memory && ++comparisionCount && T[i] == P[j])
                {
                    i--;
                    j--;
                }

                if (++comparisionCount && i <= startText + memory)
                {
                    // fprintf(fp1, "%d ", startText);
                    fprintf(fp1, "%d %d\n", startText, startText + m - 1 );
                }

                startText += p;
                memory = m - p - 1;
            }
            else
            {
                startText += j - l + 1;
                memory = -1;
            }

            j = l + 1;
        }
    }

    fprintf(fp1, "\n");

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
        char T[1000001];
        char P[51];

        fgets(P, 51, fp);
        P[strcspn(P, "\n")] = '\0';

        fscanf(fp, "\n");

        fgets(T, 500001, fp);
        T[strcspn(T, "\n")] = '\0';

        if (outputInfo == 0)
        {
            auto start = std::chrono::high_resolution_clock::now();   // Start measuring time 
            twoWayMatch(T, P, fp1);
            auto end = std::chrono::high_resolution_clock::now();// Stop measuring time
	        double time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count()) / 1e6;


            printf("Time: %f\n", time);
        }
        else if (outputInfo == 1)
        {
            printf("Comparision: %d\n", twoWayMatch(T, P, fp1));
        }
        else if (outputInfo == 2)
        {
            int cmp;

            auto start = std::chrono::high_resolution_clock::now();   // Start measuring time 
            twoWayMatch(T, P, fp1);
            auto end = std::chrono::high_resolution_clock::now();// Stop measuring time
	        double time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count()) / 1e6;

            printf("Time: %f\n", time);
            printf("Comparision: %d\n", cmp);
        }

        fclose(fp);
        fclose(fp1);
    }
}

