#include "AreteVerticaleCOR.h"

AreteVerticaleCOR::AreteVerticaleCOR(FenetreEcran * fenetre, GestionnaireCreationAretes * suivant) : CreationArete(fenetre, Vecteur2D(0, 1), suivant) {}

AreteVerticaleCOR::~AreteVerticaleCOR() {}

Arete<FormeEcran, FormeEcran>* AreteVerticaleCOR::construit(Sommet<FormeEcran>* s1, Sommet<FormeEcran>* s2) {
	sf::Shape * rectangleSFML;
	rectangleSFML = new sf::RectangleShape(sf::Vector2f(8.f, 8.f));
	rectangleSFML->setFillColor(sf::Color::Green);
	return new Arete<FormeEcran, FormeEcran>(FormeEcran(rectangleSFML, this->fenetre, (s1->valeur.getPositionEcran() + s2->valeur.getPositionEcran()) * 0.5), s1, s2);
}
