#include "Parser.hpp"

/**
 * @brief Creates helpers for all flags.
 */
void Parser::fill_helpers()
{
    helpers["-f"] = []{
        std::cout << "\n[ -f filename| --filename filename] Choses a file as a source file.\n";
    };

    helpers["-n"] = []{
        std::cout << "[-n | --filename]  Prints number of lines in file.\n";
    };

    helpers["-d"] = []{
        std::cout << "[-d | --digits]  Prints number of digits from source file.\n";
    };

    helpers["-dd"] = []{
        std::cout << "[-dd | --numbers]  Prints number of numbers from source file.\n";
    };

    helpers["-c"] = []{
        std::cout << "[-c | --chars]  Prints number of chars from source file.\n";
    };

    helpers["-w"] = []{
        std::cout << "[-w | --words]  Prints number of words from source file.\n";
    };

    helpers["-s"] = []{
        std::cout << "[-s | --sorted]  Prints a sorted(alphabetically or by length) vector.\n";
    };

    helpers["-rs"] = []{
        std::cout << "[-rs | --reverse-sorted]  Prints a reverse-sorted(alphabetically or by length) vector.\n";
    };

    helpers["-l"] = []{
        std::cout << "[-l | --by-length]  Changes the both sorting functions to sort by length.\n";
    };

    helpers["-a"] = []{
        std::cout << "[-a | --anagrams]  Prints all anagrams of all given words as a next arguments.\n";
    };

    helpers["-p"] = []{
        std::cout << "[-p | --palindromes]   Check if words given after this flag are palindromes and exist in source file\n";
    };

    helpers["-o"] = []{
        std::cout << "[-o | --output]  Sets the next argument as an output file.\n";
    };

    helpers["-i"] = []{
        std::cout << "[-i filename | --input filename]   Reads flags from file. It should be the only flag\n";
    };

    helpers["-e"] = []{
        std::cout << "[-e | --even]  Checks if there is an even number of words\n";
    };
}
/**
 * @brief Creates a validators to flags. Those validators checks if flags are inputted correctly.
 */
void Parser::fill_validators()
{
    //Checks if input is specified
    auto make_default_validator = [this]() {
        return [this](iter_t, iter_t, iter_t) {
            return input_specified ? 1 : 0;
        };
    };

    validators["-f"] = [this](iter_t it, iter_t begin, iter_t end) {
        if (it + 1 < end)
        {
            input_specified = true;
            return 2;
        }
        helpers["-f"]();
        return 0;
    };
    validators["--file"] = validators["-f"];

    validators["-n"] = make_default_validator();
    validators["--filename"] = make_default_validator();

    validators["-d"] = make_default_validator();
    validators["--digits"] = make_default_validator();

    validators["-dd"] = make_default_validator();
    validators["--numbers"] = make_default_validator();

    validators["-c"] = make_default_validator();
    validators["--chars"] = make_default_validator();

    validators["-w"] = make_default_validator();
    validators["--words"] = make_default_validator();

    validators["-s"] = make_default_validator();
    validators["--sorted"] = make_default_validator();

    validators["-e"] = make_default_validator();
    validators["--even"] = make_default_validator();

    validators["-rs"] = make_default_validator();
    validators["--reverse-sorted"] = make_default_validator();

    validators["-l"] = [this](iter_t it, iter_t begin, iter_t end) {
        if (it + 1 < end && *(it + 1) == "-s" || *(it + 1) == "-rs")
            return 2;
        helpers["-l"]();
        return 0;
    };
    validators["--by-length"] = validators["-l"];

    validators["-a"] = [this](iter_t it, iter_t begin, iter_t end) {
        while(++it != end){
            for(const auto & flag : vec_of_flags){
                if(*it == flag){
                    helpers["-a"]();
                    return 0;
                }
            }

        }
        return static_cast<int>(end-begin);
    };
    validators["--anagrams"] = validators["-a"];

    validators["-o"] = [this](iter_t it, iter_t begin, iter_t end) {
        if (it + 1 < end)
            return 2;
        helpers["-o"]();
        return 0;
    };
    validators["--output"] = validators["-o"];

    validators["-p"] = [this](iter_t it, iter_t begin, iter_t end) {
        while(++it != end){
            for(const auto & flag : vec_of_flags){
               if(*it == flag){
                   helpers["-p"]();
                   return 0;
               }

            }
        }
        return static_cast<int>(end-begin);
    };
    validators["--palindromes"] = validators["-p"];

    validators["-i"] = [this](iter_t it, iter_t begin, iter_t end) {
        if (end - begin == 2)
            return 2;
        helpers["-i"]();
        return 2; // ?
    };
    validators["--input"] = validators["-i"];
}
/**
 * @brief   Sorts all strings from input file, in alphabetical order or (optionally) by length, and passes them to vector.
 * @param   stream  Input stream
 * @param   by_length Bool that checks if function should sort by length.
 * @return Returns a vector of sorted strings.
 */
