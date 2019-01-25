#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, const Vecteur2D & positionEcran) : FormeEcran(formeSFML, fenetre, positionEcran) {}

Creature::~Creature() {}
