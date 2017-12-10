Vstup: Na prvom riadku je celé číslo N (do 1000) počet bodov, a nasleduje N dvojíc celých čísel: x-ová a y-ová súradnica i-teho bodu.

Výstup: Na štandardný výstup vypíše najmenší obvod mnohouholníka, ktorý je potrebný na to, aby všetky body boli pokryté plochou mnohouholníka. Obvod je zaokrúhlený na tri desatinné miesta.

Ukážka vstupu:

4

2 0

0 2

1 1

0 0

Výstup pre ukážkový vstup:
6.828

Na riešenie tohto problému sa používa metóda horného a dolného obalu.

#######################################################################

Refaktoring

Pri refaktoringu svojho kódu som sa snážil zlepšiť čítateľnosť, modifikovateľnosť a prenosnosť kódu.

Čítateľnosť sa dala zlepšiť pomocou zmeny názvov premenných a funkcií, oddeľovanie kódu, zmenšenia rozmerov funkcií.

Modifikovateľnosť sa zlepšila pomocou odstránenia dublicitného kódu, enkapsuláciou, zmenšenia množstva parametrov, idúcich do funkcie.

Prenosnosť sa zlepšila vďaka náhrady magických čísel konštantámi.
