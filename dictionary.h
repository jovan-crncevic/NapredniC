#ifndef DICTIONARY_H
#define DICTIONARY_H

#pragma CHECK_MISRA("-5.6")
#pragma CHECK_MISRA("-5.7")
#pragma CHECK_MISRA("-6.1")
#pragma CHECK_MISRA("-10.1")
#pragma CHECK_MISRA("-12.13")
#pragma CHECK_MISRA("-12.2")
#pragma CHECK_MISRA("-13.5")
#pragma CHECK_MISRA("-14.7")
#pragma CHECK_MISRA("-17.4")
#pragma CHECK_MISRA("-20.9")

#define TEXT_MAX_SIZE 10000
#define WORD_MAX_SIZE 15
#define WORD_MAX_COUNT 1000
#define COUNTER_TYPE int_fast16_t
#define COUNTER_SPECIFIER PRIdFAST16
#define GENERATE_OUTPUT_FILE 1

void makeDictionary(const char text[], char dictionary[][WORD_MAX_SIZE]);
void printDictionary(const char dictionary[][WORD_MAX_SIZE]);

#endif
