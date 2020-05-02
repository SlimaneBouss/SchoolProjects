////////////////////////////////////////////////////////////////////////////////
/// \file    Matrice .h
/// \author  Kevin Lam and Slimane Boussafeur
/// \version Dernière entrée : 2020-03-19
/// \since   Création : 2020-01-11
///
/// Ce fichier contient la definition ainsi que l'implementation des méthodes de la classe Matrice
////////////////////////////////////////////////////////////////////////////////

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename T>
class Matrice
{

public:
	Matrice();
	// Destructeur
	~Matrice() = default;
	T operator()(const size_t& posY, const size_t& posX) const;
	// Lecture du fichier
	bool chargerDepuisFichier(const std::string& nomFichier);
	bool lireElement(const std::string& elementFichier, const size_t& posY,
		const size_t& posX);
	// Remplir un matrice
	bool ajouterElement(T element, const size_t& posY, const size_t& posX);
	// Faire une copie
	std::unique_ptr<Matrice<T>> clone() const;
	// Setters
	void setHeight(size_t height);
	void setWidth(size_t width);
	// Getters
	size_t getHeight() const;
	size_t getWidth() const;

private:
	std::vector<std::vector<T>> elements_;
	size_t height_;
	size_t width_;
};

namespace
{
	static constexpr int CAPACITE_MATRICE = 100;
}

//! Constructeur par defaut de la classe Matrice

template <typename T>
inline Matrice<T>::Matrice()
	: elements_(std::vector<std::vector<T>>(CAPACITE_MATRICE, std::vector<T>(CAPACITE_MATRICE))),
	  height_(0),
	  width_(0) {}

//! Méthode qui retourne la taille de la matrice
//! \return height  la taille de la matrice

template <typename T>
inline size_t Matrice<T>::getHeight() const
{
	return height_;
}

//! Méthode qui retourne la largeur de la matrice
//! \return height  la largeur de la matrice

template <typename T>
inline size_t Matrice<T>::getWidth() const
{
	return width_;
}

//! Méthode de l'operateur () de la classe Matrice qui permet d'acceder a un element de la matrice
//! \param     posX        La ligne ou se trouve l'element
//! \param     PosY        La colone ou se trouve l'element
//! \return    Un element de la matrice de type T

template <typename T>
inline T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const
{
	if (posY > (height_) || posX > width_)
	{
		return T();
	}

	return elements_[posX][posY];
}


//! Méthode qui permet d'ajouter un element a la matrice
//! \param     posX        La ligne ou l'on veut ajouter l'element
//! \param     PosY        La colone ou l'on veut ajouter l'element
//! \return    un bool indiquant si l'operation a ete un succes


template <typename T>
inline bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX)
{
	if (posY <= height_ || posX <= width_)
	{
		elements_[posX][posY] = element;
		return true;
	}

	return false;
}

//! Méthode qui lit un element et qui l'ajoute a la matrice
//! \param     elementFichier       element de type generique a lire
//! \param     posX                 La ligne ou l'on veut ajouter l'element
//! \param     PosY                 La colone ou l'on veut ajouter l'element
//! \return    un bool indiquant si l'operation a ete un succes

template <typename T>
inline bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX)
{
	std::istringstream stream(elementFichier);
	T elementAAjouter;

	if (stream >> elementAAjouter)
	{
		return ajouterElement(elementAAjouter, posY, posX);
	}

	return false;
}

//! Méthode qui charge un fichier pour en creer une matrice
//! \param     nomFichier        Le nom du fichier a charger
//! \return    un bool indiquant si l'operation a ete un succes

template <typename T>
inline bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichierMatrice(nomFichier);

	if (fichierMatrice)
	{
		
		std::string ligneMatrice;
		setHeight(0);

		while (std::getline(fichierMatrice, ligneMatrice))
		{
			if (ligneMatrice != "L")
			{
				if ( !(lireElement(ligneMatrice, getHeight() - 1, getWidth())) )
				{
					return false;
				}

				setWidth(getWidth() + 1);
			}

			else
			{
				setWidth(0);
				setHeight(getHeight() + 1);
			}
		}

		return true;
	}

	return false;
}

//! Méthode qui clone la matrice
//! \return    un pointeur vers le clone de la matrice

template <typename T>
inline std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
	std::unique_ptr<Matrice<T>> cloneMatrice = std::make_unique<Matrice<T>>();
	cloneMatrice->height_ = height_;
	cloneMatrice->width_ = width_;
	cloneMatrice->elements_ = elements_;

	return move(cloneMatrice);
}

//! Méthode qui set le nombre la taille de la matrice
//! \param height  Le nouvelle taille

template <typename T>
inline void Matrice<T>::setHeight(size_t height)
{
	height_ = height;
}

//! Méthode qui set le nombre la largeur de la matrice
//! \param height  Le nouvelle largeur

template <typename T>
inline void Matrice<T>::setWidth(size_t width)
{
	width_ = width;
}

#endif