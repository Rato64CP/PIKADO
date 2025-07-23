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

struct ZvukMeta { const char* naziv; uint16_t index; };

static const ZvukMeta zvukoviMeta[] = {
    {"Triple 17", 100}, {"Double 17", 101}, {"Simple 17", 102},
    {"Triple 3", 103},  {"Double 3", 104},  {"Simple 3", 105},
    {"Triple 19", 106}, {"Double 19", 107}, {"Simple 19", 108},
    {"Triple 7", 109},  {"Double 7", 110},  {"Simple 7", 111},
    {"Triple 16", 112}, {"Double 16", 113}, {"Simple 16", 114},
    {"Triple 6", 115},  {"Double 6", 116},  {"Simple 6", 117},
    {"Triple 10",118},  {"Double 10",119}, {"Simple 10",120},
    {"Triple 15",121}, {"Double 15",122}, {"Simple 15",123},
    {"Triple 2",124},  {"Double 2",125},  {"Simple 2",126},
    {"25 (Double)",127},
    {"Triple 13",128}, {"Double 13",129}, {"Simple 13",130},
    {"Triple 8",131},  {"Double 8",132},  {"Simple 8",133},
    {"Triple 14",134}, {"Double 14",135}, {"Simple 14",136},
    {"Triple 9",137},  {"Double 9",138},  {"Simple 9",139},
    {"Triple 11",140},{"Double 11",141},{"Simple 11",142},
    {"Triple 12",143},{"Double 12",144},{"Simple 12",145},
    {"Triple 5",146}, {"Double 5",147}, {"Simple 5",148},
    {"Triple 20",149},{"Double 20",150},{"Simple 20",151},
    {"Triple 1",152}, {"Double 1",153}, {"Simple 1",154},
    {"Triple 18",155},{"Double 18",156},{"Simple 18",157},
    {"Triple 4",158}, {"Double 4",159},
    {"25 (Simple)",160},
    {"Simple 4",161}
};

void svirajZvukMete(const String& nazivMete) {
    for (const auto& zvuk : zvukoviMeta) {
        if (nazivMete == zvuk.naziv) {
            mp3.play(zvuk.index);
            return;
        }
    }
}
