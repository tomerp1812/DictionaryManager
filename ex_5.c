#include <stdio.h>
#include "string.h"
#include "stdlib.h"
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
typedef struct Word{
    char** translations;
    struct Word* next;
}Word;

typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
}Dictionary;

/******************
* Function Name:Printer
* Input:Dictionary Dictionary *dictionaries, int *pNumOfDicts, int caller,and scans an option
* Output:prints some menus , and returns userOption
* Function Operation:the function is basically prints the dictionaries
 * and will scan the user's choice and return it to the function that called it.
******************/
int Printer(Dictionary *dictionaries, int *pNumOfDicts, int caller){
    int userOption;

    /**
     * prints the menu of the languages
     * **/
    printf("Choose a dictionary:\n");
    for (int i = 0; i < (*pNumOfDicts); i++) {
        printf("%d. ",(i+1));
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            printf("%s",dictionaries[i].languages[j]);
            if(j < dictionaries[i].numOfLanguages-1)
                printf("%c",COMMA);
        }
        printf("\n");
    }

    /**
     * asks the user to enter a number more than 0 and less than the amount of dictionaries.
     * **/
    do {
        scanf("%d",&userOption);
        if((userOption<1)||(userOption>(*pNumOfDicts)))
            printf("Wrong option, try again:\n");
    } while ((userOption<1)||(userOption>(*pNumOfDicts)));

    /**
     * if the user wants to delete a word or dictionary we want him to be sure he wants to do that.
     * **/
    if(caller==THREE){
        printf("Are you sure? (y/n)\n");
        return userOption;
    }

    /**
     *if the function newWord calls this function it prints the languages of the dictionary.
     **/
    printf("Enter a word in ");
    if(caller==1){
        for (int i = 0; i < dictionaries[userOption - 1].numOfLanguages; i++) {
            printf("%s",dictionaries[userOption - 1].languages[i]);
            if(i < dictionaries[userOption - 1].numOfLanguages - 1)
                printf("%c",COMMA);
            else
                printf(":\n");
        }
    }
    else if(caller==TWO){
        printf("%s:\n",dictionaries[userOption - 1].languages[0]);
    }

    return userOption;
}

/******************
* Function Name:Search
* Input:Dictionary *dictionaries, int *pNumOfDicts, scans a string from the user
* Output:no if there is a word in dictionary will print the users search
* Function Operation:the user will input what dictionary and which word he wants to search
* and if the function finds it , will print its translations.
******************/
void Search(Dictionary *dictionaries, int *pNumOfDicts){
    char *memoryTmp;
    char word;
    int flag=0,caller=TWO,counterLetters=0;
    //user's option of the dictionary he wants to search in
    int option= Printer(dictionaries, pNumOfDicts, caller);
    scanf(" %c",&word);
    //gives to pWord location to memory in the heap
    char *pWord = (char *) malloc(sizeof (char));
    if(pWord==NULL){
        printf("The Search has failed successfully!\n");
        return;

    /**
     * scans user's word to search in a loop and reallocate the memory for every character.
     * **/
    }
    while(word != '\n'){
        pWord[counterLetters]=word;
        counterLetters++;
        //in case the reallocation has failed we want to save the memory it had to free it.
        memoryTmp = pWord;
        //increases the memory for the pWord pointer in the heap.
        pWord = (char *)realloc(pWord,sizeof (char)*(1+counterLetters));
        if(pWord == NULL){
            free(memoryTmp);
            printf("The Search has failed successfully!\n");
            return;
        }
        scanf("%c",&word);
    }
    pWord[counterLetters] = '\0';
    Word *searchWord;
    //we put in a temporary variable at the start of the linked list.
    searchWord = dictionaries[option-1].wordList ;
    //searches until the last word.
    while(searchWord != NULL){
        if((strcmp(pWord,searchWord->translations[0])==0)){

            /**
             * the word has been found in the dictionary and will print all its translations
             * **/
            printf("The translations are:\n");
            for (int i = 1; i < dictionaries[option-1].numOfLanguages; i++) {
                printf("%s: ",dictionaries[option-1].languages[i]);
                if(i<dictionaries[option-1].numOfLanguages-1)
                    printf("%s%c ",searchWord->translations[i],COMMA);
                else
                    printf("%s\n",searchWord->translations[i]);
            }
            flag =1;
            break;
        }
        else{
            //goes to next word in the linked list
            searchWord = searchWord->next;
        }
    }
    if(flag==0)
        printf("There are no translations for \"%s\" in this dictionary.\n",pWord);
    //frees the pWord , we don't need it anymore for this time.
    free(pWord);
}

