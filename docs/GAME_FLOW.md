# Game flow

This document describes the generic course of a game on the electronic dartboard. It is useful for understanding how the individual modules interact during play.

1. **Device start-up** – After power-on the modules are initialised: buttons, LED lamps, target detection, sounds and display.
2. **Choosing the game** – Press the buttons to select the desired game (301, 501, Shanghai…). LED lamps indicate the current selection.
3. **Choosing the number of players** – Use the next group of buttons to set the number of participants (1–6). Player names are shown on the display and an audio announcement is played.
4. **Extra rules** – For games 301/501/701 you can enable *Double IN* and *Double OUT*. Selected options are indicated by the corresponding LEDs.
5. **Starting a round** – Once all options are set, pressing **NEW PLAYER** starts the game. The active player is marked by a blinking lamp.
6. **Throwing darts** – Detection of hits or misses runs in real time. The result is recorded and the appropriate sound or announcement is played.
7. **End of turn** – When a player has thrown all darts, the score is displayed and `krajPoteza()` is called. The player removes the darts and confirms by pressing **NEW PLAYER**.
8. **Next player** – The function `sljedeciIgrac()` activates the next participant and the procedure repeats from step 6. All lamps and announcements adjust to the new player.
9. **End of game** – Depending on the game rules (`obradiPogodak_*` functions), when the win conditions are met, `zavrsiIgru()` is called. A victory melody is played and a message is shown on the display.
10. **New game or reset** – At this point you can press **NEW PLAYER** again for a new game with the same settings or **RESET** to return to the menu and make a new selection.

This flow applies to all supported games, while each has its specific rules described in separate files such as `game_301.cpp` or `game_cricket.cpp`.
