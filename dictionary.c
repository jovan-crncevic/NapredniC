#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

void separateWords(char text[], char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE* n)
{
    COUNTER_TYPE i = 0;
    COUNTER_TYPE m = 0;

    while(text[i] != '\0' && *n < WORD_MAX_COUNT)
    {
        if(text[i] == ' ' && m > 0)
        {
            dictionary[*n][m] = '\0';
            (*n)++;
            m = 0;
        }
        else if(isalpha(text[i]) && m < WORD_MAX_SIZE - 1)
        {
            dictionary[*n][m] = tolower(text[i]);
            m++;
        }

        i++;
    }

    if(m > 0)
    {
        dictionary[*n][m] = '\0';
        (*n)++;
    }
}

void removeDuplicates(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n, COUNTER_TYPE* uniqueCount)
{
    COUNTER_TYPE isDuplicate;

    for (COUNTER_TYPE i = 0; i < n; i++)
    {
        isDuplicate = 0;
        
        for (COUNTER_TYPE j = 0; j < *uniqueCount; j++)
        {
            if (strcmp(dictionary[i], dictionary[j]) == 0)
            {
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate)
        {
            strcpy(dictionary[*uniqueCount], dictionary[i]);
            (*uniqueCount)++;
        }
    }

    for (COUNTER_TYPE i = *uniqueCount; i < WORD_MAX_COUNT; i++)
    {
        dictionary[i][0] = '\0';
    }
}

void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n) {
    // Ako je broj reči manji od 2, nema potrebe za sortiranjem
    if (n < 2) return;

    for (COUNTER_TYPE i = 0; i < n - 1; i++) {
        for (COUNTER_TYPE j = 0; j < n - i - 1; j++) {
            // Poredi dve reči
            if (strcmp(dictionary[j], dictionary[j + 1]) > 0) {
                // Zameni reči
                char temp[WORD_MAX_SIZE];
                strcpy(temp, dictionary[j]);
                strcpy(dictionary[j], dictionary[j + 1]);
                strcpy(dictionary[j + 1], temp);
            }
        }
    }
}

void makeDictionary(char text[], char dictionary[][WORD_MAX_SIZE])
{
    COUNTER_TYPE n = 0;
    COUNTER_TYPE uniqueCount = 0;

    separateWords(text, dictionary, &n);
    removeDuplicates(dictionary, n, &uniqueCount);
    sortWords(dictionary, uniqueCount);
}

void printDictionary(char dictionary[][WORD_MAX_SIZE])
{
    COUNTER_TYPE i = 0;

    printf("\n------------------\n");
    printf("--- DICTIONARY ---\n");
    printf("------------------\n");

    while (dictionary[i][0] != '\0' && i < WORD_MAX_COUNT)
    {
        printf("%" COUNTER_SPECIFIER ".\t%s\n", i+1, dictionary[i]);
        i++;
    }

    printf("\n");
}