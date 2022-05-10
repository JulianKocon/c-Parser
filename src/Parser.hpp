#ifndef TEST_PARSER_HPP
#define TEST_PARSER_HPP

#include <map>
#include <regex>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <functional>

/**
 * @brief   Parses and handles arguments.
 */
class Parser{

private:
    using iter_t = std::vector<std::string>::const_iterator;
private:
    bool input_specified = false;
    bool output_specified = false;
    std::ostream* output = &std::cout;
    std::string input_file;
    std::map<std::string, std::function<void()>> helpers;
    std::map<std::string, std::function<int(iter_t, iter_t, iter_t)>> validators;
    std::map<std::string, std::function<int(iter_t, iter_t)>> handlers;
private:
    void fill_helpers();
    void fill_validators();
    void fill_handlers();

    void sorted(bool by_length = false);
    void reverse_sorted(bool by_length = false);

    auto sortedVec(std::ifstream &stream,bool by_length);

    auto printVec(const std::vector<std::string> &vec);
    auto checkAnagram(std::string string1, std::string string2);
    static auto removeDuplicates(std::vector<std::string>& vec);
    bool checkPalindrome(std::string string1, const std::string &string2);


    auto filename(iter_t it);
    void newlines();
    void digits();
    void numbers();
    void chars();
    void words();
    void by_length(iter_t it);
    auto anagrams(iter_t it, iter_t end);
    void palindromes(iter_t it, iter_t end);
    void input(iter_t it);
    auto output_f(iter_t it);
    void even();
    std::vector<std::string> vec_of_flags = {
            "-f",
            "-n",
            "-d",
            "-dd",
            "-c",
            "-w",
            "-s",
            "-rs",
            "-l",
            "-a",
            "-o",
            "-p",
            "-i",
            "-e",
    };

    bool validate(const std::vector<std::string>& arguments);
    void handle(const std::vector<std::string>& arguments);
public:
    Parser(const std::vector<std::string>& arguments);
    ~Parser();



};
#endif //TEST_PARSER_HPP
