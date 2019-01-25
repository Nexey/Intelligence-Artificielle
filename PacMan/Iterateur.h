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
	
	bool aSuivant() const;
	T suivant();
	void begin();

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
void Iterateur<T>::begin() {
	curseur = tete;
}

template<class T>
inline Iterateur<T>::~Iterateur() {}