auto Parser::sortedVec(std::ifstream& stream,bool by_length){
    std::vector<std::string> vec;
    for (auto string = std::string(); stream >> string;) {
        vec.push_back(string);
    }
    if(!by_length){
        std::sort(vec.begin(),vec.end());
    }
    else{
        std::sort(vec.begin(),vec.end(),[](const std::string& left,const std::string& right ){
            return left.length() < right.length();
        });
    }
    return vec;
}
/**
 * @brief   Prints vector of strings.
 * @param   vec Vector of strings.
 */
auto Parser::printVec(const std::vector<std::string>& vec){
    std::cout << "\n";
    for(auto& s : vec){
        std::cout << s << '\n';
    }
    std::cout << '\n';
}
/**
 * @brief Checks if given string1 is an anagram of other string1.
 * @param   string1 String to compare.
 * @param   string2 String to which string1 is comparing.
 * @return  Returns true if a string1 is an anagram of other string1, otherwise false.
 */
auto Parser::checkAnagram(std::string string1, std::string string2){

    if(string1.size() != string2.size() || string1 == string2){
        return false;
    }
    else{
        std::sort(string1.begin(), string1.end());
        std::sort(string2.begin(), string2.end());
        if(string1 == string2){
            return true;
        }
        return false;
    }
}
/**
 * @brief   Removes duplicates from vector of strings.
 * @param   vec    Given vector of strings.
 * @return  Returns vector with erased duplicates.
 */
auto Parser::removeDuplicates(std::vector<std::string>& vec){
    std::sort(vec.begin(),vec.end());
    vec.erase(std::unique(vec.begin(),vec.end()),vec.end());
    return vec;
}
/**
 * @brief Checks if a first string1 is a palindrome of other string1.
 * @param string1   String to compare.
 * @param string2   String to which string1 is comparing.
 * @return Returns true, if string1 is a palindrome of other string1, otherwise false.
 */
bool Parser::checkPalindrome(std::string string1, const std::string& string2){
    if(string1 != string2) return false;
    for(auto i =0; i < string1.length() ; i++){
        if(string1[i] != string1[string1.length() - i - 1]){
            return false;
        }
    }
    return true;
}
/**
 * @brief   Prints the number of lines (from source file).
 */
void Parser::newlines() {

    std::ifstream stream(input_file);

    int counter = 0;
    for (auto line = std::string(); std::getline(stream, line);) {
        counter++;
    }
    (*output) << "\nLines: " << counter;
}
/**
* @brief Sets next arguments as a source file.
* @param    it  Current iterator.
* @return int
*/
 auto Parser::filename(iter_t it){
    if (!input_file.empty())
        return 2;
    input_file = *(it + 1);
    return 2;
 }
/**
* @brief Prints number of digits from source file.
*/
 void Parser::digits() {
     std::ifstream stream(input_file);
     int counter = 0;
     for (auto string = std::string(); stream >> string;) {
         counter += std::count_if(string.begin(),string.end(),[](char x){
             return x >= '0' && x <= '9';
         });
     }
     (*output) << "\nDigits: " << counter;
 }
/**
* @brief Prints number of numbers from source file.
*/
 void Parser::numbers() {
     std::ifstream stream(input_file);
     int counter = 0;
     for (auto string = std::string(); stream >> string;) {

         counter += std::regex_match(string.begin(), string.end(), std::regex("^-?\\d+\\[.]?\\d*$"));//regex from internet
     }
     (*output) << "\nNumbers: " << counter;
 }
