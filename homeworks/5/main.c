/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 10. listopad 2012, 15:48
 */

#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT "Nespravny vstup.\n"

/*
 * 
 */

int* multiply(int *a, int degA, int *b, int degB) {
    int i, j;
    int stupRes = degA + degB;
    int *res = (int*) malloc((stupRes + 1) * sizeof (*res));

    for (i = 0; i < stupRes + 1; i++)
        res[i] = 0;

    for (i = 0; i < degA + 1; i++) {
        for (j = 0; j < degB + 1; j++) {
            res[i + j] += a[i] * b[j];
        }
    }

    return res;
}

int isZero(int *r, int degR) {
    int res = 1, i;

    for (i = 0; i < degR + 1; i++)
        if (r[i] != 0) {
            res = 0;
            return res;
        }

    return res;
}

void printTerm(int value, int degree, int printPlus) {
    if (value == 0) return;
    
    if (value < 0) printf("-");
    else if (value > 0 && printPlus) printf("+");

    if (abs(value) == 1) {
        if (degree == 0) printf("1");
        else if (degree == 1) printf("x");
        else if (degree > 1) printf("x<sup>%d</sup>", degree);
    } else {
        if (degree == 0 && value != 0) printf("%d", abs(value));
        else if (degree == 1) printf("%dx", abs(value));
        else if (degree > 1) printf("%dx<sup>%d</sup>", abs(value), degree);
    }
}

void printPolynomial(int *r, int degR) {
    int i;

    if (isZero(r, degR)) {
        printf("0\n");
        return;
    }

    for (i = 0; i < degR + 1; i++) {
        printTerm(r[i], degR - i, i != 0);
    }

    printf("\n");
}

int main(int argc, char** argv) {

    int degA, degB, i;
    int *polyA, *polyB, *res;

    //degA=1;
    //degB=1;


    printf("Zadejte stupen polynomu A:\n");
    if (scanf("%d", &degA) != 1 || degA < 0) {
        printf(WRONG_INPUT);
        return 0;
    }


    polyA = (int*) malloc((degA + 1) * sizeof (*polyA));

    printf("Zadejte koeficienty polynomu A:\n");

    for (i = 0; i < degA + 1; i++)
        if (scanf("%d", &polyA[i]) != 1) {
            printf(WRONG_INPUT);
            return 0;
        }


    //    POLYNOM B     

    printf("Zadejte stupen polynomu B:\n");
    if (scanf("%d", &degB) != 1 || degB < 0) {
        printf(WRONG_INPUT);
        return 0;
    }



    polyB = (int*) malloc((degB + 1) * sizeof (*polyB));

    printf("Zadejte koeficienty polynomu B:\n");

    for (i = 0; i < degB + 1; i++)
        if (scanf("%d", &polyB[i]) != 1) {
            printf(WRONG_INPUT);
            return 0;
        }


    /*
    polyA[0]=1;
    polyA[1]=3;
    
    polyB[0]=2;
    polyB[1]=5;
     */

    res = multiply(polyA, degA, polyB, degB);

    printPolynomial(res, degA + degB);


    return (EXIT_SUCCESS);
}