/******************
* Function Name:deleteWord
* Input:Dictionary *dictionaries, int *pNumOfDicts, and a word from the user
* Output:returns the dictionary after or without the deletion of the word
* Function Operation:the function will scan from the user a word that he wants to delete from
* the dictionary he chose, if the function finds it , will delete it and rearrange the linked
* list of the translations.
******************/
Dictionary *deleteWord(Dictionary *dictionaries, int *pNumOfDicts){
    char word;
    char yesNo;
    char *memoryTmp;
    int caller=2,counterLetters=0,flag=0;
    int userOption = Printer(dictionaries, pNumOfDicts, caller);
    scanf(" %c",&word);
    //gives to pWord location to memory in the heap
    char *pWord = (char *) malloc(sizeof (char));
    if(pWord==NULL){
        printf("The deletion of the word has failed!\n");
        return dictionaries;
    }

    /**
     * scans the letters until ENTER. counts the letters and reallocate the memory
     * for every character.
     * **/
    while(word != '\n'){
        pWord[counterLetters]=word;
        counterLetters++;
        //in case the reallocation failed we want to save the memory it had.
        memoryTmp=pWord;
        //increases the memory for the pWord pointer in the heap.
        pWord = (char *)realloc(pWord,sizeof (char)*(1+counterLetters));
        if(pWord == NULL){
            free(memoryTmp);
            printf("The deletion of the word has failed!\n");
            return(dictionaries);
        }
        scanf("%c",&word);
    }
    pWord[counterLetters] = '\0';
    printf("Are you sure? (y/n)\n");
    scanf(" %c",&yesNo);
    if(yesNo == YES){

        /**
         * we make two pointers that start at the head of the wordlist.
         * the while loop goes until it points to null, every circle
         * the tail will point to where the searchWord pointed, and the searchWord will
         * point to next location of the linked list.
         * also every circle it compares the word that the user entered and the first word
         * of the translations.
         * **/
        Word *searchWord = dictionaries[userOption - 1].wordList ;
        Word *tailTmp= searchWord;
        while(searchWord != NULL){
            if((strcmp(pWord,searchWord->translations[0])==0)){

                /**
                 * if the word is found in the dictionary, if its the first word, it will compare the head to the
                 * second word and then will delete the first word, otherwise the next pointer of the tail will point
                 * to next pointer of the search word (for example if we want to delete the third ward we point from
                 * second word the forth word).
                 * **/
                Word *tmp;
                if(searchWord == tailTmp){
                    dictionaries[userOption - 1].wordList = searchWord->next;
                    tmp = tailTmp;
                }
                else{
                    tailTmp->next = searchWord->next;
                    tmp = searchWord;
                }

                for (int i = 0; i < dictionaries[userOption - 1].numOfLanguages; i++) {
                    //frees all the translations
                    free(tmp->translations[i]);
                }
                //free the tmp.translations and tmp.
                free(tmp->translations);
                free(tmp);
                printf("The word has been deleted successfully!\n");
                flag=1;
                break;
            }
            else{
                tailTmp = searchWord;
                searchWord = searchWord->next;
            }
        }
    }
    if(flag==0){
        printf("The deletion of the word has failed!\n");
    }

    free(pWord);
    return dictionaries;
}

