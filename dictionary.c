#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

void separateWords(char text[], char dictionary[][WORD_MAX_SIZE], int_fast16_t* n)
{
    int_fast16_t i = 0;
    int_fast16_t m = 0;

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

void removeDuplicates(char dictionary[][WORD_MAX_SIZE], int_fast16_t n, int_fast16_t* uniqueCount)
{
    int_fast8_t isDuplicate;

    for (int_fast16_t i = 0; i < n; i++)
    {
        isDuplicate = 0;
        
        for (int_fast16_t j = 0; j < *uniqueCount; j++)
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

    for (int_fast16_t i = *uniqueCount; i < WORD_MAX_COUNT; i++)
    {
        dictionary[i][0] = '\0';
    }
}

/*void sortWords(char dictionary[][WORD_MAX_SIZE], int n) {
    // Kreiraj stog za čuvanje indeksa
    int stack[n];
    int top = -1;

    // Pushuj početne indekse na stog
    stack[++top] = 0;
    stack[++top] = n - 1;

    // Dok stog nije prazan
    while (top >= 0) {
        // Uzmi visoki i niski indeks
        int high = stack[top--];
        int low = stack[top--];

        // Izaberi pivot
        char pivot[WORD_MAX_SIZE];
        strcpy(pivot, dictionary[high]);
        int i = low - 1;

        // Poredi i zameni ako je potrebno
        for (int j = low; j < high; j++) {
            if (strcmp(dictionary[j], pivot) < 0) {
                i++;
                // Zameni dictionary[i] i dictionary[j]
                char temp[WORD_MAX_SIZE];
                strcpy(temp, dictionary[i]);
                strcpy(dictionary[i], dictionary[j]);
                strcpy(dictionary[j], temp);
            }
        }

        // Zameni pivot sa elementom na i+1
        char temp[WORD_MAX_SIZE];
        strcpy(temp, dictionary[i + 1]);
        strcpy(dictionary[i + 1], dictionary[high]);
        strcpy(dictionary[high], temp);
        
        // Pomeraj da bi se odredili novi indeksi
        int pivotIndex = i + 1;

        // Pushuj leve i desne indekse na stog
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}*/

void sortWords(char dictionary[][WORD_MAX_SIZE], int n) {
    // Ako je broj reči manji od 2, nema potrebe za sortiranjem
    if (n < 2) return;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
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
    int_fast16_t n = 0;
    int_fast16_t uniqueCount = 0;

    separateWords(text, dictionary, &n);
    removeDuplicates(dictionary, n, &uniqueCount);
    sortWords(dictionary, uniqueCount);
}

void printDictionary(char dictionary[][WORD_MAX_SIZE])
{
    int_fast16_t i = 0;

    printf("\n------------------\n");
    printf("--- DICTIONARY ---\n");
    printf("------------------\n");

    while (dictionary[i][0] != '\0' && i < WORD_MAX_COUNT)
    {
        printf("%ld.\t%s\n", i+1, dictionary[i]);
        i++;
    }

    printf("\n");
}