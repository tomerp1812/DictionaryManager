#include "DictionaryManager.h"

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