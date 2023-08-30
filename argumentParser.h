#include <stdio.h>


int parseArguments (int argc, const char *argv[], struct Options* programOptions);
int parserError(int status);


struct Options {
    bool    decode;
    bool    useFile;
    bool    help;
    char*   fileName;
};


enum PARSER_RESULTS
{
    OK                          = 0,
    WRONG_NUMBER_OF_ARGUMENTS   = 1,
    UNKNOWN_ARGUMENT            = 2
};


enum PROGRAM_RESULTS
{
    INCORRECT_USER_INPUT        = -1,
    TESTS_FAILED                = -2,
    ERROR_WITH_ARGUMENTS        = -3
};
