# Pikado Elektronski Sustav (Arduino + Dartboard)

Ovaj projekt detektira pogođene mete na elektronskom pikado aparatu koristeći **Arduino Mega 2560**.
Podržava više igara, više igrača, LED indikaciju i dodatna pravila poput Double IN i Double OUT.
Koristi mikrofon za detekciju promašaja i tipke za odabir igre, broja igrača i pravila.

---

## 🎯 Podržane igre

| Igra        | Opis |
|-------------|------|
| **301 / 501 / 701** | Klasične igre odbrojavanja do nule. Moguće uključiti Double IN i Double OUT. |
| **Shanghai** | Gađa se broj runde (1–20). Boduju se samo pogođeni ciljani broj. Shanghai (S+D+T) donosi automatsku pobjedu. |
| **Roulette** | Svakom igraču se dodijeli nasumični broj koji samo on smije pogađati. Pobjednik je onaj s najviše bodova nakon 5 rundi. |
| **Hangman** | Igrači pokušavaju pogoditi sve brojeve bez ponavljanja. 6 grešaka = ispadanje. |
| **Cricket** | Pogađaju se brojevi 15–20 i bull (25). Svaki broj se mora pogoditi 3 puta. Višak pogodaka donosi bodove. |
| **3-in-line** | Pobjeda ako igrač pogodi 3 uzastopna broja (npr. 8-9-10), redoslijed gađanja nije bitan. |

---

## ⚙️ Funkcionalnosti

- Detekcija svih zona na ploči (Simple, Double, Triple)
- Detekcija promašaja pomoću mikrofona (svaki promašaj se broji kao bačena strelica)
- Tipke za odabir igre, broja igrača i pravila
- LED indikacija za sve odabire
- Modularna struktura igara
- Double IN i Double OUT kao opcionalna pravila
- Serijski ispis rezultata i poruka
- Prikaz bodova na MAX7219 displayu za sve igre
- U igri **3-in-line** display prikazuje duljinu trenutnog niza pogodaka, a novi rekord blinka
- Prepoznaje bacanje strelice prije odabira igre ili igrača i pušta zvuk upozorenja
- Snimljeni glasovni pozivi igrača ("Igrač 1", "Igrač 2"...)
- Glasovna najava pogođenog polja (koristi mp3 datoteke od `0100.mp3` nadalje)
- Automatski prelazak u "sleep" način rada nakon 10 minuta neaktivnosti (display blinka svakih 5 s)

---

## 🧰 Hardver

- **Arduino Mega 2560**
- Dart ploča spojena na digitalne i analogne pinove
- Mikrofon spojen na A0 za detekciju promašaja (granična vrijednost je `THRESHOLD_PROMASAJ` iz `config.h`)
- Tipke za odabir spojene na digitalne pinove (pull-up)
- LED žaruljice upravljane preko UCN5821 (shift register)
- Segmentni display s MAX7219 (6 modula) za prikaz bodova
- JQ6500 MP3 modul za zvučne efekte (povezan na Serial1)

---

## 🛠️ Konfiguracija

Neka pravila igre se definiraju preko tipki ili u `config.h`:

- `DOUBLE_OUT` – kada je `true`, igru je moguće završiti samo Double poljem
- `DOUBLE_IN` – kada je `true`, igrač mora započeti pogodak s Double da bi bodovi vrijedili

Pravilo *bounce-out* (bust) u igrama **301** i **501** uvijek je aktivno i nije potrebno posebno podešavanje.

---

## 🔧 Kompajliranje

1. Otvori `PIKADO.ino` u Arduino IDE ili CLI
2. Odaberi ploču **Arduino Mega 2560**
3. Instaliraj Arduino biblioteku **LedControl** (za MAX7219)
4. Kompajliraj i učitaj na uređaj

---

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

---

## 🧪 Korištenje

1. Nakon učitavanja, otvori **Serial Monitor na 9600 baud**
2. Odaberi igru pomoću tipki
3. Za igre **301** i **501** nakon toga možete pritisnuti tipke
   **DOUBLE IN** i/ili **DOUBLE OUT**. Lampice tih tipki ostat će upaljene i
   pravilo će vrijediti tijekom cijele igre. Pritiskom ovih tipki za vrijeme
   igre ništa se neće promijeniti – tek nakon *RESET* opcije moguće je ponovno
   birati igru i dodatne funkcije.
4. Zatim odaberite broj igrača
5. LED žaruljice će pokazati trenutne odabire
6. Igra započinje automatski
7. Serijski monitor prikazuje sve pogođaje, bodove i status

---

## 📌 Napomena

Ovaj sustav je dizajniran modularno tako da je lako dodavati nove igre i funkcionalnosti. Može se nadograditi s prikazom na OLED/TFT ili komunikacijom s Raspberry Pi.

