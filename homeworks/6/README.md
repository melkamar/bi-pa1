# Domácí úloha 6 - Řešení osmisměrky 

Úkolem je vytvořit program, který bude řešit hlavolam - osmisměrku.

Osmisměrka je zadaná jako 2D pole znaků a seznam slov. Cílem je v poli znaků nalézt slova ze seznamu a "vyškrtnout je". Zbylá (neškrtnutá) písmena tvoří tajenku. Slova se v osmisměrce mohou nacházet kdekoliv - horizontálně, vertikálně i diagonálně, čtená zleva doprava, shora dolů i naopak. Jedno písmeno může být použito ve více vyškrtnutých slovech, škrtaná slova se mohou překrývat, slovo v seznamu může být v poli obsaženo vícekrát (pak je potřeba vyškrtat všechny výskyty).

Vstupem programu je zadání osmisměrky. Nejprve je zadané obdélníkové 2D pole s písmeny. Může obsahovat znaky malé a - z nebo znak tečka (nepoužité políčko). Pole musí mít alespoň jeden řádek a alespoň jeden sloupec. Po zadání osmisměrky následuje prázdný řádek a za ním seznam slov k vyhledání. Slova jsou zadaná po jednom na řádku. Seznam slov skončí s koncem vstupu.

Výstupem programu je nalezená tajenka. Výpis může být dlouhý, program jej proto rozdělí na řádky délky 60 znaků + případný zbytek na poslední řádce.

Program musí detekovat nesprávný vstup. Pokud je vstup nesprávný, program to zjistí, vypíše chybové hlášení a ukončí se. Za chybu je považováno:

- pole osmisměrky nemá velikost alespoň 1x1,
- pole osmisměrky není obdélníkového tvaru,
- pole osmisměrky obsahuje znaky jiné než malá písmena a tečku,
- chybí prázdný řádek za zadáním pole osmisměrky,
- slovo v seznamu není v osmisměrce obsaženo (pozor, formát chybového hlášení je zde odlišný, viz ukázka).

Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu, je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy a výstupy a přečtěte si sekci FAQ, jak využít přesměrování vstupů/výstupů k testování Vašeho programu.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu a dále je omezena i velikost dostupné paměti. Paměťový limit by v této úloze neměl být problém. Úloha může být náročná na čas výpočtu. Časový limit je nastaven tak, aby správně implementovaný naivní algoritmus prošel všemi povinnými testy. Pole osmisměrky může mít libovolnou velikost. Nepokoušejte se jej alokovat staticky. Testovací prostředí provádí testy, aby zkontrolovalo správnou práci s pamětí, věnujte proto péči alokaci a uvolňování paměti.

