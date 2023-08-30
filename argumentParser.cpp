#include <string.h>

#include "argumentParser.h"



int parseArguments (int argc, const char *argv[], struct Options* programOptions)
{

    for (int i = 1; i < argc; i++)
    {
        const char *current_option = argv[i];
        if( i == 1 ){

            if (!strcmp (current_option, "--decode") || !strcmp (current_option, "-d"))
                programOptions->decode = 1;

            else if (!strcmp (current_option, "--encode") || !strcmp (current_option, "-e"))
                programOptions->decode = 0;

            else if(!strcmp (current_option, "--help") || !strcmp(current_option, "-h"))
                programOptions->help = 1;

            else
                return PARSER_RESULTS::UNKNOWN_ARGUMENT;

        }
        else if (!strcmp (current_option, "--decode") || !strcmp (current_option, "-d"))
            programOptions->decode = 1;

        else if (!strcmp (current_option, "--file") || !strcmp (current_option, "-f"))
        {
            if ( i + 1 == argc)
                return PARSER_RESULTS::WRONG_NUMBER_OF_ARGUMENTS;

            programOptions->fileName = (char*) argv[i + 1];
            i++;
        }

        else
        {
            printf ("Unknown argument %s\n", current_option);
            return PARSER_RESULTS::UNKNOWN_ARGUMENT;
        }
    }
    return PARSER_RESULTS::OK;
}


int parserError(int status)
{
    switch (status)
    {

        case PARSER_RESULTS::UNKNOWN_ARGUMENT:
            printf("Unknown argument, leaving\n");
            return PROGRAM_RESULTS::ERROR_WITH_ARGUMENTS;

        case PARSER_RESULTS::WRONG_NUMBER_OF_ARGUMENTS:
            printf("Wrong number of arguments (probably -f flag is set, but file name wasn't passed)\n");
            return PROGRAM_RESULTS::ERROR_WITH_ARGUMENTS;

        default:
            printf("Something terrible happened");
            return -1;
    }
    return PROGRAM_RESULTS::ERROR_WITH_ARGUMENTS;
}
