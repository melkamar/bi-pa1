# Domácí úloha 7 - Větrné elektrárny 

Úkolem je vytvořit program, který bude optimalizovat stavbu větrných elektráren.

Základem větrné elektrárny je nosný tubus. Ten je příliš velký než aby bylo možné jej dopravit v jednom kuse. Proto je potřeba jej na místě sešroubovat z jednotlivých menších segmentů. Předpokládejme, že máme vyrobené jednotlivé segmenty, které mají připravené příruby. Oba konce segmentu jsou opatřeny přírubami, pro každou přírubu znáte počet šroubů, kterými se stahuje. Pořadí segmentů je pevně dané, sousední segmenty mají pochopitelně příruby kompatibilní (pro stejný počet šroubů).

Při montáži lze sestavovat segmenty libovolně. Není potřeba tubus stavět od základu po jednom segmentu v pořadí 1 - 2 - 3 - 4, naopak, na zemi lze sestavit více segmentů do většího celku a ten umístit na rostoucí tubus, máme dost výkonný jeřáb. Tedy lze například sestavit segmenty 1 - 2, pak samostatně 3 - 4 a sestavené 3 - 4 umístit na sestavené 1 - 2. Omezující je cena, kterou montáž stojí. Protože tubus musí být ideálně kolmý, musíme při montáži neustále kontrolovat přesnost sestavení.

Předpokládejme, že máme dvě sousedící části tubusu: spodní A a na ni navazující horní B. A i B mohou být tvořeny buď jedním segmentem nebo více segmenty, které byly již dříve sestavené. Část A má spodní přírubu s např. 20 šrouby a horní přírubu s např. 45 šrouby, část B má spodní přírubu s 45 šrouby (aby šla sestavit s A) a horní přírubu s např. 30 šrouby. Na sestavení částí A a B potřebujeme utáhnout 45 šroubů a zkontrolovat přesnost sestavení. Utažení šroubů stojí 45, kontrola sestavení stojí 20 * 30 (kontrolujeme každý s každým šroubem).

Program dostane na vstupu parametry segmentů, ze kterých sestavujeme tubus. Zadané jsou počty šroubů v jednotlivých přírubách. Pokud má například tubus 3 segmenty A, B a C, kde segment A má spodní přírubu s 20 šrouby, horní s 45 šrouby, segment B spodní s 45 šrouby a horní s 30 šrouby a segment C spodní s 30 a horní s 50 šrouby, budou na vstupu 4 celá čísla 20 45 30 50.

Výstupem programu bude vypočtený nejnižší možná cena za kterou lze celý tubus sestavit.

![struktura tubusu](https://github.com/melkamar/bi-pa1/tree/master/homeworks/7/struct.PNG "Struktura tubusu")

Program musí detekovat nesprávný vstup. Pokud je vstup nesprávný, program to zjistí, vypíše chybové hlášení a ukončí se. Za chybu je považováno:

- na vstupu jsou nečíselné, záporné nebo nulové hodnoty,
- na vstupu není zadaný ani jeden segment (alespoň dvě čísla).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a výstupy a přečtěte si sekci FAQ, jak využít přesměrování vstupů/výstupů k testování Vašeho programu.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu a dále je omezena i velikost dostupné paměti. Paměťový limit by v této úloze neměl být problém. Úloha může být náročná na čas výpočtu. Časový limit je nastaven tak, aby správně implementovaný naivní algoritmus prošel všemi povinnými testy.

## Ukázka práce programu:
```
Zadejte pocty sroubu pro jednotlive priruby:
30 20 25 10
Cena: 545
```
---
```
Zadejte pocty sroubu pro jednotlive priruby:
10 20 25 30
Cena: 595
```
---
```
Zadejte pocty sroubu pro jednotlive priruby:
20 18 17 15 16 20
Cena: 1336
```
---
```
Zadejte pocty sroubu pro jednotlive priruby:
101 150 99 80 100
Cena: 28508
```
---
```
Zadejte pocty sroubu pro jednotlive priruby:
17 5
Cena: 0
```
---
```
Zadejte pocty sroubu pro jednotlive priruby:
4 12 -8
Nespravny vstup.
```

### Poznámky:
- Pro výpočet minima času je potřeba propočítat všechny možnosti, kterými lze tubus sestavit a z nich vybrat minimum. Například pro 4 segmenty lze uvažovat následující možnosti:
 A (B (C D))
 A ((B C) D)
 (A B) (C D)
 (A (B C)) D
 ((A B) C) D
- Pro prozkoumání všech možností se hodí rekurze.
- Výpočet všech možností může být pomalý pro velké počty segmentů. Úloha má exponenciální časovou složitost. Pro větší počty segmentů je základní algoritmus "hrubou silou" nepoužitelný.
- Testovací prostředí je nastaveno tak, aby správně implementovaný základní algoritmus prošel povinnými testy. Pro získání bonusu je potřeba implementovaný algoritmus zlepšit, aby opakovaně nepočítal již dříve vypočtené mezivýsledky. Referenční řešení k tomu využívá techniku dynamického programování.


## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	6.6000
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.033 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 75.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.059 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test ošetření nesprávných vstupů': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.027 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.054 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Bonusový test (rychlost)': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.054 s
Využití paměti: 11720 KiB (limit: 18434 KiB)
Úspěch v bonusovém testu, hodnocení: 120.00 %

Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
Použité nápovědy: 1
Penalizace za vyčerpané nápovědy: Není (1 <= 2 limit)
Celkové procentní hodnocení: 120.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.20 * ( 5.00 + 0.50 ) = 6.60
```