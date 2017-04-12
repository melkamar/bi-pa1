# Domácí úloha 1 - Pøestupy na nádraží

Úkolem je realizovat program, který bude rozhodovat o možnostech pøestupu mezi vlaky na nádraží.

Pøedpokládáme, že na nádraží jezdí za den právì 3 vlaky - vlak A, B a C. Vlaky jezdí dennì, pøijíždìjí a odjíždìjí vždy ve stejný èas. Pro každý vlak známe hodinu a minutu pøíjezdu a odjezdu. Úkolem programu je rozhodnout, mezi kterými vlaky lze pøestoupit. Z vlaku X lze pøestoupit do vlaku Y pokud vlak Y odjíždí alespoò 5 minut po pøíjezdu vlaku X (5 minut je na pøestup). Dále, pøestoupit mùžeme pouze tehdy, pokud od pøíjezdu X do pøíjezdu Y jsou nejvýše 3 hodiny vèetnì. Pokud by vlak Y pøijel pozdìji, zdrželi bychom se na nástupišti déle než 3 hodiny a byli bychom z nádraží vykázáni jako potenciální bezdomovci. Oba limity (5 min, 3h) jsou brané vèetnì, je to i demonstrováno v ukázkách níže.

Vstupem programu je 6 èasových údajù o pøíjezdech a odjezdech vlakù, každý údaj je tvoøen hodinou a minutou. Hodiny a minuty jsou oddìlené dvojteèkou.

Výstupem programu je rozhodnutí, mezi kterými vlaky lze pøestupovat. Odpovìdi jsou postupnì pro vlaky A, B a C, každá na zvláštním øádku. Formát výstupu je zøejmý z ukázek níže. Pokud lze pøestupovat na více vlakù, jsou vlaky, na které lze pøestoupit, uvedeny abecednì:

Z vlaku B lze prestoupit na vlaky A a C.
Naopak, následující odpovìï by byla vyhodnocena jako nesprávná:
Z vlaku B lze prestoupit na vlaky C a A.
Nezapomeòte na odøádkování za každou (tedy i poslední) øádkou výpisu.
Pokud vstup není platný (na vstupu jsou neèíselné nebo nesmyslné hodnoty), program tuto situaci detekuje a vypíše chybové hlášení. Formát chybového hlášení je opìt uveden v ukázkách níže. Za chybu je považováno, pokud je na vstupu:

neèíselná hodnota,
chybìjící oddìlovaè (dvojteèka) nebo
nesmyslná hodnota (hodnota mimo rozsah 0-23, resp. 0-59).
Pokud program detekuje chybu, pøestane se dotazovat na další vstupní hodnoty, vypíše chybové hlášení a ukonèí se. Chybu je tedy potøeba detekovat okamžitì po naètení hodnoty (neodkládejte kontrolu vstupních údajù až za naètení celého vstupu). Chybové hlášení vypisujte na standardní výstup (nevypisujte jej na standardní chybový výstup).

Dodržte pøesnì formát všech výpisù. Výpis Vašeho programu musí pøesnì odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na pøesnou shodu. Pokud se výpis Vašeho programu liší od referenèního výstupu, je Vaše odpovìï považovaná za nesprávnou. Záleží i na mezerách, i na odøádkování. Nezapomeòte na odøádkování za posledním øádkem výstupu (a za pøípadným chybovým hlášením). Využijte pøiložený archiv s testovacími vstupy a výstupy a pøeètìte si sekci FAQ, jak využít pøesmìrování vstupù/výstupù k testování Vašeho programu.

Váš program bude spouštìn v omezeném testovacím prostøedí. Je omezen dobou bìhu (limit je vidìt v logu referenèního øešení) a dále je omezena i velikost dostupné pamìti (ale tato úloha by ani s jedním omezením nemìla mít problém). Testovací prostøedí dále zakazuje používat nìkteré "nebezpeèné funkce" -- funkce pro spouštìní programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

```
int main ( int argc, char * argv [] )
{

  ...
  
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
```

