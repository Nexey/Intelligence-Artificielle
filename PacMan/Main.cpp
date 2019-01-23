#include <vector>
#include "FormeEcran.h"
#include "RedimensionCOR.h"
#include "FermetureCOR.h"
#include "FermetureToucheCOR.h"
#include "DeplacementToucheCOR.h"
#include <Windows.h> // Pour les accents dans la console sous Windows

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows
	const unsigned ratio = 16u;
	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(ratio - 1, ratio - 1);
	FenetreEcran fenetre("Test Transfo Affine", ratio*ratio, ratio*ratio, CoinBasGauche, CoinHautDroit, ratio);

	std::vector<FormeEcran> formes;

	sf::Shape * cercleSFML;
	for (int i = 0; i < ratio; i++) {
		for (int j = 0; j < ratio; j++) {
			cercleSFML = new sf::CircleShape(5.f);
			cercleSFML->setOrigin(cercleSFML->getGlobalBounds().width / 2.f, cercleSFML->getGlobalBounds().height / 2);
			cercleSFML->setFillColor(sf::Color::Blue);
			formes.push_back(FormeEcran(cercleSFML, &fenetre, Vecteur2D(i, j)));
		}
	}

	GestionnaireEvenement * experts =
		new DeplacementToucheCOR(&fenetre,
			new FermetureToucheCOR(&fenetre, 
				new RedimensionCOR(&fenetre,
					new FermetureCOR(&fenetre))));

	while (fenetre.isOpen()) {
		sf::Event event;
		while (fenetre.pollEvent(event)) {
			experts->gerer(event);
		}

		fenetre.clear();
		std::vector<FormeEcran>::iterator it = formes.begin();
		for (it; it < formes.end(); it++)
			it->dessine();
		fenetre.display();
	}
	system("pause");
	return 0;
}