## Ukázka práce programu:
```
Zadejte osmismerku:
dsjellivhsanxrr
riemjudhgdffcfz
elfkumrayldwory
iofcnoorteyclit
lperenfriitnuci
earaatticfspmhc
pnsmugrsegarbma
taoshoabknioiom
niniomhuainvano
odcbnexrlrtirdh
mnicorwgtppdepa
witslyxolsaevll
xhybuvoyaxunnvk
atnaltapsllcelo
ryedunuhyxhedfy

atlanta
saltlakecity
indianapolis
montpelier
juneau
bismarck
oklahomacity
saintpaul
denver
honolulu
richmond
harrisburg
columbia
nashville
springfield
providence
montgomery
hartford
jeffersoncity
Vysledek:
dxrrmugfffzdwyctnxcwpwsxolxhbvoyxvpllryednuhyxhfy
```
---
```
Zadejte osmismerku:
.......iadky..........
.....lwvnaete.........
....dqiaw..zss........
...gmrlws...nrr.......
..aogydmi....tce......
..yirebqf....dzzjthf..
.snarhodeislandinwxpp.
.imfeopmississippiejlo
ainigrivtsewawngopvnzb
izcxconnecticutnomrevd
fdssttesuhcassamjggroi
nzafycjanilorachtuosoe
.nghainavlysnnepnolws.
..xdok.........jjia...
...lo...........gc....

virginia
southcarolina
pennsylvania
connecticut
newjersey
maryland
vermont
iowa
idaho
mississippi
massachusetts
rhodeisland
westvirginia
Vysledek:
iaklwaetdqwzsgmwsnraodmitcyebqfdzzthfsinxppfeopjloawngopvzbz
cxdfsjggronzfycjengnolsxdkjjilogc
```
---
```
Zadejte osmismerku:
azatosennimy.....dcjmlt......
n....daapklh......eafb.......
a....uttueuvr......nc........
i....ygnimoyw..vu..ly........
d....qvgmqrpg..dw..aw........
netiruossimabsngujipknav.....
itlgatokadhtuoscsnevnejdau...
atokadhtronvjxoornraqwgzrf...
gunqerawaledanfondlythldkr...
ippississimdnnfsjgpeiahnnn...
adirolfqndaeiiyfgtnlhmvae....
louisianavcsllxsfnlzapilb....
sasnakraetnavzsseimowsryr....
eoufdrcniocanaasnoikahgraa...
haarjwvcconkxssojhaiiiiasfy..
puuawtuscigeneiqojjmirnmklhu.
usvybtilagtaesalabamaeivasxeu
...oywdz.ykasm.pkfwb.zazqy...
....ynu...ftk...zlb...akn....

missouri
delaware
newhampshire
connecticut
ohio
wisconsin
wyoming
mississippi
maryland
texas
kansas
northdakota
nevada
florida
hawaii
nebraska
pennsylvania
indiana
virginia
louisiana
tennessee
alabama
arkansas
california
illinois
minnesota
southdakota
Vysledek:
zydcjmltdaapklheafbuttueuvrncyvulyqvgmqrpgdwwetabsngujkavtlg
svnjdauvjxoraqgzrfgunqfdlylkrjgphnqndfgtxsfzzmeoufdrcnokahaa
rjwvokjaifypuuawtcgqjjmlhuusvyblgvsxeuoydzyasmpkfwbzzqyynuft
kzlbakn
```
---
```
Zadejte osmismerku:
............xcx............
.........qeztodlea.........
.......ecnedivorpuzy.......
.....bqfjwxqindnrsatrs.....
....ucaamadisonoctoieax....
...ozkttqdxwltstaivcilex...
...ujknnakigzfasxninltxc...
..rabxaa...kohce...oelnyd..
..rithls...momrl...spayvh..
.awecktlukrnloardaartkrhxu.
.lqezhacyooyznmapqaenemrqg.
.besldmyelpnltehshefocgnhd.
daasizoouuhjigncoavfmiokwsn
jncanfblnnoueotzqkyehtwduip
rywhcjuowdentmoniewjnyeypcs
.adao.wljwneoenazpgea.ofoq.
.icll..ntciaxrlraoru..mlev.
.tflnk..xtxueyakgth..vummp.
..tayie.............xmmee..
..htgjbj...........mbflvq..
...littlerockihhcftidaja...
...oklahomacityzoyapsshm...
....kjehgufspringfieldr....
.....fjwyjjmnwdenverzl.....
.......qnarzlhejwwtc.......
.........enneyehcn.........
............jjy............

honolulu
oklahomacity
charleston
madison
montgomery
saltlakecity
springfield
juneau
tallahassee
providence
phoenix
santafe
trenton
albany
lincoln
jeffersoncity
atlanta
austin
littlerock
sacramento
topeka
denver
cheyenne
montpelier
salem
richmond
columbia
Vysledek:
xcxqeztodlezbqjwxqindrauccoxozkqdxwltavexujkakigzfxixcabxkon
ydrthmyvhwklukrldaarhxuqzcyoyzpqamrqgedyenlsheghddazouiovkws
njcfbnezqyhwduiprwjowtniweypsadwljwonazgaofqicntcxlraumevtfk
xteakghvmptyiexmehgjbjmfvqihhcftdjazoypshmkjehgufrfjwyjjmnwz
lqnarzlhejwwtcnjjy
Zadejte osmismerku:
..hle.............psu..
.tkagls.........lqhajp.
etacrelon.....mpcgebrhi
rgfcrrfih.....hbvndover
fiutdaijvt...yfcudvrcew
cocoxsmsqh...hjjgimlfjf
pnjhrcesbys.cbpsdaiaajl
.bulmnkniuqalviedjtzraj
..qiaoogibrinlniinttcj.
....kgntmotgocshafb....
.......datmpeods.......
.....cmplbasnplhjf.....
....pgbernloepnrxkx....
..ndhnrgaxukcdaustino..
.abrwofiupalsacramento.
.fojczdxpapanomctmwfzy.
hslkonirmytheybehgielar
oxypievkk.non.dlaugusta
lummotycs.imo.rcolumbia
fcpvghdk..aas..vkmtbhsi
xoijcbp...sck...lansing
.iajol....iic....twbkq.
..igs.....tta.....pys..
..........cyj..........
..........bgf..........

desmoines
dover
madison
richmond
nashville
bismarck
columbia
batonrouge
oklahomacity
olympia
saintpaul
raleigh
harrisburg
indianapolis
providence
austin
sacramento
augusta
jackson
littlerock
lansing
juneau
santafe
Vysledek:
lpstgslqhjtaeonmpcgbhifcfhhbvftdjtyfcdrcwcoxqhjgljfpnjcycbpi
ajlbulkqvjzrajqiagittcjkgmhfbdcmpplhjfpgbrpnrxkxndhngxcoabrw
fupfjzxpanomctmwfzyhsoirmyeybeoxpevkkdllumotycsrfcvghdkvkmtb
hsixojcbpijolitwbkqigstpyscbgf
```
---
```
Zadejte osmismerku:
dhobshneptuney
uejihunysthaor
dnauueeemaenwa
wnaiplutonaodh
aghplizooerusu
rdeihctmnwtnsh
fhyhopbeoqhiue
racoeaarrteoae
usaturncplanet
rtaehftueuleee
ieucufarovceio
arfairayaoeirh
toainiabearnae
oiateoenaaehua
ediddoedutsets
eszeehophslums

venus
earth
ceres
asteroids
jupiter
saturn
neptune
uranus
pluto
dwarf
mars
Slovo 'mars' nenalezeno.
```
---
```
Zadejte osmismerku:
abcde
abcdef
Nespravny vstup.
```
---
```
Zadejte osmismerku:
abcde
edbca
Nespravny vstup.
```


