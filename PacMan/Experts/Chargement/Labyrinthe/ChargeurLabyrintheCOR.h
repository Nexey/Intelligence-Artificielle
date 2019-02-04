#pragma once
#include "./Experts/Chargement/ChargeurCOR.h"
#include "./Experts/Cr�ation/Graphe/Sommets/Types de sommets/SommetCOR.h"
#include "./Experts/Cr�ation/Graphe/Ar�tes/Ar�tes orient�es/AreteHorizontaleCOR.h"
#include "./Experts/Cr�ation/Graphe/Ar�tes/Ar�tes orient�es/AreteVerticaleCOR.h"
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

	GestionnaireCreationSommet * expertCreationSommets = new SommetCOR(this->fenetre);
	
	std::ifstream fichierLaby(chemin);
	char elementsLabyrinthe[32][32];

	Sommet<FormeEcran> * sommet;

	for (int i = 31; i >= 0; i--) {
		for (int j = 31; j >= 0; j--) {
			fichierLaby >> elementsLabyrinthe[i][j];
			if ((sommet = expertCreationSommets->gerer(elementsLabyrinthe[i][j], Vecteur2D(j, i))) != nullptr)
				niveau->listeSommets.ajouterElem(*sommet);
		}
	}

	Iterateur<Sommet<FormeEcran>> iterateurListeTemp = niveau->listeSommets.getIterateur();
	Iterateur<Sommet<FormeEcran>> iterateurSommetGraphe = niveau->listeSommets.getIterateur();

	Sommet<FormeEcran> * teteListeSommets;
	Sommet<FormeEcran> * teteListeTemp;

	GestionnaireCreationAretes * expertCreationAretes =
		new AreteHorizontaleCOR(this->fenetre,
			new AreteVerticaleCOR(this->fenetre)
		);

	Arete<FormeEcran, FormeEcran> * arete;

	while (iterateurSommetGraphe.aSuivant()) {
		teteListeSommets = iterateurSommetGraphe.suivant();
		while (iterateurListeTemp.aSuivant()) {
			teteListeTemp = iterateurListeTemp.suivant();
			if (teteListeTemp != teteListeSommets) {
				if ((arete = expertCreationAretes->gerer(teteListeSommets, teteListeTemp)) != nullptr)
					niveau->listeAretes.ajouterElem(*arete);
			}
		}
		iterateurListeTemp.debut();
	}

	/*	// Iterator pour conversion en string
		// Je le garde ici parce que j'aime beaucoup m�me si ce n'est pas utile
	std::string labyStr(
		(std::istreambuf_iterator<char>(fichierLaby)),
		(std::istreambuf_iterator<char>()));
	labyStr.erase(remove(labyStr.begin(), labyStr.end(), ' '), labyStr.end());*/
	
	fichierLaby.close();
	return niveau;
}
