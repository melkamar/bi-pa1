/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 25. listopad 2012, 14:59
 * 
 * Algorithm based on lecture at http://www.cs.ucsb.edu/~suri/cs130b/NewDynProg.pdf
 * My wannabe-explanation: http://goo.gl/XxSIY
 */

#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT "Nespravny vstup.\n"

/*
 * 
 */

int countCost(int *src, int size) {
    int i, j, k, minval=0, thisval=0;
    //int x, y;
    int **minCosts;

    int step = 1;

    minCosts = (int**) malloc((size) * sizeof (*minCosts));
    for (i = 0; i < size; i++)
        minCosts[i] = (int*) malloc((size) * sizeof (**minCosts));

    for (j = 0; j < size; j++)
        for (i = 0; i < size; i++) {
            minCosts[i][j] = -1;
        }

    for (i = 0; i < size; i++)
        minCosts[i][i] = 0;

    /*printf("Beginning! minCosts:\n");
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) {
            printf("%8d ", minCosts[i][j]);
        }
        printf("\n");
    }
    printf("\n"); */

    /*
     * napr. ABCD
     * 
     * Dynamic programming - pocita se "odspodu", urci se nejmensi mozne hodnoty 
     * nejdrive pro sestaveni dvojic, trojic atd. pricemz vypocet probiha 
     * pouze plnenim pole a koukanim se na jiz vypocitane hodnoty. Proto je
     * algoritmus casove nenarocny. Pro ilustraci viz hlavicka.
     * 
     */

    for (step = 1; step < size; step++) {
        for (i = 0; i + step < size; i++) {

            //printf("\nPossibilities: \n");
            for (k = i; k < i + step; k++) {
                thisval = minCosts[i][k] + minCosts[k + 1][i + step] + src[i] * src[i + step + 1] + src[k + 1];
                //printf("    %d (%d + %d + <%d*%d+%d>) \n", thisval, minCosts[i][k], minCosts[k + 1][i + step], src[i], src[i + step + 1], src[k + 1]);

                if (thisval < minval || k == i)
                    minval = thisval;
            }

            minCosts[i][i + step] = minval;



            /*printf("\n--------------------------\n");
            printf("i = %d | step = %d | minCosts:\n", i, step);
            for (y = 0; y < size; y++) {
                for (x = 0; x < size; x++) {
                    printf("%8d ", minCosts[x][y]);
                }
                printf("\n");
            }
            printf("\n");*/

        }
    }

    minval = minCosts[0][size - 1];
    for (i = 0; i < size; i++)
        free(minCosts[i]);
    free(minCosts);

    return minval;
}

int main(int argc, char** argv) {
    int *pole;
    int read = 0, size = 0;
    int multiplier = 1;
    int totalCost;


    ///printf("%d", combination(12,5));
    //return 0;

    printf("Zadejte pocty sroubu pro jednotlive priruby:\n");

    pole = (int*) malloc(multiplier * sizeof (int));
    size = multiplier;
    multiplier *= 2;

    while (scanf("%d", &pole[read++]) == 1) {
        if (pole[read - 1] <= 0) {
            printf(WRONG_INPUT);
            return 0;
        }

        if (read >= size) {
            pole = (int*) realloc(pole, multiplier * sizeof (int));
            size = multiplier;
            multiplier *= 2;
        }
    }
    
    read--;

    if (!feof(stdin) || read <2) {
        printf(WRONG_INPUT);
        return 0;
    }

    pole = (int*) realloc(pole, read * sizeof (int));
    size = read;


    totalCost = countCost(pole, size - 1);

    //totalCost = compress(pole, read, 0, read);

    printf("Cena: %d\n", totalCost);
    
    free(pole);

    return (EXIT_SUCCESS);
}