Toto nebude v testovacím prostøedí fungovat - je zakázáno spouštìní jiného programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by totiž nikdo, kdo by pauzu "odmáèkl", program by èekal vìènì a pøekroèil by tak maximální dobu bìhu.) Pokud tedy chcete zachovat pauzu pro testování na Vašem poèítaèi a zároveò chcete mít jistotu, že program pobìží správnì, použijte následující trik:

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
---
```
Zadejte cas prijezdu vlaku A:
12:00
Zadejte cas odjezdu vlaku A:
12:30
Zadejte cas prijezdu vlaku B:
12:10
Zadejte cas odjezdu vlaku B:
12:20
Zadejte cas prijezdu vlaku C:
12:40
Zadejte cas odjezdu vlaku C:
13:00
Z vlaku A lze prestoupit na vlaky B a C.
Z vlaku B lze prestoupit na vlaky A a C.
Z vlaku C nelze prestupovat.
```
---
```
Zadejte cas prijezdu vlaku A:
10:00
Zadejte cas odjezdu vlaku A:
10:10
Zadejte cas prijezdu vlaku B:
10:05
Zadejte cas odjezdu vlaku B:
10:15
Zadejte cas prijezdu vlaku C:
10:06
Zadejte cas odjezdu vlaku C:
10:16
Z vlaku A lze prestoupit na vlaky B a C.
Z vlaku B lze prestoupit na vlaky A a C.
Z vlaku C lze prestoupit na vlak B.
```
---
```
Zadejte cas prijezdu vlaku A:
10:00
Zadejte cas odjezdu vlaku A:
10:30
Zadejte cas prijezdu vlaku B:
13:00
Zadejte cas odjezdu vlaku B:
13:10
Zadejte cas prijezdu vlaku C:
13:01
Zadejte cas odjezdu vlaku C:
14:00
Z vlaku A lze prestoupit na vlak B.
Z vlaku B lze prestoupit na vlak C.
Z vlaku C lze prestoupit na vlak B.
```
---
```
Zadejte cas prijezdu vlaku A:
23:00
Zadejte cas odjezdu vlaku A:
23:30
Zadejte cas prijezdu vlaku B:
23:50
Zadejte cas odjezdu vlaku B:
0:15
Zadejte cas prijezdu vlaku C:
0:10
Zadejte cas odjezdu vlaku C:
0:45
Z vlaku A lze prestoupit na vlaky B a C.
Z vlaku B lze prestoupit na vlak C.
Z vlaku C lze prestoupit na vlak B.
```
---
```
Zadejte cas prijezdu vlaku A:
12:00
Zadejte cas odjezdu vlaku A:
12:65
Nespravny vstup.
Zadejte cas prijezdu vlaku A:
12:00
Zadejte cas odjezdu vlaku A:
12:abc
Nespravny vstup.
```
---
## Hodnocení
```
Stav odevzdání:	Ohodnoceno	 
Hodnocení:	5.5000
Hodnotitel: automat
Program zkompilován

Test 'Základní tst s parametry podle ukázky': Úspìch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba bìhu: 0.006 s (limit: 2.000 s)
Celková doba bìhu: 0.033 s
Využití pamìti: 11720 KiB (limit: 18434 KiB)
Úspìch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspìch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba bìhu: 0.006 s (limit: 2.000 s)
Celková doba bìhu: 0.037 s
Využití pamìti: 11720 KiB (limit: 18434 KiB)
Úspìch v závazném testu, hodnocení: 100.00 %

Test 'Kontrola ošetøení nesprávných vstupù': Úspìch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba bìhu: 0.024 s (limit: 2.000 s)
Celková doba bìhu: 0.092 s
Využití pamìti: 11720 KiB (limit: 18434 KiB)
Úspìch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými hodnotami': Úspìch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba bìhu: 0.006 s (limit: 2.000 s)
Celková doba bìhu: 0.158 s
Využití pamìti: 11720 KiB (limit: 18434 KiB)
Úspìch v závazném testu, hodnocení: 100.00 %

Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00)
Celkové procentní hodnocení: 100.00 %
Bonus za vèasné odevzdání: 0.50
Celkem bodù: 1.00 * ( 5.00 + 0.50 ) = 5.50
```