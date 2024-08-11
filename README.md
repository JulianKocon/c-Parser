# C++ Parser
## Description
A tool designed for performing various operations on the contents of text files saved in ANSI format.

## Running the Program
The application is run from the command line, and based on the provided flags, it produces the appropriate text containing the required information.
For example:
```
-f input.txt -n -c -o output.txt -l -s -dd -d -c -w -p ala ma kota
```
### Description of Flags
-f expects the next argument to be the path to the source file.

-n displays the number of lines in the source file.

-d displays the number of digits in the source file. A digit does not need to be a separate word (i.e., separated by whitespace or the beginning/end of the file).

-dd displays the number of numbers in the source file.

-c displays the number of characters in the source file.

-w displays the number of words in the source file. A word is any sequence of non-whitespace characters. Numbers are also considered words.

-s displays all the words from the input file in alphabetical order.

-rs displays all the words from the input file in reverse alphabetical order.

-l modifies the operation of the following -s or -rs flag to sort by the length of the words rather than alphabetical order.

-a should be the last specified flag, followed by an undefined number of words. The program with this flag displays all words from the source file that are anagrams of the words provided after this flag. The displayed words do not repeat.

-p should be the last specified flag, followed by an undefined number of words. The program with this flag displays all the words provided after the flag that are palindromes and appear in the source file. The displayed words do not repeat.

-o expects the next argument to be a path to a file. Modifies the program’s behavior so that instead of displaying the output on the console, the output is written to the specified file.

-i expects the next argument to be a path to an input file. Modifies the program’s behavior so that instead of specifying the rest of the flags as arguments, the application takes the flags and related data from the mentioned input file. This flag should be the only one provided when running the application (the rest of the flags are found in the input file).

## Author
Julian Kocon

### Creation Date: June 2021
