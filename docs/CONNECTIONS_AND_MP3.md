# Connections and MP3 files

This document extracts the section from the README describing pin layout and MP3 file names for easier reference.

## 🪛 Connections

Note: pins **20** (SDA) and **21** (SCL) are reserved for the LCD I2C bus and must not be used for buttons or other peripherals.

### Buttons

| Pins | Function |
|--------|------------------|
| 28–46  | Game selection (even pins) |
| 27–37  | Player count (odd pins) |
| 50, 52 | Rules (Double OUT / IN) |

### LED lamps (via UCN5821)

| Pin | Function |
|-----|----------|
| 5   | DATA |
| 6   | CLOCK |
| 7   | LATCH |

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

- **Active sensor pins:** A4, A5, A6, A7, A8, A9, A10, A11, 53, 51, 49, 47, 45, 43, 41, 39
- **Common pins:** A15 (`COM_45`), A14 (`COM_47`), A12 (`COM_A1`), A13 (`COM_A2`)
- **Microphone for misses:** A0 (`PIN_MIKROFON`)

### JQ6500 MP3 module

The module is connected to the Arduino via **Serial1** (TX1=18, RX1=19). It stores all MP3 files for sound effects.

#### File names

Files must have a four-digit prefix to match the numbering used by `mp3.play()`. Recommended names are:

| No. | File | Description |
|-----:|-----------------|-------------------------|
| 1    | `0001.mp3`      | Intro melody |
| 2    | `0002.mp3`      | Dart throw sound |
| 3    | `0003.mp3`      | Miss sound |
| 4    | `0004.mp3`      | Dart removal sound |
| 6    | `0006.mp3`      | Victory melody |
| 7    | `0007.mp3`      | Button press sound |
| 8    | `0008.mp3`      | Warning: game not selected |
| 9    | `0009.mp3`      | "Bust" sound |
| 21   | `0021.mp3`      | "Player 1" recording |
| 22   | `0022.mp3`      | "Player 2" recording |
| 23   | `0023.mp3`      | "Player 3" recording |
| 24   | `0024.mp3`      | "Player 4" recording |
| 25   | `0025.mp3`      | "Player 5" recording |
| 26   | `0026.mp3`      | "Player 6" recording |
| 30   | `0030.mp3`      | "Roulette start" |
| 31   | `0031.mp3`      | "Target is" announcement |
| 32   | `0032.mp3`      | "Target hit" |
| 33   | `0033.mp3`      | "Roulette over" |
| 34   | `0034.mp3`      | "Shanghai" win |
| 35   | `0035.mp3`      | "Try again" message |

### Files for individual targets

These recordings announce the specific field hit. Each file corresponds to one board zone.

| No. | File | Description |
|-----:|---------|-----------|
| 100 | `0100.mp3` | Triple 17 |
| 101 | `0101.mp3` | Double 17 |
| 102 | `0102.mp3` | Single 17 |
| 103 | `0103.mp3` | Triple 3 |
| 104 | `0104.mp3` | Double 3 |
| 105 | `0105.mp3` | Single 3 |
| 106 | `0106.mp3` | Triple 19 |
| 107 | `0107.mp3` | Double 19 |
| 108 | `0108.mp3` | Single 19 |
| 109 | `0109.mp3` | Triple 7 |
| 110 | `0110.mp3` | Double 7 |
| 111 | `0111.mp3` | Single 7 |
| 112 | `0112.mp3` | Triple 16 |
| 113 | `0113.mp3` | Double 16 |
| 114 | `0114.mp3` | Single 16 |
| 115 | `0115.mp3` | Triple 6 |
| 116 | `0116.mp3` | Double 6 |
| 117 | `0117.mp3` | Single 6 |
| 118 | `0118.mp3` | Triple 10 |
| 119 | `0119.mp3` | Double 10 |
| 120 | `0120.mp3` | Single 10 |
| 121 | `0121.mp3` | Triple 15 |
| 122 | `0122.mp3` | Double 15 |
| 123 | `0123.mp3` | Single 15 |
| 124 | `0124.mp3` | Triple 2 |
| 125 | `0125.mp3` | Double 2 |
| 126 | `0126.mp3` | Single 2 |
| 127 | `0127.mp3` | 25 (Double) |
| 128 | `0128.mp3` | Triple 13 |
| 129 | `0129.mp3` | Double 13 |
| 130 | `0130.mp3` | Single 13 |
| 131 | `0131.mp3` | Triple 8 |
| 132 | `0132.mp3` | Double 8 |
| 133 | `0133.mp3` | Single 8 |
| 134 | `0134.mp3` | Triple 14 |
| 135 | `0135.mp3` | Double 14 |
| 136 | `0136.mp3` | Single 14 |
| 137 | `0137.mp3` | Triple 9 |
| 138 | `0138.mp3` | Double 9 |
| 139 | `0139.mp3` | Single 9 |
| 140 | `0140.mp3` | Triple 11 |
| 141 | `0141.mp3` | Double 11 |
| 142 | `0142.mp3` | Single 11 |
| 143 | `0143.mp3` | Triple 12 |
| 144 | `0144.mp3` | Double 12 |
| 145 | `0145.mp3` | Single 12 |
| 146 | `0146.mp3` | Triple 5 |
| 147 | `0147.mp3` | Double 5 |
| 148 | `0148.mp3` | Single 5 |
| 149 | `0149.mp3` | Triple 20 |
| 150 | `0150.mp3` | Double 20 |
| 151 | `0151.mp3` | Single 20 |
| 152 | `0152.mp3` | Triple 1 |
| 153 | `0153.mp3` | Double 1 |
| 154 | `0154.mp3` | Single 1 |
| 155 | `0155.mp3` | Triple 18 |
| 156 | `0156.mp3` | Double 18 |
| 157 | `0157.mp3` | Single 18 |
| 158 | `0158.mp3` | Triple 4 |
| 159 | `0159.mp3` | Double 4 |
| 160 | `0160.mp3` | 25 (Single) |
| 161 | `0161.mp3` | Single 4 |
