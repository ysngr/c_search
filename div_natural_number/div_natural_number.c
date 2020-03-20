/* div_natural_number.c */
#include <stdio.h>
#include <stdlib.h>

int divnum;

int Atoi(char*);
void part(int*, int, int);
int *gencpy(int*, int);


int main(int argc, char *argv[])
{
    int num;

    if( argc != 3 ){
        printf("Invalid arguments.\n\n");
        printf("Usage: %s num divnum\n", argv[0]);
        printf("num, divnum in N\\{0} (num >= divnum).\n");
        printf("divide num into divnum.\n");
        return -1;
    }

    num = Atoi(argv[1]);
    divnum = Atoi(argv[2]);

    if( num < divnum ){
        printf("Invalid argument.\n");
        printf("num >= divnum.\n");
        return -1;
    }

    printf("divide %d into %d.\n", num, divnum);
    part(NULL, 0, num);

    return 0;
}



int Atoi(char *str)
{
    int n;

    if( (n = atoi(str)) <= 0 ){
        printf("Invalid argument.\n");
        printf("n, d > 0.\n");
        exit(EXIT_FAILURE);
    }

    return n;
}


void part(int *parted, int plen, int n)
{
    // num = parted[0] + ... + parted[plen-1] + n

    int i;
    int *next_parted;

    if( plen + 1 == divnum ){
        for( i = 0; i < plen; i++ ){
            printf("%2d + ", parted[i]);
        }
        printf("%2d\n", n);
        return ;
    }

    next_parted = gencpy(parted, plen);

    for ( i = 1; i < n; i++ ){
        next_parted[plen] = i;
        part(next_parted, plen+1, n-i);
    }

    free(next_parted);

    return ;
}


int *gencpy(int *ns, int len)
{
    int i;
    int *cns;

    if( (cns = (int*)malloc(sizeof(int)*(len+1))) == NULL ){
        printf("Memory cannot be secured.\n");
        exit(EXIT_FAILURE);
    }

    for( i = 0; i < len; i++ ){
        cns[i] = ns[i];
    }

    return cns;
}
