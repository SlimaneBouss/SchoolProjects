////////////////////////////////////////////////////////////////////////////////
/// \file    Auteur .cpp
/// \author  Kevin Lam and Slimane Boussafeur
/// \version Dernière entrée : 2020-02-29
/// \since   Création : 2020-01-29
///
/// Ce fichier contient les méthodes de la class Auteur
////////////////////////////////////////////////////////////////////////////////

#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance) :
	  nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{
}
//! Méthode de l'operateur == de la classe Auteur qui compare le nom de deux auteurs
//! \param   nomAuteur        Un string représentant le nom de d'un auteur a comparer
//! \return  un bool          Un bool indiquant si les deux noms sont similaires
bool Auteur::operator==(const std::string& nomAuteur) {
	
	return (nom_ == nomAuteur);

}
//! Méthode globale de l'operateur ==  permettant la commutativite lors de la comparaison du noms du string et du nom de lauteur
//! \param   nomAuteur        Un string représentant le nom de d'un auteur a comparer
//! \param   auteur           Un auteur dont on veut comparer le nom 
//! \return  un bool          Un bool indiquant si les deux noms sont similaires
bool operator==(const std::string& nomAuteur, const Auteur& auteur) {

	return(nomAuteur == auteur.nom_);
}
//! Méthode de l'operateur << de la classe Auteur qui affiche un auteur et ses informations
//! \param     stream         Le stream dans lequel afficher
//! \param     auteur         L'auteur qu'on veut afficher dans le stream
//! \return    stream         Le stream modifié
std::ostream& operator<<(std::ostream& stream, const Auteur& auteur)
{

	stream << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
		<< " | Nombre de films: " << auteur.nbFilms_;
	return stream;
}

//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}