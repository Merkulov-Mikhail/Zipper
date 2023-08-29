#include <stdio.h>


#include "coder.h"


int main(){
    struct Node* result = encodeLZ77("ABCDEFGHLABCDAABCD");
    for ( int i = 0; result[i].next; i++ ){
        printf("%d, %d, %c\n", result[i].position->offset, result[i].position->length, result[i].next);
    }
}
