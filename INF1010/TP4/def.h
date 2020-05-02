/*
 * Titre : def.h - Travail Pratique #4 - Programmation Orientee Objet
 * Date : 27 Fevrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef DEF_H
#define DEF_H

#include <iomanip>
#include <iostream>

/** ----------------------------------------------------------------------- **/
struct Coordonnees {
  int x;
  int y;
};
/** ----------------------------------------------------------------------- **/
enum class Direction { first_ = -1, Right, Left, last_ };
/** Classe Couleur est définie pour les tests! Veuillez ne pas la modifier! **/
/** ----------------------------------------------------------------------- **/
class Couleur {
public:
  Couleur() : couleur_("Noir"){};
  Couleur(std::string couleur) : couleur_(couleur){};
  void operator=(const Couleur &couleur) { couleur_ = couleur.couleur_; }
  bool operator==(const std::string &couleur) { return couleur_ == couleur; }
  bool operator==(const Couleur &couleur) {
    return couleur_ == couleur.couleur_;
  }
  std::string couleur_;
};
/** Operateur >> : nécessaire pour que la classe soit compatible avec
 * l'implémentation de la classe générique Matrice **/
std::istream &operator>>(std::istream &is, Couleur &couleur) {
  is >> couleur.couleur_;
  return is;
}
/** Operateur << : nécessaire pour que la classe soit compatible avec
 * l'implémentation de la classe générique Image **/
std::ostream &operator<<(std::ostream &os, Couleur couleur) {
  os << std::setw(10) << std::setfill(' ') << couleur.couleur_;
  return os;
}
/** ---------------------------------------------------------------------- **/
/** Classe Entier est définie pour les tests! Veuillez ne pas la modifier! **/
class Entier {
public:
  Entier() : nombre_(26){};
  Entier(int nombre) : nombre_(nombre){};
  void operator=(const Entier &entier) { nombre_ = entier.nombre_; }
  bool operator==(const int &nombre) { return nombre_ == nombre; }
  bool operator==(const Entier &entier) { return nombre_ == entier.nombre_; }
  int nombre_;
};
/** Operateur >> : nécessaire pour que la classe soit compatible avec
 * l'implémentation de la classe générique Matrice **/
std::istream &operator>>(std::istream &is, Entier &entier) {
  is >> entier.nombre_;
  return is;
}

#endif