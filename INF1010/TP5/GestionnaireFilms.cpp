/// Gestionnaire de films.
/// \author Kevin Lam (2024921) Slimane Boussafeur (2017001)
/// \date 2020-04-08

#include "GestionnaireFilms.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Foncteurs.h"
#include "RawPointerBackInserter.h"

/// Constructeur par copie.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
GestionnaireFilms::GestionnaireFilms(const GestionnaireFilms& other)
{
	films_.reserve(other.films_.size());
	filtreNomFilms_.reserve(other.filtreNomFilms_.size());
	filtreGenreFilms_.reserve(other.filtreGenreFilms_.size());
	filtrePaysFilms_.reserve(other.filtrePaysFilms_.size());

	for (const auto& film : other.films_)
	{
		// TODO: Uncomment une fois que la fonction ajouterFilm est écrite
		ajouterFilm(*film);
	}
}

/// Opérateur d'assignation par copie utilisant le copy-and-swap idiom.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
/// \return         Référence à l'objet actuel.
GestionnaireFilms& GestionnaireFilms::operator=(GestionnaireFilms other)
{
	std::swap(films_, other.films_);
	std::swap(filtreNomFilms_, other.filtreNomFilms_);
	std::swap(filtreGenreFilms_, other.filtreGenreFilms_);
	std::swap(filtrePaysFilms_, other.filtrePaysFilms_);
	return *this;
}

/// Affiche les informations des films gérés par le gestionnaire de films à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des films.
/// \param gestionnaireFilms    Le gestionnaire de films à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireFilms& gestionnaireFilms)
{
	// TODO: Uncomment une fois que la fonction getNombreFilms est écrite
	outputStream << "Le gestionnaire de films contient " << gestionnaireFilms.getNombreFilms() << " films.\n"
		<< "Affichage par catégories:\n";

	// TODO: Réécrire l'implémentation avec des range-based for et structured bindings (voir énoncé du TP)
	for (const auto& [key, value] : gestionnaireFilms.filtreGenreFilms_)
	{
		Film::Genre genre = key;
		std::vector<const Film*> listeFilms = value;
		outputStream << "Genre: " << getGenreString(genre) << " (" << listeFilms.size() << " films):\n";
		for (std::size_t i = 0; i < listeFilms.size(); i++)
		{
			outputStream << '\t' << *listeFilms[i] << '\n';
		}
	}

	return outputStream;
}

/// Ajoute les films à partir d'un fichier de description des films.
/// \param nomFichier   Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		films_.clear();
		filtreNomFilms_.clear();
		filtreGenreFilms_.clear();
		filtrePaysFilms_.clear();

		bool succesParsing = true;

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			std::istringstream stream(ligne);

			std::string nom;
			int genre;
			int pays;
			std::string realisateur;
			int annee;

			if (stream >> std::quoted(nom) >> genre >> pays >> std::quoted(realisateur) >> annee)
			{
				// TODO: Uncomment une fois que la fonction ajouterFilm est écrite
				ajouterFilm(Film{ nom, static_cast<Film::Genre>(genre), static_cast<Pays>(pays), realisateur, annee });
			}
			else
			{
				std::cerr << "Erreur GestionnaireFilms: la ligne " << ligne
					<< " n'a pas pu être interprétée correctement\n";
				succesParsing = false;
			}
		}
		return succesParsing;
	}
	std::cerr << "Erreur GestionnaireFilms: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
	return false;
}

/// Ajoute un film, tout en mettant à jour les filtres, mais il ne peut pas avoir le meme film plus d'un fois
/// \param film         Le film que l'on veut ajouter
/// \return             True si on ajoute le film et false si on n'ajoute pas le film
bool GestionnaireFilms::ajouterFilm(const Film& film)
{
	if (getFilmParNom(film.nom) == nullptr)
	{
		films_.push_back(std::make_unique<Film>(film));
		filtreNomFilms_.emplace(film.nom, films_.back().get());
		filtreGenreFilms_[film.genre].push_back(films_.back().get());
		filtrePaysFilms_[film.pays].push_back(films_.back().get());
		return true;
	}

	return false;
}

