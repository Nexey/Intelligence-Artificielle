#pragma once
#include <utility>
#include "./PElement.h"
#include "./Arete.h"
#include "./Liste.h"

template<class Ar, class So>
class Graphe {
public:
	//PElement< Sommet<So> > * 	listeSommets;
	//PElement< Arete<Ar, So> > *	listeAretes;
	Liste< Sommet<So> > listeSommets;
	Liste< Arete<Ar, So> > listeAretes;

#pragma region CREATIONS
	//Constructeurs
	Graphe() {}
	Graphe(const Graphe<Ar, So> & graphe) : Graphe() { this->copie(graphe); }

	//Destructeur
	~Graphe() { this->effaceTout(); }

	/*Operateur =*/
	const Graphe<Ar, So> & operator = (const Graphe<Ar, So> & graphe) { this->effaceTout(); this->copie(graphe); return *this; }

#pragma region SOMMETS
	Sommet<So> * creeSommet(const So & info);
#pragma endregion

#pragma region ARETES
	Arete<Ar, So> * creeArete(const Ar & info, Sommet<So> * debut, Sommet<So> * fin);
#pragma endregion

#pragma region COPIE
	/*Au départ, le graphe this est vide.
	* Crée une copie de chaques sommets et chaques aretes.*/
	void copie(const Graphe<Ar, So> & graphe);

	/*Utilisé par l'operateur = et par le destructeur*/
	void effaceTout();
#pragma endregion

#pragma endregion

#pragma region CONSULTATION
	//simple
	int nombreSommets() const { return PElement< Sommet<So> >::taille(listeSommets.tete); }
	int nombreAretes() const { return PElement< Arete<Ar, So> >::taille(listeAretes.tete); }

	//compliqué
	Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > > *	adjacences(const Sommet<So> * sommet) const;
	Liste< Arete<Ar, So> > *							aretesAdjacentes(const Sommet<So> * sommet) const;
	Liste< Sommet<So> > *							voisins(const Sommet<So> * sommet) const;

	/*Recherche une arete à partir d'un sommet (debut et fin confondu)*/
	Arete<Ar, So> * getAreteParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const;

	//OPERATORS
	operator std::string() const;
#pragma endregion

#pragma region DESSIN (visiteur)
	// Dessine d'abord les aretes, puis les sommets
	// Renvoie True seulement en cas de succès complet

	template< class FENETRE>
	bool dessineToutesAretes(FENETRE & fenetre) const;

	template< class FENETRE>
	bool dessineTousSommets(FENETRE & fenetre) const;

	template  <class FENETRE>
	bool dessine(FENETRE & fenetre) const;
#pragma endregion
};

#pragma region OPERATORS
template <class Ar, class So>
std::ostream & operator << (std::ostream & os, const Graphe<Ar, So> & gr) { return os << (std::string)gr; }

template <class Ar, class So>
Graphe<Ar, So>::operator std::string() const {
	std::ostringstream oss;
	oss << "Graphe : [" << std::endl;
	oss << "Prochain identifiant = " << AElement::getProchainIdentifiant() << std::endl;
	oss << "Nombre de sommets = " << this->nombreSommets() << std::endl;

	oss << PElement<Sommet<So> >::toString(listeSommets.tete, "", "\n", "\n");

	oss << "Nombre d'aretes = " << this->nombreAretes() << std::endl;

	oss << PElement<Arete<Ar, So> >::toString(listeAretes.tete, "", "\n", "\n");
	oss << "]";
	return oss.str();
}

/*Operateur = et destruceur*/
template <class Ar, class So>
void Graphe<Ar, So>::effaceTout() {
	PElement< Arete<Ar, So>>::efface2(this->listeAretes.tete);
	PElement<Sommet<So> >::efface2(this->listeSommets.tete);
}
#pragma endregion

#pragma region CREATIONS
template <class Ar, class So>
Sommet<So> * Graphe<Ar, So>::creeSommet(const So & info) {
	Sommet<So> * sommetCree = new Sommet<So>(info);
	listeSommets.tete = new PElement< Sommet<So> >(sommetCree, listeSommets.tete);

	return sommetCree;
}


template <class Ar, class So>
Arete<Ar, So> * Graphe<Ar, So>::creeArete(const Ar & info, Sommet<So> * debut, Sommet<So> * fin) {
	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!PElement< Sommet<So> >::appartient(debut, listeSommets.tete)) throw Erreur("debut d'arete non defini");
	if (!PElement< Sommet<So> >::appartient(fin, listeSommets.tete)) throw Erreur("fin d'arete non definie");

	Arete<Ar, So> *  nouvelleArete = new Arete<Ar, So>(info, debut, fin);

	listeAretes.ajouterElem(*nouvelleArete);

	return nouvelleArete;
}
#pragma endregion

#pragma region COPIE
/*Foncteur pour la recherche dans une liste PElement.
* Remplace l'operateur == des pointeurs par une comparaison des clefs*/
template <class So>
class SommetDejaPresentDansLaCopie {
public:
	const Sommet<So> * s;
	SommetDejaPresentDansLaCopie(const Sommet<So> * s) : s(s) {}

	bool operator () (const Sommet<So> * sommet) const { return sommet->identifiant == s->identifiant; }
};