/**
* @brief Prints number of chars from source file.
*/
 void Parser::chars() {
     std::ifstream stream(input_file);
     int counter = 0;
     for (auto string = std::string(); stream >> string;) {
         for (char const &c : string){
             counter++;
         }
     }
     (*output) << "\nChars: " << counter;
 }
/**
* @brief Prints number of words from source file.
*/
 void Parser::words() {
     std::ifstream stream(input_file);
     int counter = 0;
     for (auto word = std::string(); stream >> word;) {
         counter++;
     }
     (*output) << "\nWords: " << counter;
 }
/**
* @brief Changes the both sorting functions to sort by length.
* @param it Current iterator.
*/
 void Parser::by_length(iter_t it) {
     if (*(it + 1) == "-s")
         sorted(true);
     else if (*(it + 1) == "-rs")
         reverse_sorted(true);
 }
/**
* @brief Sets the next argument as an output file.
* @param it Current iterator.
* @return Returns int
*/
 auto Parser::output_f(iter_t it) {
     if (output_specified)
         return 2;
     output_specified = true;
     output = new std::ofstream(*(it + 1));
    return 2;
}
/**
* @brief Prints all anagrams of all given words as a next arguments.
* @param it Current iterator.
* @param end Points the end of a vector.
*/
 auto Parser::anagrams(iter_t it, iter_t end) {
     std::ifstream stream(input_file);
     std::vector<std::string> vec;
     std::vector<std::string> anagrams;
     for (auto i = it+1; i < end; i++) {
         vec.push_back(*i);
     }
     for (auto word = std::string(); stream >> word;) {
         for(const auto& v : vec){
             if (checkAnagram(word,v)){
                 anagrams.push_back(word);
             }
         }
     }
     removeDuplicates(anagrams);
     std::cout << "\nAnagrams compared and found: \n";
     printVec(anagrams);

 }
/**
* @brief Prints all palindromes of all given words as a next arguments.
* @param it Current iterator.
* @param end Points the end of a vector.
*/
 void Parser::palindromes(iter_t it, iter_t end) {
     std::ifstream stream(input_file);
     std::vector<std::string> vec;
     std::vector<std::string> palindromes;
     for (auto i = it + 1; i < end; i++) {
         vec.push_back(*i);
     }
     for (auto word = std::string(); stream >> word;) {
         for (const auto &v : vec) {
             if (checkPalindrome(word, v)) {
                 palindromes.push_back(word);
             }
         }
     }
     removeDuplicates(palindromes);
     std::cout << "\nPalindromes compared and found: \n";
     printVec(palindromes);

 }
/**
* @brief Sets the content of the next argument as an arguments. It should be the only flag.
* @param it Current iterator.
*/
 void Parser::input(iter_t it) {
     std::ifstream ifstream(*(it+1));
     std::vector<std::string> args;
     for (auto word = std::string(); ifstream >> word;) {
         args.push_back(word);
     }
     Parser parser(args);
 }
 /**
  * @brief Prints the information about parity of number of words in source file.
  */
