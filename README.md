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
- LCD preko I2C na pinovima SDA=20 i SCL=21

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
4. Instaliraj Arduino biblioteku **LiquidCrystal_I2C** (za LCD)
5. Kompajliraj i učitaj na uređaj

---
Detaljan popis priključaka i MP3 datoteka nalazi se u [POVEZIVANJE_I_MP3.md](POVEZIVANJE_I_MP3.md).


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
7. Serijski monitor i LCD prikazuje sve pogođaje, bodove i status

Za detaljniji opis toka igre pogledajte datoteku [TIJEK_IGARA.md](TIJEK_IGARA.md).

---

## 📌 Napomena

Ovaj sustav je dizajniran modularno tako da je lako dodavati nove igre i funkcionalnosti. Može se nadograditi s prikazom na OLED/TFT ili komunikacijom s Raspberry Pi.