/******************
* Function Name:recursionWordErasing
* Input:Word **tmp, int numOfLanguages
* Output:no output
* Function Operation:the function will start from the head of the word linked list
* of the specified dictionary. will go down the ladder by calling it self until its next points to null.
* then it will start erasing the words in LIFO order. everytime it first erases the translations and only then
* the words it self.
******************/
void recursionWordErasing(Word **tmp, int numOfLanguages){

    //when the next is pointing to null it means we got to the last translation. and we can delete the last word
    if((*tmp)->next==NULL){
            for (int i = 0; i < numOfLanguages; i++) {
                //frees all the translations
                free((*tmp)->translations[i]);
            }
            //frees the pointer tmp and tmp.translations
            free((*tmp)->translations);
            free(*tmp);
    }
    else{
        //it's not the last word , so we point to the next word.
        *tmp = (*tmp)->next ;
        //calls it's self
        recursionWordErasing(tmp, numOfLanguages);
    }
}

/******************
* Function Name:langErase
* Input:Dictionary *dictionaries, int userOption
* Output:dictionaries , after the deletion
* Function Operation: frees from the heap the dictionary that the user asked to delete
******************/
Dictionary* langErase(Dictionary *dictionaries, int userOption){
    for (int i = 0; i < dictionaries[userOption - 1].numOfLanguages; i++) {
        //free all the languages
        free(dictionaries[userOption - 1].languages[i]);
    }
    //free the pointer to languages
    free(dictionaries[userOption - 1].languages);
    return dictionaries;
}

/******************
* Function Name:newArrangement
* Input:Dictionary *dictionaries, int *pNumOfDicts, int userOption
* Output:dictionaries or NULL
* Function Operation:the function will arrange the new amount of dictionaries.
* if there is no more dictionaries it frees all the memory that the dictionary struct had in the heap.
******************/
Dictionary* newArrangement(Dictionary *dictionaries, int *pNumOfDicts, int userOption,int *caller){
    Dictionary *memoryTmp;

    /**
     * all the dictionaries from the dictionary we freed are going 1 place back in the order.
     * **/
    for(int i=0 ; i < ((*pNumOfDicts) - userOption); i++){
        dictionaries[i + userOption - 1] = dictionaries[i + userOption];
    }
    //decrease the number of dictionaries
    (*pNumOfDicts) --;

    /**
     * if no dictionaries left return NULL to dictionaries.
     * **/
    if(*pNumOfDicts==0) {
        free(dictionaries);
        return NULL;
    }
    else {
        //in case the reallocation failed we want to save the memory it had.
        memoryTmp=dictionaries;
        //reallocates the memory for the dictionaries in the heap.
        dictionaries = (Dictionary *) realloc(dictionaries, ((*pNumOfDicts)) * (sizeof(Dictionary)));
        if (dictionaries == NULL) {
            dictionaries=memoryTmp;
            printf("The deletion of the dictionary has failed!\n");
            *caller=0;
            return dictionaries;
        }
        return dictionaries;
    }
}

/******************
* Function Name:deleteDic
* Input:Dictionary *dictionaries, int userOption, int *pNumOfDicts
* Output:the updated dictionaries
* Function Operation: the function will delete a dictionary that the user asked to.
* first it will see if there are any translations to erase if yes, it will call
* the recursionWordErasing function, then comes back to call to langErase. after this two steps that the dictionary
* has been deleted we call the newArrangement function that will arrange the functions in new order.
******************/
Dictionary * deleteDic(Dictionary *dictionaries, int userOption, int *pNumOfDicts,int *caller){

    /**
     * if there is translations call the recursionWordErasing to erase the the translations,
     * if there is no translations don't go in.
     * **/
    if(dictionaries[userOption - 1].wordList != NULL){
        //tmp to the head of the linked list of the translations
        Word *tmp = dictionaries[userOption - 1].wordList;
        recursionWordErasing(&tmp, dictionaries[userOption - 1].numOfLanguages);
        dictionaries[userOption - 1].wordList=NULL;
    }
    //calls to delete the languages
    dictionaries= langErase(dictionaries, userOption);
    dictionaries[userOption - 1].languages=NULL;
    //makes new arrange for the dictionaries
    dictionaries= newArrangement(dictionaries, pNumOfDicts, userOption,caller);
    return dictionaries;
}

