#pragma once
#include <string>
#include <sstream>

class AElement {
public:
	int clef;

	explicit AElement(const int clef) : clef(clef) {}
	operator std::string() const { std::ostringstream o; o << "clef = " << clef; return o.str(); }

	friend std::ostream & operator << (std::ostream & os, const AElement& aElement) { return os << (std::string)aElement; }
};