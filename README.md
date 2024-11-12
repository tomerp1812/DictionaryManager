# DictionaryManager

## Description
Dictionary Manager is a dynamic dictionary management system built in C as part of a computer science Introduction course at Bar-Ilan University.
This console-based application allows users to manage multiple dictionaries, facilitating operations like adding, deleting, and searching for words along with their translations.

## Key Features
- **Multiple Dictionaries**: Support for creating and managing multiple dictionaries simultaneously.
- **Dynamic Memory Management**: Utilizes `malloc` and `free` for dynamic memory allocation and deallocation on the heap.
- **Recursive Deletion**: Implements a recursive function to delete words from the dictionaries, ensuring thorough cleanup of memory.
- **Interactive Menus**: User-friendly interactive menus to navigate through different functionalities.

## How It Works
The program offers the following options through an interactive menu:
1. **Create a New Dictionary**: Initialize a new dictionary where you can add words and their translations.
2. **Add a Word**: Add a new word and its translations to an existing dictionary.
3. **Delete a Word**: Remove a word from a dictionary.
4. **Search for a Word**: Look up a word and display its translations across all languages in the dictionary.
5. **Delete a Dictionary**: Completely remove a dictionary and all its contents.
6. **Exit**: Terminate the program.

Each dictionary is structured using a `Dictionary` struct, containing pointers to `Word` structs, forming a linked list where each `Word` node holds translations and a pointer to the next word.

### Example Runs
Below are some images demonstrating typical interactions with the Dictionary Manager. These examples show the creation of dictionaries, addition of words, and other functionalities in action.

<p align="center">
  <img src="https://github.com/tomerp1812/DictionaryManager/assets/110912180/187beb26-c800-46c5-a424-6fb46435875b" alt="Example Run 1" width="30%">
  <img src="https://github.com/tomerp1812/DictionaryManager/assets/110912180/24777eb8-5be1-4671-94a4-b23da6cf4de3" alt="Example Run 2" width="30%">
  <img src="https://github.com/tomerp1812/DictionaryManager/assets/110912180/e2b202a6-9de5-40ae-885c-3835151ac50c" alt="Example Run 3" width="30%">
</p>



## Installation and Compilation
Ensure you have GCC compiler installed on your machine to compile and run the program.



### Cloning and Compiling the Program
Open your terminal in the desired directory then follow those steps:
```bash
git clone https://github.com/tomerp1812/DictionaryManager.git   
```
then move to the directory of the project:
```bash
cd DictionaryManager
```
compile the source file:
```bash
gcc -Wall -o DictionaryManager main.c DictionaryManager.c utils.c
```
run the program with either:
```bash
./DictionaryManager
```
or
```bash
DictionaryManager
```
