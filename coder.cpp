#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <stdio.h>

#include "coder.h"


#define WINDOW_SIZE 1024
#define START_SIZE 200
#define min(a, b) a < b ? a : b


char* decodeLZ77(const struct Node* arr){

    assert(arr);

    int resSize = START_SIZE;

    // res - initial string, that would be uncompressed from arr
    char* res = (char*) calloc(resSize, sizeof(char));
    if ( !res )
        return nullptr;

    // pointer to the last symbol in res
    int pos = 0;

    for ( int i = 0; ; i++ ){
        const Node* currentNode = arr + i;

        int offset = currentNode->position.offset;
        int length = currentNode->position.length;
        char ch = currentNode->next;

        if (offset){
            // if we can not fit length symbols in res string, multiply its size by 2

            void* status = relocateArray((void*) res, &resSize, pos + length, sizeof(char));
            if (!status)
                return nullptr;
            else
                res = (char*) status;

            strncpy(res + pos, res + pos - offset, length);
            pos += length;
        }

        res[pos] = ch;
        pos += 1;
        if (arr[i].next == 0)
            break;
    }

    return res;
}

struct Node* encodeLZ77(const char* str){

    assert(str);

    // moving window in str. Its size equals to WINDOW_SIZE
    const char *window = str;
    struct Node *res = nullptr;

    int pos = 0;
    int resSize = START_SIZE;

    // result array. Will always multiply its size by 2 until '\0' is met in str
    res = (Node*) calloc(resSize, sizeof(Node));

    if( !res )
        return nullptr;

    assert(res != NULL);

    int used = 0;
    struct StringPosition match = {};

    while ( str[pos] ){
        findPrefix(window, str + pos, &match, min(pos, WINDOW_SIZE));
        pos += match.length;

        Node newNode = {};
        newNode.position = match;
        newNode.next = str[pos];

        res[used] = newNode;
        used++;
        // move buffer
        if (pos > WINDOW_SIZE)
            window = str + pos - WINDOW_SIZE + 1;

        // if result array is full, multiply its size by 2

        void* status = relocateArray((void*) res, &resSize, pos, sizeof(Node));

        if (!status)
            return nullptr;
        else
            res = (Node*) status;
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
    char *correctHaystack = (char*) calloc(n + 1, sizeof(char));

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
            free(correctHaystack);
            return;
        }
        // offset counts from backwards, so n - (ptr - correctHay)
        StrPos->offset = n - (ptr - correctHaystack);
        StrPos->length = i;

    }
    free(correctHaystack);
}


void* relocateArray(void* array, int *size, int newSize, int elSize){

    if ( newSize < *size )
        return array;

    *size *= 2;
    void* ptr = realloc(array, *size * elSize);

    if (!ptr)
        free(array);

    return ptr;
}
