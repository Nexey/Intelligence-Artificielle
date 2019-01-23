#include <vector>
#include "../Ecran/Formes/FormeEcran.h"
#include "../Experts/�v�nements/Redimension/RedimensionCOR.h"
#include "../Experts/�v�nements/Fermeture/FermetureCOR.h"
#include "../Experts/�v�nements/Touches/Fermeture/FermetureToucheCOR.h"
#include "../Experts/�v�nements/Touches/D�placement/DeplacementToucheCOR.h"
#include <Windows.h> // Pour les accents dans la console sous Windows

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows
	const unsigned ratio = 16u;
	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(ratio - 1, ratio - 1);
	FenetreEcran fenetre("Test Transfo Affine", 2*ratio*ratio, 2*ratio*ratio, CoinBasGauche, CoinHautDroit, ratio);
	std::vector<FormeEcran> formes;

	sf::Shape * rectangleSFML;
	for (int i = 0; i < ratio; i++) {
		for (int j = 0; j < ratio; j++) {
			rectangleSFML = new sf::RectangleShape(sf::Vector2f(ratio, ratio));
			rectangleSFML->setFillColor(sf::Color::Blue);
			formes.push_back(FormeEcran(rectangleSFML, &fenetre, Vecteur2D(i, j)));
		}
	}

	FormeEcran rectangle(new sf::RectangleShape(sf::Vector2f(ratio / 2, ratio / 2)), &fenetre, Vecteur2D(4, 4));
	rectangle.formeSFML->setFillColor(sf::Color::Red);
	rectangle.formeSFML->setOutlineColor(sf::Color::Green);

	sf::FloatRect rectGlobBounds = rectangle.formeSFML->getGlobalBounds();
	rectangle.setPos(Vecteur2D(4., 4.));

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
		rectangle.dessine();
		fenetre.display();
	}
	system("pause");
	return 0;
}