template <class Ar, class So>
void Graphe<Ar, So>::copie(const Graphe<Ar, So> & graphe) {
	Iterateur<Sommet<So>> itSommets = listeSommets.getIterateur();
	itSommets.debut();

	// -------------- d'abord on recopie les sommets --------------------
	const Sommet<So> * sommet;
	while (itSommets.aSuivant()) {
		sommet = &itSommets.suivant();						// sommet courant à recopier
		this->creeSommet(sommet->identifiant, sommet->valeur);		// on crée la copie du sommet courant avec le même identifiant
	}

	// -------------------- et maintenant on recopie les aretes --------------------

	// attention, la recopie des aretes est plus compliquee car il faut rebrancher les aretes sur les nouveaux sommets qui viennent d'etre crees.
	// Pour retrouver les "bons sommets" on utilise les clefs qui ont ete conservees

	Iterateur<Arete<Ar, So>> itAretes = listeAretes.getIterateur();
	itAretes.debut();

	while (itAretes.aSuivant()) {
		const Arete<Ar, So> * a = itAretes.suivant();			// arête courante à recopier
		Sommet<So> * debut, *fin;							// le début et la fin de la nouvelle arête qui va être créée
		Liste< Sommet<So> > p;

		// on recherche d dans la nouvelle liste de sommets grâce à son identifiant
		SommetDejaPresentDansLaCopie<So> conditionDebut(a->debut);
		p.ajouterElem(PElement< Sommet<So> >::appartient(listeSommets, conditionDebut));
		debut = p->tete->valeur;

		// on recherche f dans la nouvelle liste de sommets grace a sa identifiant
		SommetDejaPresentDansLaCopie<So> conditionFin(a->fin);
		p.ajouterElem(PElement< Sommet<So> >::appartient(listeSommets, conditionFin));
		fin = p->tete->valeur;

		this->creeArete(a->valeur, debut, fin);
	}
}


#pragma endregion

#pragma region CONSULTATION
template <class Ar, class So>
Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > >  *  Graphe<Ar, So>::adjacences(const Sommet<So> * sommet) const {
	Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > > * r = new Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > >();
	
	Iterateur< Arete<Ar, So> > itAretes = listeAretes.getIterateur();
	itAretes.debut();

	Arete<Ar, So> * tmp;

	while (itAretes.aSuivant()) {
		tmp = &itAretes.suivant();
		if (sommet == tmp->debut)
			r->ajouterElem(PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >(new std::pair< Sommet<So> *, Arete<Ar, So>* >(itAretes.suivant()->fin, &tmp)));
		else
			if (sommet == tmp->fin)
				r->ajouterElem(PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >(new std::pair< Sommet<So> *, Arete<Ar, So>* >(itAretes.suivant()->debut, &tmp)));
	}
	return r;
}


template <class Ar, class So>
Liste< Arete<Ar, So> > *  Graphe<Ar, So>::aretesAdjacentes(const Sommet<So> * sommet) const {
	Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > > ladj = *this->adjacences(sommet);

	Liste< Arete<Ar, So> > * r = new Liste< Arete<Ar, So> >();

	Iterateur< std::pair< Sommet<So> *, Arete<Ar, So>* > > itLadj = ladj.getIterateur();
	while (itLadj.aSuivant())
		r->ajouterElem(PElement< Arete<Ar, So> >(itLadj.suivant()->second));

	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj.tete);

	return r;
}


template <class Ar, class So>
Liste< Sommet<So> > *  Graphe<Ar, So>::voisins(const Sommet<So> * sommet) const {
	Liste< std::pair< Sommet<So> *, Arete<Ar, So>* > > ladj = *this->adjacences(sommet);
	Iterateur< std::pair< Sommet<So> *, Arete<Ar, So>* > > itLadj = ladj.getIterateur();
	itLadj.debut();

	Liste< Sommet<So> > * r;

	while(itLadj.aSuivant())
		r->ajouterElem(PElement< Sommet<So> >(itLadj.suivant()->first));

	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj.tete);

	return r;
}

template <class Ar, class So>
Arete<Ar, So> * Graphe<Ar, So>::getAreteParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const {
	Iterateur<Arete<Ar, So> > itL = listeAretes.getIterateur();
	itL.debut();
	Arete<Ar, So> * areteS1S2;
	while (itL.aSuivant()) {
		areteS1S2 = itL.suivant();
		if (areteS1S2->estEgal(s1, s2))
			return areteS1S2;
	}
	return NULL;
}
#pragma endregion

#pragma region DESSIN
template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessine(FENETRE & fenetre) const {
	if (!this->dessineTousSommets(fenetre)) return false;
	return this->dessineToutesAretes(fenetre); 
}

template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessineToutesAretes(FENETRE & fenetre) const {
	Iterateur< Arete<Ar, So>> IterateurArete = listeAretes.getIterateur();
	while (IterateurArete.aSuivant())
		if (!fenetre.dessine(&IterateurArete.suivant())) return false;	// tente de dessiner puis retourne false en cas d'echec
	return true;
}

template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessineTousSommets(FENETRE & fenetre) const {
	Iterateur< Sommet<So>> IterateurSommet = listeSommets.getIterateur();
	while (IterateurSommet.aSuivant())
		if (!fenetre.dessine(&IterateurSommet.suivant())) return false;	// tente de dessiner puis retourne false en cas d'echec
	return true;
}
/*
template <class So, class FENETRE>
bool dessine(const PElement<Sommet<So>> * chemin, FENETRE & fenetre, const unsigned int couleur) {
	if (!(chemin && chemin->suivant)) // le chemin est vide ou ne contient qu'un sommet : il n'y  a rien a dessiner
		return true;

	else {
		// on dessine d'abord la 1ere arete
		if (!fenetre.dessine(chemin->valeur, chemin->suivant->valeur, couleur)) return false;

		return dessine(chemin->suivant, fenetre, couleur);		// puis on dessine les aretes suivantes
	}
}*/
#pragma endregion