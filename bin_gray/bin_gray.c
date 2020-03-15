/* bin_gray.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define True 1
#define False 0

struct data{
    double val;
    double min;
    double max;
    int len;
    int *xs;
    int is_gray;
};


struct data* get_args(int, char*[]);
void encode(struct data*);
double decode(struct data*);



int main(int argc, char *argv[])
{
    int i;
    struct data *d;

    d = get_args(argc, argv);

    encode(d);
    printf("Encoded value = ");
    for( i = 0; i < d->len; i++ ){
        printf("%d", d->xs[i]);
    }
    printf("\n");

    printf("Decoded value = %lf\n", decode(d));

    return 0;
}



struct data* get_args(int argc, char *argv[])
{
    struct data *d;

    if( argc == 1 ){
        printf("Usage: %s value min max length option\n", argv[0]);
        printf("value=num in [min, max)\n");
        printf("length=num\n");
        printf("option: gray=1, bin=otherwise\n");
        exit(1);
    }else if( argc != 6 ){
        printf("Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }

    if( (d = (struct data*)malloc(sizeof(struct data))) == NULL ){
        printf("Cannot secure meory.\n");
        exit(EXIT_FAILURE);
    }

    d->val = atof(argv[1]);
    d->min = atof(argv[2]);
    d->max = atof(argv[3]);
    d->len = atoi(argv[4]);
    d->is_gray = ( strcmp(argv[5], "1") == 0 )? True : False;

    if( d->max < d->min ){
        printf("Invalid range.\n");
        exit(EXIT_FAILURE);
    }
    if( d->val < d->min || d->max <= d->val  ){
        printf("Value is not in range.\n");
        exit(EXIT_FAILURE);
    }
    if( (d->xs = (int*)malloc(sizeof(int)*(d->len))) == NULL ){
        printf("Cannot secure memory.\n");
        exit(EXIT_FAILURE);
    }

    printf("value = %lf, range = [%lf, %lf)\ncode length = %d, ", d->val, d->min, d->max, d->len);
    if( d->is_gray ){
        printf("option = gray");
    }else{
        printf("option = bin");
    }
    printf("\n\n");

    return d;
}


void encode(struct data *d)
{
    int i;
    double rem;
    double bitval;  // precision : represented range by this code
    int pxs;  // bin_{i-1}

    rem = d->val - d->min;
    pxs = 0;  // bin_{-1} := 0 (ignored)

    for( i = 0; i < d->len; i++ ){
        // real number -> binary
        bitval = (d->max - d->min) / pow(2, i+1);
        fflush(stdout);
        if( rem >= bitval ){
            d->xs[i] = 1;
            rem -= bitval;
        }else{
            d->xs[i] = 0;
        }

        // binary -> gray
        if( d->is_gray ){
            int temp = d->xs[i];
            d->xs[i] = pxs ^ d->xs[i];  // gray_{i} = bin_{i-1} ^ bin{i}
            pxs = temp;
        }
    }

    return ;
}


double decode(struct data *d)
{
    int i;
    double decval;
    int b;

    b = 0;  // gray_{-1} := 0 (ignored)
    decval = d->min;

    for( i = 0; i < d->len; i++ ){
        if( d->is_gray ){  // gray -> bin
            b = b ^ d->xs[i];  // bin_{i} = (gray_{0} ^ ... ^ gray_{i-1}) ^ gray_{i}
        }else{  // bin
            b = d->xs[i];
        }
        decval += b * (d->max - d->min) / pow(2, i+1);  // bin -> real number
    }

    return decval;
}