/******************
* Function Name:deleteFullDic
* Input:Dictionary *dictionaries, int *pNumOfDicts, and userOption from the user
* Output: the updated dictionary
* Function Operation: the function scans what dictionary the user wants to delete by calling the printer
* function asks him to insure that he wants to delete it , if no it prints cancel if yes it calls
* the deleteDic function. after the deleteDic finished it will print the succession and returns
* the updated dictionary
******************/
Dictionary* deleteFullDic(Dictionary *dictionaries, int *pNumOfDicts){
    char yesNo;
    //when we call the printer we want to send him who called him
    int caller = THREE;
    //gets the user's option from the printer function
    int userOption = Printer(dictionaries, pNumOfDicts, caller);
    scanf(" %c",&yesNo);
    if(yesNo == YES){
        //if user pressed 'y' goes to delete the dictionary
        dictionaries= deleteDic(dictionaries, userOption, pNumOfDicts,&caller);
        if(caller==0)
            return dictionaries;
        printf("The dictionary has been deleted successfully!\n");
    }
    else{
        printf("The deletion of the dictionary has been canceled.\n");
    }
    return dictionaries;
}

/******************
* Function Name:memoryToNewDic
* Input:Dictionary *dictionaries, int *pNumOfDicts
* Output: dictionaries
* Function Operation: the function is making new place to memory to the dictionary in the heap.
******************/
Dictionary* memoryToNewDic(Dictionary *dictionaries, int numOfDicts,int *caller){
    Dictionary *memoryTmp=dictionaries;
    //reallocate the dictionary to be bigger in the heap.
    dictionaries = (Dictionary*) realloc(dictionaries,((numOfDicts)+1)*(sizeof (Dictionary)));
    //if there is no place in the heap we don't want to lose the memory of all the dictionaries.
    if(dictionaries==NULL){
        dictionaries=memoryTmp;
        printf("The creation of the dictionary has failed!\n");
        *caller=0;
        return dictionaries;
    }

    /**
     * nullifies the dictionary.
     * **/
    dictionaries[numOfDicts].languages = NULL;
    dictionaries[numOfDicts].numOfLanguages = 0;
    dictionaries[numOfDicts].wordList = NULL;
    return dictionaries;
}

/******************
* Function Name:scanStringFromTheUser
* Input:int *counterComma, and a string from the user
* Output:the string from the user
* Function Operation:the function scans the string from the user gives it memory in the
* heap and counts the amount of letters that it has and it returns it to who called it.
* it also counts the amount of words it has with a pointer (counterComma)
* to see how many words the user put.
******************/
char * scanStringFromTheUser(int *counterComma,int *caller){
    int counterLetters=0;
    char character;
    char *memoryTmp;
    scanf(" %c",&character);
    char *Letters = (char *) malloc(sizeof (char));
    if(Letters == NULL){
        if (*caller==1)
            printf("The addition of the word has failed!\n");
        else
            printf("The creation of the dictionary has failed!\n");
        (*caller)=0;
        return NULL;
    }

    /**
     * we scan the characters from the user until he presses ENTER , we count the amount of
     * commas which tells us about the amount of words. we reallocate the Letters for every character
     * **/
    while (character != '\n'){
        if(character==COMMA)
            (*counterComma)++;
        Letters[counterLetters]=character;
        counterLetters++;
        memoryTmp=Letters;
        Letters = (char *) realloc(Letters, (counterLetters+1)* sizeof (char));
        if(Letters == NULL){
            //we don't have space in the heap. so we free the word.
            free(memoryTmp);
            if(*caller==1)
                printf("The addition of the word has failed!\n");
            else
                printf("The creation of the dictionary has failed!\n");
            (*caller)=0;
            return NULL;
        }
        scanf("%c",&character);
    }
    //we want the last character to be NULL
    Letters[counterLetters] = '\0';
    return Letters;
}

