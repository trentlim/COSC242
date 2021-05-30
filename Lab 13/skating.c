#include <stdio.h>
#include <stdlib.h>

int main (void){
    double s1, s2, s3, high = 0, score = 0;
    int num, winner = 0;

    while(4 == scanf("%d%lg%lg%lg", &num, &s1, &s2, &s3)){
        if (s1 < s2 && s1 < s3){
            score = (s2+s3)/2;
        } else if (s2 < s1 && s2 < s3){
            score = (s1+s3)/2;
        } else {
            score = (s1+s2)/2;
        }
        if (score > high){
            high = score;
            winner = num;
        }
    }
    printf("%d\n", winner);
    return EXIT_SUCCESS;
}
