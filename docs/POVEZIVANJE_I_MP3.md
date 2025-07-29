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
| Triple 17        | A11         | A15            |
| Double 17        | A4          | A15            |
| Simple 17        | A5          | A15            |
| Triple 3         | A10         | A15            |
| Double 3         | 51          | A15            |
| Simple 3         | 53          | A15            |
| Triple 19        | A9          | A15            |
| Double 19        | 47          | A15            |
| Simple 19        | 49          | A15            |
| Triple 7         | A8          | A15            |
| Double 7         | 43          | A15            |
| Simple 7         | 45          | A15            |
| Triple 16        | A7          | A15            |
| Double 16        | 41          | A15            |
| Simple 16        | 39          | A15            |
| **Common A14**   |             |                |
| Triple 6         | A10         | A14            |
| Double 6         | 51          | A14            |
| Simple 6         | 53          | A14            |
| Triple 10        | A9          | A14            |
| Double 10        | 47          | A14            |
| Simple 10        | 49          | A14            |
| Triple 15        | A8          | A14            |
| Double 15        | 43          | A14            |
| Simple 15        | 45          | A14            |
| Triple 2         | A7          | A14            |
| Double 2         | 41          | A14            |
| Simple 2         | 39          | A14            |
| 25 (Double)      | A6          | A14            |
| Triple 13        | A11         | A14            |
| Double 13        | A4          | A14            |
| Simple 13        | A5          | A14            |
| **Common A12**   |             |                |
| Triple 8         | A11         | A12            |
| Double 8         | A4          | A12            |
| Simple 8         | A5          | A12            |
| Triple 14        | A9          | A12            |
| Double 14        | 47          | A12            |
| Simple 14        | 49          | A12            |
| Triple 9         | A8          | A12            |
| Double 9         | 43          | A12            |
| Simple 9         | 45          | A12            |
| Triple 11        | A10         | A12            |
| Double 11        | 51          | A12            |
| Simple 11        | 53          | A12            |
| Triple 12        | A7          | A12            |
| Double 12        | 41          | A12            |
| Simple 12        | 39          | A12            |
| **Common A13**   |             |                |
| Triple 5         | A11         | A13            |
| Double 5         | A4          | A13            |
| Simple 5         | A5          | A13            |
| Triple 20        | A10         | A13            |
| Double 20        | 51          | A13            |
| Simple 20        | 53          | A13            |
| Triple 1         | A9          | A13            |
| Double 1         | 47          | A13            |
| Simple 1         | 49          | A13            |
| Triple 18        | A8          | A13            |
| Double 18        | 43          | A13            |
| Simple 18        | 45          | A13            |
| Triple 4         | A7          | A13            |
| Double 4         | 41          | A13            |
| 25 (Simple)      | A6          | A13            |
| Simple 4         | 39          | A13            |


Detaljan popis MP3 datoteka nalazi se u [POPIS_MP3_ZVUKOVA.md](POPIS_MP3_ZVUKOVA.md).

