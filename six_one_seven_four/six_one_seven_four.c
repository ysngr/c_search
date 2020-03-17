/* six_one_seven_four.c */
#include <stdio.h>
#include <stdlib.h>

#define DIGIT 4
#define MAX_DEPTH 20

void kaprekar(int[DIGIT], int);
void numtodig(int, int[DIGIT]);
void ascsort(int[DIGIT]);


int main(int argc, char *argv[])
{
    int x;
    int xs[DIGIT];

    if( argc != 2 ){
        printf("Invalid argument.\n");
        printf("Usage: %s num\n", argv[0]);
        printf("num = natural number in (0, 10000)\\{1111, 2222, ... , 9999}\n");
        return -1;
    }

    x = atoi(argv[1]);
    numtodig(x, xs);
    printf("x = %d\n", x);

    kaprekar(xs, 0);

    return 0;
}



void kaprekar(int xs[DIGIT], int depth)
{
    int i;
    int max, min;

    if( depth > MAX_DEPTH ){
        return ;
    }

    min = 0; max = 0;

    ascsort(xs);
    for( i = 0; i < DIGIT; i++ ){
        max = 10 * max + xs[i];
        min = 10 * min + xs[DIGIT-i-1];
    }
    printf("max = %04d, min = %04d, max - min = %d\n", max, min, max-min);

    numtodig(max-min, xs);

    kaprekar(xs, depth+1);

    return ;
}


void numtodig(int num, int digs[DIGIT])
{
    int i;

    for( i = 0; i < DIGIT; i++ ){
        digs[i] = num % 10;
        num /= 10;
    }

    if( num != 0 ){
        printf("Invalid number. Maxdigit = %d\n", DIGIT);
        exit(EXIT_FAILURE);
    }

    return ;
}


void ascsort(int xs[DIGIT])
{
    int i, j;
    int max, idx;
    int temp;

    for( i = 0; i < DIGIT; i++ ){
        max = -1;
        for( j = i; j < DIGIT; j++ ){
            if( max <= xs[j] ){
                max = xs[j];
                idx = j;
            }
        }

        temp = xs[i];
        xs[i] = max;
        xs[idx] = temp;
    }

    return ;
}
