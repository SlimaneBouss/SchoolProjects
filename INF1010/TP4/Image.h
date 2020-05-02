/*
 * Titre : Image.h - Travail Pratique #4 - Programmation Orientée Objet
 * Date : 27 Février 2020
 * Auteur : Nabil Dabouz
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "AgrandirMatrice.h"
#include "PivoterMatrice.h"
#include <iostream>

template <typename M> class Image {
public:
  Image(std::unique_ptr<M> matrice);
  M *getMatrice();
  void redimensionnerImage(const unsigned int &rapport);
  void pivoterMatrice(Direction direction);

private:
  AgrandirMatrice<M> agrandissement_;
  PivoterMatrice<M> pivotement_;
  std::unique_ptr<M> matrice_;
};

/**
 * @brief constructeur par paramètres de la classe
 */
template <typename M>
Image<M>::Image(std::unique_ptr<M> matrice)
    : matrice_(std::move(matrice)), agrandissement_(matrice.get()),
      pivotement_(matrice.get()) {}

/**
 * @brief retourne la matrice de l'image
 * @return pointeur de type shared_ptr qui pointe vers un element de type M
 */
template <typename M> M *Image<M>::getMatrice() { return matrice_.get(); }
/**
 * @brief redimensionne l'image avec un rapport passé en params
 * @param rapport, le rapport de redimensionnement de type unsigned int
 */
template <typename M>
void Image<M>::redimensionnerImage(const unsigned int &rapport) {
  agrandissement_.redimensionnerImage(rapport);
}
/**
 * @brief pivote l'image dans une direction passé en params
 * @param direction, de type Direction
 */
template <typename M>
inline void Image<M>::pivoterMatrice(Direction direction) {
  pivotement_.pivoterMatrice(direction);
}
/**
 * @brief operateur << pour afficher une image
 * @param os, de type ostream
 * @param image, un pointeur vers l'image à afficher
 */
template <typename M>
std::ostream &operator<<(std::ostream &os, Image<M> *image) {
  for (unsigned int i = 0; i < image->getMatrice()->getHeight(); i++) {
    for (unsigned int j = 0; j < image->getMatrice()->getWidth(); j++)
      if (j < image->getMatrice()->getWidth() - 1)
        os << image->getMatrice()->operator()(i, j) << " | ";
      else
        os << image->getMatrice()->operator()(i, j) << " |";
    os << std::endl;
  }
  return os;
}

#endif