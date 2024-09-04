#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COMMA ','
#define YES 'y'
#define TWO 2
#define THREE 3

/**
 * two structs, the Dictionary struct which contains languages of type
 * pointer to pointer , numOfLanguages that contains the amount of languages in this
 * dictionary. and wordlist which is of type struct. this struct contains translations
 * with type of pointer to pointer, and a pointer next.
 * **/
typedef struct Word {
    char** translations;
    struct Word* next;
} Word;

typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

// Utility function signatures
extern int Printer(Dictionary *dictionaries, int *pNumOfDicts, int caller);
extern char* scanStringFromTheUser(int *counterComma, int *caller);
extern void strDivider(char *Letters, int *caller, char **Lines);

#endif // UTILS_H
