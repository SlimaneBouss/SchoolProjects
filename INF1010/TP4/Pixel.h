/*
 * Titre : Pixel.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <iomanip>
#include <iostream>

class Pixel {
public:
  // Constructeurs
  Pixel();
  Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu);
  // Destructeur
  ~Pixel() = default;
  // Operateurs
  void operator=(const Pixel &pixel);
  // Setters
  void setRouge(int rouge);
  void setVert(int vert);
  void setBleu(int bleu);
  // Getters
  uint8_t getRouge() const;
  uint8_t getVert() const;
  uint8_t getBleu() const;

private:
  uint8_t rouge_;
  uint8_t vert_;
  uint8_t bleu_;
};

std::ostream &operator<<(std::ostream &os, Pixel pixel);
std::istream &operator>>(std::istream &is, Pixel &pixel);

#endif
