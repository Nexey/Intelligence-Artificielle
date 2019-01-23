#include "FormeEcran.h"
#include "../../Exceptions/Erreur.h"

FormeEcran::FormeEcran(sf::Shape * forme, FenetreEcran * fenetre, const Vecteur2D & p) : formeSFML(forme), fenetre(fenetre), positionEcran(p) {
	this->formeSFML->setOrigin(this->formeSFML->getGlobalBounds().width / 2.f, this->formeSFML->getGlobalBounds().height / 2);
	this->setPos(positionEcran);
}

FormeEcran::FormeEcran(const FormeEcran & f) : formeSFML(f.formeSFML), fenetre(f.getFenetre()), positionEcran(f.getPositionEcran()) {}

void FormeEcran::setPos(const Vecteur2D & nouvPos) {
	this->formeSFML->setPosition(fenetre->calculPos(nouvPos));
}

const bool FormeEcran::dessine() {
	try {
		fenetre->draw(*formeSFML);
	}
	catch (Erreur e) {
		return false;
	}
	return true;
}

FenetreEcran * FormeEcran::getFenetre() const {
	return fenetre;
}

const Vecteur2D FormeEcran::getPositionEcran() const {
	return positionEcran;
}

FormeEcran::~FormeEcran() {}
