# Domácí úloha 3 - Ořezávání úseček  

Úkolem je realizovat funkci, která bude počítat ořezávání úsečky obdélníkem.

V počítačové grafice je potřeba počítat ořezávání grafických útvarů při jejich vykreslování. Typickým příkladem je vykreslování do okna, kde chceme vidět pouze aktuálně zobrazovanou část obrazu. Nejjednodušší variantou je ořezávání úsečky. Úsečka je zadaná dvěma body, tyto body mohou ležet mimo aktuální výřez. Chceme zjistit, zda úsečka bude vykreslovaná a pokud ano, chceme vypočítat krajní body vykreslované části úsečky.

Vaším úkolem je realizovat funkci, která ze zadaných parametrů výřezu (obdélníku) a krajních bodů úsečky vypočte, zda je alespoň část takové úsečky vidět a pokud ano, určí krajní body viditelné části úsečky. Požadovaná funkce má rozhraní:

```
int clipLine ( double rx1, double ry1,
               double rx2, double ry2,
               double * ax, double * ay,
               double * bx, double * by );
```

- ```rx1,ry1```
je souřadnice jednoho rohu obdélníku výřezu, kterým má být úsečka ořezána,
- ```rx2,ry2```
je souřadnice druhého (protilehlého) rohu obdélníku výřezu, kterým má být úsečka ořezána (obdélník má strany rovnoběžné s osami x a y),
- ```ax, ay```
jsou vstupně výstupní parametry, které určují jeden koncový bod ořezávané úsečky. Volající hodnotu vyplní souřadnicí koncového bodu, Vaše funkce uloženou souřadnici upraví, pokud potřebuje úsečku ořezat,
- ```bx, by```
jsou vstupně výstupní parametry, které popisují druhý koncový bod úsečky. Parametry se jinak chovají stejně jako parametry ax a ay,
- ```návratová hodnota```
funkce vrátí hodnotu 1 pokud po ořezání alespoň část úsečky zasahuje do ořezávacího obdélníku, hodnotu 0 pokud je celá úsečka mimo ořezávaný obdélník.

Odevzdávejte zdrojový soubor s implementací funkce clipLine. Odevzdávaný soubor musí obsahovat implementaci této funkce, s rozhraním (parametry), které odpovídají předpisu nahoře. Dále ve zdrojovém souboru musí být další Vaše funkce, které z funkce clipLine voláte. V odevzdávaném zdrojovém souboru by naopak neměly být zbytečnosti (pozůstatky vývoje a ladění), vkládání hlavičkových souborů ani funkce main - toto je již obsaženo v testovacím prostředí. Pro usnadnění vývoje a odevzdávání (abyste nemuseli před každým odevzdáním ručně odstraňovat funkci main a vkládání hlaviček) použijte šablonu níže. Všimněte si, že funkce main a vkládání hlavičkových souborů je v bloku podmíněného překladu, tedy jsou testovacím prostředím přeskočeny.

```c++
#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#endif /* __PROGTEST__ */

/* pripadne Vase pomocne funkce */

int clipLine ( double rx1, double ry1,
               double rx2, double ry2,
               double * ax, double * ay,
               double * bx, double * by )
 {
   /* Vase implementace */
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   /* Vase testy */
 }
#endif /* __PROGTEST__ */
```

Vaše funkce je testovaná v omezeném prostředí. Omezena je doba běhu i dostupná paměť. Konkrétní omezení je zřejmé z výpisu testování referenčního řešení. V této jednoduché úloze by se ale ani paměťové ani časové omezení nemělo uplatnit.

### Ukázka použití funkce:

```
int res;
double x1, y1, x2, y2;

x1 = 60.000000;
y1 = 40.000000;
x2 = 70.000000;
y2 = 50.000000;
res = clipLine ( 10.000000, 20.000000, 90.000000, 100.000000, &x1, &y1, &x2, &y2 );
/* res = 1
 * x1  = 60.000000
 * y1  = 40.000000
 * x2  = 70.000000
 * y2  = 50.000000
 */

x1 = 0.000000;
y1 = 50.000000;
x2 = 20.000000;
y2 = 30.000000;
res = clipLine ( 90.000000, 100.000000, 10.000000, 20.000000, &x1, &y1, &x2, &y2 );
/* res = 1
 * x1  = 10.000000
 * y1  = 40.000000
 * x2  = 20.000000
 * y2  = 30.000000
 */

x1 = 0.000000;
y1 = 30.000000;
x2 = 120.000000;
y2 = 150.000000;
res = clipLine ( 10.000000, 20.000000, 90.000000, 100.000000, &x1, &y1, &x2, &y2 );

/* res = 1
 * x1  = 10.000000
 * y1  = 40.000000
 * x2  = 70.000000
 * y2  = 100.000000
 */

x1 = -10.000000;
y1 = -10.000000;
x2 = -20.000000;
y2 = -20.000000;
res = clipLine ( 10.000000, 20.000000, 90.000000, 100.000000, &x1, &y1, &x2, &y2 );
/* res = 0
 * x1  = N/A
 * y1  = N/A
 * x2  = N/A
 * y2  = N/A
 */

x1 = 0.000000;
y1 = 30.000000;
x2 = 20.000000;
y2 = 10.000000;
res = clipLine ( 10.000000, 20.000000, 90.000000, 100.000000, &x1, &y1, &x2, &y2 );
/* res = 1
 * x1  = 10.000000
 * y1  = 20.000000
 * x2  = 10.000000
 * y2  = 20.000000
 */
 ```

### Nápověda:
Při implementaci se Vám bude hodit více pomocných funkcí (např. pro ořezání v ose x a v ose y).

## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	5.5000
Hodnotitel: automat
Program zkompilován

Test 'Zakladni test podle ukazky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Celková doba běhu: 0.000 s (limit: 2.000 s)
Využití paměti: 12536 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Extenzivni test (vsechny vzajemne polohy)': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Celková doba běhu: 0.005 s (limit: 2.000 s)
Využití paměti: 12536 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Celkové hodnocení: 100.00 % (= 1.00 * 1.00)
Použité nápovědy: 2
Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
Celkové procentní hodnocení: 100.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50
```