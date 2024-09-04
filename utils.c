#include "utils.h"

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
