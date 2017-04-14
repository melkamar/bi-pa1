# Soutěžní domácí úloha - Křížovka 

Úkolem v soutěžní úloze je navrhnout efektivní program, který dokáže vyřešit zadanou křížovku.

Předpokládáme, že křížovka je zadaná svým tvarem a seznamem slov, která má program dosazovat. Křížovka je obdélníkového tvaru, ohraničená rámečkem. Uvnitř rámečku jsou mezery pro dosazení písmen a hvězdičky v místech, kde nemá být dosazeno nic. Hvězdičky spolu s hranicemi křížovky vyhrazují prostor pro slova. Seznam slov k vyplnění do křížovky následuje za definicí tvaru křížovky. Každé slovo ze seznamu musí být umístěno do nějakého volného prostoru shodné délky. Slovo může být umístěno buď horizontálně (zleva doprava) nebo vertikálně (shora dolů), proto jsou v prvním vzorovém zadání celkem 3 slova. Křížovka je omezena velikostí nejvýše 16 x 16 políček uvnitř rámečku a obsahuje nejvýše 60 slov. Slova dosazovaná do křížovky jsou tvořena malými písmeny anglické abecedy (a až z).

Na standardním vstupu dostane program zadání křížovky, Zadávání slov je ukončeno s koncem std. vstupu (aktivní EOF). Přesný formát vstupu je vidět v ukázkovém běhu dole.

Program analyzuje zadanou křížovku a rozhodne, která ze tří variant nastala:

- na vstupu byla zadaná křížovka tak, že má pouze jedno platné řešení. V tom případě program toto řešení zobrazí.
- Na vstupu byla zadaná křížovka, kterou nelze sestavit (0 řešení). Program zobrazí informaci o neúspěšném pokusu.
- Zadaný vstup lze doplnit do pole křížovky více různými způsoby, neexistuje tedy jednoznačné řešení. V takovém případě program vypočte kolika různými způsoby lze křížovku vyplnit. Různým způsobem vyplnění se rozumí, že obsahy vyplněných křížovek se liší alespoň v jednom písmenu.

Program musí kontrolovat platnost vstupních dat. Pokud jsou na vstupu zadané nesprávné, nesmyslné nebo nekonzistentní hodnoty, program to detekuje, zobrazí chybové hlášení a ukončí se. Formát chybového hlášení je zobrazen v ukázkovém běhu níže. Za chybu je považováno:

- chybějící, nepravidelný nebo neúplný rámeček pole,
- obsah pole odlišný od mezery a hvězdičky,
- pole větší než 16 x 16,
- počet slov větší než 60,
- slova obsahující jiné znaky než písmena malé abecedy,
- nesouhlasí počet slov a okénka v křížovce (např. v křížovce je 5 okének pro slova délky 3, tedy na vstupu musí být právě 5 slov délky 3 písmena).

Program je testován v omezeném prostředí. Je omezen velikostí dostupné paměti a dobou běhu. Oba limity jsou vidět v logu testování vzorového řešení. Obecně, úloha není náročná na paměť. Je však velmi náročná na procesorový čas. Pokud má křížovka více řešení, může být zkoumání všech možností velmi časově náročné. Je potřeba navrhnout efektivní algoritmus, který nebude zbytečně ztrácet čas zbytečným procházením pokusů, které nevedou k cíli.

Úloha je hodnocena v režimu soutěže. To znamená, že je náročnější než standardní úlohy. Vyžaduje kombinaci programátorských a algoritmizačních dovedností. Předpokládá se, že úlohu budou řešit studenti, kteří mají určité znalosti programování, tedy studenti, pro které jsou standardní úlohy nudné. Hodnocení je tvořeno jednak bodovým ziskem garantovaným (úspěch v nesoutěžních testech) a dále bodovým ziskem získaným na základě umístění v soutěži s ostatními studenty (tyto body budou připsané po skončení soutěže).

