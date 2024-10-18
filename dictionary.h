#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdint.h>
#include <limits.h>

#define TEXT_MAX_SIZE 8192
#define WORD_MAX_SIZE 16
#define WORD_MAX_COUNT 1024
#define COUNTER_TYPE int_fast16_t
#define COUNTER_SPECIFIER PRIdFAST16

void separateWords(char text[], char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE* n);
void removeDuplicates(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n, COUNTER_TYPE* uniqueCount);
void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n);
void makeDictionary(char text[], char dictionary[][WORD_MAX_SIZE]);
void printDictionary(char dictionary[][WORD_MAX_SIZE]);

#endif