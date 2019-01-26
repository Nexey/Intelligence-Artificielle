#pragma once

#include "Graphe\PElement.h"
#include <cassert>

template<class T>
class Iterateur {
	PElement<T> * tete;
	PElement<T> * curseur;
	Iterateur() = delete;
public:
	Iterateur(PElement<T> * tete);
	Iterateur(const Iterateur<T>& it);
	
	// Regarde si PElement possède un maillon suivant
	bool aSuivant() const;

	// Récupère le maillon suivant
	T suivant();

	// Remets le curseur au début de la liste
	void debut();

	virtual ~Iterateur();
};

template<class T>
inline Iterateur<T>::Iterateur(PElement<T>* tete) : tete(tete), curseur(tete) {
}

template<class T>
inline Iterateur<T>::Iterateur(const Iterateur<T>& it) : tete(it.tete), curseur(it.curseur) {}

template<class T>
inline bool Iterateur<T>::aSuivant() const {
	return curseur != NULL;
}

template<class T>
T Iterateur<T>::suivant() {
	assert(aSuivant());
	T v = *(curseur->v);
	curseur = curseur->s;
	return v;
}

template<class T>
void Iterateur<T>::debut() {
	curseur = tete;
}

template<class T>
inline Iterateur<T>::~Iterateur() {}