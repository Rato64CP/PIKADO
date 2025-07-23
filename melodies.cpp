#include "melodies.h"
#include "jq6500.h"
#include "config.h"

static JQ6500 mp3(Serial1);

void inicijalizirajZvuk() { mp3.begin(); }

void svirajUvodnuMelodiju() { mp3.play(1); }
void svirajZvukBacanja() { mp3.play(2); }
void svirajZvukPromasaja() { mp3.play(3); }
void svirajZvukVadenja() { mp3.play(4); }
void svirajZvukPobjede() { mp3.play(6); }
void svirajZvukTipke() { mp3.play(7); }
void svirajZvukNepostavljenaIgra() { mp3.play(8); }
void svirajZvukBust() { mp3.play(9); }

void svirajImeIgraca(uint8_t index) {
    if (index < 6) {
        mp3.play(20 + index);
    }
}
