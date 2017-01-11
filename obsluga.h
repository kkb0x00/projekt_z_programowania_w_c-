#ifndef PROJEKT_OBSLUGA_H
#define PROJEKT_OBSLUGA_H
#include "figura.h"
#include <windows.h>

#define KLAWISZ_GORA 72
#define KLAWISZ_DOL 80
#define KLAWISZ_LEWO 75
#define KLAWISZ_PRAWO 77

class ObslugaProgramu {
 private:
  bool kontynuuj;
  int wysokosc_terminala;
  int szerokosc_terminala;
  Figura *figura;
  char lewo, prawo, gora, dol, powieksz, pomniejsz, koniec;
  HANDLE oknoProgramu;

 public:
  ObslugaProgramu();
  ~ObslugaProgramu();

  HANDLE PobierzIdentyfikatorOkna();
  void PokazMenu(); 
  int PobierzWysokosc();
  int UstawWysokosc(HANDLE);
  int UstawSzerokosc(HANDLE);
  void CzyscEkran(HANDLE);
  void UstawZnak();
  void UkryjZnakZachety(HANDLE);
  void UstawWysokoscPoczatkowa();
  void WypiszFigure();
  void CzytajKlawisz();
  void Odpal();
};

#endif //PROJEKT_OBSLUGA_H
