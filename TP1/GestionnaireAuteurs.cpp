// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include<GestionnaireAuteurs.h>

// TODO: Constructeur par défault en utilisant la liste d'initialisation
GestionnaireAuteurs::GestionnaireAuteurs() :
	
	nbAuteurs_(0)

{

}
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur) {
	if (nbAuteurs_ < NB_AUTEURS_MAX) {
		auteurs_[nbAuteurs_++] = auteur;
		return true;
	}
	else
		return false;
	
}
// Ajouter un auteur au tableau des auteurs.
// Retourner false si il n'y a plus de place dans le tableau.

Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur) {
	Auteur* auteurVoulu = nullptr;
	for (size_t i = 0; i < nbAuteurs_; i++) {
		if (auteurs_[i].getNom() == nomAuteur) {
			auteurVoulu = &auteurs_[i];
		}
	}
	return auteurVoulu;
}
// Chercher dans la liste des auteurs si un auteur comporte le nom passé en paramètre.
// Retourner un nullptr si ce n'est pas le cas.

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    nbAuteurs_ = 0;
	std::ifstream fichier(nomFichier);
	bool peutCharger = true;
    if (fichier)
	{
		std::string ligne;
		while (getline(fichier, ligne) && peutCharger)
				peutCharger = lireLigneAuteur(ligne);
			
		return peutCharger;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        auteurs_[i].afficher(stream);
        stream << '\n';
    }
}

size_t GestionnaireAuteurs::getNbAuteurs() const {
	return nbAuteurs_;
}
//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
	
	std::istringstream stream(ligne);
    std::string nom;
    unsigned int age;
   

    // TODO
    // Utiliser l'opérateur d'extraction (>>) depuis le stream
	if (stream >> std::quoted(nom) >> age) {
	
		return ajouterAuteur(Auteur(nom, age));
	}
	else {
		return false;
	}

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
}