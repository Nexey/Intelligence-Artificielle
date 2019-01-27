#pragma once
#include "./AElement.h"
/*
Represente la classe template de base des elements d'un graphe qui peuvent etre des sommets ou des aretes.

A ce niveau, on ne peut que definir que l'identifiant d'un element et la valeur (c'est-a-dire l'information ) inscrite dans cet element.

En effet tout element d'un graphe est defini par un identifiant (c-a-d une valeur non nulle et unique) et contient  generalement une information,
qui peut etre un nom, une couleur, une position, etc.
*/

template <class T>
class GElement :
	public AElement {
public:
	T valeur;
	GElement(const T & valeur): AElement(), valeur(valeur) {}
	operator std::string() const {
		std::ostringstream o;
		o << this->AElement::operator std::string() << ", Valeur = " << valeur;
		return o.str();
	}
	
	friend std::ostream & operator << (std::ostream & os, const GElement<T>& g) {
		return os << (std::string) g;
	}
};