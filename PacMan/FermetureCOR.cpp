#include "FermetureCOR.h"

FermetureCOR::FermetureCOR(FenetreEcran * fenetre) : EvenementCOR(fenetre, sf::Event::Closed) {}

FermetureCOR::FermetureCOR(FenetreEcran * fenetre, GestionnaireEvenement * suivant) : EvenementCOR(fenetre, sf::Event::Closed, suivant) {}

FermetureCOR::~FermetureCOR() {}

const bool FermetureCOR::appliquer() {
	std::cout << "Fermeture de la fenêtre de jeu..." << std::endl;
	this->fenetre->close();
	return true;
}