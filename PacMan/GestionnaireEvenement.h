#pragma once
#include <SFML/Graphics.hpp>
#include "FenetreEcran.h"
class GestionnaireEvenement {
public:
	virtual const bool gerer(const sf::Event&) = 0;
};