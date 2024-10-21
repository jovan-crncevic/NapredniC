#ifndef DICTIONARY_H
#define DICTIONARY_H

#define TEXT_MAX_SIZE 10000
#define WORD_MAX_SIZE 15
#define WORD_MAX_COUNT 1000
#define COUNTER_TYPE int_fast16_t
#define COUNTER_SPECIFIER PRIdFAST16
#define GENERATE_OUTPUT_FILE 1

void makeDictionary(const char text[], char dictionary[][WORD_MAX_SIZE]);
void printDictionary(const char dictionary[][WORD_MAX_SIZE]);

#endif
