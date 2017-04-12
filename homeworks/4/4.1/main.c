/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 3. listopad 2012, 10:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WRONG_INPUT "Nespravny vstup.\n"
#define TYPE_OVERFLOW "Vysledek mimo rozsah datoveho typu.\n"

/*
 * 
 */

unsigned int gcd(unsigned int a, unsigned int b) {
    unsigned int tmp;
    
    // Přehození hodnot tak, aby a>b
    if (b > a) {
        b += a;
        a = b - a;
        b -= a;
    }
    
    while (b > 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

unsigned int lcm(unsigned int a, unsigned int b) {
    unsigned int gcd_res = gcd(a, b);

    if (a / gcd_res > (double) UINT_MAX / b) return 0;
    else return a * b / gcd_res;
}

/*
void initArray(unsigned int *p, int length) {
    p = (unsigned int*) malloc(length * sizeof (*p));
}
*/

void printTime(unsigned int minutes) {
    if (minutes % 60 < 10)
        printf("%d:0%d", minutes / 60, minutes % 60);
    else printf("%d:%d", minutes / 60, minutes % 60);
}

int main(int argc, char** argv) {
    //*
    int n = 0, i, hr, min;
    unsigned int *p = NULL;
    unsigned int res;

    printf("Zadejte pocet vlaku:\n");
    
    if (scanf("%d", &n) != 1 || n < 1 || n > 20) {
        printf(WRONG_INPUT);
        return 0;
    }

    
    p = (unsigned int*) malloc(n * sizeof (*p));
    //initArray(&p, n);
    for (i = 0; i < n; i++) {
        printf("Interval vlaku %d:\n", i + 1);
        if (scanf("%d : %d", &hr, &min) != 2 || min < 0 || min > 59 || (hr == 0 && min == 0) || hr < 0){
            printf(WRONG_INPUT);
            return 0;
        }
 
        p[i] = hr * 60 + min;
 
    }


    res = p[0];
    for (i = 1; i < n; i++) {
        res = lcm(res, p[i]);
        if (res == 0) {
            printf(TYPE_OVERFLOW);
            return 0;
        }
    }

    printf("Vsechny vlaky se potkaji za: ");
    printTime(res);

    printf("\nMezitim projede:\n");
    for (i = 0; i < n - 2; i++)
        printf("* vlak %d: %dx,\n", i + 1, res / p[i] - 1);
    if (n > 1) printf("* vlak %d: %dx a\n", n - 1, res / p[n - 2] - 1);
    printf("* vlak %d: %dx.\n", n, res / p[n - 1] - 1);

    return (EXIT_SUCCESS);
}

