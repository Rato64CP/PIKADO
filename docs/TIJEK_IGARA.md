# Tijek izvršavanja igara

Ovaj dokument opisuje generičan tijek igre na elektroničkom pikadu. Koristan je za razumijevanje kako se pojedine komponente i moduli povezuju kroz igru.

1. **Pokretanje uređaja** – Nakon uključivanja Arduina, inicijaliziraju se svi moduli: tipke, žaruljice (LED), detekcija mete, zvukovi i display.
2. **Odabir igre** – Pritiskom na tipke odabire se željena igra (301, 501, Shanghai …). LED lampice signaliziraju trenutno odabranu opciju.
3. **Odabir broja igrača** – Sljedećim skupom tipki bira se broj sudionika (1–6). Imena igrača prikazuju se na displayu i reproducira se snimljena najava.
4. **Dodatna pravila** – Za igre 301/501/701 moguće je uključiti opcije *Double IN* i *Double OUT*. Odabrane opcije prikazuju se paljenjem odgovarajućih LED lampica.
5. **Pokretanje runde** – Nakon što su postavljene sve opcije, pritisak na tipku **NEW PLAYER** pokreće igru. Aktivni igrač naznačen je blinkajućom lampicom.
6. **Bacanje strelica** – Detekcija pogođenog polja ili promašaja odvija se u realnom vremenu. Rezultat se zapisuje, a na zvučniku se reproducira odgovarajući zvuk ili najava.
7. **Završetak poteza** – Kada igrač baci sve strelice, na displayu se ispisuje rezultat i poziva se funkcija `krajPoteza()`. Igrač vadi strelice i potvrđuje završetak pritiskom na **NEW PLAYER**.
8. **Sljedeći igrač** – Funkcija `sljedeciIgrac()` aktivira idućeg sudionika i postupak se ponavlja od točke 6. Sve lampice i najave prilagođavaju se novom igraču.
9. **Kraj igre** – Ovisno o pravilima pojedine igre (`obradiPogodak_*` funkcije), kada se ispune uvjeti pobjede poziva se `zavrsiIgru()`. Na zvučniku se pušta pobjednička melodija, a na displayu se prikazuje poruka.
10. **Nova igra ili reset** – U tom trenutku moguće je ponovno pritisnuti **NEW PLAYER** za novu igru sa istim postavkama ili **RESET** za povratak na izbornik i novi odabir igre/igrača.

Ovaj tok vrijedi za sve podržane igre, dok svaka od njih ima specifična pravila opisana u pojedinim datotekama (npr. `game_301.cpp`, `game_cricket.cpp`).
