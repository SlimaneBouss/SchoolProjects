// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <iostream>
#include <Film.h>
#include "Pays.h"
#include "typesafe_enum.h"
using namespace std;

namespace
{
    constexpr std::size_t CAPACITE_PAYS_INITIALE = 2;

    //! Fonction qui convertit le enum Film::Genre en string.
    //! \param genre    Le genre à convertir.
    //! \return         Le string qui représente le enum.
    const std::string& getGenreString(Film::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Pays>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string.
    //! \param pays     Le pays à convertir.
    //! \return         Le string qui représente le enum.
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
}

// TODO: Constructeur par paramètre en utilisant la liste d'initialisation
// Utiliser CAPACITE_PAYS_INITIALE pour la taille initiale de paysRestreints_ (allocation
// dynamique!)
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
	bool estRestreintParAge, Auteur* auteur) :
	nom_(nom),
	anneeDeSortie_(anneeDeSortie),
	genre_(genre),
	pays_(pays),
	estRestreintParAge_(estRestreintParAge),
	auteur_(auteur),
	paysRestreints_(make_unique<Pays[]>(CAPACITE_PAYS_INITIALE)),
	nbPaysRestreints_(0),
	capacitePaysRestreints_(CAPACITE_PAYS_INITIALE)
{
}
//! Méthode qui ajoute un pays à liste des pays restreints du film.
//! \param pays Pays à ajouter à la liste.
void Film::ajouterPaysRestreint(Pays pays)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_PAYS = 2;

    // TODO
    // Verifier si assez de mémoire est allouée
	if (nbPaysRestreints_ >= capacitePaysRestreints_) {
		capacitePaysRestreints_ *= AUGMENTATION_CAPACITE_PAYS;
		unique_ptr<Pays[]> nouveau = make_unique<Pays[]>(capacitePaysRestreints_);
		for (size_t i = 0; i < nbPaysRestreints_; i++) {
			nouveau[i] = paysRestreints_[i];
		}
		paysRestreints_ = move(nouveau);
	}
	paysRestreints_[nbPaysRestreints_++] = pays;
    // Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_CAPACITE_PAYS)
    // Ajouter le pays au tableau
    // Utiliser std::make_unique<Pays[]> ainsi que std::move pour transférer le ownership
    // du tableau temporaire vers le tableau membre paysRestreints_;
}

void Film::supprimerPaysRestreints() {
	nbPaysRestreints_ = 0;
}

bool Film ::estRestreintDansPays(Pays pays) const {
	bool estRestrein = false;
	for (size_t i = 0; i < nbPaysRestreints_; i++) {
		if ( paysRestreints_[i] == pays) {
			estRestrein = true;
		}
	}
	return estRestrein;
}
// Chercher si le pays en paramètre se retrouve dans la liste des pays restreints.

//! Méthode qui affiche le film.
//! \param stream Le stream dans lequel afficher.
void Film::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
           << "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
           << "\n\tPays: " << getPaysString(pays_)
           << (nbPaysRestreints_ == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < nbPaysRestreints_; i++)
    {
        stream << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    stream << '\n';
}

Film::Genre Film::getGenre() const {
	return genre_;
 }

bool Film::estRestreintParAge() const const {
	return estRestreintParAge_;
}
const string& Film::getNom() const {
	return nom_;
}

Auteur* Film:: getAuteur() {
	return auteur_;
}