/******************
* Function Name:strDivider
* Input:Dictionary *dictionaries,int userOption,char *Letters
* Output:the pointer to pointer to the string the user input in the scanStringFromUser function
* Function Operation:the function will separate the string to words by looking for comma.
* it will make amount of pointers to pointer as the amount of words the user input.
* every pointer to pointer will point to a specific place in the string .
******************/
void strDivider(char *Letters,int *caller,char **Lines){
    char *token;
    int lineNum=0;
    char *tokenTemp;
    //couldn't make the comma as a DEFINE , already used 1 for ','
    token = strtok(Letters,",");
    while (token != NULL){
        //gives memory in the heap for the amount of letters and +1 to the \0.
        tokenTemp = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if(tokenTemp==NULL){
            if(*caller==1)
                printf("The addition of the word has failed!\n");
            else
                printf("The creation of the dictionary has failed!\n");
            (*caller)=0;
            return ;
        }
        //copies the word to token tmp from token
        strcpy(tokenTemp, token);
        Lines[lineNum] = tokenTemp;
        //goes to next word
        token = strtok(NULL,",");
        lineNum++;
    }
}

/******************
* Function Name:newWord
* Input:Dictionary *dictionaries,int *pNumOfDicts, and the word and its translations
* the user wants to put into a dictionary
* Output:the updated dictionaries
* Function Operation: the function is calling the scanStringFromTheUser and strDivider
* to divide the string with pointers . then it will put the translations in the last place of the
* linked list.
******************/
Dictionary* newWord(Dictionary *dictionaries,int *pNumOfDicts){
    int userOption,caller=1;
    int counterComma=1;
    //gets the user option to the dictionaries we want to add word in.
    userOption= Printer(dictionaries, pNumOfDicts, caller);
    char *Letters = scanStringFromTheUser(&counterComma,&caller);
    //if the allocation failed return from the function
    if(caller==0)
        return dictionaries;
    //we make enough space for as many pointers as languages
    char **Lines = (char**) malloc((dictionaries[userOption - 1].numOfLanguages) * sizeof (char*));
    if(Lines==NULL){
        printf("The addition of the word has failed!\n");
        (caller)=0;
        return dictionaries;
    }
    strDivider(Letters,&caller,Lines);
    if(caller==0){
        free(Letters);
        return dictionaries;
    }
    //we are done with using the Letters, we free them
    free(Letters);
    Word *name = (Word*) malloc(sizeof (Word));
    if (name == NULL){
        printf("The addition of the word has failed!\n");
        return dictionaries;
    }

    /**
     * in the first time the head is null so we put translations in the first place,
     * and points his next pointer to NULL so the next time we will know where it ends.
     * **/
    if(dictionaries[userOption - 1].wordList == NULL){
        dictionaries[userOption - 1].wordList=name;
        name->next=NULL;
    }
    else{

        /**
         * from the second word and so on we will go thru the list of words until we see NULL.
         * we will put there the word and point its next pointer to NULL for next time.
         * **/
        Word *iterations=dictionaries[userOption - 1].wordList;
        while(iterations->next != NULL){
            iterations=iterations->next;
        }
        iterations->next = name;
        name->next=NULL;
    }

    name->translations=Lines;
    printf("The word has been added successfully!\n");
    return dictionaries;
}

