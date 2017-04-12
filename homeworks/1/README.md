# Dom�c� �loha 1 - P�estupy na n�dra��

�kolem je realizovat program, kter� bude rozhodovat o mo�nostech p�estupu mezi vlaky na n�dra��.

P�edpokl�d�me, �e na n�dra�� jezd� za den pr�v� 3 vlaky - vlak A, B a C. Vlaky jezd� denn�, p�ij�d�j� a odj�d�j� v�dy ve stejn� �as. Pro ka�d� vlak zn�me hodinu a minutu p��jezdu a odjezdu. �kolem programu je rozhodnout, mezi kter�mi vlaky lze p�estoupit. Z vlaku X lze p�estoupit do vlaku Y pokud vlak Y odj�d� alespo� 5 minut po p��jezdu vlaku X (5 minut je na p�estup). D�le, p�estoupit m��eme pouze tehdy, pokud od p��jezdu X do p��jezdu Y jsou nejv��e 3 hodiny v�etn�. Pokud by vlak Y p�ijel pozd�ji, zdr�eli bychom se na n�stupi�ti d�le ne� 3 hodiny a byli bychom z n�dra�� vyk�z�ni jako potenci�ln� bezdomovci. Oba limity (5 min, 3h) jsou bran� v�etn�, je to i demonstrov�no v uk�zk�ch n�e.

Vstupem programu je 6 �asov�ch �daj� o p��jezdech a odjezdech vlak�, ka�d� �daj je tvo�en hodinou a minutou. Hodiny a minuty jsou odd�len� dvojte�kou.

V�stupem programu je rozhodnut�, mezi kter�mi vlaky lze p�estupovat. Odpov�di jsou postupn� pro vlaky A, B a C, ka�d� na zvl�tn�m ��dku. Form�t v�stupu je z�ejm� z uk�zek n�e. Pokud lze p�estupovat na v�ce vlak�, jsou vlaky, na kter� lze p�estoupit, uvedeny abecedn�:

Z vlaku B lze prestoupit na vlaky A a C.
Naopak, n�sleduj�c� odpov�� by byla vyhodnocena jako nespr�vn�:
Z vlaku B lze prestoupit na vlaky C a A.
Nezapome�te na od��dkov�n� za ka�dou (tedy i posledn�) ��dkou v�pisu.
Pokud vstup nen� platn� (na vstupu jsou ne��seln� nebo nesmysln� hodnoty), program tuto situaci detekuje a vyp�e chybov� hl�en�. Form�t chybov�ho hl�en� je op�t uveden v uk�zk�ch n�e. Za chybu je pova�ov�no, pokud je na vstupu:

ne��seln� hodnota,
chyb�j�c� odd�lova� (dvojte�ka) nebo
nesmysln� hodnota (hodnota mimo rozsah 0-23, resp. 0-59).
Pokud program detekuje chybu, p�estane se dotazovat na dal�� vstupn� hodnoty, vyp�e chybov� hl�en� a ukon�� se. Chybu je tedy pot�eba detekovat okam�it� po na�ten� hodnoty (neodkl�dejte kontrolu vstupn�ch �daj� a� za na�ten� cel�ho vstupu). Chybov� hl�en� vypisujte na standardn� v�stup (nevypisujte jej na standardn� chybov� v�stup).

Dodr�te p�esn� form�t v�ech v�pis�. V�pis Va�eho programu mus� p�esn� odpov�dat uk�zk�m. Testov�n� prov�d� stroj, kter� kontroluje v�pis na p�esnou shodu. Pokud se v�pis Va�eho programu li�� od referen�n�ho v�stupu, je Va�e odpov�� pova�ovan� za nespr�vnou. Z�le�� i na mezer�ch, i na od��dkov�n�. Nezapome�te na od��dkov�n� za posledn�m ��dkem v�stupu (a za p��padn�m chybov�m hl�en�m). Vyu�ijte p�ilo�en� archiv s testovac�mi vstupy a v�stupy a p�e�t�te si sekci FAQ, jak vyu��t p�esm�rov�n� vstup�/v�stup� k testov�n� Va�eho programu.

V� program bude spou�t�n v omezen�m testovac�m prost�ed�. Je omezen dobou b�hu (limit je vid�t v logu referen�n�ho �e�en�) a d�le je omezena i velikost dostupn� pam�ti (ale tato �loha by ani s jedn�m omezen�m nem�la m�t probl�m). Testovac� prost�ed� d�le zakazuje pou��vat n�kter� "nebezpe�n� funkce" -- funkce pro spou�t�n� programu, pro pr�ci se s�t�, ... Pokud jsou tyto funkce pou�it�, program se nespust�. Mo�n� ve sv�m programu pou��v�te vol�n�:

```c++
int main ( int argc, char * argv [] )
{

  ...
  
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
```

Toto nebude v testovac�m prost�ed� fungovat - je zak�z�no spou�t�n� jin�ho programu. (I pokud by se program spustil, byl by odm�tnut. Nebyl by toti� nikdo, kdo by pauzu "odm��kl", program by �ekal v��n� a p�ekro�il by tak maxim�ln� dobu b�hu.) Pokud tedy chcete zachovat pauzu pro testov�n� na Va�em po��ta�i a z�rove� chcete m�t jistotu, �e program pob�� spr�vn�, pou�ijte n�sleduj�c� trik:

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
    
## Uk�zka pr�ce programu:
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
## Hodnocen�
```
Stav odevzd�n�:	Ohodnoceno	 
Hodnocen�:	5.5000
Hodnotitel: automat
Program zkompilov�n

Test 'Z�kladn� tst s parametry podle uk�zky': �sp�ch
Dosa�eno: 100.00 %, po�adov�no: 100.00 %
Max doba b�hu: 0.006 s (limit: 2.000 s)
Celkov� doba b�hu: 0.033 s
Vyu�it� pam�ti: 11720 KiB (limit: 18434 KiB)
�sp�ch v z�vazn�m testu, hodnocen�: 100.00 %

Test 'Test mezn�ch hodnot': �sp�ch
Dosa�eno: 100.00 %, po�adov�no: 50.00 %
Max doba b�hu: 0.006 s (limit: 2.000 s)
Celkov� doba b�hu: 0.037 s
Vyu�it� pam�ti: 11720 KiB (limit: 18434 KiB)
�sp�ch v z�vazn�m testu, hodnocen�: 100.00 %

Test 'Kontrola o�et�en� nespr�vn�ch vstup�': �sp�ch
Dosa�eno: 100.00 %, po�adov�no: 50.00 %
Max doba b�hu: 0.024 s (limit: 2.000 s)
Celkov� doba b�hu: 0.092 s
Vyu�it� pam�ti: 11720 KiB (limit: 18434 KiB)
�sp�ch v z�vazn�m testu, hodnocen�: 100.00 %

Test 'Test n�hodn�mi hodnotami': �sp�ch
Dosa�eno: 100.00 %, po�adov�no: 50.00 %
Max doba b�hu: 0.006 s (limit: 2.000 s)
Celkov� doba b�hu: 0.158 s
Vyu�it� pam�ti: 11720 KiB (limit: 18434 KiB)
�sp�ch v z�vazn�m testu, hodnocen�: 100.00 %

Celkov� hodnocen�: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00)
Celkov� procentn� hodnocen�: 100.00 %
Bonus za v�asn� odevzd�n�: 0.50
Celkem bod�: 1.00 * ( 5.00 + 0.50 ) = 5.50
```