#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "utils.h"

// Function signatures
void Search(Dictionary *dictionaries, int *pNumOfDicts);
Dictionary* deleteWord(Dictionary *dictionaries, int *pNumOfDicts);
void recursionWordErasing(Word **tmp, int numOfLanguages);
Dictionary* langErase(Dictionary *dictionaries, int userOption);
Dictionary* newArrangement(Dictionary *dictionaries, int *pNumOfDicts, int userOption, int *caller);
Dictionary* deleteDic(Dictionary *dictionaries, int userOption, int *pNumOfDicts, int *caller);
Dictionary* deleteFullDic(Dictionary *dictionaries, int *pNumOfDicts);
Dictionary* memoryToNewDic(Dictionary *dictionaries, int numOfDicts, int *caller);
Dictionary* newWord(Dictionary *dictionaries, int *pNumOfDicts);
Dictionary* newDictionary(Dictionary *dictionaries, int *pNumOfDicts);
void deleteEverything(Dictionary *dictionaries, int *pNumOfDicts);

#endif // DICTIONARY_H
