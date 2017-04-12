/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 14. říjen 2012, 17:13
 */

#include <stdio.h>
#include <math.h>

// Prestup x -> y
int canTransfer(int xin, int xout, int yin, int yout) 
{
   int ok=1;
   
   
   //printf(">>> xin, xout: %d, %d | yin, yout:%d, %d\n", xin, xout, yin, yout);

   
    if ( (  (xin<yout && fabs(xin-yout)<1440-fabs(xin-yout)) // xin je menší než yout a zároveň nepřesahuje přes půlnoc NEBO
         || (xin>yout && fabs(xin-yout)>1440-fabs(xin-yout)) ) // xin je větší než yout a přesahuje půlnoc
       && fabs(yout-xin) >= 5 ) //printf(">>  5 min ok\n"); // a pokud je vzdálenost víc než pět
        ;
    else 
    {
        //printf(">>  5 min FAIL (%d-%d)\n",yout,xin);
        ok=0;
        return ok;
    }
    
   
   if ( ( (yin<yout && yin<xin && xin<yout) || (yin>yout && (xin>yin || xin<yout)) ) // pokud nemusím kontrolovat 3h nebo jsou splněny
           || (fabs(xin-yin) <= 3*60 || 1440-fabs(xin-yin)<=3*60) )
   

      // printf(">>  3 hod ok\n");
       ;
    else 
    {
        //printf(">>  3 hod FAIL (%d-%d)\n",yin,xin);
        ok=0;
        return ok;
    }

   // if (yout-xin >= 5 && yin-xin <= 3*60) printf(">>  PASS\n"); 
   return ok;
}

int main (int argc, char ** argv)
{
  int ain=0, aout=0;
  int bin=0, bout=0;
  int cin=0, cout=0;
  int inm, inh;
  
  int can1, can2;

  
  // ----- Vlak A -----
  printf("Zadejte cas prijezdu vlaku A:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  ain = inh*60+inm;

  printf("Zadejte cas odjezdu vlaku A:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  aout = inh*60+inm;
  

  
  // ----- Vlak B -----
  printf("Zadejte cas prijezdu vlaku B:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  bin = inh*60+inm;

  printf("Zadejte cas odjezdu vlaku B:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  bout = inh*60+inm;
  
  
  // ----- Vlak C -----
  printf("Zadejte cas prijezdu vlaku C:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  cin = inh*60+inm;

  printf("Zadejte cas odjezdu vlaku C:\n");
  if (scanf("%d:%d", &inh, &inm)!=2 || inh<0 || inh>23 || inm<0 || inm>59)
  {
    printf("Nespravny vstup.\n");
    return (1);
  }

  cout = inh*60+inm;
  
  //printf("A = %d-%d\n", ain, aout);
  //printf("B = %d-%d\n", bin, bout);
  //printf("C = %d-%d\n", cin, cout);

  
  can1 = canTransfer(ain,aout,bin,bout);
  can2 = canTransfer(ain,aout,cin,cout);
  
  if (can1 && can2) printf("Z vlaku A lze prestoupit na vlaky B a C.\n"); else
      if (can1) printf("Z vlaku A lze prestoupit na vlak B.\n"); else
          if (can2) printf("Z vlaku A lze prestoupit na vlak C.\n"); else
              printf("Z vlaku A nelze prestupovat.\n");
  
  
  
  can1 = canTransfer(bin,bout,ain,aout);  
  can2 = canTransfer(bin,bout,cin,cout);
  
  if (can1 && can2) printf("Z vlaku B lze prestoupit na vlaky A a C.\n"); else
      if (can1) printf("Z vlaku B lze prestoupit na vlak A.\n"); else
          if (can2) printf("Z vlaku B lze prestoupit na vlak C.\n"); else
              printf("Z vlaku B nelze prestupovat.\n");
  
  
  
  can1 = canTransfer(cin,cout,ain,aout);
  can2 = canTransfer(cin,cout,bin,bout);
  
  if (can1 && can2) printf("Z vlaku C lze prestoupit na vlaky A a B.\n"); else
      if (can1) printf("Z vlaku C lze prestoupit na vlak A.\n"); else
          if (can2) printf("Z vlaku C lze prestoupit na vlak B.\n"); else
              printf("Z vlaku C nelze prestupovat.\n");
  return(0);
}
