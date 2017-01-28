#include "obsluga.h"
#include "figura.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

#undef max

using namespace std;

ObslugaProgramu::ObslugaProgramu() {
  oknoProgramu = PobierzIdentyfikatorOkna();
  wysokosc_terminala = this->UstawWysokosc(oknoProgramu);
  szerokosc_terminala = this->UstawSzerokosc(oknoProgramu);
  this->UkryjZnakZachety(oknoProgramu);
  kontynuuj = true;
  figura = new Figura();
  lewo = KLAWISZ_LEWO, prawo = KLAWISZ_PRAWO, gora = KLAWISZ_GORA, dol = KLAWISZ_DOL;
  powieksz = '+', pomniejsz = '-';
  koniec = 'q';
}

ObslugaProgramu::~ObslugaProgramu() {
  delete figura;
}

HANDLE ObslugaProgramu::PobierzIdentyfikatorOkna() {
  return GetStdHandle(STD_OUTPUT_HANDLE);
}

int ObslugaProgramu::PobierzWysokosc() {
  return wysokosc_terminala;
}

int ObslugaProgramu::UstawWysokosc(HANDLE okno) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(okno, &csbi);

  return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int ObslugaProgramu::UstawSzerokosc(HANDLE okno) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(okno, &csbi);
  return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void ObslugaProgramu::CzyscEkran(HANDLE okno) {
  DWORD n;
  DWORD rozmiar;
  COORD wspolrzedne = { 0 };
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(okno, &csbi);
  rozmiar = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter(okno, TEXT(' '), rozmiar, wspolrzedne, &n);
  GetConsoleScreenBufferInfo(okno, &csbi);
  FillConsoleOutputAttribute(okno, csbi.wAttributes, rozmiar, wspolrzedne, &n);
  SetConsoleCursorPosition(okno, wspolrzedne);
}

void ObslugaProgramu::PokazMenu() {
  cout << "Do poruszania uzyj strzalek, + i - do zwieszkania/zmniejszania." << endl;
  cout << "Do wyjscia z programu nacisnij litere 'q' (jak quit)." << endl;
}

void ObslugaProgramu::UstawZnak() {
  char znak;

  cout << "Podaj znak z jakiego będzie zbudowana figura. : ";

  while (cin >> znak && !isgraph(znak)) {
    cout << "Podales zly znak. Daj taki, ktory da sie wyswietlic. :";
  }

  figura->UstawZnak(znak);
}

void ObslugaProgramu::UkryjZnakZachety(HANDLE okno) {
  CONSOLE_CURSOR_INFO info;
  GetConsoleCursorInfo(okno, &info);
  info.bVisible = false;
  SetConsoleCursorInfo(okno, &info);
}

void ObslugaProgramu::UstawWysokoscPoczatkowa() {
  unsigned int wysokosc_poczatkowa;

  cout << "Podaj jakiej wysokosci bedzie figura, maksymalna wysokosc to rozmiar ekranu, czyli " << wysokosc_terminala << ". : ";

  while (!(cin >> wysokosc_poczatkowa) || wysokosc_poczatkowa > PobierzWysokosc() || !wysokosc_poczatkowa) {
    cout << "Nieodpowiednia wysokosc, podaj nie wieksza wysokosc niz terminal. : ";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  figura->UstawWysokosc(wysokosc_poczatkowa);
  this->CzyscEkran(oknoProgramu);
}

void ObslugaProgramu::WypiszFigure() {
  wysokosc_terminala = this->UstawWysokosc(oknoProgramu);
  szerokosc_terminala = this->UstawSzerokosc(oknoProgramu);

  figura->UstawSrodekX(szerokosc_terminala / 2 + figura->PobierzPrzesuniecieX());
  figura->UstawSrodekY(wysokosc_terminala / 2 + figura->PobierzPrzesuniecieY());
  figura->UstawWysokoscWypelnienia(wysokosc_terminala);

  for (int wiersz = 0; wiersz < wysokosc_terminala; wiersz++) {
    figura->UstawDlugoscWypelnienia(wiersz, szerokosc_terminala);

    for (int kolumna = 0; kolumna < szerokosc_terminala; kolumna++) {
      if (figura->JestWZakresieUzytkownika(wiersz) && figura->JestNaPrzekatnej(wiersz, kolumna)) {
        figura->UstawZnakKomorki(wiersz, kolumna, figura->PobierzZnak());
      }
      else {
        figura->UstawZnakKomorki(wiersz, kolumna, ' ');
      }
    }
  }
  
  LockWindowUpdate(GetConsoleWindow());
  CzyscEkran(oknoProgramu);
  
  for (int i = 0; i < wysokosc_terminala; ++i) {
    for (int j = 0; j < szerokosc_terminala; ++j) {
      cout << figura->PobierzZnakKomorki(i, j);
    }
  }
  
  LockWindowUpdate(NULL);
}

void ObslugaProgramu::CzytajKlawisz() {
  if (_kbhit()) {
    char opcja = _getch();

    if (opcja == lewo && figura->PobierzZaczepienieX() > 0) {
      figura->PrzesunLewo();
    }
    if (opcja == prawo && figura->PobierzZaczepienieX() < szerokosc_terminala - 1) {
      figura->PrzesunPrawo();
    }

    if (opcja == gora && figura->PobierzZaczepienieY() > 0) {
      figura->PrzesunGora();
    }
    if (opcja == dol && figura->PobierzZaczepienieY() < wysokosc_terminala - 1) {
      figura->PrzesunDol();
    }

    if (opcja == powieksz && figura->PobierzWysokosc() < wysokosc_terminala) {
      figura->Powieksz();
    }
    if (opcja == pomniejsz && figura->PobierzWysokosc() > 1) {
      figura->Pomniejsz();
    }
    if (opcja == koniec) {
      kontynuuj = false;
    }
  }
}

void ObslugaProgramu::Odpal() {
  PokazMenu();
  UstawZnak();
  UstawWysokoscPoczatkowa();

  while (kontynuuj) {
    WypiszFigure();
    CzytajKlawisz();
  }
}
