/**
 * Fonction main qui test le programme.
 * \file main.cpp
 * \author Nabil Dabouz
 * \date 27 Février 2020
 **/

#include "Image.h"
#include "Matrice.h"
#include "Pixel.h"
#include "debogageMemoire.h"
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// NOTE: Pour que le programme compile initialement, vous pouvez changer tous
// les #if true à des #if false, et mettre en commentaire tout le code qui a été
// écrit pour vous. Ainsi, vous pourrez graduellement les #if true et tester des
// petits blocs de code à la fois. Commencez par écrire vos constructeurs!

int main() {
  initDebogageMemoire();
  std::vector<bool> tests;
#if false
  Matrice<int> matriceNombres;
  if (matriceNombres.chargerDepuisFichier("matrice_nombres.txt")) {
    Image<Matrice<int>> *imageNombres =
        new Image<Matrice<int>>(std::make_unique<Matrice<int>>(matriceNombres));
    std::cout << "############################## Affichage de la matrice des "
                 "entiers #############################"
              << std::endl
              << std::endl;
    std::cout << imageNombres << std::endl;
    imageNombres->pivoterMatrice(Direction::Left);
    std::cout << "############ Affichage de la matrice des entiers apres le "
                 "pivotement vers la gauche ############"
              << std::endl
              << std::endl;
    std::cout << imageNombres << std::endl;
    imageNombres->redimensionnerImage(3);
    std::cout << "############### Affichage de la matrice des entiers apres le "
                 "redimmensionnement ################"
              << std::endl
              << std::endl;
    std::cout << imageNombres << std::endl << std::endl;
    delete imageNombres;
  }

  Matrice<Pixel> matricePixels;
  if (matricePixels.chargerDepuisFichier("matrice_pixel.txt")) {
    Image<Matrice<Pixel>> *imagePixels = new Image<Matrice<Pixel>>(
        std::make_unique<Matrice<Pixel>>(matricePixels));
    std::cout << "############################## Affichage de la matrice des "
                 "pixels ##############################"
              << std::endl
              << std::endl;
    std::cout << imagePixels << std::endl;
    imagePixels->pivoterMatrice(Direction::Right);
    std::cout << "############ Affichage de la matrice des pixels apres le "
                 "pivotement vers la droite #############"
              << std::endl
              << std::endl;
    std::cout << imagePixels << std::endl;
    imagePixels->redimensionnerImage(2);
    std::cout << "################ Affichage de la matrice des pixels apres le "
                 "redimmensionnement ################"
              << std::endl
              << std::endl;
    std::cout << imagePixels << std::endl;
    delete imagePixels;
  }

  Matrice<Couleur> matriceCouleur;
  if (matriceCouleur.chargerDepuisFichier("matrice_text.txt")) {
    Image<Matrice<Couleur>> *imageCouleur = new Image<Matrice<Couleur>>(
        std::make_unique<Matrice<Couleur>>(matriceCouleur));
    std::cout << "################# Affichage de la matrice des couleurs en "
                 "chaine de caracteres #################"
              << std::endl
              << std::endl;
    std::cout << imageCouleur << std::endl << std::endl;
    delete imageCouleur;
  }

#else
  // Tests de la classe Pixel: Tests 1-4
#if true
  Pixel pixel;
  // Setters
  pixel.setRouge(255);
  pixel.setVert(1998);
  pixel.setBleu(-522);
  bool pixelSetters = (pixel.getRouge() == 255) && (pixel.getVert() == 255) &&
                      (pixel.getBleu() == 0);
  tests.push_back(pixelSetters);

  // Opérateur =
  pixel = Pixel(1, 200, 111);
  bool pixelOperator = (pixel.getRouge() == 1) && (pixel.getVert() == 200) &&
                       (pixel.getBleu() == 111);
  tests.push_back(pixelOperator);

  // Opérateur <<
  std::stringstream streamPixel;
  streamPixel << pixel;
  pixelOperator = streamPixel.str() == "#01 C8 6F";
  tests.push_back(pixelOperator);

  // Opérateur >>
  Pixel pixelLu;
  streamPixel.str("");
  streamPixel << 152 << " " << 35 << " " << 425;
  streamPixel >> pixelLu;
  pixelOperator = (pixelLu.getRouge() == 152) && (pixelLu.getVert() == 35) &&
                  (pixelLu.getBleu() == 255);
  ;
  tests.push_back(pixelOperator);

#else
  tests.push_back(false);
  tests.push_back(false);
  tests.push_back(false);
  tests.push_back(false);
#endif
  // Tests de la classe Matrice
  // Initialisation de la matrice
#if true
  Matrice<Entier> matriceTest;
  bool initialisationTest = (matriceTest.getHeight() == 0) &&
                            (matriceTest.getWidth() == 0) &&
                            (matriceTest(10, 24) == 26);
  tests.push_back(initialisationTest);

  // Ajout d'un element
  matriceTest.ajouterElement(Entier(12), 5, 3);
  bool ajouterElementTest = (matriceTest(5, 3) == 26);
  matriceTest.setHeight(3);
  matriceTest.setWidth(3);
  matriceTest.ajouterElement(Entier(27), 2, 2);
  ajouterElementTest &= (matriceTest(2, 2) == 27);
  tests.push_back(ajouterElementTest);

  // Clone une matrice
  matriceTest.ajouterElement(Entier(12), 1, 1);
  std::unique_ptr<Matrice<Entier>> matriceCopie = matriceTest.clone();
  bool cloneTest = (matriceCopie->operator()(2, 2) == 27) &&
                   (matriceCopie->operator()(1, 1) == 12);
  cloneTest &=
      (matriceCopie->getHeight() == 3) && (matriceCopie->getWidth() == 3);
  tests.push_back(cloneTest);

  // Lire element et l'ajouter
  std::string element("15");
  matriceTest.lireElement(element, 0, 0);
  bool lireElementTest = matriceTest(0, 0) == 15;
  tests.push_back(lireElementTest);
#else
  tests.push_back(false);
  tests.push_back(false);
  tests.push_back(false);
  tests.push_back(false);
#endif
  // Tests de la classe NearestNeighbourAlgo
  std::unique_ptr<Matrice<Entier>> ptrMatrice =
  std::make_unique<Matrice<Entier>>(matriceTest);
  // Trouver point plus proche
#if true
  AgrandirMatrice<Matrice<Entier>> agrandissment(ptrMatrice.get());
  bool algorithmeTest =
      (agrandissment.trouverLePlusProcheVoisin(5, 3, 4).x == 0) &&
      (agrandissment.trouverLePlusProcheVoisin(5, 3, 4).y == 0);
  tests.push_back(algorithmeTest);
  // Redimmensionner
  agrandissment.redimensionnerImage(3);
  bool redimmensionnementTest =
      (ptrMatrice->getHeight() == 9) && (ptrMatrice->getWidth() == 9);
  redimmensionnementTest &= (ptrMatrice->operator()(0, 0) == 15) &&
                            (ptrMatrice->operator()(1, 1) == 15);
  redimmensionnementTest &= (ptrMatrice->operator()(3, 3) == 12) &&
                            (ptrMatrice->operator()(5, 5) == 12);
  redimmensionnementTest &= (ptrMatrice->operator()(7, 7) == 27) &&
                            (ptrMatrice->operator()(8, 8) == 27);
  tests.push_back(redimmensionnementTest);
#else
  tests.push_back(false);
  tests.push_back(false);
#endif
  // Tests de la classe PivoterMatrice
#if true
  PivoterMatrice<Matrice<Entier>> pivotement(ptrMatrice.get());
  pivotement.pivoterMatrice(Direction::Left);
  bool pivoterMatriceTest =
      (ptrMatrice->getHeight() == 9) && (ptrMatrice->getWidth() == 9);
  pivoterMatriceTest &= (ptrMatrice->operator()(8, 0) == 15) &&
                        (ptrMatrice->operator()(7, 1) == 15);
  pivoterMatriceTest &= (ptrMatrice->operator()(5, 3) == 12) &&
                        (ptrMatrice->operator()(3, 5) == 12) &&
                        (ptrMatrice->operator()(4, 4) == 12);
  pivoterMatriceTest &= (ptrMatrice->operator()(1, 7) == 27) &&
                        (ptrMatrice->operator()(0, 8) == 27);
  tests.push_back(pivoterMatriceTest);
#else
  tests.push_back(false);
#endif

  // Affichage
  std::vector<float> ponderationTests = {1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 4};
  float totalPoints = 0;
  for (std::size_t i = 0; i < tests.size(); i++) {
    switch (i) {
    case 0:
      std::cout << "La classe Pixel ----------------------- /4" << std::endl;
      break;
    case 4:
      std::cout << "La classe Matrice --------------------- /5" << std::endl;
      break;
    case 8:
      std::cout << "La classe NearestNeighbourAlgo -------- /4" << std::endl;
      break;
    case 10:
      std::cout << "La classe PivoterMatrice -------------- /4" << std::endl;
      break;
    default:
      break;
    }
    std::string output = "Test " + std::to_string(i + 1) + ": ";
    if (tests[i] == true) {
      output += "OK!";
      std::stringstream stream;
      stream << ponderationTests[i] << '/' << ponderationTests[i];
      std::cout << std::left << std::setw(15) << std::left << output
                << stream.str() << '\n';
      totalPoints += ponderationTests[i];
    } else {
      output += "ECHEC!";
      std::stringstream stream;
      stream << '0' << '/' << ponderationTests[i];
      std::cerr << std::left << std::setw(15) << output << "0/"
                << ponderationTests[i] << '\n';
    }
  }
  std::stringstream stream;
  stream << totalPoints << "/"
         << std::accumulate(ponderationTests.begin(), ponderationTests.end(),
                            0.0f);
  std::cout << std::left << std::setw(16) << "TOTAL: " << stream.str() << '\n';
#endif

  return 0;
}