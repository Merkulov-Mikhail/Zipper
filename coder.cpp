#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <stdio.h>

#include "coder.h"


#define WINDOW_SIZE 1024
#define START_SIZE 200
#define min(a, b) a < b ? a : b

// abababababababbababababababa
// abababababababbababababababaabababababababbababababababaabababababababbababababababa



struct Node* encodeLZ77(const char* str){

    assert(str);

    // moving window in str. Its size equals to WINDOW_SIZE
    const char *window = str;
    struct Node *res = nullptr;

    int used = 0;
    int resSize = START_SIZE;

    // result array. Will always multiply its size by 2 until '\0' is met in str
    res = (Node*) realloc(res, resSize * sizeof(Node));
    assert(res != NULL);

    int pos = 0;
    while ( str[pos] ){
        struct StringPosition match;
        findPrefix(window, str + pos, &match, min(pos, WINDOW_SIZE));
        // ABCDEFGHLABCDAABCD
        pos += match.length;

        // move buffer
        if (pos > WINDOW_SIZE){
            if (pos - WINDOW_SIZE < match.length)
                window += pos - WINDOW_SIZE;
            else
                window += match.length;
        }

        Node newNode = {};
        newNode.position = &match;
        newNode.next = str[pos];

        res[used] = newNode;
        printf("NEW NODE\n%d, %d, %d\n", res[used].position->offset, res[used].position->length, res[used].next);
        used++;

        // if result array is full, multiply its size by 2
        if (used == resSize){

            resSize *= 2;
            res = (Node*) realloc(res, resSize * sizeof(Node));
            assert(res != NULL);
        }
        if (str[pos])
            pos++;
    }
    return res;
}


void findPrefix(const char* haystack, const char* needle, StringPosition* StrPos, int n){
    if ( n == 0 ){
        StrPos->length = 0;
        StrPos->offset = 0;
        return;
    }
    // we start with searching for prefix with length of 1
    // max length of prefix is size of the buffer
    // curr - current possible prefix

    char curr[WINDOW_SIZE] = "";
    char *correctHaystack = (char*) malloc(n * sizeof(char));

    // haystack and needle is just a pointer to a position in initial string
    // so not to break anything, it's necessery to limit haystack from above
    // n - is length of the window in the algorithm
    strncpy(correctHaystack, haystack, n);
    for ( int i = 1; needle[i - 1] && (haystack + i != needle); i++ ) {
        // copies first i elements to curr
        // needed to correctly find length of prefix
        strncpy(curr, needle, i);

        char *ptr = strstr(correctHaystack, curr);
        // if there is no prefix in correctHaystack, further prefixes wont be found either
        // so just return
        if (ptr == NULL){
            return;
        }
        // offset counts from backwards, so n - (ptr - correctHay)
        StrPos->offset = n - (ptr - correctHaystack);
        StrPos->length = i;
    }
}
