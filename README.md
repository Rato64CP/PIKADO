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

## Compiling the Sketch

1. Open `PIKADO.ino` in the Arduino IDE or the Arduino CLI.
2. Select **Arduino Mega 2560** as the target board.
3. No external libraries are required – only the standard Arduino core is used.
4. Compile and upload the sketch to the board.

## Wiring

### Buttons

The buttons are read using the internal pull‑ups on the Mega. Connect one side of
each push button to ground and the other side to the following pins:

```
22–31  Game selection
32–37  Player count
38–39  Other options
```

### LEDs

LEDs (via a shift register) are driven from these pins:

```
DATA  -> pin 5
CLOCK -> pin 6
LATCH -> pin 7
```

## Usage Example

After uploading, open the serial monitor at 9600 baud. The sketch will prompt
you to select a game and the number of players using the buttons. The LEDs will
light up according to the current selections and the game can then begin.
