#pragma once
#include <Arduino.h>

enum Tipka {
  IGRA_301 = 0,
  IGRA_501,
  IGRA_SHANGHAI,
  IGRA_HANGMAN,
  IGRA_ROULETTE,
  IGRA_SCRAM,
  IGRA_CRICKET,
  IGRA_3INLINE,
  IGRA_NEW_PLAYER,
  IGRA_RESET,

  IGRAC_1,
  IGRAC_2,
  IGRAC_3,
  IGRAC_4,
  IGRAC_5,
  IGRAC_6,

  OSTALO_OUT_TEAM,
  OSTALO_IN_CUTTHROAT,

  BROJ_TIPKI
};

void inicijalizirajTipke();
void ocitajTipke();
bool tipkaStisnuta(int indeks);