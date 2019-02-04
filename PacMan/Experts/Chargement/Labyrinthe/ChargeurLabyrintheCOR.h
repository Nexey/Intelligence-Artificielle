#pragma once
#include "./Experts/Chargement/ChargeurCOR.h"
#include "./Experts/Création/Graphe/Sommets/Types de sommets/SommetCOR.h"
#include "./Graphe/Graphe.h"
#include <fstream>
#include <algorithm>

template<class T>
class ChargeurLabyrintheCOR :
	public ChargeurCOR<T> {
public:
	ChargeurLabyrintheCOR(FenetreEcran * fenetre, GestionnaireChargement<T> * suivant = NULL) : ChargeurCOR<T>(fenetre, "txt", suivant) {}

	T * construit(const std::string & chemin);

	virtual ~ChargeurLabyrintheCOR() {}
};

template<class T>
inline T * ChargeurLabyrintheCOR<T>::construit(const std::string & chemin) {
	Graphe<FormeEcran, FormeEcran> * niveau = new Graphe<FormeEcran, FormeEcran>();

	GestionnaireCreationSommet * expertCreationSommet = new SommetCOR(this->fenetre);
	
	std::ifstream fichierLaby(chemin);
	char elementsLabyrinthe[32][32];

	Sommet<FormeEcran> * sommet;

	for (int i = 31; i >= 0; i--) {
		for (int j = 31; j >= 0; j--) {
			fichierLaby >> elementsLabyrinthe[i][j];
			if ((sommet = expertCreationSommet->gerer(elementsLabyrinthe[i][j], Vecteur2D(j, i))) != nullptr)
				niveau->listeSommets.ajouterElem(*sommet);
		}
	}
	

	/*	// Iterator pour conversion en string
		// Je le garde ici parce que j'aime beaucoup même si ce n'est pas utile
	std::string labyStr(
		(std::istreambuf_iterator<char>(fichierLaby)),
		(std::istreambuf_iterator<char>()));
	labyStr.erase(remove(labyStr.begin(), labyStr.end(), ' '), labyStr.end());*/
	
	fichierLaby.close();
	return niveau;
}
