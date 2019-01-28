#pragma once
#include <iostream>
#include <string>
#include <sstream>

class AElement {
	// Identifiant est la cl� unique
	// Sauf qu'�crire "int cle" c'est moche donc je l'appelle identifiant
	int identifiant;

	static int generateurIdentifiant;
public:
	explicit AElement() : identifiant(++generateurIdentifiant) {}
	operator std::string() const { std::ostringstream o; o << "Identifiant : " << identifiant; return o.str(); }
	int getIdentifiant() const { return identifiant; }
	static const int getProchainIdentifiant() { return generateurIdentifiant; }
	friend std::ostream & operator << (std::ostream & os, const AElement& aElement) { return os << (std::string)aElement; }
};