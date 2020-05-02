// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"
#include<Librairie.h>
namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
}

// TODO: Constructeur par défault en utilisant la liste d'initialisation
Librairie::Librairie() :
	films_(new Film* [CAPACITE_FILMS_INITIALE]{}),
	nbFilms_(0),
	capaciteFilms_(CAPACITE_FILMS_INITIALE)

{
}
// Utiliser CAPACITE_FILMS_INITIALE pour la taille initiale de films_ (allocation dynamique!)
Librairie :: ~Librairie() {
	supprimerFilms();
	delete[] films_;
	films_ = nullptr;
}
// TODO: Destructeur
// Ne pas oublier de désallouer le tableau ET les films

//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe devient propriétaire du
//!             film.
void Librairie::ajouterFilm(Film* film)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

    // TODO
    // Verifier si assez de mémoire est allouée
	if (nbFilms_ >= CAPACITE_FILMS_INITIALE) {
		capaciteFilms_ *= AUGMENTATION_CAPACITE_FILMS;
		Film** nouveau = new Film * [capaciteFilms_];
		for (size_t i = 0; i < nbFilms_; i++) {
			nouveau[i] = films_[i];
		}
		delete films_;
		films_ = nouveau;
	}
    // Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_CAPACITE_FILMS)
	if (film != nullptr) {
		Auteur* auteur = film->getAuteur();
		auteur->setNbFilms(auteur->getNbFilms() + 1);
		films_[nbFilms_++] = film;
	}
	// Ajouter le film au tableau seulement si film n'est pas un nullptr
}

void Librairie::retirerFilm(const std::string& nomFilm) {

	if (trouverIndexFilm(nomFilm) >= 0) {
		
		Auteur* auteur = films_[trouverIndexFilm(nomFilm)]->getAuteur();
		auteur->setNbFilms(auteur->getNbFilms() - 1);
		films_[trouverIndexFilm(nomFilm)] = films_[nbFilms_-1];
		films_[nbFilms_ - 1] = nullptr;
		nbFilms_-1;
		

	}


}
    
// Retirer un film ayant le même nom que celui envoyé en paramètre
// Si le film n'existe pas, ne rien faire
// Faire appel à la fonction trouverIndexFilm

Film* Librairie::chercherFilm(const std::string& nomFilm){
	Film* filmRechercher = nullptr;
	if (trouverIndexFilm(nomFilm) >= 0) {
		filmRechercher = films_[trouverIndexFilm(nomFilm)];
	}
	return filmRechercher;
}

// Retourner un pointeur vers le film recherché
// Si le film n'existe pas, retourner nullptr
// Utiliser la fonction trouverIndexFilm

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{

	bool estCharger = true;
	std::string ligne = "";
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		supprimerFilms();
		nbFilms_ = 0;
		while (getline(fichier, ligne) && estCharger)
			estCharger = lireLigneFilm(ligne, gestionnaireAuteurs);
		return estCharger;
	}
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
	bool estCharger = true;
	if (fichier)
    {
		for (int i = 0; i < nbFilms_; i++) {
			films_[i]->supprimerPaysRestreints();
		}
		std::string ligne = " ";
		while (std::getline(fichier, ligne)&& estCharger) 
			estCharger = lireLigneRestrictions(ligne);
		return estCharger;
			
		
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher.
void Librairie::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbFilms_; i++)
    {
        films_[i]->afficher(stream);
        stream << '\n';
    }
}

size_t Librairie::getNbFilms() const {
	return nbFilms_;
}

void Librairie::supprimerFilms() {
	for (size_t i = 0; i < nbFilms_; i++) {
		films_[i]->getAuteur()->setNbFilms(0);
		delete films_[i];
	}
	nbFilms_ = 0;
}
// Supprimer les films du tableau (delete)

//! Méthode qui ajoute les restrictions d'un film avec un string.
//! \param ligne Le string comportant les restrictions du film.
//! \return      Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
	int numero =0;

	if (stream >> std::quoted(nomFilm)) {
		if (trouverIndexFilm(nomFilm) == -1) {
			return false;
		}
		while (stream >> numero ) {
			
			films_[trouverIndexFilm(nomFilm)]->ajouterPaysRestreint(to_enum<Pays>(numero));
			return true;
		}
			// TODO
			// Pour extraire tout ce qui se trouve entre "" dans un stream,
			// il faut faire stream >> std::quoted(variable)
			// Utiliser l'opérateur d'extraction (>>) pour retrouver le nom du film
			// Trouver le film qui comporte le nom
			// Si le film n'existe pas, retourner false
			// Faire une boucle while (stream >> int), puis utiliser ce int pour appeler la fonction
	} // film->ajouterPaysRestreint
	return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

 if (stream >> quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge >> quoted(nomAuteur)) {


		if (gestionnaireAuteurs.chercherAuteur(nomAuteur) == nullptr) {
			return false;
		}
		else
		{
			if (trouverIndexFilm(nomFilm) == -1) {
				ajouterFilm(new Film(nomFilm, anneeSortie, to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), estRestreintParAge, gestionnaireAuteurs.chercherAuteur(nomAuteur)));
				return true;
			}
		}


		// TODO
		// Pour extraire tout ce qui se trouve entre "" dans un stream,
		// il faut faire stream >> std::quoted(variable)
		// Utiliser l'opérateur d'extraction (>>) pour retrouver les attributs du films
		// Si l'auteur n'existe pas, retourner false

 }else
		return false;
}

int Librairie::trouverIndexFilm(const std::string& nomFilm) const {
	int index = -1;
	for (size_t i = 0; i < nbFilms_; i++) {
		if (films_[i]->getNom() == nomFilm) {
			index = i;
			
		}
	}
	return index;
}
// Retourner l'indexe du film comportant le nom envoyé en paramètre
// Si le film n'existe pas, retourner -1 (FILM_INEXSISTANT)