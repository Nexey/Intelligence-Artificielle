#pragma once
#include <SFML/Graphics.hpp>
#include "../Ecran/Fenetre/FenetreEcran.h"
class GestionnaireEvenement {
public:
	// Un expert h�ritant de cette classe peut g�rer les �v�nements produits par la fen�tre
	virtual const bool gerer(const sf::Event&) = 0;
};