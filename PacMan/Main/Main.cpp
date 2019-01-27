#include <vector>
#include "../Ecran/Formes/Creature.h"
#include "../Experts/Évènements/Redimension/RedimensionCOR.h"
#include "../Experts/Évènements/Fermeture/FermetureCOR.h"
#include "../Experts/Évènements/Touches/Fermeture/FermetureToucheCOR.h"
#include "../Experts/Évènements/Touches/Déplacement/DeplacementToucheCOR.h"
#include "../Graphe/Graphe.h"
#include "../Liste.h"
#include <Windows.h> // Pour les accents dans la console sous Windows

int main() {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows
	const unsigned ratio = 16u;

	Vecteur2D
		CoinBasGauche(0, 0),
		CoinHautDroit(ratio - 1, ratio - 1);
	FenetreEcran fenetre("PacMan", 2*ratio*ratio, 2*ratio*ratio, CoinBasGauche, CoinHautDroit, ratio);

	Graphe<FormeEcran, FormeEcran> graphe;
	sf::Shape * rectangleSFML;
	for (int i = 0; i < ratio; i++) {
		for (int j = 0; j < ratio; j++) {
			rectangleSFML = new sf::RectangleShape(sf::Vector2f(ratio, ratio));
			rectangleSFML->setFillColor(sf::Color::Blue);
			graphe.creeSommet(FormeEcran(rectangleSFML, &fenetre, Vecteur2D(i, j)));
		}
	}

	Creature rectangle(new sf::RectangleShape(sf::Vector2f(ratio / 3, ratio / 3)), &fenetre, Vecteur2D(4, 4));
	rectangle.formeSFML->setFillColor(sf::Color::Red);
	rectangle.formeSFML->setOutlineColor(sf::Color::Green);
	rectangle.formeSFML->setOutlineThickness(2.f);
	fenetre.ajouterForme(rectangle);

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
		graphe.dessineTousSommets<FenetreEcran>(fenetre);

		fenetre.effectuer(&FenetreEcran::deplacer);
		fenetre.effectuer(&FenetreEcran::dessine);
		fenetre.display();
	}
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}