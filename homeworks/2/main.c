/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 20. říjen 2012, 10:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/*
 * 
 */

int invertNumber(unsigned long long int *in) {
    int i = 0;
    unsigned long long int res = 0;
    unsigned long long prev = 0;
    for (i = 0;; i++) {
        prev = res;
        res *= 10;
        res += *in % 10;
        *in /= 10;

        if (prev > res / 10) return 0; // 0 = fail
        if (*in == 0) {
            *in = res;
            return 1; // 1 = ok
        }
    }
}

int sumInverted(unsigned long long int *in) {
    unsigned long long int inv = *in;
    //printf("\n\ninverting %llu\n", *in);
    if (!invertNumber(&inv)) return 0;

    //printf("inverted num: %llu\n", inv);
    if (ULLONG_MAX - *in < inv) return 0;

    *in = *in + inv;
    //printf("invert sum: %llu", *in);
    return 1;
}

int numberLen(unsigned long long int in) {
    int i = 0;
    if (in == 0) return 0;

    for (i = 1;; i++) {
        in /= 10;
        if (in == 0) return i;
    }
}

int isPalindrome(unsigned long long int in) {
    int len = numberLen(in);
    int i = 0;

    int limit=len/2 + len%2;
    //printf("\n<isPalindrome>: len=%d, limit=%d\n",len, limit);
        for (i = 0; i < limit; i++) {
            int a = (in % (unsigned long long int) pow(10, i + 1)) / (unsigned long long int) pow(10, i);
            int b = (in / (unsigned long long int) pow(10, len - i - 1)) % 10;
            //printf("in=%llu, (int)pow=%d\n", in, (unsigned long long int)pow(10,len-i-1));
            //printf("a=%d, b=%d  | i=%d\n", a,b,i);

            if (a != b) return 0;
        }
    
    return 1;
}


int main(int argc, char** argv) {
    unsigned long long int in;
    unsigned long long int sum;

    /*
    if (isPalindrome(89540004598))
    {
        printf("Vypocteny palindrom: %llu (iteraci: 0)\n", in);
        return 0;
    }
    */
    
    printf("Zadejte cislo:\n");
    if (scanf("%llu", &in) != 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }
    
    if (isPalindrome(in))
    {
        printf("Vypocteny palindrom: %llu (iteraci: 0)\n", in);
        return 0;
    }
        
    sum = in;
    
    int i=1;
    while (sumInverted(&sum))
    {
       ///printf("\nIterace: %d\n", i);
        if (isPalindrome(sum))
        {
            printf("Vypocteny palindrom: %llu (iteraci: %d)\n", sum, i);
            return 0;
        }
        i++;
    }
    
    printf("Palindrom nenalezen.\n");
    

    return (EXIT_SUCCESS);
}

