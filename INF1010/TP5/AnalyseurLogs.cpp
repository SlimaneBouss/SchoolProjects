/// Gestionnaire de films.
/// \author Kevin Lam (2024921) Slimane Boussafeur (2017001)
/// \date 2020-04-08

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string &nomFichier,
                                         GestionnaireUtilisateurs &gestionnaireUtilisateurs,
                                         GestionnaireFilms &gestionnaireFilms)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        logs_.clear();
        vuesFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string timestamp;
            std::string idUtilisateur;
            std::string nomFilm;

            if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
            {
                // TODO: Uncomment une fois que la fonction creerLigneLog est écrite
                creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
            }
            else
            {
                std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/// Creer une ligne log a partir des informations envoyées en parametre si celle si n'existe pas déjà.
/// \param timestamp                Le timeStamp de ligne log.
/// \param idUtuilisateur           Le id pour la ligne log.
/// \param nomFilm                  Le nom du film pour la ligne log.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout la création de ligne log s'est effectué avec succès, false sinon.

bool AnalyseurLogs::creerLigneLog(const std::string &timestamp, const std::string &idUtilisateur, const std::string &nomFilm,
                                  GestionnaireUtilisateurs &gestionnaireUtilisateurs, GestionnaireFilms &gestionnaireFilms)
{
    if ((gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur) != nullptr) && (gestionnaireFilms.getFilmParNom(nomFilm) != nullptr))
    {
        LigneLog log = {timestamp, gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur), gestionnaireFilms.getFilmParNom(nomFilm)};
        ajouterLigneLog(log);
        return true;
    }

    return false;
}



/// Ajoute une ligne logs au vecteur et incrémente de nombre de vues pour ce film.
/// \param ligneLog        Ligne log à ajouter
void AnalyseurLogs::ajouterLigneLog(const LigneLog &ligneLog)
{
    auto iter = std::lower_bound(logs_.begin(), logs_.end(), ligneLog, ComparateurLog());
    logs_.insert(iter, ligneLog);
    vuesFilms_[ligneLog.film]++;
}


/// Retourne le nombre de vues pour un certain film.
/// \param film                     Le film pour lequel nous voulons le nombre de vues.
/// \return                         Le nombre de vues.

int AnalyseurLogs::getNombreVuesFilm(const Film *film) const
{
	if (vuesFilms_.find(film) == vuesFilms_.end()) {
		return 0;
	}
    return vuesFilms_.at(film);
}


/// Retourne le film le plus populaire si le vecteur de log n'est pas vide.
/// \return             Un pointeur vers le film le populaire ou nullptr.

const Film *AnalyseurLogs::getFilmPlusPopulaire() const
{
    if (!logs_.empty())
    {
        return std::max_element(vuesFilms_.begin(), vuesFilms_.end(), ComparateurSecondElementPaire<const Film *, int>())->first;
    }

    return nullptr;
}

/// Retourne la liste des n films les plus populaires
/// \param nombre       Le nombre de films voulu.
/// \return             La liste des n films les plus populaires.

std::vector<std::pair<const Film *, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{
    std::vector<std::pair<const Film *, int>> vecPopulaire(std::min(nombre, vuesFilms_.size()));
    std::partial_sort_copy(vuesFilms_.begin(), vuesFilms_.end(), vecPopulaire.begin(), vecPopulaire.end(),
		[](const std::pair<const Film *, int> &premier, const std::pair<const Film *, int> &deuxieme) -> bool { return premier.second > deuxieme.second; });
    return vecPopulaire;
}

/// Retourne le nombre de vue pour un certain utilisateur
/// \param nombre       Un pointeur vers l'utilisateur en question.
/// \return             Le nombre de vue.

int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur *utilisateur) const
{
    return static_cast<int>(std::count_if(logs_.begin(), logs_.end(), [&utilisateur](const LigneLog &log) { return log.utilisateur == utilisateur; }));
}


/// Retourne la liste de tout les films vue par l'utilisateur
/// \param nombre       Un pointeur vers l'utilisateur en question.
/// \return             Le liste de tous le films vues.

std::vector<const Film *> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur *utilisateur) const
{
    std::unordered_set<const Film *> setFilms;
    for (unsigned int i = 0; i < logs_.size(); i++)
    {
        if (utilisateur == logs_[i].utilisateur)
        {
            setFilms.insert(logs_[i].film);
        }
    }

    return std::vector<const Film *>(setFilms.begin(), setFilms.end());
}