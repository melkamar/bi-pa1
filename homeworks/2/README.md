# Domácí úloha 2 - Číselné palindromy

Úkolem je realizovat program, který bude počítat číselné palindromy (čísla, která mají stejný tvar při čtení zleva doprava i zprava doleva).

Předpokládejme nezáporné číslo x. Pokud číslo x není číselný palindrom, vezmeme x a číslo x zapsané pozpátku a tato dvě čísla sečteme. Součet y je s velkou pravděpodobností číselný palindrom. Pokud y číselný palindrom není, opakujeme postup (přičteme k y hodnotu y zapsanou pozpátku), dokud číselný palindrom nezískáme. Příklad pro x = 1498:
```
1498   +   8941 =  10439
10439  +  93401 = 103840
103840 + 048301 = 152141
152141 + 141251 = 293392  (palindrom)
```

Je otevřenou otázkou, zda uvedený postup vede k palindromu pro všechna nezáporná celá čísla. Pro některá čísla (např. 196) se palindrom tímto postupem zatím nepodařilo najít. Úkolem programu je pokusit se najít uvedeným postupem palindrom pro zadané vstupní celé číslo. Pokud se při výpočtu dostanete s hodnotou součtu mimo meze datového typu `unsigned long long int`, výpočet ukončíte s tím, že palindrom se nepodařilo nalézt.

Vstupem programu je nezáporné celé číslo, pro které máte výše uvedeným způsobem najít palindrom.

Výstupem programu je hodnota nalezeného číselného palindromu a počet iterací algoritmu, který k hodnotě vedl. V případě, že se číselný palindrom nepodařilo nalézt (pokud se součet dostane mimo meze datového typu unsigned long long int), zobrazí program oznámení o neúspěchu. Formát výstupu programu je uveden v ukázkách níže. Nezapomeňte na odřádkování za každou (tedy i poslední) řádkou výpisu.

Pokud vstup není platný (na vstupu je nečíselná hodnota), program tuto situaci detekuje a vypíše chybové hlášení. Formát chybového hlášení je opět uveden v ukázkách níže. Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a výstupy a přečtěte si sekci FAQ, jak využít přesměrování vstupů/výstupů k testování Vašeho programu.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít problém). Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

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
Zadejte cislo:
127
Vypocteny palindrom: 848 (iteraci: 1)
```
---
```
Zadejte cislo:
427
Vypocteny palindrom: 2662 (iteraci: 2)
```
---
```
Zadejte cislo:
592
Palindrom nenalezen.
```
---
```
Zadejte cislo:
abc
Nespravny vstup.
```
---
## Nápověda:
Při výpočtu používejte datový typ unsigned long long int.
Kompilátor hlásí při použití tohoto typu varování (nejedná se o standardní datový typ v ANSI/ISO C). Varování můžete potlačit přepínačem -Wno-long-long (kompilátor Progtestu toto varování potlačuje).
Pro načítání a výpis hodnot typu unsigned long long int použijte ve funkcích printf a scanf formát %llu.
Mez datového typu unsigned long long int naleznete v hlavičkovém souboru <limits.h> jako symbolickou konstantu ULLONG_MAX.

## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	5.5000
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.022 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.081 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test ošetření vstupních dat': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.021 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.106 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00)
Použité nápovědy: 2
Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
Celkové procentní hodnocení: 100.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50
```