#pragma once
#include "./GElement.h"

// Sommet d'un graphe en general
// Valeur est l'information associee au sommet : elle depend de l'application du graphe

template <class T>
class Sommet :
	public GElement<T> {
public:
	int degre;
	// Rappel : degre = nombre d'aretes adjacentes a ce sommet
	
	// Un sommet est toujours cree isole (c'est-a-dire qu'il n'y a pas d'arete adjacente a ce sommet)
	Sommet(const T & valeur) : GElement<T>(valeur), degre(0) {}

	operator std::string () const;
};

template <class T>
Sommet<T>::operator std::string () const {
	std::ostringstream oss;

	oss << "Sommet : [" << std::endl;
	oss << GElement<T>::operator std::string() << std::endl;
	oss << "Degré = " << degre << std::endl;
	oss << "]";
	return oss.str();
}

template <class T>
std::ostream & operator << (std::ostream & os, const Sommet<T> & sommet) {
	return os << (std::string)sommet;
}
