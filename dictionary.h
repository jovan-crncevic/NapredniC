#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdint.h>

#define TEXT_MAX_SIZE 2056
#define WORD_MAX_SIZE 16
#define WORD_MAX_COUNT 256

void separateWords(char text[], char dictionary[][WORD_MAX_SIZE], int_fast16_t* n);
void removeDuplicates(char dictionary[][WORD_MAX_SIZE], int_fast16_t n, int_fast16_t* uniqueCount);
void sortWords(char dictionary[][WORD_MAX_SIZE], int n);
void makeDictionary(char text[], char dictionary[][WORD_MAX_SIZE]);
void printDictionary(char dictionary[][WORD_MAX_SIZE]);

#endif