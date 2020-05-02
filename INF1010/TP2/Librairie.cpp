////////////////////////////////////////////////////////////////////////////////
/// \file    Librairie .cpp
/// \author  Kevin Lam and Slimane Boussafeur
/// \version Dernière entrée : 2020-02-29
/// \since   Création : 2020-01-29
///
/// Ce fichier contient les méthodes de la class Librairie
////////////////////////////////////////////////////////////////////////////////

#include "Librairie.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

//! Constructeur par copie de la classe Librairie
//! \param librairie         La librairie a copier
Librairie ::Librairie(const Librairie& librairie)

{
	*this = librairie;
}
//! Constructeur par défaut de la classe Librairie
Librairie::Librairie()
	
{
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
	for (size_t i = 0; i < films_.size(); i++) {

		films_[i]->getAuteur()->setNbFilms(0);
    }
	supprimerFilms();
    
}
//! Méthode qui retourne le vecteur de films
//! \return films_  le vecteur de films
const std::vector<std::unique_ptr<Film>>& Librairie::getFilms() const
{
    return films_;
}

//! Méthode de l'operateur += de la classe Librairie qui ajoute un film à la liste des films
//! \param   film     Le film alloué dynamiquement à ajouter à la liste. La classe devient propriétaire du
//!                   film.
//! \return  *this    La librairie a laquelle nous avons ajouté un film
Librairie& Librairie::operator+=(Film* film)
{
	if (film != nullptr) {
		film->getAuteur()->setNbFilms(film->getAuteur()->getNbFilms() + 1);
		films_.push_back(std::unique_ptr<Film>(film));
		return *this;
	}
	return *this;
}

//! Méthode de l'operateur -= de la classe Librairie qui retire un film à la liste des films
//! \param   nomFilm     Le string du nom du film qu'on veut retirer
//! \return  *this       La librairie a laquelle nous avons retiré un film
Librairie& Librairie::operator-=(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm != FILM_INEXSISTANT)
    {
		films_[indexFilm]->getAuteur() ->setNbFilms(films_[indexFilm]->getAuteur()->getNbFilms() - 1);
		films_[indexFilm] = move(films_[films_.size() - 1]);
		films_.pop_back();
	}
	return *this;
    
}

//! Méthode qui retourne un film comportant le même nom que celui envoyé en paramètre
//! \param nomFilm Le nom du film à chercher
//! \return        Un pointeur vers le film. Nullptr si le film n'existe pas
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);
    if (indexFilm == FILM_INEXSISTANT)
    {
        return nullptr;
    }
    return films_[indexFilm].get();
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // Supprimers les vieux films avant de lire les nouveaux
		// Cette duplication de code est necessaire puisque nous n'avons pas de droit de remettre
		//le nombre d'auteur a 0 dans la methode supprimerFilms

		for (size_t i = 0; i < films_.size(); i++) {

			films_[i]->getAuteur()->setNbFilms(0);

		}
		supprimerFilms();

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (std::size_t i = 0; i < films_.size(); i++)
        {
            films_[i]->supprimerPaysRestreints();
        }
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneRestrictions(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode de l'operateur << de la classe Librairie qui affiche une libraire et ses informations
//! \param     stream         Le stream dans lequel afficher
//! \param     auteur         La librairie qu'on veut afficher dans le stream
//! \return    stream         Le stream modifié
std::ostream& operator<<(std::ostream& stream, const Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.films_.size(); i++)
    {
        stream << *(librairie.films_[i]);
        stream << '\n';
    }
	return stream;
}

//! Méthode qui retourne le nombre de films
//! \return Le nombre de films
std::size_t Librairie::getNbFilms() const
{
    return films_.size();
}

//! Méthode qui supprime tous les films
void Librairie::supprimerFilms()
{
	films_.clear();
}

//! Méthode qui ajoute les restrictions d'un film avec un string
//! \param ligne Le string comportant les restrictions du film
//! \return      Un bool représentant si l'opération est un succès
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> std::quoted(nomFilm))
    {
        Film* film = chercherFilm(nomFilm);
        if (film == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            film->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film
//! \param ligne                Le string comportant les attributs du film
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >>
        estRestreintParAge >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        Film* film = new Film(nomFilm,
                              anneeSortie,
                              to_enum<Film::Genre>(genreValeurEnum),
                              to_enum<Pays>(paysValeurEnum),
                              estRestreintParAge,
                              auteur);
        *this += film;
        return true;
    }
    return false;
}

//! Méthode qui retourne l'index d'un film en cherchant son nom
//! \param nomFilm Le nom du film à trouver
//! \return        L'index du film. Retourne -1 si le film n'existe pas
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    for (std::size_t i = 0; i < films_.size(); i++)
    {
        if (films_[i]->getNom() == nomFilm)
        {
            return (int)i;
        }
    }
    return FILM_INEXSISTANT;
}

//! Méthode de l'operateur = de la classe Librairie qui écrase les données de la librairie en copiant celles d'une autre librairie
//! \param   librairie    La librairie dont on va copier les informations
//! \return  *this        La librairie dont les données ont été écrasé
Librairie& Librairie::operator=(const Librairie& librairie) {


	if (films_ != librairie.films_)
	{
		supprimerFilms(); // S'assurer que tous les films ont été supprimé avant de pouvoir copier
		for (std::size_t i = 0; i < librairie.films_.size(); i++) {
			films_.push_back(std::make_unique<Film>(*librairie.films_[i]));
		}
	}
	return *this;
}