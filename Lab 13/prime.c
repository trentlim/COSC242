#include <stdio.h>
#include <stdlib.h>

int is_prime(int c){
    int n = 0;
    for (n = 2; n < c; n++){
        if (c%n == 0){
            return 0;
        }
    }
    return 1;
}

int main (void){
    int c = 2;
    int num_printed = 0;
    while (num_printed < 200){
        if(is_prime(c)){
            printf("%5d",c);
            num_printed++;
            if (num_printed % 10 == 0){
                printf("\n");
            }
        }
        c++;
    }
    return EXIT_SUCCESS;
}
