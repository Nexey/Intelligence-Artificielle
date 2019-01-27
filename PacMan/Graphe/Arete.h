#pragma once
#include "./Sommet.h"

/**

// Représente une arête d'un graphe en general.

Une arête est définie par un sommet-début et par un sommet-fin et par une information valeur.

On ne connait pas la nature de valeur à ce niveau (valeur pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information portée par un sommet et
S est la nature de l'information portée par une arete

*/

template <class S, class T>
class Arete :
	public GElement<S> {
public:
	Sommet <T> *debut, *fin;
	// debut et fin peuvent etre interpretees comme des clefs etrangeres vers une table de sommets

	// Met à jour le degré des sommets que cette nouvelle arête va connecter
	Arete(const S & valeur, Sommet<T> * debut, Sommet<T> * fin) :
		GElement<S>(valeur), debut(debut), fin(fin) {
		debut->degre++;
		fin->degre++;
	}

	// Met a jour le degré des sommets que cette nouvelle arête va déconnecter
	virtual ~Arete() {
		debut->degre--;
		fin->degre--;
	}

	operator std::string () const;

	// Verifie si *this s'appuie sur s1 et s2
	// DONNEES : *this, s1, s2
	// RESULTATS : true si *this s'appuie sur s1 et s2 c'est-a-dire si (debut == s1 et fin == s2) ou (debut == s2 et fin == s1), false sinon
	bool estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Arete<S, T>::operator std::string () const {
	std::ostringstream oss;
	oss << "Arete : [" << std::endl;
	oss << GElement<S>::operator std::string() << std::endl;
	oss << "Identifiant début = " << debut->getIdentifiant() << std::endl;
	oss << "Identifiant fin = " << fin->getIdentifiant() << std::endl;
	oss << "]";
	return oss.str();
}

template <class S, class T>
std::ostream & operator << (std::ostream & os, const Arete<S, T> & arete) {
	return os << (std::string)arete;
}

template <class S, class T>
bool Arete<S, T>::estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const {
	return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
}