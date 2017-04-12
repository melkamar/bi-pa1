/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 27. ┼Ö├şjen 2012, 9:03
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#endif /* __PROGTEST__ */

/*
 * 
 */

int segIntersect(double a1, double a2, double b1, double b2,
        double r1, double r2, double s1, double s2, double *res1, double *res2) {
    double u1 = b1 - a1;
    double u2 = b2 - a2;
    double v1 = s1 - r1;
    double v2 = s2 - r2;

    double k = -(-a2 * u1 + r2 * u1 + a1 * u2 - r1 * u2) / (-u2 * v1 + u1 * v2);
    double t = -(-a2 * v1 + r2 * v1 + a1 * v2 - r1 * v2) / (-u2 * v1 + u1 * v2);

    //printf("\n  k = %f\n  t=%f\n", k, t);
    //printf("    u1=%f, u2=%f, v1=%f, v2=%f\n", u1, u2, v1, v2);
    //printf("    r1=%f, r2=%f, s1=%f, s2=%f\n\n", r1, r2, s1, s2);
    
    if (k >= 0 && k <= 1 && t >= 0 && t <= 1) { /* Pokud jsou parametry t,k v intervalu
                                                 * <0;1>, průsečík je na úsečkách. 
                                                 * Jinak je mimo ně (ret 0) */
        
        *res1 = r1 + k*v1;
        *res2 = r2 + k*v2;
        return 1;
    } else {
        return 0;
    }
}

int inRect(double rx1, double ry1, double rx2, double ry2, double x, double y) {

    int inside = 1;

    if (rx1 < rx2) {
        if (x < rx1 || x > rx2) inside = 0;
    } else if (x < rx2 || x > rx1) inside = 0;

    if (ry1 > ry2) {
        if (y > ry1 || y < ry2) inside = 0;
    } else if (y > ry2 || y < ry1) inside = 0;

    return inside;
}

int linesSect(double a1, double a2, double b1, double b2, double *res1, double *res2) {
    /* Proházení pořadí proměnných tak, aby a1 bylo vlevo, a1<a2 a b1<b2:
     * |-------------------------|
     *   a1     b1         a2 b2
     * */

    if (a1==b1 && a2==b2)
    {
        *res1=a1;
        *res2=a2;
        return 1;
    } else if (a1 > b1 || (a1==b1 && b2>a2)) {
        double tmp = a1;
        a1 = b1;
        b1 = tmp;

        tmp = a2;
        a2 = b2;
        b2 = tmp;
    } 

    if (a1 > a2) {
        double tmp = a1;
        a1 = a2;
        a2 = tmp;
    }

    if (b1 > b2) {
        double tmp = b1;
        b1 = b2;
        b2 = tmp;
    }

    /* Výpočet rozměrů
     */

    //printf("\nroz1");
    if (a2 < b1) {
        *res1 = 0;
        *res2 = 0;
        return 0;
        // Tvar:
        //      a1-------a2    
        //  |------------------------------------------|
        //

    } else if (a2 >= b1 && a2 <= b2) {
        *res1 = b1;
        *res2 = a2;
        return 1;
        // Tvar:
        //      a1---------------------a2
        //                 b1------------------b2
        
    } else if (a2>b2){
        *res1=b1;
        *res2=b2;
        return 1;
        // Tvar:
        //      a1---------------------a2
        //           b1---------b2
    }
    return 0;
}

