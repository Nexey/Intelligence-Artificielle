#pragma once
#include <string>
#include <sstream>

class AElement {
	int clef;

	static int genereateurCle;
public:

	explicit AElement() : clef(genereateurCle++) {}
	operator std::string() const { std::ostringstream o; o << "clef = " << clef; return o.str(); }
	int getClef() const { return clef; }
	friend std::ostream & operator << (std::ostream & os, const AElement& aElement) { return os << (std::string)aElement; }
};