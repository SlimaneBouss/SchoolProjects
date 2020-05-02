/// Gestionnaire de films.
/// \author Kevin Lam (2024921) Slimane Boussafeur (2017001)
/// \date 2020-04-08

#ifndef FONCTEUR_H
#define FONCTEUR_H 
#include <iostream>
#include <algorithm>
#include "LigneLog.h"

/// Foncteur qui vérifie si la date sortie d'un film se trouve dans un certain intervalle

class EstDansIntervalleDatesFilm {
public :
	EstDansIntervalleDatesFilm(int borneInf, int borneSup)
		: borneInf_(borneInf), borneSup_(borneSup) {}

	bool operator() (const std::unique_ptr<Film>& film) {
		return (film->annee <= borneSup_ && film->annee >= borneInf_);
	}
private:
	int borneInf_;
	int borneSup_;
};

/// Foncteur qui compare les time stamp de deux lignes log

class ComparateurLog {
public:

	bool operator() (const LigneLog& premier, const LigneLog& deuxieme) {
		return premier.timestamp < deuxieme.timestamp;
	}

};

/// Foncteur générique qui compare  les seconds elements de deux pairs

template< typename T1, typename T2>
class ComparateurSecondElementPaire {

public :

	bool operator() (const std::pair<T1,T2>& premier, const std::pair<T1, T2>& deuxieme) {
		return premier.second < deuxieme.second;
	}
};

#endif