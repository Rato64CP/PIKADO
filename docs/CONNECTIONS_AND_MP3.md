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

This table shows which pin is connected to each dartboard target and the common line it belongs to.

| Target           | Active pin | Common pin |
|------------------|-----------:|------------|
| **Common A15**   |            |            |
| Triple 12        | 41         | A15        |
| Double 12        | A7         | A15        |
| Single 12        | A6         | A15        |
| Triple 9         | 43         | A15        |
| Double 9         | A5         | A15        |
| Single 9         | A4         | A15        |
| Triple 14        | 45         | A15        |
| Double 14        | A3         | A15        |
| Single 14        | A2         | A15        |
| Triple 11        | 47         | A15        |
| Double 11        | A1         | A15        |
| Single 11        | A0         | A15        |
| Triple 8         | 49         | A15        |
| Double 8         | 35         | A15        |
| Single 8         | 37         | A15        |
| **Common A14**   |            |            |
| Triple 4         | 41         | A14        |
| Double 4         | A7         | A14        |
| Single 4         | A6         | A14        |
| Triple 18        | 43         | A14        |
| Double 18        | A5         | A14        |
| Single 18        | A4         | A14        |
| Triple 1         | 45         | A14        |
| Double 1         | A3         | A14        |
| Single 1         | A2         | A14        |
| Triple 20        | 47         | A14        |
| Double 20        | A1         | A14        |
| Single 20        | A0         | A14        |
| Triple 5         | 49         | A14        |
| Double 5         | 35         | A14        |
| Single 5         | 37         | A14        |
| 25 (Single)      | 39         | A14        |
| **Common A13**   |            |            |
| Triple 2         | 41         | A13        |
| Double 2         | A7         | A13        |
| Single 2         | A6         | A13        |
| Triple 15        | 43         | A13        |
| Double 15        | A5         | A13        |
| Single 15        | A4         | A13        |
| Triple 10        | 45         | A13        |
| Double 10        | A3         | A13        |
| Single 10        | A2         | A13        |
| Triple 6         | 47         | A13        |
| Double 6         | A1         | A13        |
| Single 6         | A0         | A13        |
| Triple 13        | 49         | A13        |
| Double 13        | 35         | A13        |
| Single 13        | 37         | A13        |
| 25 (Double)      | 39         | A13        |
| **Common A12**   |            |            |
| Triple 16        | 41         | A12        |
| Double 16        | A7         | A12        |
| Single 16        | A6         | A12        |
| Triple 7         | 43         | A12        |
| Double 7         | A5         | A12        |
| Single 7         | A4         | A12        |
| Triple 19        | 45         | A12        |
| Double 19        | A3         | A12        |
| Single 19        | A2         | A12        |
| Triple 3         | 47         | A12        |
| Double 3         | A1         | A12        |
| Single 3         | A0         | A12        |
| Triple 17        | 49         | A12        |
| Double 17        | 35         | A12        |
| Single 17        | 37         | A12        |


A full list of MP3 files is available in [MP3_SOUND_LIST.md](MP3_SOUND_LIST.md).

