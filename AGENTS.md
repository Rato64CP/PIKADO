# Agents Overview – Pikado Elektronski Sustav

Ova datoteka opisuje uloge (agents) unutar sustava elektroničkog pikada, kako bi se lakše razumjelo tko (koji dio koda) što radi. Svaki "agent" predstavlja logičku odgovornost – bilo hardversku, softversku ili korisničku.

---

## 🧠 1. Game Engine Agent (`game.cpp`, `game_*.cpp`)

- **Odgovornost:** Glavna logika vođenja igre (pravila, redoslijed, pobjede)
- **Područje:** `game_301.cpp`, `game_501.cpp`, itd.
- **Upravljanje igračima:** Bodovi, prelazak na sljedećeg, pobjednik
- **Komunikacija:** Šalje poruke serijskom sučelju, ažurira LED/segmentne prikaze

---

## 🎮 2. Input Agent (`buttons.cpp`)

- **Odgovornost:** Čita sve fizičke tipke (gumbi) s ploče
- **Područje:** izbor igre, broj igrača, posebna pravila (Double In/Out)
- **Tehnika:** INPUT_PULLUP logika – tipke idu na masu
- **Tipke:** 22–39 (igra, igrači, IN/OUT)

---

## 💡 3. Output Agent (`zaruljice.cpp`)

- **Odgovornost:** Upravljanje žaruljicama (LED) povezanima s tipkama
- **Hardver:** UCN5821 shift register
- **Područje:** prikazuje koji su izbori trenutno aktivni
- **Pinovi:** DATA (5), CLOCK (6), LATCH (7)

---

## 🎯 4. Dartboard Detection Agent (`detection.cpp`)

- **Odgovornost:** Očitava gdje je strelica pogodila
- **Metoda:** Matrica pogođenih pinova (16x4)
- **Detekcija promašaja:** preko mikrofona na A0 (analogno očitanje)
- **Povezivanje s igrom:** Vraća ime pogođene mete (npr. “Double 20”)

---

## ⚙️ 5. Configuration Agent (`config.h`)

- **Odgovornost:** Centralno mjesto za definiranje konstanti i globalnih postavki
- **Postavke:** BOUNCE_OUT, DOUBLE_OUT, DOUBLE_IN
- **Povezuje se:** uključuje se u sve glavne module

---

## 📺 6. Display Agent (planirano)

- **Odgovornost:** Prikaz bodova i statusa na segmentnim LED displayima
- **Tehnologija:** MAX7219, LedControl ili MD_MAX72XX
- **Prikaz:** Bodovi svakog igrača, status igre, redoslijed

---

## 👤 7. User Agent

- **Fizički korisnik:** igrači koji pritišću tipke i bacaju strelice
- **Interakcija s hardverom:** tipke, vizualni prikaz (LED), serijski ispis
- **Odabir:** igre, igrača, pravila

---

## 📡 8. Serial Monitor Agent (debug UI)

- **Odgovornost:** Ispisuje poruke za korisnika i razvoj
- **Svrha:** status, pogodak, pobjeda, greška
- **Koristi se:** u svim igrama i funkcijama (Serial.println)

---

## 🛠️ 9. Setup Agent (`PIKADO.ino`)

- **Odgovornost:** Glavni ulaz, inicijalizira sve agente
- **Logika:** bira igru, broj igrača, pravila
- **Pokreće:** `pokreniAktivnuIgru()` i zatim prepušta tok

---

Ova arhitektura omogućuje jasan razdjelj funkcionalnosti, modularnost i lako nadogradive segmente (nove igre, ekran, Wi-Fi).
