# Connections and MP3 files

This document extracts the section from the README describing pin layout and MP3 file names for easier reference.

## 🪛 Connections

Note: pins **20** (SDA) and **21** (SCL) are reserved for the LCD I2C bus and must not be used for buttons or other peripherals.

### Buttons

| Pins | Function |
|--------|------------------|
| 28–46  | Game selection (even pins) |
| 23–33  | Player count (odd pins) |
| 50, 52 | Rules (Double OUT / IN) |

### LED lamps (via UCN5821)

| Pin | Function |
|-----|----------|
| 2   | DATA |
| 3   | CLOCK |
| 4   | LATCH |

### MAX7219 display

| Pin | Function |
|-----|----------|
| 9   | DIN |
| 10  | CLK |
| 11  | CS |

### LCD (I2C)

| Pin | Function |
|-----|----------|
| 20  | SDA |
| 21  | SCL |
|     | I2C address 0x27 |

### Dartboard (detection)

- **Active sensor pins:** A0, A1, A2, A3, A4, A5, A6, A7, 53, 51, 49, 47, 45, 43, 41, 39
- **Common pins:** A15 (`COM_A15`), A14 (`COM_A14`), A12 (`COM_A12`), A13 (`COM_A13`)
- **Microphone for misses:** A8 (`PIN_MIKROFON`)


A full list of MP3 files is available in [MP3_SOUND_LIST.md](MP3_SOUND_LIST.md).

