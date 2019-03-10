#include "FormeEcran.h"
#include "../../Exceptions/Erreur.h"

FormeEcran::FormeEcran(sf::Sprite * forme, FenetreEcran * fenetre, const Vecteur2D & p) : formeSFML(new sf::Sprite(*forme)), fenetre(fenetre), positionEcran(p) {
	//this->formeSFML->setOrigin(this->formeSFML->getGlobalBounds().width / 2.f, this->formeSFML->getGlobalBounds().height / 2);
	this->miseAJourPositionEcran(positionEcran);
}

FormeEcran::FormeEcran(const FormeEcran & f) : formeSFML(new sf::Sprite(*f.formeSFML)), fenetre(f.fenetre), positionEcran(f.positionEcran) {}

void FormeEcran::miseAJourPositionEcran(const Vecteur2D & nouvPos) {
	this->formeSFML->setPosition(fenetre->calculPos(nouvPos));
}

const bool FormeEcran::dessiner() {
	try {
		fenetre->draw(*formeSFML);
	}
	catch (Erreur e) {
#ifdef _DEBUG
		std::cerr << e.message << std::endl;
#endif
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

FormeEcran::operator std::string() const {
	std::stringstream ss;
	ss << "Position écran : " << positionEcran << std::endl;
	ss << "Position réelle : " << formeSFML->getPosition().x << ", " << formeSFML->getPosition().y << std::endl;
	return ss.str();
}

FormeEcran::~FormeEcran() {}

std::ostream & operator<<(std::ostream &o, const FormeEcran &f) {
	return o << (std::string)f;
}