## Ukázka práce programu:
```
Zadejte krizovku:
+--+
|  |
+--+
ab
a
b
Krizovka ma 1 reseni:
+--+
|ab|
+--+
```
---
```
Zadejte krizovku:
+-----+
|  *  |
|     |
+-----+
a
ababa
bb
cc
ba
bb
ca
cb
Celkem ruznych reseni: 2
```
---
```
Zadejte krizovku:
+-----+
|   * |
|     |
|    *|
|   * |
|  * *|
|  *  |
|     |
+-----+
cdi
zobxzst
tdxic
r
sc
zro
rgfvacd
oikf
df
x
c
r
xvf
ogish
za
sh
fc
hh
h
bfkh
Krizovka ma 1 reseni:
+-----+
|zro*h|
|ogish|
|bfkh*|
|xvf*r|
|za*c*|
|sc*df|
|tdxic|
+-----+
```
---
```
Zadejte krizovku:
+-----+
|  *  |
|  *  |
+-----+
aa
aa
aa
aa
aa
aa
aa
aa
Krizovka ma 1 reseni:
+-----+
|aa*aa|
|aa*aa|
+-----+
```
---
```
Zadejte krizovku:
+-----+
|  *  |
|  *  |
+-----+
ab
ba
aa
aa
aa
aa
aa
aa
Celkem ruznych reseni: 4
```
---
```
Zadejte krizovku:
+------+
|  *   |
|  *   |
+------+
ab
ba
abc
abc
aa
aa
aa
bc
cb
Krizovka nema reseni.
```
---
```
Zadejte krizovku:
+-----+
|  *  |
|  *
Nespravny vstup.
```
---
```
Zadejte krizovku:
+-----+
|  *  |
|  *  |
+-----+
ab
ba
abc
ab
aa
aa
aa
aa
Nespravny vstup.
```
---

- Každé umístěné písmeno zabere v křížovce právě jedno místo. Dvojhlásky (jako například ch) se považují za dvě písmena.
- Soutěžní úloha je dobrovolná, pro zájemce. Její zvládnutí není k absolvování předmětu nutné (i bez jejího vyřešení lze získat známku A). K úloze nejsou poskytované nápovědy v Progtestu a ze strany cvičících bude poskytována pouze velmi omezená podpora.
- Řešení hrubou silou není možné, nebude fungovat. Uvažme křížovku s 15 slovy a předpokládáme řešení hrubou silou s backtrackingem. Je potřeba otestovat všech 15! = 1 307 674 368 000 permutací. Pokud odhadneme jednu permutaci na 1000 strojových cyklů (v praxi to nejspíš bude více) a víme, že program je testován na 2GHz procesoru, bude potřeba 1000 * 1307674368000 / 2000000000 sec = 653837 sec = 7.5 dne. Ale abyste prošli soutěžním testem, musí Váš program za několik sekund otestovat i větší zadání (až 60 slov).
- Při výpočtu máte najít unikátní řešení. Není rozumné ukládat si všechna nalezená řešení a duplikáty pak pracně odstraňovat. To by bylo náročné jak na paměť, tak na čas. Lepší je zařídit, aby program znovu negeneorval řešení, které již dříve zkoušel.


## Hodnocení

```
Stav odevzdání:	Ohodnoceno
Hodnocení:	5.0000
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.043 s
Využití paměti: 11732 KiB (limit: 40895 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.007 s (limit: 2.000 s)
Celková doba běhu: 0.047 s
Využití paměti: 11864 KiB (limit: 40895 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test ošetření nesprávných vstupních dat': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.088 s
Využití paměti: 11732 KiB (limit: 40895 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty (málo řešení)': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.116 s
Využití paměti: 11732 KiB (limit: 40895 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty (mnoho řešení)': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.335 s (limit: 2.000 s)
Celková doba běhu: 1.017 s
Využití paměti: 11864 KiB (limit: 40895 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Soutěžní test (velmi mnoho řešení)':
Program násilně ukončen po: 6.010 s (limit: 6.000 s)
Využití paměti: 11996 KiB (limit: 40895 KiB)
Součet času výpočtu (správné výsledky): 6.939 s
Časové penále (timeout, segfault, ...): 24.000 s
Cyklomatická složitost: 42
Skóre v soutěži: -135.890 pt (= 5000.0 * 0.6000 - 100.0 * ( 6.939 + 24.000 ) - 1.0 * 42.000)
Překročení doby běhu
Překročení doby běhu
Překročení doby běhu
Překročení doby běhu

Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
Celkové skóre v soutěži: -135.890
Celkové procentní hodnocení: 100.00 %
Celkem bodů: 1.00 * 5.00 = 5.00
```