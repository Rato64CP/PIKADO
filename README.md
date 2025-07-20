# Pikado Elektronski Sustav (Arduino + Dartboard)

Ovaj projekt detektira pogođene mete na elektronskom pikado aparatu koristeći **Arduino Mega 2560**.
Podržava više igara, više igrača, LED indikaciju i dodatna pravila poput Double IN i Double OUT.
Koristi mikrofon za detekciju promašaja i tipke za odabir igre, broja igrača i pravila.

---

## 🎯 Podržane igre

| Igra        | Opis |
|-------------|------|
| **301 / 501** | Klasične igre odbrojavanja do nule. Moguće uključiti Double IN i Double OUT. |
| **Shangai** | Gađa se broj runde (1–20). Boduju se samo pogođeni ciljani broj. Shanghai (S+D+T) donosi automatsku pobjedu. |
| **Scram**   | 2 faze: blocker zaključava brojeve, scorer skuplja bodove. Zatim se zamijene uloge. |
| **Roulette** | Svakom igraču se dodijeli nasumični broj koji samo on smije pogađati. Pobjednik je onaj s najviše bodova nakon 5 rundi. |
| **Hangman** | Igrači pokušavaju pogoditi sve brojeve bez ponavljanja. 6 grešaka = ispadanje. |
| **Cricket** | Pogađaju se brojevi 15–20 i bull (25). Svaki broj se mora pogoditi 3 puta. Višak pogodaka donosi bodove. |
| **3-in-line** | Pobjeda ako igrač pogodi 3 uzastopna broja (npr. 8-9-10), redoslijed gađanja nije bitan. |

---

## ⚙️ Funkcionalnosti

- Detekcija svih zona na ploči (Simple, Double, Triple)
- Detekcija promašaja pomoću mikrofona
- Tipke za odabir igre, broja igrača i pravila
- LED indikacija za sve odabire
- Modularna struktura igara
- Double IN i Double OUT kao opcionalna pravila
- Serijski ispis rezultata i poruka

---

## 🧰 Hardver

- **Arduino Mega 2560**
- Dart ploča spojena na digitalne i analogne pinove
- Mikrofon spojen na A0
- Tipke za odabir spojene na digitalne pinove (pull-up)
- LED žaruljice upravljane preko UCN5821 (shift register)

---

## 🛠️ Konfiguracija

Neka pravila igre se definiraju preko tipki ili u `config.h`:

- `BOUNCE_OUT` – kada je `true`, prelazak ispod nule poništava potez
- `DOUBLE_OUT` – kada je `true`, igru je moguće završiti samo Double poljem
- `DOUBLE_IN` – kada je `true`, igrač mora započeti pogodak s Double da bi bodovi vrijedili

---

## 🔧 Kompajliranje

1. Otvori `PIKADO.ino` u Arduino IDE ili CLI
2. Odaberi ploču **Arduino Mega 2560**
3. Nisu potrebne dodatne biblioteke
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

---

## 🧪 Korištenje

1. Nakon učitavanja, otvori **Serial Monitor na 9600 baud**
2. Odaberi igru i broj igrača pomoću tipki
3. LED žaruljice će pokazati trenutne odabire
4. Igra započinje automatski
5. Serijski monitor prikazuje sve pogođaje, bodove i status

---

## 📌 Napomena

Ovaj sustav je dizajniran modularno tako da je lako dodavati nove igre i funkcionalnosti. Može se nadograditi s prikazom na OLED/TFT ili komunikacijom s Raspberry Pi.

