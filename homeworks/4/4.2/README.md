# Domácí úloha 4.2 - Vláčky na nádraží II  

Úloha je rozšířením jednodušší úlohy o počítání setkávání vlaků. Před jejím řešením se nejprve podívejte na zadání jednodušší.

Nejvyšší pan železničář se rozhodl na Smíchovském nádraží vybudovat informační systém, který usnadní cestujícím orientaci v odjezdech vlaků. Připomeňme, že na nádraží je n spojů, každý spoj má vyhrazenou vlastní kolej a každý spoj má pevně daný interval. Na informačních tabulích se pro cestující pro každý vlak objevuje informace o zastávkách, jeho interval (ten se nemění) a zbývající čas do odjezdu dalšího vlaku v tomto směru (ten se samozřejmě v čase mění). Nejvyššího pana železničáře zaujala setkání všech vlaků na nádraží. Chtěl by rozšířit informační systém tak, aby dokázal na základě znalosti intervalu a zbývajícího času do odjezdu jednotlivých spojů vypočítat, za jak dlouho se všechny vlaky setkají. To je úkolem Vašeho programu.

Vstupem programu je počet vlaků n. Kolejí (a tím i vlaků) je na Smíchovském nádraží nejvýše 20. Pak následuje 2 * n hodnot. Pro každý vlak je zadaný jeho interval a zbývající čas do odjezdu. Interval i zbývající čas do odjezdu je zadán v hodinách a minutách.

Výstupem programu je vypočtená doba, za kterou se všechny vlaky opět na Smíchovském nádraží setkají (budou odjíždět ve stejný čas). Hodnota je zobrazena opět jako hodina:minuta. Pokud pro zadané intervaly a zbývající časy odjezdu k setkání nedojde, program to detekuje a zobrazí. Formát výpisu je zřejmý v ukázkách níže.

Pokud vstup není platný (na vstupu jsou nečíselné nebo nesmyslné hodnoty), program tuto situaci detekuje a vypíše chybové hlášení. Formát chybového hlášení je opět uveden v ukázkách níže. Za chybu je považováno, pokud je na vstupu:

nečíselná hodnota,
nesmyslná hodnota (počet vlaků mimo 1-20, záporná hodina nebo minuta, minuta přes 59),
nulový interval odjezdu vlaku nebo
doba do odjezdu vlaku je větší nebo rovna intervalu spoje.
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

```
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

```
Zadejte pocet vlaku:
1
Interval vlaku 1:
1:23
Pristi odjezd vlaku 1:
0:12
Vsechny vlaky se potkaji za: 0:12
```
---
```
Zadejte pocet vlaku:
1
Interval vlaku 1:
1:23
Pristi odjezd vlaku 1:
0:00
Vsechny vlaky se potkaji za: 0:00
```
---
```
Zadejte pocet vlaku:
2
Interval vlaku 1:
0:12
Pristi odjezd vlaku 1:
0:00
Interval vlaku 2:
0:45
Pristi odjezd vlaku 2:
0:15
Vsechny vlaky se potkaji za: 1:00
```
---
```
Zadejte pocet vlaku:
3
Interval vlaku 1:
0:15
Pristi odjezd vlaku 1:
0:02
Interval vlaku 2:
2:30
Pristi odjezd vlaku 2:
0:47
Interval vlaku 3:
1:20
Pristi odjezd vlaku 3:
1:07
Vsechny vlaky se potkaji za: 15:47
```
---
```
Zadejte pocet vlaku:
3
Interval vlaku 1:
0:15
Pristi odjezd vlaku 1:
0:02
Interval vlaku 2:
2:30
Pristi odjezd vlaku 2:
0:37
Interval vlaku 3:
1:20
Pristi odjezd vlaku 3:
1:07
Vlaky se nikdy nesetkaji.
```
---
```
Zadejte pocet vlaku:
2
Interval vlaku 1:
0:15
Pristi odjezd vlaku 1:
0:02
Interval vlaku 2:
2:30
Pristi odjezd vlaku 2:
3:12
Nespravny vstup.
```
---
```
Zadejte pocet vlaku:
abc
Nespravny vstup.
```
---

### Poznámky:
- Pro reprezentaci časových údajů použijte datový typ long long int. Kompilátor Progtestu používá přepínač -Wno-long-long, tedy použití tohoto datového typu nebude generovat varování.
- Časové údaje je vhodné převést z reprezentace hodina:minuta na reprezentaci v minutách.
- Vstupní data jsou zadávána tak, aby při správné implementaci hodnoty nepřetekly rozsah datového typu long long int. Kontroly rozsahu se tedy v tomto řešení nemusíte zabývat.
- Program umožňuje získání bonusu 20% bodů za časově efektivní řešení. Správně implementovaný naivní algoritmus projde všemi testy kromě testu bonusového. Pro získání bonusu je potřeba použít výkonnější algoritmus (inspirace: Wikipedie - rozšířený Euklidův algoritmus).
- Další inspirací může být večerníček "Pohádky o mašinkách" s postavou nejvyššího pana železničáře.


## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	7.9200
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.037 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.058 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Kontrola ošetření vstupních údajů': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.089 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 3.000 s)
Celková doba běhu: 0.105 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test rychlosti (bonusový)': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.021 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v bonusovém testu, hodnocení: 120.00 %

Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
Použité nápovědy: 2
Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
Celkové procentní hodnocení: 120.00 %
Bonus za včasné odevzdání: 0.60
Celkem bodů: 1.20 * ( 6.00 + 0.60 ) = 7.92
```