### Poznámky:
- Délky řetězců ani velikost osmisměrky není omezena. Alokujte je dynamicky podle aktuální potřeby.
- Při natahování řetězců a polí nezvětšujte velikost po jedničce. Pole zvětšujte s větším krokem (např. 1024) nebo ještě lépe v geometrické řadě (např. 50 - 100 - 200 - 400 - 800 - ...).
- Správně implementovaný naivní algoritmus projde všemi základními testy. Bonusový test zkouší osmisměrky větší, naivní algoritmus neprojde na časový limit. Pro zvládnutí bonusového testu je potřeba vyhledávání slov zefektivnit. Referenční řešení používá pro zrychlení algoritmus založená na algoritmu suffix array.


## Hodnocení
```
Stav odevzdání:	Ohodnoceno
Hodnocení:	5.5000
Hodnotitel: automat
Program zkompilován

Test 'Základní test s parametry podle ukázky': Úspěch
Dosaženo: 100.00 %, požadováno: 100.00 %
Max doba běhu: 0.010 s (limit: 2.000 s)
Celková doba běhu: 0.055 s
Využití paměti: 11724 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test mezních hodnot': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.031 s
Využití paměti: 11724 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test ošetření nesprávných vstupů': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.005 s (limit: 2.000 s)
Celková doba běhu: 0.026 s
Využití paměti: 11724 KiB (limit: 18434 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 1.230 s (limit: 2.000 s)
Celková doba běhu: 3.195 s
Využití paměti: 11724 KiB (limit: 25270 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Test náhodnými daty + test práce s pamětí': Úspěch
Dosaženo: 100.00 %, požadováno: 50.00 %
Max doba běhu: 0.116 s (limit: 6.000 s)
Celková doba běhu: 0.503 s
Využití paměti: 18844 KiB (limit: 27223 KiB)
Úspěch v závazném testu, hodnocení: 100.00 %

Test 'Bonusový test (velké osmisměrky)': Program překročil přidělenou maximální dobu běhu
Program násilně ukončen po: 6.004 s (limit: 6.000 s)
Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
Překročení doby běhu [Zpřístupnit nápovědu (32.00 KiB)]

Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
Použité nápovědy: 1
Penalizace za vyčerpané nápovědy: Není (1 <= 2 limit)
Celkové procentní hodnocení: 100.00 %
Bonus za včasné odevzdání: 0.50
Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50
```