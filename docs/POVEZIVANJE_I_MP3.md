# Povezivanje i MP3 datoteke

Sadržaj README datoteke koji opisuje raspored pinova na ploči i nazive MP3 datoteka izdvojen je ovdje radi preglednosti.

## 🪛 Povezivanje

Napomena: pinovi **20** (SDA) i **21** (SCL) rezervirani su za I2C vezu s LCD
ekranom te se ne smiju koristiti za tipke ili druge periferije.

### Tipke (gumbi)

| Pinovi | Funkcija         |
|--------|------------------|
| 28–46  | Odabir igre (parni pinovi) |
| 23–33  | Broj igrača (neparni pinovi) |
| 50, 52 | Pravila (Double OUT / IN) |

Raspored pojedinih tipki:

| Pin | Povezana tipka |
|-----|----------------|
| 36  | Igra 301 |
| 34  | Igra 501 |
| 30  | Shanghai |
| 40  | Hangman |
| 28  | Roulette |
| 38  | 701 |
| 32  | Cricket |
| 42  | 3-in-line |
| 46  | NEW PLAYER |
| 44  | RESET |
| 33  | Igrač 1 |
| 31  | Igrač 2 |
| 29  | Igrač 3 |
| 27  | Igrač 4 |
| 25  | Igrač 5 |
| 23  | Igrač 6 |
| 50  | Double OUT |
| 52  | Double IN |

### LED žaruljice (preko UCN5821)

| Pin    | Funkcija         |
|--------|------------------|
| 2      | DATA             |
| 3      | CLOCK            |
| 4      | LATCH            |

### MAX7219 display

| Pin | Funkcija |
|-----|----------|
| 9   | DIN      |
| 10  | CLK      |
| 11  | CS       |

### LCD (I2C)

| Pin | Funkcija |
|-----|----------|
| 20  | SDA      |
| 21  | SCL      |
|     | I2C adresa 0x27 |

### Pikado ploča (detekcija)

- **Aktivni pinovi senzora:** A0, A1, A2, A3, A4, A5, A6, A7, 53, 51, 49, 47, 45, 43, 41, 39
- **Zajednički pinovi:** A15 (`COM_A15`), A14 (`COM_A14`), A12 (`COM_A12`), A13 (`COM_A13`)
- **Mikrofon za promašaje:** A8 (`PIN_MIKROFON`)

Ova tablica prikazuje koji je pin povezan s kojom metom na pikado ploči, te kojem zajedničkom vodu (common) pripada.

| Meta             | Aktivni pin | Zajednički pin |
|------------------|-------------|----------------|
| **Common A15**   |             |                |
| Triple 12        | 41          | A15            |
| Double 12        | A7          | A15            |
| Simple 12        | A6          | A15            |
| Triple 9         | 43          | A15            |
| Double 9         | A5          | A15            |
| Simple 9         | A4          | A15            |
| Triple 14        | 45          | A15            |
| Double 14        | A3          | A15            |
| Simple 14        | A2          | A15            |
| Triple 11        | 47          | A15            |
| Double 11        | A1          | A15            |
| Simple 11        | A0          | A15            |
| Triple 8         | 49          | A15            |
| Double 8         | 35          | A15            |
| Simple 8         | 37          | A15            |
| **Common A14**   |             |                |
| Triple 4         | 41          | A14            |
| Double 4         | A7          | A14            |
| Simple 4         | A6          | A14            |
| Triple 18        | 43          | A14            |
| Double 18        | A5          | A14            |
| Simple 18        | A4          | A14            |
| Triple 1         | 45          | A14            |
| Double 1         | A3          | A14            |
| Simple 1         | A2          | A14            |
| Triple 20        | 47          | A14            |
| Double 20        | A1          | A14            |
| Simple 20        | A0          | A14            |
| Triple 5         | 49          | A14            |
| Double 5         | 35          | A14            |
| Simple 5         | 37          | A14            |
| 25 (Simple)      | 39          | A14            |
| **Common A13**   |             |                |
| Triple 2         | 41          | A13            |
| Double 2         | A7          | A13            |
| Simple 2         | A6          | A13            |
| Triple 15        | 43          | A13            |
| Double 15        | A5          | A13            |
| Simple 15        | A4          | A13            |
| Triple 10        | 45          | A13            |
| Double 10        | A3          | A13            |
| Simple 10        | A2          | A13            |
| Triple 6         | 47          | A13            |
| Double 6         | A1          | A13            |
| Simple 6         | A0          | A13            |
| Triple 13        | 49          | A13            |
| Double 13        | 35          | A13            |
| Simple 13        | 37          | A13            |
| 25 (Double)      | 39          | A13            |
| **Common A12**   |             |                |
| Triple 16        | 41          | A12            |
| Double 16        | A7          | A12            |
| Simple 16        | A6          | A12            |
| Triple 7         | 43          | A12            |
| Double 7         | A5          | A12            |
| Simple 7         | A4          | A12            |
| Triple 19        | 45          | A12            |
| Double 19        | A3          | A12            |
| Simple 19        | A2          | A12            |
| Triple 3         | 47          | A12            |
| Double 3         | A1          | A12            |
| Simple 3         | A0          | A12            |
| Triple 17        | 49          | A12            |
| Double 17        | 35          | A12            |
| Simple 17        | 37          | A12            |


Detaljan popis MP3 datoteka nalazi se u [POPIS_MP3_ZVUKOVA.md](POPIS_MP3_ZVUKOVA.md).

