/// Gestionnaire de films.
/// \author Kevin Lam (2024921) Slimane Boussafeur (2017001)
/// \date 2020-04-08

#include "GestionnaireUtilisateurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/// Affiche les informations des utilisateurs gérés par le gestionnaire d'utilisateurs à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des utilisateurs.
/// \param gestionnaireFilms    Le gestionnaire d'utilisateurs à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireUtilisateurs& gestionnaireUtilisateurs)
{
	// TODO: Uncomment une fois que la fonction getNombreUtilisateurs est écrite
	outputStream << "Le gestionnaire d'utilisateurs contient " << gestionnaireUtilisateurs.getNombreUtilisateurs()
		<< " utilisateurs:\n";

	// TODO: Réécrire l'implémentation avec des range-based for et structured bindings (voir énoncé du TP)
	for (const auto& [key, value] : gestionnaireUtilisateurs.utilisateurs_)
	{
		outputStream << '\t' << value << '\n';
	}

	return outputStream;
}

/// Ajoute les utilisateurs à partir d'un fichier de données d'utilisateurs.
/// \param nomFichier   Le fichier à partir duquel lire les informations des utilisateurs.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireUtilisateurs::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		utilisateurs_.clear();

		bool succesParsing = true;

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			std::istringstream stream(ligne);

			std::string id;
			std::string nom;
			int age;
			int pays;

			if (stream >> id >> std::quoted(nom) >> age >> pays)
			{
				// TODO: Uncomment une fois que la fonction ajouterUtilisateur est écrite
				ajouterUtilisateur(Utilisateur{ id, nom, age, static_cast<Pays>(pays) });
			}
			else
			{
				std::cerr << "Erreur GestionnaireUtilisateurs: la ligne " << ligne
					<< " n'a pas pu être interprétée correctement\n";
				succesParsing = false;
			}
		}
		return succesParsing;
	}
	std::cerr << "Erreur GestionnaireUtilisateurs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
	return false;
}

/// Ajoute un utilisateur dans l'unordered_map de la classe GestionnaireUtilisateur.
/// \param utilisateur  L'utilisateur que l'on souhaite ajouter.
/// \return             True si l'ajout s'est effectué, sinon false.
bool GestionnaireUtilisateurs::ajouterUtilisateur(const Utilisateur& utilisateur)
{
	return utilisateurs_.emplace(utilisateur.id, utilisateur).second;
}

/// Supprime un utilisateur dans l'unordered_map de la classe GestionnaireUtilisateur.
/// \param utilisateur  L'utilisateur que l'on souhaite supprimer.
/// \return             True si la supression s'est effectué, sinon false.
bool GestionnaireUtilisateurs::supprimerUtilisateur(const std::string& idUtilisateur)
{
	return utilisateurs_.erase(idUtilisateur) == 1;
}

/// Nous donne le nombre d'utilisateur present dans l'unordered_map de la classe GestionnaireUtilisateur.
/// \return             le nombre d'element dans l'unordered_map.
std::size_t GestionnaireUtilisateurs::getNombreUtilisateurs() const
{
	return utilisateurs_.size();
}

/// Recherche un utilisateur selon un identifiant
/// \param id           L'identifiant de l'utilisateur.
/// \return             Un pointeur vers l'utilisateur s'il est présent dans le conteneur, sinon nullptr.
const Utilisateur* GestionnaireUtilisateurs::getUtilisateurParId(const std::string& id) const
{
	if (utilisateurs_.find(id) != utilisateurs_.end())
	{
		return &utilisateurs_.find(id)->second;
	}

	return nullptr;
}