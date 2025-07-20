# Dartboard Detection Project

Ovaj projekt detektira pogođene mete na elektronskom pikado aparatu koristeći Arduino Mega. Uz to koristi mikrofon za detekciju promašaja.

## Funkcionalnosti

- Detekcija svih zona na ploči
- Detekcija promašaja pomoću mikrofona
- Modularni kod spreman za proširenje (score, igrači, ekran...)

## Hardver

- Arduino Mega 2560
- Dart ploča povezana na digitalne i analogne pinove
- Mikrofon na A0

## Konfiguracija

Ponašanje nekih pravila igre može se mijenjati u `config.h`:

- `BOUNCE_OUT` - kada je `true`, prelazak ispod nule poništava potez i vraća prijašnje bodove (bust)
- `DOUBLE_OUT` - kada je `true`, partija se može završiti samo pogođenim dvostrukim poljem
