#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdint.h>

#define TEXT_MAX_SIZE 10000
#define WORD_MAX_SIZE 15
#define WORD_MAX_COUNT 1000
#define COUNTER_TYPE int_fast16_t
#define COUNTER_SPECIFIER PRIdFAST16
#define GENERATE_OUTPUT_FILE 1

void separateWords(char text[], char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE* n);
void removeDuplicates(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n, COUNTER_TYPE* uniqueCount);
void sortWords(char dictionary[][WORD_MAX_SIZE], COUNTER_TYPE n);
void generateOutputFile(char dictionary[][WORD_MAX_SIZE]);
void makeDictionary(char text[], char dictionary[][WORD_MAX_SIZE]);
void printDictionary(char dictionary[][WORD_MAX_SIZE]);

#endif