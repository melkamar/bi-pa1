# Domácí úloha 4.1 - Vláčky na nádraží
Úkolem je realizovat program, který bude počítat potkávání vlaků na nádraží.

Na Smíchovském nádraží je n kolejí. Každá kolej je vyhrazena právě jednomu vlaku (spoji). Každý vlak má daný svůj pevný interval (např. odjíždí každé 2 hodiny), intervaly jsou pro různé vlaky odlišné. Dne 17.9.2012 v 7:30 slavili železničáři svátek - všechny vlaky se na Smíchovském nádraží potkaly ve stejný okamžik. Nejvyšší pan železničář chce vědět, kdy ke stejnému svátku dojde příště. Úkolem Vašeho programu je to vypočítat.

Vstupem programu je počet vlaků n. Kolejí (a tím i vlaků) je na Smíchovském nádraží nejvýše 20. Pak následuje n hodnot intervalů pro každý vlak. Interval je zadán v hodinách a minutách.

Výstupem programu je vypočtená doba, za kterou se všechny vlaky opět na Smíchovském nádraží setkají. Hodnota je zobrazena opět jako hodina:minuta. Následuje pro každý vlak počet odjezdů mezi dvojicí setkání všech vlaků. Formát výstupu je zřejmý z ukázek níže. Nezapomeňte na odřádkování za výpisem. Pozor: všimněte si oddělovačů řádek ve výpisu. Řádky jsou oddělené čárkou, ale poslední řídka je oddělena spojkou 'a'.

Vypočtená doba setkání může být velmi vysoká. Pokud se vypočtená hodnota vyjádřená v minutách nevejde do rozsahu datového typu unsigned int, program to musí po načtení všech vstupů detekovat a místo výsledku oznámit (opět viz ukázka).

Pokud vstup není platný (na vstupu jsou nečíselné nebo nesmyslné hodnoty), program tuto situaci detekuje a vypíše chybové hlášení. Formát chybového hlášení je opět uveden v ukázkách níže. Za chybu je považováno, pokud je na vstupu:

- nečíselná hodnota,
- nesmyslná hodnota (počet vlaků mimo 1-20, záporná hodina nebo minuta, minuta přes 59) nebo
- nulový interval odjezdu vlaku.

Pokud program detekuje chybu, přestane se dotazovat na další vstupní hodnoty, vypíše chybové hlášení a ukončí se. Chybu je tedy potřeba detekovat okamžitě po načtení hodnoty (neodkládejte kontrolu vstupních údajů až za načtení celého vstupu). Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a výstupy a přečtěte si sekci FAQ, jak využít přesměrování vstupů/výstupů k testování Vašeho programu.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení, viz též poznámky níže) a dále je omezena i velikost dostupné paměti (ale tato úloha by s paměťovým omezením neměla mít problém). Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

```c++
int main ( int argc, char * argv [] )
{

  ...

  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
```

Toto nebude v testovacím prostředí fungovat - je zakázáno spouštění jiného programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by totiž nikdo, kdo by pauzu "odmáčkl", program by čekal věčně a překročil by tak maximální dobu běhu.) Pokud tedy chcete zachovat pauzu pro testování na Vašem počítači a zároveň chcete mít jistotu, že program poběží správně, použijte následující trik:

```c++
int main ( int argc, char * argv [] )
{

  ...

#ifndef __PROGTEST__
  system ( "pause" ); /* toto progtest "nevidi" */
#endif /* __PROGTEST__ */
  return 0;
}
```

## Ukázka práce programu:
---
```
Zadejte pocet vlaku:
1
Interval vlaku 1:
1:23
Vsechny vlaky se potkaji za: 1:23
Mezitim projede:
* vlak 1: 0x.
```
---
```
Zadejte pocet vlaku:
2
Interval vlaku 1:
0:12
Interval vlaku 2:
0:45
Vsechny vlaky se potkaji za: 3:00
Mezitim projede:
* vlak 1: 14x a
* vlak 2: 3x.
```
---
```
Zadejte pocet vlaku:
3
Interval vlaku 1:
0:15
Interval vlaku 2:
2:30
Interval vlaku 3:
1:20
Vsechny vlaky se potkaji za: 20:00
Mezitim projede:
* vlak 1: 79x,
* vlak 2: 7x a
* vlak 3: 14x.
```
---
```
Zadejte pocet vlaku:
5
Interval vlaku 1:
1:30
Interval vlaku 2:
2:15
Interval vlaku 3:
3:17
Interval vlaku 4:
0:15
Interval vlaku 5:
0:20
Vsechny vlaky se potkaji za: 1773:00
Mezitim projede:
* vlak 1: 1181x,
* vlak 2: 787x,
* vlak 3: 539x,
* vlak 4: 7091x a
* vlak 5: 5318x.
```
---
```
Zadejte pocet vlaku:
5
Interval vlaku 1:
49:17
Interval vlaku 2:
49:23
Interval vlaku 3:
49:29
Interval vlaku 4:
49:31
Interval vlaku 5:
49:59
Vysledek mimo rozsah datoveho typu.
```
---
```
Zadejte pocet vlaku:
abc
Nespravny vstup.
```
---
```
Zadejte pocet vlaku:
2
Interval vlaku 1:
1:-5
Nespravny vstup.
```
---

## Nápověda
- Pro reprezentaci časových údajů použijte datový typ `unsigned int`.
- Časové údaje je vhodné převést z reprezentace hodina:minuta na reprezentaci v minutách.
- Rozsah datového typu unsigned int je dán hodnotou symbolické konstanty `UINT_MAX` v hlavičkovém souboru `#include <limits.h>`
- Program umožňuje získání bonusu 10% bodů za časově efektivní řešení. Správně implementovaný naivní algoritmus projde všemi testy kromě testu bonusového. Pro získání bonusu je potřeba použít výkonnější algoritmus.


## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	6.0500
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.038 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.033 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Kontrola ošetření vstupních údajů': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.086 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 4.000 s)
Celková doba běhu: 0.107 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test rychlosti (bonusový)': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.021 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v bonusovém testu, hodnocení: 110.00 %

Celkové hodnocení: 110.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.10)
Použité nápovědy: 1
Penalizace za vyčerpané nápovědy: Není (1 <= 2 limit)
Celkové procentní hodnocení: 110.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.10 * ( 5.00 + 0.50 ) = 6.05
```