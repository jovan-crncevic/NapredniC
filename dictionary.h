#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdint.h>
#include <limits.h>

#define TEXT_MAX_SIZE 8192
#define WORD_MAX_SIZE 16
#define WORD_MAX_COUNT 1024
#define COUNTER_TYPE int_fast16_t
#define COUNTER_SPECIFIER 

void separateWords(signed char text[], signed char dictionary[][WORD_MAX_SIZE], int_fast16_t* n);
void removeDuplicates(signed char dictionary[][WORD_MAX_SIZE], int_fast16_t n, int_fast16_t* uniqueCount);
void sortWords(signed char dictionary[][WORD_MAX_SIZE], int n);
void makeDictionary(signed char text[], signed char dictionary[][WORD_MAX_SIZE]);
void printDictionary(signed char dictionary[][WORD_MAX_SIZE]);

#endif