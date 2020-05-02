////////////////////////////////////////////////////////////////////////////////
/// \file    Pixel .h
/// \author  Kevin Lam and Slimane Boussafeur
/// \version Dernière entrée : 2020-03-19
/// \since   Création : 2020-01-11
///
/// Ce fichier contient l'implementation des méthodes de la classe Pixel
////////////////////////////////////////////////////////////////////////////////

#include "Pixel.h"

//! Constructeur par defaut de la classe Matrice

Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}


//! constructeur par paramètres de la classe
//! \param rouge	 l'élément R du pixel, entre 0 -> 255
//!		   vert		 l'élément G du pixel, entre 0 -> 255
//!		   bleu		 l'élément B du pixel, entre 0 -> 255

Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
	: rouge_(rouge), vert_(vert), bleu_(bleu) {}

//! Méthode  de l'operateur =  permettant de copier chacune des couleurs d'un pixel
//! \param   pixel			  Pixel duquel nous allons copier

void Pixel::operator=(const Pixel& pixel)
{
	if (this != &pixel)
	{
		rouge_ = pixel.rouge_;
		vert_ = pixel.vert_;
		bleu_ = pixel.bleu_;
	}
}

//! Méthode qui set la couleur rouge du pixel
//! \param rouge  Le nouvelle couleur rouge

void Pixel::setRouge(int rouge)
{
	rouge_ = (rouge > 255) ? 255 : (rouge < 0) ? 0 : static_cast<uint8_t>(rouge);
}

//! Méthode qui set la couleur verte du pixel
//! \param vert  Le nouvelle couleur verte

void Pixel::setVert(int vert)
{

	vert_ = (vert > 255) ? 255 : (vert < 0) ? 0 : static_cast<uint8_t>(vert);
}

//! Méthode qui set la couleur bleue du pixel
//! \param bleu  Le nouvelle couleur bleue

void Pixel::setBleu(int bleu)
{
	bleu_ = (bleu > 255) ? 255 : (bleu < 0) ? 0 : static_cast<uint8_t>(bleu);
}

//! Méthode qui retourne la couleur rouge du pixel
//! \return la couleur rouge

uint8_t Pixel::getRouge() const { return rouge_; }

//! Méthode qui retourne la couleur verte du pixel
//! \return la couleur verte

uint8_t Pixel::getVert() const { return vert_; }

//! Méthode qui retourne la couleur bleue du pixel
//! \return la couleur verte

uint8_t Pixel::getBleu() const 
{
	return bleu_; 
}

//! Méthode de l'operateur << qui affiche  ses informations d'un pixel
//! \param     os             Le stream dans lequel afficher
//! \param     pixel          Le pixel qu'on veut afficher dans le stream
//! \return    os             Le stream modifié

std::ostream& operator<<(std::ostream& os, Pixel pixel)
{
	// TO DO
	os << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<int>(pixel.getRouge()) << " "
		<< std::setfill('0') << std::setw(2) << static_cast<int>(pixel.getVert()) << " "
		<< std::setfill('0') << std::setw(2) << static_cast<int>(pixel.getBleu());
	return os;
}

//! Méthode de l'operateur >> qui lit ses informations d'un pixel
//! \param     is             Le stream duquel nous voulons lire
//! \param     pixel          Le pixel lu
//! \return    is             Le stream modifié

std::istream& operator>>(std::istream& is, Pixel& pixel)
{
	
	int rouge, vert, bleu;
	is >> rouge >> vert >> bleu;

	pixel.setRouge(rouge);
	pixel.setVert(vert);
	pixel.setBleu(bleu);

	return is;
}