void Parser::even() {
    std::ifstream stream(input_file);
    int counter = 0;
    for (auto word = std::string(); stream >> word;) {
        counter++;
    }
    if(counter % 2 == 0){
        std::cout << "\nNumber of words in source file is even";
    }
    else{std::cout << "Number of words in source file is odd";}
}
/**
* @brief Creates handlers for all flags;
*/
void Parser::fill_handlers()
{
    handlers["-e"] = [this](iter_t it, iter_t end){
        even();
        return 1;
    };
    handlers["--even"] = handlers["-e"];
    handlers["-f"] = [this](iter_t it, iter_t end){
       filename(it);
        return 2;
    };
    handlers["--file"] = handlers["-f"];

    handlers["-n"] = [this](iter_t it, iter_t end) {
        newlines();
        return 1;
    };

    handlers["--filename"] = handlers["-n"];

    handlers["-d"] = [this](iter_t it, iter_t end) {
        digits();
        return 1;
    };
    handlers["--digits"] =  handlers["-d"];

    handlers["-dd"] = [this](iter_t it, iter_t end) {
       numbers();
        return 1;
    };
    handlers["--numbers"] =  handlers["-dd"];

    handlers["-c"] = [this](iter_t it, iter_t end) {
      chars();
        return 1;
    };
    handlers["--chars"] =  handlers["-c"];

    handlers["-w"] = [this](iter_t it, iter_t end) {
       words();
        return 1;
    };
    handlers["--words"] = handlers["-w"];

    handlers["-s"] = [this](iter_t it, iter_t end) {
        sorted();
        return 1;
    };
    handlers["--sorted"] = handlers["-s"];

    handlers["-rs"] = [this](iter_t it, iter_t end) {
        reverse_sorted();
        return 1;
    };
    handlers["--reverse-sorted"] = handlers["-rs"];

    handlers["-l"] = [this](iter_t it, iter_t end) {
      by_length(it);
        return 2;
    };
    handlers["--by-length"] = handlers["-l"];

    handlers["-o"] = [this](iter_t it, iter_t end) {
       return output_f(it);
    };
    handlers["--output"] =  handlers["-o"];

    handlers["-a"] = [this](iter_t it, iter_t end) {
        anagrams(it,end);
        return end-it;

    };
    handlers["--anagrams"] =  handlers["-a"];

    handlers["-p"] = [this](iter_t it, iter_t end) {
    palindromes(it,end);
        return end-it;
    };
    handlers["--palindromes"] =  handlers["-p"];

    handlers["-i"] = [this](iter_t it, iter_t end) {
      input(it);
        return 2;
    };
    handlers["--input"] =  handlers["-i"];

}
/**
 * @brief Prints a sorted(alphabetically or by length) vector.
 * @param by_length Bool, true if sorting by length, otherwise false.
 */
void Parser::sorted(bool by_length){
    std::ifstream stream(input_file);
    auto vec = sortedVec(stream,by_length);
    printVec(vec);
}
/**
 * @brief  Prints a reverse-sorted(alphabetically or by length) vector.
 * @param by_length Bool, true if sorting by length, otherwise false.
 */
void Parser::reverse_sorted(bool by_length){
    std::ifstream stream(input_file);
   auto vec = sortedVec(stream,by_length);
   std::reverse(vec.begin(),vec.end());
    printVec(vec);
}
/**
 * @brief   Checks if flags are properly specified.
 * @param   arguments   Vector of all arguments.
 * @return  Returns bool that says if flags are properly specified.
 */
bool Parser::validate(const std::vector<std::string>& arguments)
{
    int result = 0;
    auto begin = arguments.begin();
    auto end = arguments.end();

    if(arguments.empty()){
        std::cout << "This is PJAText2. The purpose of this app is to handle various operations on\n the content of text files saved as ANSI format.";

        return false;

    }

    auto it = std::find_if(begin, end, [](const std::string& str) {
        return str == "-f" || str == "--file";
    });
    if (it != end)
    {
        result = validators[*it](it, begin, end);
        if (!result)
            return false;
    }

    for (it = begin; it < end; )
    {
        auto map_it = validators.find(*it);
        if (map_it == validators.end())
        {
            std::cout << "Unknown option '" << *it << "'\n";
            return false;
        }

        if ((result = validators[*it](it, begin, end)))
            it += result;
        else
            return false;
    }
    return true;
}
/**
 * @brief   Handles all specified flags.
 * @param   arguments   Vector of all arguments.
 */
void Parser::handle(const std::vector<std::string>& arguments)
{
    int result = 0;
    auto begin = arguments.begin();
    auto end = arguments.end();
    auto it = std::find_if(begin, end, [](const std::string& str) {
        return str == "-f" || str == "--file";
    });
    if (it != end)
        handlers[*it](it, end);

    it = std::find_if(begin, end, [](const std::string& str) {
        return str == "-o" || str == "--output";
    });
    if (it != end)
        handlers[*it](it, end);

    for (it = begin; it < end; )
    {
        result = handlers[*it](it, end);
        it += result;
    }

}
Parser::Parser(const std::vector<std::string>& arguments)
{
    fill_helpers();
    fill_validators();
    fill_handlers();

    if (!validate(arguments))
    {
        for(const auto & flag : vec_of_flags){
            helpers[flag]();
        }

    }
    else{
        handle(arguments);
    }
}

Parser::~Parser()
{
    if (output_specified)
        delete output;
}
