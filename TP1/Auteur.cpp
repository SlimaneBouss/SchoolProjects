// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <iostream>
#include<Auteur.h>
using namespace std;
// TODO: Constructeur par paramètre en utilisant la liste d'initialisation
Auteur:: Auteur(const string& nom, unsigned int anneeDeNaissance) :
	nom_(nom),
    anneeDeNaissance_(anneeDeNaissance),
	nbFilms_(0)
{
}
//! Méthode qui affiche un auteur.
//! \param stream Le stream dans lequel afficher.
void Auteur::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << nom_ << " | Date de naissance: " << anneeDeNaissance_
           << " | Nombre de films: " << nbFilms_;
}

const string& Auteur:: getNom() const
{
	return nom_;
} 

unsigned int Auteur::getAnneeDeNaissance() const {
	return anneeDeNaissance_;
}

unsigned int Auteur:: getNbFilms() const {
	return nbFilms_;
 }

void Auteur ::setNbFilms(unsigned int nbFilms) {
	nbFilms_ = nbFilms;
}
