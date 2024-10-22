#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

static void separateWords(const char text[], char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE* n);
static void removeDuplicates(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n, COUNTER_TYPE* uniqueCount);
static void swap(char a[], char b[]);
static void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE uniqueCount);
static void generateOutputFile(const char dictionary[][WORD_MAX_SIZE]);

static void separateWords(const char text[], char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE* n)
{
    assert(text != NULL);
    assert(dictionary != NULL);
    assert(n != NULL);

    COUNTER_TYPE i = 0;
    COUNTER_TYPE m = 0;

    while ((text[i] != '\0') && (*n < WORD_MAX_COUNT))
    {
        if ((text[i] == ' ') && (m > 0))
        {
            dictionary[*n][m] = '\0';
            (*n)++;
            m = 0;
            i++;
        }
        else if ((isalpha(text[i])) && (m < WORD_MAX_SIZE - 1))
        {
            dictionary[*n][m] = tolower(text[i]);
            m++;
            i++;
        }
        else
        {
            i++;
        }
    }

    if (m > 0)
    {
        dictionary[*n][m] = '\0';
        (*n)++;
    }
}

static void removeDuplicates(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n, COUNTER_TYPE* uniqueCount)
{
    assert(dictionary != NULL);
    assert(uniqueCount != NULL);
    assert(n <= WORD_MAX_COUNT);

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

static void swap(char a[], char b[])
{
    assert(a != NULL);
    assert(b != NULL);
    
    char temp[WORD_MAX_SIZE] = {'\0'};

    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

static void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE uniqueCount)
{
    assert(dictionary != NULL);
    assert(uniqueCount <= WORD_MAX_COUNT);

    COUNTER_TYPE stack[uniqueCount];
    COUNTER_TYPE top = -1;

    top++;
    stack[top] = 0;
    top++;
    stack[top] = uniqueCount - 1;

    while (top >= 0)
    {
        COUNTER_TYPE right = stack[top];
        top--;
        COUNTER_TYPE left = stack[top];
        top--;

        char pivot[WORD_MAX_SIZE] = {'\0'};
        strcpy(pivot, dictionary[right]);
        COUNTER_TYPE i = left - 1;

        for (COUNTER_TYPE j = left; j < right; j++)
        {
            if (strcmp(dictionary[j], pivot) <= 0)
            {
                i++;
                swap(dictionary[i], dictionary[j]);
            }
        }
        swap(dictionary[i + 1], dictionary[right]);

        COUNTER_TYPE pivotIndex = i + 1;

        if ((pivotIndex - 1) > left)
        {
            top++;
            stack[top] = left;
            top++;
            stack[top] = pivotIndex - 1;
        }
        if ((pivotIndex + 1) < right)
        {
            top++;
            stack[top] = pivotIndex + 1;
            top++;
            stack[top] = right;
        }
    }
}

static void generateOutputFile(const char dictionary[][WORD_MAX_SIZE])
{
    assert(dictionary != NULL);

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

        while ((dictionary[i][0] != '\0') && (i < WORD_MAX_COUNT))
        {
            fprintf(file, "%" COUNTER_SPECIFIER ".\t%s\n", i + 1, dictionary[i]);
            i++;
        }
    }

    fclose(file);
}

void makeDictionary(const char text[], char dictionary[][WORD_MAX_SIZE])
{
    assert(text != NULL);
    assert(dictionary != NULL);

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

void printDictionary(const char dictionary[][WORD_MAX_SIZE])
{
    assert(dictionary != NULL);

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

        while ((dictionary[i][0] != '\0') && (i < WORD_MAX_COUNT))
        {
            printf("%" COUNTER_SPECIFIER ".\t%s\n", i + 1, dictionary[i]);
            i++;
        }
    }

    printf("\n");
}
