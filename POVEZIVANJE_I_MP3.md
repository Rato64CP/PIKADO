# Povezivanje i MP3 datoteke

Sadržaj README datoteke koji opisuje raspored pinova na ploči i nazive MP3 datoteka izdvojen je ovdje radi preglednosti.

## 🪛 Povezivanje

### Tipke (gumbi)

| Pinovi | Funkcija         |
|--------|------------------|
| 22–31  | Odabir igre      |
| 32–37  | Broj igrača      |
| 38–39  | Pravila (IN/OUT) |

### LED žaruljice (preko UCN5821)

| Pin    | Funkcija         |
|--------|------------------|
| 5      | DATA             |
| 6      | CLOCK            |
| 7      | LATCH            |

### MAX7219 display

| Pin | Funkcija |
|-----|----------|
| 9   | DIN      |
| 10  | CLK      |
| 11  | CS       |

### Pikado ploča (detekcija)

- **Aktivni pinovi senzora:** A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, 53, 49, 43
- **Zajednički pinovi:** 45 (`COM_45`), 47 (`COM_47`), A1 (`COM_A1`), A2 (`COM_A2`)
- **Mikrofon za promašaje:** A0 (`PIN_MIKROFON`)

### JQ6500 MP3 modul

Modul je spojen na **Serial1** konekciju Arduina (TX1=18, RX1=19). Na njemu se nalaze MP3 datoteke za sve zvučne efekte.

#### Nazivi datoteka

Datoteke moraju imati prefiks s četiri znamenke kako bi odgovarale numeraciji `mp3.play()` funkcije. Preporučeni nazivi su:

| Broj | Datoteka        | Opis                     |
|-----:|-----------------|-------------------------|
| 1    | `0001.mp3`      | Uvodna melodija         |
| 2    | `0002.mp3`      | Zvuk bacanja strelice   |
| 3    | `0003.mp3`      | Zvuk promašaja          |
| 4    | `0004.mp3`      | Zvuk vađenja strelice   |
| 6    | `0006.mp3`      | Pobjednička melodija    |
| 7    | `0007.mp3`      | Zvuk pritiska tipke     |
| 8    | `0008.mp3`      | Upozorenje nepostavljene igre |
| 9    | `0009.mp3`      | Zvuk "Bust" (prelazak preko 0) |
| 21   | `0021.mp3`      | Snimka "Igrač 1"        |
| 22   | `0022.mp3`      | Snimka "Igrač 2"        |
| 23   | `0023.mp3`      | Snimka "Igrač 3"        |
| 24   | `0024.mp3`      | Snimka "Igrač 4"        |
| 25   | `0025.mp3`      | Snimka "Igrač 5"        |
| 26   | `0026.mp3`      | Snimka "Igrač 6"        |
| 30   | `0030.mp3`      | "Roulette start"        |
| 31   | `0031.mp3`      | "Target is" najava      |
| 32   | `0032.mp3`      | "Target hit"            |
| 33   | `0033.mp3`      | "Roulette over"         |
| 34   | `0034.mp3`      | "Shanghai" pobjeda      |
| 35   | `0035.mp3`      | "Try again" poruka      |

### Datoteke za pojedinacne mete

Ove snimke najavljuju pogođeno polje. Svaka datoteka odgovara jednoj zoni na ploci.

| Broj | Datoteka | Opis |
|-----:|---------|------|
| 100 | `0100.mp3` | Triple 17 |
| 101 | `0101.mp3` | Double 17 |
| 102 | `0102.mp3` | Simple 17 |
| 103 | `0103.mp3` | Triple 3 |
| 104 | `0104.mp3` | Double 3 |
| 105 | `0105.mp3` | Simple 3 |
| 106 | `0106.mp3` | Triple 19 |
| 107 | `0107.mp3` | Double 19 |
| 108 | `0108.mp3` | Simple 19 |
| 109 | `0109.mp3` | Triple 7 |
| 110 | `0110.mp3` | Double 7 |
| 111 | `0111.mp3` | Simple 7 |
| 112 | `0112.mp3` | Triple 16 |
| 113 | `0113.mp3` | Double 16 |
| 114 | `0114.mp3` | Simple 16 |
| 115 | `0115.mp3` | Triple 6 |
| 116 | `0116.mp3` | Double 6 |
| 117 | `0117.mp3` | Simple 6 |
| 118 | `0118.mp3` | Triple 10 |
| 119 | `0119.mp3` | Double 10 |
| 120 | `0120.mp3` | Simple 10 |
| 121 | `0121.mp3` | Triple 15 |
| 122 | `0122.mp3` | Double 15 |
| 123 | `0123.mp3` | Simple 15 |
| 124 | `0124.mp3` | Triple 2 |
| 125 | `0125.mp3` | Double 2 |
| 126 | `0126.mp3` | Simple 2 |
| 127 | `0127.mp3` | 25 (Double) |
| 128 | `0128.mp3` | Triple 13 |
| 129 | `0129.mp3` | Double 13 |
| 130 | `0130.mp3` | Simple 13 |
| 131 | `0131.mp3` | Triple 8 |
| 132 | `0132.mp3` | Double 8 |
| 133 | `0133.mp3` | Simple 8 |
| 134 | `0134.mp3` | Triple 14 |
| 135 | `0135.mp3` | Double 14 |
| 136 | `0136.mp3` | Simple 14 |
| 137 | `0137.mp3` | Triple 9 |
| 138 | `0138.mp3` | Double 9 |
| 139 | `0139.mp3` | Simple 9 |
| 140 | `0140.mp3` | Triple 11 |
| 141 | `0141.mp3` | Double 11 |
| 142 | `0142.mp3` | Simple 11 |
| 143 | `0143.mp3` | Triple 12 |
| 144 | `0144.mp3` | Double 12 |
| 145 | `0145.mp3` | Simple 12 |
| 146 | `0146.mp3` | Triple 5 |
| 147 | `0147.mp3` | Double 5 |
| 148 | `0148.mp3` | Simple 5 |
| 149 | `0149.mp3` | Triple 20 |
| 150 | `0150.mp3` | Double 20 |
| 151 | `0151.mp3` | Simple 20 |
| 152 | `0152.mp3` | Triple 1 |
| 153 | `0153.mp3` | Double 1 |
| 154 | `0154.mp3` | Simple 1 |
| 155 | `0155.mp3` | Triple 18 |
| 156 | `0156.mp3` | Double 18 |
| 157 | `0157.mp3` | Simple 18 |
| 158 | `0158.mp3` | Triple 4 |
| 159 | `0159.mp3` | Double 4 |
| 160 | `0160.mp3` | 25 (Simple) |
| 161 | `0161.mp3` | Simple 4 |

