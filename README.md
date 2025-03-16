Opis aplikacije BlackjackGame:

Ovo je konzolna aplikacija izrađena u C++ jeziku koja simulira klasičnu igru s kartama Blackjack. 
Igrač se natječe protiv dealera (u ovom smislu protiv programa - konzole) s ciljem da skupi zbroj karata što bliže 21, bez da ga prijeđe.
Svaka karta ima svoju vrijednost, a as može biti ili 1 ili 11, ovisno o tome što je korisnije za igrača. 
Igrač može odabrati opciju "hit" (izvuci kartu) ili "stand" (ostani s trenutnim kartama) dok ne bude zadovoljan svojim zbrojem ili dok ne prijeđe 21 (što se zove "bust").

Upute za igru:

1. Kada pokrenete igru, najprije ćete unijeti početni iznos novca (balance) kojim želite ući u igranje.
2. Nakon unosa početnog iznosa novca, od vas će biti zatraženo da odaberete iznos oklade za trenutnu rundu.
3. Na početku svake runde, igrač i dealer dobivaju po dvije karte. Jedna karta dealera bit će skrivena, dok ćete vi vidjeti sve svoje karte.
4. Nakon što vidite svoje karte i kartu dealera, imate mogućnost odabrati:
"Hit" - Izvucite još jednu kartu.
"Stand" - Zadržite svoje trenutne karte i završite svoj potez.
5. Dealer će povući karte dok njegov zbroj ne bude barem 17 ili više. Ako zbroj dealera prijeđe 21, dealer gubi rundu.
6. Nakon što obje strane završe svoje poteze, uspoređuju se zbrojevi karata. Ako ste bliže 21 od dealera, vi pobjeđujete i vraćate dvostruko od vaše uložene oklade. Ako dealer pobijedi, gubite okladu. Ako je izjednačeno, vraćate svoj ulog.
7. Igra se nastavlja dok imate novca za oklade. Ako vam ponestane novca, igra je završena.

Napomene:

1. Početni ulozi za igru su unaprijed definirani i ne mogu biti različiti (apoeni su: 1, 2, 5, 10, 20, 50, 100)
2. Dodana je opcija "cashout" koja se može unijeti tokom određivanja uloga. Opcijom "cashout" igrač povlači svoj trenutni balance i igra završava.
3. Moguće je dobiti Blackjack (zbroj 21) i u prve dvije karte, tada se čeka potez dealera koji dobiva svoje karte.
