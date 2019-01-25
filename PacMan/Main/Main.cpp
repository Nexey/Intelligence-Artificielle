#include <vector>
#include "../Ecran/Formes/Creature.h"
#include "../Experts/Évènements/Redimension/RedimensionCOR.h"
#include "../Experts/Évènements/Fermeture/FermetureCOR.h"
#include "../Experts/Évènements/Touches/Fermeture/FermetureToucheCOR.h"
#include "../Experts/Évènements/Touches/Déplacement/DeplacementToucheCOR.h"
#include "../Graphe/PElement.h"
#include "../Liste.h"
#include <Windows.h> // Pour les accents dans la console sous Windows

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows
	const unsigned ratio = 16u;

	Liste<int> l;
	l.ajouterElem(new int(5));
	l.ajouterElem(new int (12));
	l.ajouterElem(new int (45));

	Iterateur<int> it = l.getIterateur();
	while (it.aSuivant()) {
		std::cout << it.suivant() << std::endl;
	}


	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(ratio - 1, ratio - 1);
	FenetreEcran fenetre("PacMan", 2*ratio*ratio, 2*ratio*ratio, CoinBasGauche, CoinHautDroit, ratio);
	std::vector<FormeEcran> formes;

	sf::Shape * rectangleSFML;
	for (int i = 0; i < ratio; i++) {
		for (int j = 0; j < ratio; j++) {
			rectangleSFML = new sf::RectangleShape(sf::Vector2f(ratio, ratio));
			rectangleSFML->setFillColor(sf::Color::Blue);
			formes.push_back(FormeEcran(rectangleSFML, &fenetre, Vecteur2D(i, j)));
		}
	}

	Creature rectangle(new sf::RectangleShape(sf::Vector2f(ratio / 2, ratio / 2)), &fenetre, Vecteur2D(4, 4));
	rectangle.formeSFML->setFillColor(sf::Color::Red);
	rectangle.formeSFML->setOutlineColor(sf::Color::Green);

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