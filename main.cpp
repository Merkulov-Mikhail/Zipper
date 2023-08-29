#include <stdio.h>
#include <stdlib.h>


#include "coder.h"


int main(int argc, char* argv[]){
    struct Node* result = encodeLZ77("ABCDEFGHLABCDAABCD");
    printf("ABCDEFGHLABCDAABCD\n");
    printf("%s\n", decodeLZ77(result));
    free(result);
}
