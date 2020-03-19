/* fibonacci_problem.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define True 1
#define False 0

int is_square(int);
int is_num_of_fib_prob(int, int);


int main(void)
{
    int p, q;  // x = q / p

    for( q = 1; q < 5000; q++ ){
        for( p = 1; p < q; p++ ){
            if( is_num_of_fib_prob(p, q) ){
                printf("x = %d / %d\n", q, p);
                printf("x^2 + 5 = (%d / %d)^2\n", (int)sqrt(5*p*p+q*q), p);
                printf("x^2 - 5 = (%d / %d)^2\n", (int)sqrt(-5*p*p+q*q), p);
                goto BREAK;
            }
        }
    }
    BREAK:

    return 0;
}


int is_square(int n)
{
    int sqrt_n;

    if( n < 0 ){
        return False;
    }

    sqrt_n = (int)sqrt(n);
    if( sqrt_n * sqrt_n == n ){
        return True;
    }

    return False;
}


int is_num_of_fib_prob(int p, int q)
{
    int sq_p = p * p;
    int sq_q = q * q;

    if( is_square(5*sq_p + sq_q) && is_square(-5*sq_p + sq_q) ){
        return True;
    }

    return False;
}
