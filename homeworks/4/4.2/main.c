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


long long int gcd(long long int a, long long int b) {
    long long int tmp;

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

void printTime(long long int minutes) {
    if (minutes % 60 < 10)
        printf("%lld:0%lld", minutes / 60, minutes % 60);
    else printf("%lld:%lld", minutes / 60, minutes % 60);
}

long long int egcd(long long int ain, long long int bin, long long int *u, long long int *v) {
    long long int a = ain, b = bin;

    long long int x = 0;
    long long int lastx = 1;

    long long int y = 1;
    long long int lasty = 0;

    //printf("\nBEFORE: a=%lld, b=%lld\n", a, b);
    int signa = a / llabs(a);
    int signb = b / llabs(b);
    //printf(" SIGNS: sa=%d, sb=%d\n", signa, signb);

    a = llabs(a);
    b = llabs(b);
    //printf("AFTER: a=%lld, b=%lld\n\n", a, b);

    long long q = 0;

    while (b != 0) {
        q = a / b;

        long long int tmp = a;
        a = b;
        b = tmp % b;

        tmp = x;
        x = lastx - q*x;
        lastx = tmp;

        tmp = y;
        y = lasty - q*y;
        lasty = tmp;
    }

    //printf("\n%lld, %lld\n", lastx, lasty);
    a = ain * lastx * signa + bin * lasty*signb;
    *u = lastx*signa;
    *v = lasty*signb;
    return a;
}

/*
 * a - interval 1. posl.
 * offa - posunutí 1. posl.
 * b - interval 2. posl.
 * offb - posunuti 2. posl.
 * 
 * x - výsledný interval z 1. posl. (nutno mít pro každou soustavu jednu 
 *     "referencni" rovnici (4 rovnice -> řeší se 12, 13, 14. Pak x1x2, x1x3)
 * offx - výsledné posunutí 1. posl.
 */
void solve(long long int ina, long long int inoffa, long long int inb,
        long long int inoffb, long long int *x, long long int *offx) {
    //printf("\nSOLVE> ina=%lld, inoffa=%lld, inb=%lld, inoffb=%lld", ina, inoffa, inb, inoffb);

    long long int a = ina, b = -inb;
    long long int u, v;
    long long int g = egcd(a, b, &u, &v);


    //printf("\nEGCD: g=%lld, u=%lld, v=%lld\n", g, u, v);
    *offx = u * (inoffb - inoffa) / g;

    *x = inb / g;
    //printf("\noffx1: %lld\n", *offx);
    if (*offx <= 0) {
        int mod = *offx % *x;
        *offx = *offx + *x * (llabs(*offx) / *x);
        if (mod != 0) *offx = *offx + *x;
    }
    *offx = *offx % *x;

    //printf("RES: x=%lld, offx=%lld\n", *x, *offx);
}

int canMeet(long long int inarr[20][21][2], int count) {
    int i = 0, j, flag = 1;
    long long int gcd_val;
    long long int mod_val;

    for (i = 0; i < count; i++)
        for (j = i + 1; j < count; j++) {
            gcd_val = gcd(inarr[i][0][0], inarr[j][0][0]); //interval[i], interval[j]);
            mod_val = inarr[i][0][1] % gcd_val; //departure[i] % gcd_val;
            if (inarr[j][0][1] % gcd_val != mod_val) { //departure[j]
                flag = 0;
                break;
            }

            if (!flag) break;
        }

    return flag;
}

int main(int argc, char** argv) {
    //*
    int n = 0, i, j, hr, min, hrint, minint;
    long long int sum, x, xoff;
    long long int array[20][21][2];

    printf("Zadejte pocet vlaku:\n");
    if (scanf("%d", &n) != 1 || n < 1 || n > 20) {
        printf(WRONG_INPUT);
        return 0;
    }


    //array = (long long int**) malloc(n * sizeof (*array));

    //for (i = 0; i < n; i++)
    //    array[i] = (long long int*) malloc(2 * sizeof (**array));


    for (i = 0; i < n; i++) {
        printf("Interval vlaku %d:\n", i + 1);
        if (scanf("%d : %d", &hr, &min) != 2 || min < 0 || min > 59 || (hr == 0 && min == 0) || hr < 0) {
            printf(WRONG_INPUT);
            return 0;
        }

        array[i][0][0] = hr * 60 + min;


        printf("Pristi odjezd vlaku %d:\n", i + 1);
        if (scanf("%d : %d", &hrint, &minint) != 2 || minint < 0 || minint > 59 || hrint < 0 || hrint * 60 + minint >= hr * 60 + min) {
            printf(WRONG_INPUT);
            return 0;
        }

        array[i][0][1] = hrint * 60 + minint;
    }


    if (!canMeet(array, n)) {
        printf("Vlaky se nikdy nesetkaji.\n");
        return 0;
    }

    //printf("VSTUPY::: \n");
    //for (i = 0; i < n; i++) {
    //    printf("0:  %6lld | %6lld \n", array[i][0], array[i][1]);
    //}

    //printf("\nRESENI LVL 1\n");
    for (j = 0; j < n; j++) {
        for (i = 1; i < n - j; i++) {
            //printf("  i=%d ------------------ \n", i);
            //printf("    x=%lld, xoff=%lld\n", x, xoff);
            //printf("    SOLVE(%lld, %lld, %lld, %lld)\n", x, xoff, array[i][0], array[i][1]);
            solve(array[0][j][0], array[0][j][1], array[i][j][0], array[i][j][1], &x, &xoff);
            array[i-1][j + 1][0] = x;
            array[i-1][j + 1][1] = xoff;
            //solve(array[0][0], array[0][1], array[i][0], array[i][1], &x, &xoff);
            //printf("    SOLVE RESULT: %lld, %lld\n\n", x, xoff);


            //array[i][0] = x;
            //array[i][1] = xoff;
        }
    }

    /*
    printf("\nPRVNI VYPIS:\n");
    for (j = 0; j < n; j++){
        for (i = 0; i < n-j; i++)
            printf("%lld | ", array[i][j][0]);
        printf("\n");
    }
    
    printf("\nDRUHY VYPIS:\n");
    for (j = 0; j < n; j++){
        for (i = 0; i < n-j; i++)
            printf("%lld | ", array[i][j][1]);
        printf("\n");
    }
    */

            sum = array[0][n - 1][1];

    for (i = n - 2; i >= 0; i--) {
        sum = sum * array[0][i][0];
        sum += array[0][i][1];
    }

    printf("Vsechny vlaky se potkaji za: ");
    printTime(sum);
    printf("\n");

    return (EXIT_SUCCESS);
}

