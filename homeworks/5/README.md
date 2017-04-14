# Domácí úloha 5 - Násobení polynomů  

Úkolem je vytvořit program, který bude násobit polynomy.

Program má na vstupu zadaná dva polynomy. Pro každý polynom je zadán jeho stupeň n (tedy nejvyšší mocnina je xn) a pro každou mocninu x je zadán odpovídající koeficient (celé číslo). Tedy například polynom:

x<sup>3</sup>-x<sup>2</sup>+2x-4

bude zadán jako n=3 a koeficienty budou `1 -1 2 -4`.

Výstupem programu je nalezený součin zadaných polynomů. Výstup navíc bude s dodanými HTML značkami pro exponenty a bude převeden do kompaktního zápisu. Pokud to matematický zápis připouští, program potlačí výpis:

- členů s nulovým koeficientem,
- koeficienty s hodnotami 1 a -1,
- exponent s hodnotou 1.

Pokud vstup není platný (na vstupu jsou nečíselné nebo nesmyslné hodnoty), program tuto situaci detekuje a vypíše chybové hlášení. Formát chybového hlášení je opět uveden v ukázkách níže. Za chybu je považováno, pokud je na vstupu:

- nečíselná hodnota,
- nesmyslná hodnota (záporný stupeň polynomu).

Pokud program detekuje chybu, přestane se dotazovat na další vstupní hodnoty, vypíše chybové hlášení a ukončí se. Chybu je tedy potřeba detekovat okamžitě po načtení hodnoty (neodkládejte kontrolu vstupních údajů až za načtení celého vstupu). Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a výstupy a přečtěte si sekci FAQ, jak využít přesměrování vstupů/výstupů k testování Vašeho programu.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení, viz též poznámky níže) a dále je omezena i velikost dostupné paměti. Testovací prostředí provádí testy, aby zkontrolovalo správnou práci s pamětí, věnujte proto péči alokaci a uvolňování paměti.

## Ukázka práce programu:
```
Zadejte stupen polynomu A:
1
Zadejte koeficienty polynomu A:
1 3
Zadejte stupen polynomu B:
1
Zadejte koeficienty polynomu B:
2 5
2x<sup>2</sup>+11x+15
```
---
```
Zadejte stupen polynomu A:
4
Zadejte koeficienty polynomu A:
1 0 0 2 0
Zadejte stupen polynomu B:
3
Zadejte koeficienty polynomu B:
1 1 1 1
x<sup>7</sup>+x<sup>6</sup>+x<sup>5</sup>+3x<sup>4</sup>+2x<sup>3</sup>+2x<sup>2</sup>+2x
```
---
```
Zadejte stupen polynomu A:
0
Zadejte koeficienty polynomu A:
3
Zadejte stupen polynomu B:
2
Zadejte koeficienty polynomu B:
1 2 3
3x<sup>2</sup>+6x+9
```
---
```
Zadejte stupen polynomu A:
2
Zadejte koeficienty polynomu A:
-1 3 4
Zadejte stupen polynomu B:
1
Zadejte koeficienty polynomu B:
1 -3
-x<sup>3</sup>+6x<sup>2</sup>-5x-12
```
---
```
Zadejte stupen polynomu A:
4
Zadejte koeficienty polynomu A:
1 0 0 2 0
Zadejte stupen polynomu B:
6
Zadejte koeficienty polynomu B:
1 0 1 0 0 0 1
x<sup>10</sup>+x<sup>8</sup>+2x<sup>7</sup>+2x<sup>5</sup>+x<sup>4</sup>+2x
```
---
```
Zadejte stupen polynomu A:
-3
Nespravny vstup.
Zadejte stupen polynomu A:
2
Zadejte koeficienty polynomu A:
1 2 abcd
Nespravny vstup.
```
---

### Poznámky:
- Úloha neomezuje stupeň vstupních polynomů. Statická alokace paměti proto není dobrý nápad.
- Násobení polynomů je časově náročná operace, pokud jsou stupně polynomů vysoké. Standardní testy zkoušejí násobení pro polynomy s rozumným stupněm. V těchto testech projde správně implementovaný základní algoritmus (algoritmus, který používá člověk při násobení polynomů).
- Pro vysoké stupně polynomů je základní algoritmus příliš pomalý. Je proto vhodné jej nahradit algoritmem výkonnějším. Bonusový test zkouší násobení polynomů s velkým stupněm, základní algoritmus takové polynomy nezvládne vynásobit ve vymezeném čase.
- Prvním bonusovým testem projde program, který správně implementuje Karatsuba algoritmus (podrobněji - Wikipedia).
- Pro úspěšné zvládnutí obou bonusových testů testu lze například použít algoritmus založený na diskrétní konvoluci (polynomy je potřeba převést pomocí algoritmu FFT). Návod je například zde. Protože implementace algoritmu FFT je pracnější, je tentokrát bonusový test hodnocen + 50% bodů.


## Hodnocení


```
Stav odevzdání:	Ohodnoceno
Hodnocení:	5.5000
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.037 s
Využití paměti: 11720 KiB (limit: 22340 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.049 s
Využití paměti: 11720 KiB (limit: 22340 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test ošetření nesprávných vstupů': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.006 s (limit: 2.000 s)
Celková doba běhu: 0.033 s
Využití paměti: 11720 KiB (limit: 22340 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.057 s (limit: 2.000 s)
Celková doba běhu: 0.111 s
Využití paměti: 12296 KiB (limit: 22340 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty + test práce s pamětí': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.219 s (limit: 2.000 s)
Celková doba běhu: 0.421 s
Využití paměti: 20916 KiB (limit: 46754 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Bonusový test (vysoký stupeň polynomu)': Program překročil přidělenou maximální dobu běhu
Program násilně ukončen po: 6.004 s (limit: 6.000 s)
Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
Překročení doby běhu [Zpřístupnit nápovědu (32.00 KiB)]

Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
Celkové procentní hodnocení: 100.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50
```