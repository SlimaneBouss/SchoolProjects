////////////////////////////////////////////////////////////////////////////////
/// \file    AgrandirMatrice .h
/// \author  Kevin Lam and Slimane Boussafeur
/// \version Dernière entrée : 2020-03-19
/// \since   Création : 2020-01-11
///
/// Ce fichier contient la definition ainsi que l'implementation des méthodes de la classe AgrandirMatrice
////////////////////////////////////////////////////////////////////////////////


#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M>
class AgrandirMatrice
{
public:
	AgrandirMatrice();
	AgrandirMatrice(M* matrice);
	~AgrandirMatrice() = default;
	Coordonnees trouverLePlusProcheVoisin(const unsigned int& rapport,
		size_t posY, size_t posX) const;
	void redimensionnerImage(const unsigned int& rapport);

private:
	M* matrice_;
};

//! Constructeur  par defaut de la classe AgrandirMatrice

template <class M>
AgrandirMatrice<M>::AgrandirMatrice() 
	: matrice_(nullptr) {}

//! Constructeur de la classe AgrandirMatrice
//! \param Matrice    Pointeur vers une matrice de type generique M

template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M* matrice) 
	: matrice_(matrice) {}


//! Methode qui trouve le point le plus proche du point (posX, posY) dans la matrice originale
//! \param  rapport  le rapport du redimensionnement de l'image
//!         posX     la colonne du point dans la nouvelle image
//!         posY     la ligne du point dans la nouvelle image
//! \return coordonnées du point le plus proche

template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int& rapport,
	size_t posY, size_t posX) const
{
	return Coordonnees{ static_cast<int>(posX / rapport), static_cast<int>(posY / rapport) };
}

//! Methode qui redimensionne la matrice selon le rapport grace a la methode du plus proche voisin
//! \param  rapport  le rapport du redimensionnement de l'image


template <class M>
void AgrandirMatrice<M>::redimensionnerImage(const unsigned int& rapport)
{
	std::unique_ptr<M> copieMatrice = matrice_->clone();

	matrice_->setHeight(matrice_->getHeight() * rapport);
	matrice_->setWidth(matrice_->getWidth() * rapport);

	for (size_t i = 0; i < matrice_->getHeight(); i++)
	{
		for (size_t j = 0; j < matrice_->getWidth(); j++)
		{
			matrice_->ajouterElement((*copieMatrice)(static_cast<size_t>(trouverLePlusProcheVoisin(rapport, i, j).x), static_cast<size_t>(trouverLePlusProcheVoisin(rapport, i, j).y)), j, i);
		}
	}
}

#endif