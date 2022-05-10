#include <vector>
#include <iostream>
#include "Parser.hpp"


int main(int args_count, const char *args[]){

    const std::vector<std::string> arguments(args + 1, args + args_count);

        Parser p(arguments);

}