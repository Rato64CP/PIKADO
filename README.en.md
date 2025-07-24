# Pikado Electronic System (Arduino + Dartboard)

This project detects hits on an electronic dartboard using an **Arduino Mega 2560**. It supports multiple games and players, LED indication and optional rules such as Double IN and Double OUT. A microphone detects misses while buttons select the game, number of players and rules.

---

## 🎯 Supported games

| Game | Description |
|-------------|------|
| **301 / 501 / 701** | Classic countdown games to zero. Double IN and Double OUT can be enabled. |
| **Shanghai** | You shoot the number of the current round (1–20). Only the targeted number counts. Hitting S+D+T in the same round wins automatically. |
| **Roulette** | Each player gets a random number that only they may hit. After 5 rounds the player with the highest score wins. |
| **Hangman** | Players try to hit all numbers without repeating. 6 mistakes means elimination. |
| **Cricket** | Numbers 15–20 and bull (25) are hit. Each must be hit 3 times. Extra hits score points. |
| **3-in-line** | Win by hitting 3 consecutive numbers (e.g. 8‑9‑10) in any order. |

---

## ⚙️ Features

- Detection of all zones on the board (Single, Double, Triple)
- Miss detection via microphone (every miss counts as a thrown dart)
- Buttons for selecting game, player count and rules
- LED indication for every selection
- Modular game structure
- Double IN and Double OUT as optional rules
- Serial output of results and messages
- Score display on a MAX7219 display for all games
- In **3-in-line** the display shows the length of the current streak and blinks when a new record is reached
- Detects a dart throw before selecting a game or player and plays a warning sound
- Recorded voice calls for players ("Player 1", "Player 2"...)
- Voice announcement of the hit field (uses mp3 files starting from `0100.mp3`)
- Automatically enters sleep mode after 10 minutes of inactivity (display blinks every 5 s)
- Error indication by blinking the **RESET** button LED

---

## 🧰 Hardware

- **Arduino Mega 2560**
- Dartboard connected to digital and analog pins
- Microphone on A0 for miss detection (`THRESHOLD_PROMASAJ` in `config.h`)
- Selection buttons wired to digital pins (pull-up)
- LED lamps driven via UCN5821 shift register
- MAX7219 6-module seven segment display for scores
- JQ6500 MP3 module for sounds (connected to Serial1)
- LCD via I2C on SDA=20 and SCL=21

---

## 🛠️ Configuration

Some game rules are defined via buttons or in `config.h`:

- `DOUBLE_OUT` – when `true`, the game can end only on a Double field
- `DOUBLE_IN` – when `true`, the player must start scoring with a Double field

The *bounce-out* rule in **301** and **501** is always active and needs no extra setting.

---

## 🔧 Building

1. Open `PIKADO.ino` in the Arduino IDE or CLI
2. Select the **Arduino Mega 2560** board
3. Install the **LedControl** library (for MAX7219)
4. Install the **LiquidCrystal_I2C** library (for the LCD)
5. Compile and upload to the device

---
A detailed list of connections and MP3 files can be found in [CONNECTIONS_AND_MP3.md](docs/CONNECTIONS_AND_MP3.md).

---

## 🧪 Usage

1. After uploading, open the **Serial Monitor at 9600 baud**
2. Choose the game using the buttons
3. For **301** and **501**, you can then press the **DOUBLE IN** and/or **DOUBLE OUT** buttons. Their LEDs will stay on and the rule applies for the whole game. Pressing them during a game has no effect – you must *RESET* to choose again.
4. Then select the number of players
5. LEDs show the current selections
6. The game starts automatically
7. Serial monitor and LCD show all hits, scores and status

For a more detailed game flow see [GAME_FLOW.md](docs/GAME_FLOW.md).

---

## 📌 Note

The system is modular so new games and features can easily be added. It can be expanded with an OLED/TFT display or communication with a Raspberry Pi.

## ❗ Errors and signalling

Errors can be reported with `signalGreska()`. While active, the **RESET** button LED blinks so the user knows to restart or check the system.
