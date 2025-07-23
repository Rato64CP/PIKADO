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
- Prepoznaje bacanje strelice prije odabira igre ili igrača i pušta zvuk upozorenja
- Snimljeni glasovni pozivi igrača ("Igrač 1", "Igrač 2"...)
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
| 5    | `0005.mp3`      | Zvuk za novog igrača    |
| 6    | `0006.mp3`      | Pobjednička melodija    |
| 7    | `0007.mp3`      | Zvuk pritiska tipke     |
| 8    | `0008.mp3`      | Upozorenje nepostavljene igre |
| 21   | `0021.mp3`      | Snimka "Igrač 1"        |
| 22   | `0022.mp3`      | Snimka "Igrač 2"        |
| 23   | `0023.mp3`      | Snimka "Igrač 3"        |
| 24   | `0024.mp3`      | Snimka "Igrač 4"        |
| 25   | `0025.mp3`      | Snimka "Igrač 5"        |
| 26   | `0026.mp3`      | Snimka "Igrač 6"        |

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