int clipLine(double rx1, double ry1,
        double rx2, double ry2,
        double *ax, double *ay,
        double *bx, double *by) {

    int offset = 0;
    double res[4];

    /* Pokud je úsečka vodorovná nebo svislá, a má stejnou y, resp. x
     * souřadnici jako jedna z hran, zkontrolovat průnik.
     */
    if (*ax == *bx)
    {
        double res1, res2;
        if (*ax == rx1 || *ax == rx2)
        {
            if (linesSect(*ay, *by, ry1, ry2, &res1, &res2))
            {
                //printf("\nSection! Res: %f, %f\n", res1, res2);
                *ay = res1;
                *by = res2;
                return 1;
            }
            else {
                //printf("\nNo section!\n"); 
                return 0;
            }
        }
        else; 
            //printf("\nSVISLY, not same coordinate!\n");
    } else if (*ay == *by)
    {
        double res1, res2;
        if (*ay == ry1 || *ay == ry2)
        {
            if (linesSect(*ax, *bx, rx1, rx2, &res1, &res2))
            {
                //printf("\nSection2! Res: %f, %f\n", res1, res2);
                *ax = res1;
                *bx = res2;
                return 1;
            }
            else {
                //printf("\nNo section!\n");
                return 0;
            }
        }
        else; //printf("\nVODOROVNY, not same coordinate!\n");
    }
    
    //printf("hier!");
    /* Úsečka není vodorovná ani svislá, kontrola průsečíků */
    if (inRect(rx1, ry1, rx2, ry2, * ax, *ay)) {
        //printf("A in rect\n");
        res[offset] = *ax;
        res[offset + 1] = *ay;

        //if (*ax != rx1 && *ax !=rx2 && *ay != ry1 && *ay != ry2)
        offset += 2;
    }

    if (inRect(rx1, ry1, rx2, ry2, *bx, *by)) {
         //printf("B in rect\n");

        res[offset] = *bx;
        res[offset + 1] = *by;

        //if (*bx != rx1 && *bx !=rx2 && *by != ry1 && *by != ry2)
        offset += 2;
    }

    if (offset == 4) { // Oba body jsou v obdélníku, nic se neseká, return.
        return 1;
    }


    //printf("    CALL segIntersect rx1=%f, ry1=%f, rx2=%f, ry2=%f\n", rx1, ry1, rx2, ry2);
    if (offset!=2 || res[0]!=rx1)
    if (offset < 4 && segIntersect(*ax, *ay, *bx, *by, rx1, ry1, rx1, ry2, &res[offset], &res[offset + 1])) {
        offset += 2;
    }

    //printf("    CALL segIntersect rx1=%f, ry1=%f, rx2=%f, ry2=%f\n", rx1, ry1, rx2, ry2);
    if (offset!=2 || res[1]!=ry1)
    if (offset < 4 && segIntersect(*ax, *ay, *bx, *by, rx1, ry1, rx2, ry1, &res[offset], &res[offset + 1])) {
        offset += 2;
    }

    ///printf("    CALL segIntersect rx1=%f, ry1=%f, rx2=%f, ry2=%f\n", rx1, ry1, rx2, ry2);
    if (offset!=2 || res[0]!=rx2)
    if (offset < 4 && segIntersect(*ax, *ay, *bx, *by, rx2, ry2, rx2, ry1, &res[offset], &res[offset + 1])) {
        offset += 2;
    }

    //printf("    CALL segIntersect rx1=%f, ry1=%f, rx2=%f, ry2=%f\n", rx1, ry1, rx2, ry2);
    if (offset!=2 || res[1]!=ry2)
    if (offset < 4 && segIntersect(*ax, *ay, *bx, *by, rx2, ry2, rx1, ry2, &res[offset], &res[offset + 1])) {
        offset += 2;
    }

    if (offset == 0) /* Žádný průsečík s žádnou stranou a úsečka není uvnitř, tedy
                      * úsečka není vůbec vidět */
    {
        //printf("fail 2");
        return 0;
    }


    if (offset == 2) { /* Jeden průsečík s obdélníkem a bod v něm určitě neleží
                          * (jinak offset==4), úsečka se tedy obdélníku dotýká
                          * zvenku a vidět je jen bod. */
        res[2] = res[0];
        res[3] = res[1];
    }

    if (res[0] < res[2]) { /* Vypsání výsledků tak, aby x1 < x2 */
        *ax = res[0];
        *ay = res[1];
        *bx = res[2];
        *by = res[3];
    } else {
        *ax = res[2];
        *ay = res[3];
        *bx = res[0];
        *by = res[1];
    }

    return 1;
}

#ifndef __PROGTEST__

int main(int argc, char * argv []) {
    /* #1
    double a1=60;
    double a2=40;
    double b1=70;
    double b2=50;
    
    
    double rx1=10;
    double ry1=20;
    double rx2=90;
    double ry2=100;
     */

    /*
    double a1 = 0;
    double a2 = 50;
    double b1 = 20;
    double b2 = 30;


    double rx1 = 90;
    double ry1 = 100;
    double rx2 = 10;
    double ry2 = 20;
     */

    /*
    double a1 = 0;
    double a2 = 30;
    double b1 = 120;
    double b2 = 150;


    double rx1 = 10;
    double ry1 = 20;
    double rx2 = 90;
    double ry2 = 100;
     */

    /*
    double a1 = -10;
    double a2 = -10;
    double b1 = -20;
    double b2 = -20;


    double rx1 = 10;
    double ry1 = 20;
    double rx2 = 90;
    double ry2 = 100;
     */

    /*
    double a1 = 0;
    double a2 = 30;
    double b1 = 20;
    double b2 = 10;


    double rx1 = 10;
    double ry1 = 20;
    double rx2 = 90;
    double ry2 = 100;
     */

    
    double a1 = 1532.500;
    double a2 = 341;
    double b1 = 3499;
    double b2 = 171.750;


    double rx1 = 877;
    double ry1 = 341;
    double rx2 = 1751;
    double ry2 = -336;
     
    
    
    /*double a1 = 1575;
    double a2 = 320.75;
    double b1 = 2851;
    double b2 = 1061;

    double rx1 = 1575;
    double ry1 = 403;
    double rx2 = 937;
    double ry2 = 74;
     * */
    /*
    double a1 = 12;
    double a2 = 10;
    double b1 = 7.45;
    double b2 = 10;

    double rx1 = 0;
    double ry1 = 0;
    double rx2 = 10;
    double ry2 = 10;
    */
    //12 10 7.45 10 0 0 10 10
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &a1,&a2,&b1,&b2,&rx1,&ry1,&rx2,&ry2);
    
    
    
     
    if (clipLine(rx1, ry1, rx2, ry2, &a1, &a2, &b1, &b2)) {
        printf("\n\nFinal intersects ---------\n");
        printf("x1 = %f\n", a1);
        printf("y1 = %f\n", a2);
        printf("x2 = %f\n", b1);
        printf("y2 = %f\n", b2);
    } else printf("RET 0");

    return 0;
}
#endif /* __PROGTEST__ */
