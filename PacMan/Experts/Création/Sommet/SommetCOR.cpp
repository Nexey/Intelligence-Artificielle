#include "./SommetCOR.h"

SommetCOR::SommetCOR(FenetreEcran * fenetre, GestionnaireCreation * suivant) : CreationCOR(fenetre, suivant) {
	formes.push_back('1');
	formes.push_back('2');
	formes.push_back('3');
	formes.push_back('4');
	formes.push_back('5');
}

FormeEcran * SommetCOR::construit(const char & forme, const Vecteur2D & coords) {
	sf::Shape * rectangle = new sf::RectangleShape(sf::Vector2f(8.f, 8.f));
	rectangle->setFillColor(sf::Color::Blue);
	return new FormeEcran(rectangle, fenetre, coords);
}

SommetCOR::~SommetCOR() {}