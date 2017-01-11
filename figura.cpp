#include "figura.h"
#include <cstdlib>

Figura::Figura() {
  przesuniecie_x = 0;
  przesuniecie_y = 0;
}

char Figura::PobierzZnak() {
  return znak;
}

void Figura::UstawZnak(char znak_) {
  znak = znak_;
}

void Figura::UstawWysokoscWypelnienia(int liczba_wierszy) {
  wypelnienie = new char *[liczba_wierszy];
}

void Figura::UstawDlugoscWypelnienia(int wiersz, int liczba_kolumn) {
  wypelnienie[wiersz] = new char[liczba_kolumn];
}

char Figura::PobierzZnakKomorki(int wiersz, int kolumna) {
  return wypelnienie[wiersz][kolumna];
}

void Figura::UstawZnakKomorki(int wiersz, int kolumna, char znak) {
  wypelnienie[wiersz][kolumna] = znak;
}

int Figura::PobierzWysokosc() {
  return wysokosc;
}

void Figura::UstawWysokosc(int wysokosc_) {
  wysokosc = wysokosc_;
}

int Figura::PobierzPrzesuniecieX() {
  return przesuniecie_x;
}

int Figura::PobierzPrzesuniecieY() {
  return przesuniecie_y;
}

void Figura::UstawSrodekX(int kolumny) {
  srodek_x = kolumny;
}

void Figura::UstawSrodekY(int wiersze) {
  srodek_y = wiersze;
}

int Figura::PobierzZaczepienieX() {
  return srodek_x - wysokosc / 2;
}

int Figura::PobierzZaczepienieY() {
  return srodek_y + wysokosc / 2;
}

void Figura::PrzesunLewo() {
  przesuniecie_x--;
}

void Figura::PrzesunPrawo() {
  Figura::przesuniecie_x++;
}

void Figura::PrzesunDol() {
  przesuniecie_y++;
}

void Figura::PrzesunGora() {
  przesuniecie_y--;
}

void Figura::Powieksz() {
  wysokosc++;
};

void Figura::Pomniejsz() {
  wysokosc--;
};

bool Figura::JestNaPrzekatnej(int wiersz, int kolumna) {
  //zeby komorka byla na przekatnej musi zajsc: |y-y0| == |x-x0|
  return abs(wiersz - srodek_y) == abs(kolumna - srodek_x);
}

bool Figura::JestWZakresieUzytkownika(int wiersz) {
  return abs(wiersz - srodek_y) < wysokosc / 2 + 1;
}

//test
