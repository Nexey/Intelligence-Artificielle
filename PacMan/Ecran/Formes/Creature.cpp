#include "Creature.h"

Creature::Creature(sf::Shape * formeSFML, FenetreEcran * fenetre, Sommet<FormeEcran>* positionSommet, int choixNiveau) :
	formeSFML(formeSFML),
	fenetre(fenetre),
	sommetActuel(positionSommet),
	choixNiveau(choixNiveau),
	prochainSommet(positionSommet),
	directionCreature(FenetreEcran::VECTEUR2D_STOP),
	alpha(0.f),
	velocite(0.05f) {
	this->formeSFML->setOrigin(this->formeSFML->getGlobalBounds().width / 2.f, this->formeSFML->getGlobalBounds().height / 2.f);
	this->miseAJourPositionEcran(positionSommet->valeur.getPositionEcran());
}

Creature::~Creature() {}

void Creature::miseAJourVoisins() {
	voisins = fenetre->niveaux->at(this->choixNiveau)->voisins(this->sommetActuel);
}

void Creature::miseAJourPositionEcran(const Vecteur2D & nouvPos) {
	this->formeSFML->setPosition(fenetre->calculPos(nouvPos));
}

const bool Creature::estImmobile() const {
	return alpha == 0.f;
}

bool Creature::dessiner() {
	fenetre->draw(*formeSFML);
	return true;
}