/// Supprime le film qu'on souhaite supprimer, tout en mettant à jour les filtres.
/// \param nomFilm      Le film que nous souhaitons supprimer.
/// \return             True si nous avons supprimer le film, sinon retourne false, car le film est inexistant.
bool GestionnaireFilms::supprimerFilm(const std::string& nomFilm)
{
	std::vector<std::unique_ptr<Film>>::iterator iter = std::find_if(films_.begin(), films_.end(),
		[&nomFilm](const std::unique_ptr<Film>& film) {
			return film->nom == nomFilm;
		});
	if (iter != films_.end())
	{
		std::vector<const Film*>& vecGenre = filtreGenreFilms_.at(iter->get()->genre);
		std::vector<const Film*>& vecPays = filtrePaysFilms_.at(iter->get()->pays);

		filtreNomFilms_.erase(iter->get()->nom);
		vecGenre.erase(std::remove_if(vecGenre.begin(), vecGenre.end(), [&nomFilm](const Film* film) {
			return film->nom == nomFilm;
			}),
			vecGenre.end());
		vecPays.erase(std::remove_if(vecPays.begin(), vecPays.end(), [&nomFilm](const Film* film) {
			return film->nom == nomFilm;
			}),
			vecPays.end());

		films_.erase(iter);
		return true;
	}

	return false;
}

/// Nous donne le nombre de film présent
/// \return             le nombre de film dans le films_ de la classe GestionnaireFilms
std::size_t GestionnaireFilms::getNombreFilms() const
{
	return films_.size();
}

/// Recherche un film par rapport à son nom.
/// \param nom          Le nom du film recherché.
/// \return             nullptr si le film n'est pas présente, sinon il retourne un pointeur vers ce film.
const Film* GestionnaireFilms::getFilmParNom(const std::string& nom) const
{
	if (filtreNomFilms_.find(nom) != filtreNomFilms_.end())
	{
		return filtreNomFilms_.find(nom)->second;
	}

	return nullptr;
}

/// Recherche des films par rapport à son genre.
/// \param genre        Le genre de film recherché.
/// \return             le vecteur de pointeur de film si le genre existe dans notre filtre sinon retourne un vecteur vide.
std::vector<const Film*> GestionnaireFilms::getFilmsParGenre(Film::Genre genre) const
{
	if (filtreGenreFilms_.find(genre) != filtreGenreFilms_.end())
	{
		return filtreGenreFilms_.find(genre)->second;
	}

	return std::vector<const Film*>{};
}

/// Recherche des films par rapport à son pays.
/// \param pays         Le pays du film recherché.
/// \return             le vecteur de pointeur de film si le pays existe dans notre filtre sinon retourne un vecteur vide.
std::vector<const Film*> GestionnaireFilms::getFilmsParPays(Pays pays) const
{
	if (filtrePaysFilms_.find(pays) != filtrePaysFilms_.end())
	{
		return filtrePaysFilms_.find(pays)->second;
	}

	return std::vector<const Film*>{};
}

/// Recherche des films par rapport à un intervalle d'année.
/// \param anneeDebut   L'annee qui débute l'intervalle.
/// \param anneeFin     L'annee qui finie l'intervalle.
/// \return             le vecteur de pointeur de film qui contient tous les films qui respectent l'intervalle.
std::vector<const Film*> GestionnaireFilms::getFilmsEntreAnnees(int anneeDebut, int anneeFin)
{
	std::vector<const Film*> filmsCopie;
	std::copy_if(films_.begin(), films_.end(), RawPointerBackInserter(filmsCopie), EstDansIntervalleDatesFilm(anneeDebut, anneeFin));
	return filmsCopie;
}