#pragma once
#include "Iterateur.h"

template<class T>
class Liste {
	PElement<T> * tete;
public:
	Liste() : tete(NULL) {}

	// G�n�re un it�rateur pour parcourir la liste
	Iterateur<T> getIterateur() const;

	// Ajoute un �l�ment au PElement
	void ajouterElem(T v);
	virtual ~Liste();
};

template<class T>
inline Iterateur<T> Liste<T>::getIterateur() const {
	return Iterateur<T>(tete);
}

template<class T>
inline void Liste<T>::ajouterElem(T v) {
	PElement<T>::insertion(&v, tete);
}

template<class T>
inline Liste<T>::~Liste() {
	PElement<T>::efface1(tete);
}
