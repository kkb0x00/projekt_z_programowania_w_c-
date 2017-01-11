#ifndef PROJEKT_FIGURA_H
#define PROJEKT_FIGURA_H

class Figura {
 private:
  char znak;
  char **wypelnienie;
  int wysokosc;
  int przesuniecie_x, przesuniecie_y;
  int srodek_x, srodek_y;

 public:
  Figura();

  char PobierzZnak();
  void UstawZnak(char);
  void UstawWysokoscWypelnienia(int);
  void UstawDlugoscWypelnienia(int, int);
  char PobierzZnakKomorki(int, int);
  void UstawZnakKomorki(int, int, char);
  int PobierzWysokosc();
  void UstawWysokosc(int);
  int PobierzPrzesuniecieX();
  int PobierzPrzesuniecieY();
  void UstawSrodekX(int);
  void UstawSrodekY(int);
  int PobierzZaczepienieX();
  int PobierzZaczepienieY();
  void PrzesunLewo();
  void PrzesunPrawo();
  void PrzesunDol();
  void PrzesunGora();
  void Powieksz();
  void Pomniejsz();
  bool JestNaPrzekatnej(int, int);
  bool JestWZakresieUzytkownika(int);
};

#endif //PROJEKT_FIGURA_H

//test
