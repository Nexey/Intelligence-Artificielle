#pragma once
#include <SFML/Graphics.hpp>

class GestionnaireEvenement {
public:
	// Un expert héritant de cette classe peut gérer les évènements produits par la fenêtre
	virtual const bool gerer(const sf::Event&) = 0;
};