/******************
* Function Name:newDictionary
* Input:Dictionary *dictionaries,int *pNumOfDicts
* Output:dictionaries, and the amount of dictionaries
* Function Operation:the function will get the string divided from the functions scanStringFromTheUser
* and strDivider will update the languages and their amount in the current dictionary. and will
* add 1 to the number of dictionaries.
******************/
Dictionary* newDictionary(Dictionary *dictionaries,int *pNumOfDicts){
    int counterComma=1,caller=2;
    int lastPlaceDic = *pNumOfDicts;
    printf("Define a new dictionary:\n");
    dictionaries = memoryToNewDic(dictionaries, lastPlaceDic,&caller);
    //if there was no memory to give we will return
    if(caller==0)
        return dictionaries;
    char *Letters = scanStringFromTheUser(&counterComma,&caller);
    if(caller==0)
        return dictionaries;
    char **Lines = (char**) malloc(counterComma * sizeof (char*));
    if(Lines==NULL){
        printf("The creation of the dictionary has failed!\n");
        (caller)=0;
        return NULL;
    }
    strDivider(Letters,&caller,Lines);
    if(caller==0){
        free(Letters);
        return dictionaries;
    }
    //we are done with using the Letters, we free it
    free(Letters);
    //we point with languages to the same place the Lines is pointing to which is the words.
    dictionaries[*pNumOfDicts].languages = Lines;
    //amount of commas+1 is the amount of words.
    dictionaries[*pNumOfDicts].numOfLanguages = counterComma;
    (*pNumOfDicts)++;
    printf("The dictionary has been created successfully!\n");
    return dictionaries;
}

/******************
* Function Name:deleteEverything
* Input:Dictionary *Dictionaries, int *pNumOfDicts
* Output:dictionaries = NULL
* Function Operation: calls the function deleteDic as many times as the amount of dictionaries
******************/
void deleteEverything(Dictionary *Dictionaries, int *pNumOfDicts){
    int caller=1;
    //call all the dictionaries from the last to first to avoid new arrangement
    for (int i = (*pNumOfDicts); i > 0; i--) {
        //call the deleteDic function to delete a specific dictionary each iteration.
      Dictionaries = deleteDic(Dictionaries, i, pNumOfDicts,&caller);
      if(caller==0)
          break;
    }
}

/******************
* Function Name:main
* Input:userOption
* Output:prints the menu everytime we come to the main.
* Function Operation:the function is printing the menu and goes to the make the
* operation the user asked to.
******************/
int main() {
    Dictionary* dictionaries =  NULL;
    int numOfDictionaries=0;
    int userOption=0;
    int wrongOptionFlag = 0;
    while (userOption >= 0 && userOption < 6){
        if(wrongOptionFlag==0){
            printf("Welcome to the dictionaries manager!\n"
                   "Choose an option:\n"
                   "1. Create a new dictionary.\n"
                   "2. Add a word to a dictionary.\n"
                   "3. Delete a word from a dictionary.\n"
                   "4. Find a word in a dictionary.\n"
                   "5. Delete a dictionary.\n"
                   "6. Exit.\n");
        }
        else
            wrongOptionFlag=0;
        scanf("%d",&userOption);

        /**
         * if there are no dictionaries and the user pressed 2-5 we ask him to try again, or if he pressed
         * a wrong option which is less than 1 or more than 6 , ask him to try again.
         * **/
        if((numOfDictionaries==0 && userOption > 1 && userOption <= 5)||(userOption<1||userOption>6)){
            printf("This option is not available right now, try again:\n");
            userOption=0;
            wrongOptionFlag = 1;
            continue;
        }
        switch (userOption) {
            case 1: dictionaries = newDictionary(dictionaries,&numOfDictionaries);
                    break;
            case 2: dictionaries = newWord(dictionaries,&numOfDictionaries);
                    break;
            case 3: dictionaries = deleteWord(dictionaries, &numOfDictionaries);
                    break;
            case 4: Search(dictionaries, &numOfDictionaries);
                    break;
            case 5: dictionaries = deleteFullDic(dictionaries, &numOfDictionaries);
                    break;
            case 6: deleteEverything(dictionaries, &numOfDictionaries);
                    printf("Bye!\n");
                    break;
            default:userOption=0;
                    printf("Wrong option, try again:\n");
        }
    }
    return 0;
}
