
 ////////////////////////////////////////////////////////////////////////////////
 /// \file    PivoterMatrice .h
 /// \author  Kevin Lam and Slimane Boussafeur
 /// \version Dernière entrée : 2020-03-19
 /// \since   Création : 2020-01-11
 ///
 /// Ce fichier contient la definition ainsi que l'implementation des méthodes de la classe PivoterMatrice
 ////////////////////////////////////////////////////////////////////////////////

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M>
class PivoterMatrice
{
public:
	// Constructeurs
	PivoterMatrice();
	PivoterMatrice(M* matrice);
	// Destructeur
	~PivoterMatrice() = default;
	void pivoterMatrice(Direction direction);

private:
	Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
	Coordonnees recupererCoordonnees(Coordonnees coords) const;
	M* matrice_;
};

//! Constructeur  par defaut de la classe PivoterMatrice

template <class M>
inline PivoterMatrice<M>::PivoterMatrice()
	: matrice_(nullptr) {}

//! Constructeur de la classe PivoterMatrice
//! \param Matrice    Pointeur vers une matrice de type generique M

template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M* matrice) 
	: matrice_(matrice) {}

 //! Méthode qui change les coordonees des elements de la matrices par apport au centre
 //! \param     coords         Les coordonnees a changer
 //! \return    Coordonnees    Les nouvelles coordonnees

template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const
{
	int diviseur = 2;
	return Coordonnees{ coords.x - (static_cast<int>(matrice_->getHeight()) / diviseur), coords.y - (static_cast<int>(matrice_->getHeight()) / diviseur) };
}

//! Méthode qui nous permet de revenir au systeme de coordonnees precedent 
//! \param     coords         Les coordonnees a rapatrier
//! \return    Coordonnees    Les coordonees originales

template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const
{
	int diviseur = 2;
	return Coordonnees{ coords.x + (static_cast<int>(matrice_->getHeight()) / diviseur), coords.y + (static_cast<int>(matrice_->getHeight()) / diviseur) };
}

//! Méthode qui nous permet de faire pivoter chaque point de la matrice grace a une matrice de rotation 
//! \param     direction       la direction par laquel nous voulons faire notre rotation

template <class M>
inline void PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
	std::unique_ptr<M> copieMatrice = matrice_->clone();

	for (size_t i = 0; i < copieMatrice->getHeight(); i++)
	{
		for (size_t j = 0; j < copieMatrice->getWidth(); j++)
		{
			Coordonnees coordsMatrice{ static_cast<int>(j), static_cast<int>(i) };
			coordsMatrice = changerCoordonneesCentreMatrice(coordsMatrice);

			if (direction == Direction::Left)
			{
				Coordonnees coordsRotation{ coordsMatrice.y, (coordsMatrice.x * -1) };
				coordsRotation = recupererCoordonnees(coordsRotation);
				matrice_->ajouterElement((*copieMatrice)(static_cast<size_t>(coordsRotation.x), static_cast<size_t>(coordsRotation.y)), j, i);
	
			}

			else
			{
				Coordonnees coordsRotation{ (coordsMatrice.y * -1), coordsMatrice.x };
				coordsRotation = recupererCoordonnees(coordsRotation);
				matrice_->ajouterElement((*copieMatrice)(static_cast<size_t>(coordsRotation.x), static_cast<size_t>(coordsRotation.y)), j, i);
			}
		}
	}
}

#endif
