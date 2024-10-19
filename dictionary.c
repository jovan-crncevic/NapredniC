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

    while (text[i] != '\0' && *n < WORD_MAX_COUNT)
    {
        if (text[i] == ' ' && m > 0)
        {
            dictionary[*n][m] = '\0';
            (*n)++;
            m = 0;
        }
        else if (isalpha(text[i]) && m < WORD_MAX_SIZE - 1)
        {
            dictionary[*n][m] = tolower(text[i]);
            m++;
        }

        i++;
    }

    if (m > 0)
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
    if (n < 2) return;

    for (COUNTER_TYPE i = 0; i < n - 1; i++) {
        for (COUNTER_TYPE j = 0; j < n - i - 1; j++) {
            if (strcmp(dictionary[j], dictionary[j + 1]) > 0) {
                char temp[WORD_MAX_SIZE];
                strcpy(temp, dictionary[j]);
                strcpy(dictionary[j], dictionary[j + 1]);
                strcpy(dictionary[j + 1], temp);
            }
        }
    }
}

/*void merge(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE left, COUNTER_TYPE mid, COUNTER_TYPE right) {
    COUNTER_TYPE i, j, k;
    COUNTER_TYPE n1 = mid - left + 1;
    COUNTER_TYPE n2 = right - mid;

    char leftArray[n1][WORD_MAX_SIZE], rightArray[n2][WORD_MAX_SIZE];

    // Kopiraj podatke u leve i desne nizove
    for (i = 0; i < n1; i++)
        strcpy(leftArray[i], dictionary[left + i]);
    for (j = 0; j < n2; j++)
        strcpy(rightArray[j], dictionary[mid + 1 + j]);

    i = 0; // Početak leve strane
    j = 0; // Početak desne strane
    k = left; // Početak spajanog niza

    // Spajanje niza
    while (i < n1 && j < n2) {
        if (strcmp(leftArray[i], rightArray[j]) <= 0) {
            strcpy(dictionary[k], leftArray[i]);
            i++;
        } else {
            strcpy(dictionary[k], rightArray[j]);
            j++;
        }
        k++;
    }

    // Kopiranje preostalih elemenata
    while (i < n1) {
        strcpy(dictionary[k], leftArray[i]);
        i++;
        k++;
    }
    while (j < n2) {
        strcpy(dictionary[k], rightArray[j]);
        j++;
        k++;
    }
}

void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n) {
    COUNTER_TYPE curr_size;
    COUNTER_TYPE left_start;

    // Spajanje podnizova u rastućem redosledu
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            COUNTER_TYPE mid = left_start + curr_size - 1;
            COUNTER_TYPE right_end = (left_start + 2 * curr_size - 1 < n - 1) ? (left_start + 2 * curr_size - 1) : (n - 1);

            if (mid < right_end) {
                merge(dictionary, left_start, mid, right_end);
            }
        }
    }
}*/

void generateOutputFile(char dictionary[][WORD_MAX_SIZE])
{
    FILE *file = fopen("dictionary.txt", "w");

    if (file == NULL)
    {
        perror("Error opening output file");
        return;
    }

    fprintf(file, "------------------\n");
    fprintf(file, "--- DICTIONARY ---\n");
    fprintf(file, "------------------\n");

    if (dictionary[0][0] == '\0')
    {
        fprintf(file, "Dictionary is empty");
    }
    else
    {
        COUNTER_TYPE i = 0;

        while (dictionary[i][0] != '\0' && i < WORD_MAX_COUNT)
        {
            fprintf(file, "%" COUNTER_SPECIFIER ".\t%s\n", i+1, dictionary[i]);
            i++;
        }
    }

    fclose(file);
}

void makeDictionary(char text[], char dictionary[][WORD_MAX_SIZE])
{
    COUNTER_TYPE n = 0;
    COUNTER_TYPE uniqueCount = 0;

    separateWords(text, dictionary, &n);
    removeDuplicates(dictionary, n, &uniqueCount);
    sortWords(dictionary, uniqueCount);
    if (GENERATE_OUTPUT_FILE)
    {
        generateOutputFile(dictionary);
    }
}

void printDictionary(char dictionary[][WORD_MAX_SIZE])
{
    printf("\n------------------\n");
    printf("--- DICTIONARY ---\n");
    printf("------------------\n");

    if (dictionary[0][0] == '\0')
    {
        printf("Dictionary is empty");
    }
    else
    {
        COUNTER_TYPE i = 0;

        while (dictionary[i][0] != '\0' && i < WORD_MAX_COUNT)
        {
            printf("%" COUNTER_SPECIFIER ".\t%s\n", i+1, dictionary[i]);
            i++;
        }
    }

    printf("\n");
}