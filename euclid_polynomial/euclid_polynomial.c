/* euclid_polynomial.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0


void get_degree(int, char*[], int*, int*);
void invalid_args_exit(void);
int *get_polynomial(char*[], int, int);
void print_polynomial(int*, int);
void euclid_polynomial(int*, int, int*, int);
void div_min_coef(int*, int);
int calc_gcd(int, int);
void multiple_polynomial(int, int*, int);
int update_polynomial(int*, int);



int main(int argc, char *argv[])
{
    int *p, n, *q, m;

    if( argc < 5 ){
        printf("Invalid arguments.\n\n");
        printf("Usage: %s n pn ... p1 p0 m qm ... q1 q0\n", argv[0]);
        printf("n = deg(p(x)) : p(x) = pn*x^n + ... + p1*x + p0\n");
        printf("m = deg(q(x)) : q(x) = qm*x^m + ... + q1*x + q0\n");
        printf("p(x) and q(x) are an polynomial with integer coefficients.\n");
        return -1;
    }

    get_degree(argc, argv, &n, &m);
    p = get_polynomial(argv, 2, n);
    q = get_polynomial(argv, n+4, m);

    // print initial p(x) and q(x)
    printf("p(x) = ");
    print_polynomial(p, n);
    printf("q(x) = ");
    print_polynomial(q, m);

    // solve
    if( n > m ){
        euclid_polynomial(p, n, q, m);
    }else{
        euclid_polynomial(q, m, p, n);
    }

    return 0;
}



void get_degree(int argc, char *argv[], int *n, int *m)
{
    // n <- argv[1] : p(x) <- argv[2..2+n]
    if( (*n = atoi(argv[1])) <= 0 ){
        invalid_args_exit();
    }
    if( argc <= *n+2 + 1 ){
        invalid_args_exit();
    }

    // m <- argv[n+3] : q(x) <- argv[n+4..n+4+m]
    if( (*m = atoi(argv[*n+3])) <= 0 ){
        invalid_args_exit();
    }
    if( argc != *n+*m+4 + 1 ){
        invalid_args_exit();
    }

    return ;
}


void invalid_args_exit(void)
{
    printf("Invalid arguments.\n");
    exit(EXIT_FAILURE);
}


int *get_polynomial(char *argv[], int start, int deg)
{
    int i;
    int *p;

    if( (p = (int*)malloc(sizeof(int)*(deg+1))) == NULL ){
        printf("Memory cannot be secured.\n");
        exit(EXIT_FAILURE);
    }

    for( i = 0; i <= deg; i++ ){
        p[i] = atoi(argv[start+i]);
    }

    return p;
}


void print_polynomial(int *p, int deg)
{
    int i;

    // x^{n}
    if( p[0] < 0 ){
        printf("- ");
    }
    if( abs(p[0]) != 1 ){
        printf("%d", abs(p[0]));
    }
    switch( deg ){
        case 0 :  printf("%d", p[0]);   break;
        case 1 :  printf("x ");         break;
        default : printf("x^%d ", deg); break;
    }

    // x^{n-1} ... x^{0}
    for( i = 1; i <= deg; i++ ){
        if( p[i] == 0 ){
            continue;
        }
        // sign
        if( p[i] >= 0 ){
            printf("+ ");
        }else{
            printf("- ");
        }
        // coefficient
        if( (p[i] != 1 && p[i] != -1) || i == deg ){
            printf("%d", abs(p[i]));
        }
        if( i != deg ){
            if( deg - i == 1 ){
                printf("x ");
            }else{
                printf("x^%d ", deg-i);
            }
        }
    }
    printf("\n");

    return ;
}


void euclid_polynomial(int *p, int deg_p, int *q, int deg_q)
{
    int i;
    int coef_p, coef_q;
    int gcd;

    if( deg_q == -1 ){
        div_min_coef(p, deg_p);
        printf("GCD(p(x), q(x)) = ");
        print_polynomial(p, deg_p);
        return ;
    }

    do{
        // coefficients
        coef_p = p[0];
        coef_q = q[0];
        gcd = calc_gcd(p[0], q[0]);
        multiple_polynomial(coef_q/gcd, p, deg_p);
        multiple_polynomial(coef_p/gcd, q, deg_q);

        // subtract
        for( i = 0; i <= deg_q; i++ ){
            p[i] = p[i] - q[i];
        }
        deg_p = update_polynomial(p, deg_p);
    }while( deg_p >= deg_q && deg_p >= 0 );

    euclid_polynomial(q, deg_q, p, deg_p);

    return ;
}


void div_min_coef(int *p, int deg)
{
    int i;
    int abs_min_coef = INT_MAX;

    for( i = 0; i <= deg; i++ ){
        if( p[i] == 0 ){
            continue;
        }
        if( abs(p[i]) < abs_min_coef ){
            abs_min_coef = abs(p[i]);
        }
    }

    if( p[0] < 0 ){
        abs_min_coef *= -1;
    }

    for( i = 0; i <= deg; i++ ){
        if( p[i] % abs_min_coef != 0 ){
            return ;
        }
    }

    for( i = 0; i <= deg; i++ ){
        p[i] /= abs_min_coef;
    }

    return ;
}


int calc_gcd(int m, int n)
{
    int r;

    if( (r = m % n) == 0 ){
        return n;
    }

    return calc_gcd(n, r);
}


void multiple_polynomial(int n, int *p, int deg)
{
    int i;
    for( i = 0; i <= deg; i++ ){
        p[i] *= n;
    }

    return ;
}


int update_polynomial(int *p, int deg)
{
    int i;
    int maxd;

    // find current maximum degree : p[maxd]
    for( maxd = 0 ; maxd <= deg; maxd++ ){
        if( p[maxd] != 0 ){
            break;
        }
    }

    if( maxd > deg ){  // p(x) = 0
        return -1;
    }

    // shift
    for( i = 0; i <= deg-maxd; i++ ){
        p[i] = p[i+maxd];
    }

    return deg - maxd;
}
