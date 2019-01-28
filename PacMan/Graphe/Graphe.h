#pragma once
#include <utility>
#include "./PElement.h"
#include "./Arete.h"

template<class Ar, class So>
class Graphe {
public:
	PElement< Sommet<So> > * 	listeSommets;
	PElement< Arete<Ar, So> > *	listeAretes;

#pragma region CREATIONS
	//Constructeurs
	Graphe() : listeSommets(NULL), listeAretes(NULL) {}
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
	int nombreSommets() const { return PElement< Sommet<So> >::taille(listeSommets); }
	int nombreAretes() const { return PElement< Arete<Ar, So> >::taille(listeAretes); }

	//compliqué
	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > *	adjacences(const Sommet<So> * sommet) const;
	PElement< Arete<Ar, So> > *							aretesAdjacentes(const Sommet<So> * sommet) const;
	PElement< Sommet<So> > *							voisins(const Sommet<So> * sommet) const;

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

	oss << PElement<Sommet<So> >::toString(listeSommets, "", "\n", "\n");

	oss << "Nombre d'aretes = " << this->nombreAretes() << std::endl;

	oss << PElement<Arete<Ar, So> >::toString(listeAretes, "", "\n", "\n");
	oss << "]";
	return oss.str();
}

/*Operateur = et destruceur*/
template <class Ar, class So>
void Graphe<Ar, So>::effaceTout() {
	PElement< Arete<Ar, So>>::efface2(this->listeAretes);
	PElement<Sommet<So> >::efface2(this->listeSommets);
}
#pragma endregion

#pragma region CREATIONS
template <class Ar, class So>
Sommet<So> * Graphe<Ar, So>::creeSommet(const So & info) {
	Sommet<So> * sommetCree = new Sommet<So>(info);
	listeSommets = new PElement< Sommet<So> >(sommetCree, listeSommets);

	return sommetCree;
}


template <class Ar, class So>
Arete<Ar, So> * Graphe<Ar, So>::creeArete(const Ar & info, Sommet<So> * debut, Sommet<So> * fin) {
	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!PElement< Sommet<So> >::appartient(debut, listeSommets)) throw Erreur("debut d'arete non defini");
	if (!PElement< Sommet<So> >::appartient(fin, listeSommets)) throw Erreur("fin d'arete non definie");

	Arete<Ar, So> *  nouvelleArete = new Arete<Ar, So>(info, debut, fin);

	listeAretes = new PElement< Arete<Ar, So> >(nouvelleArete, listeAretes);

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
	const PElement<Sommet<So>> * pS;

	// -------------- d'abord on recopie les sommets --------------------

	for (pS = graphe.listeSommets; pS; pS = pS->suivant) {
		const Sommet<So> * sommet = pS->valeur;				// sommet courant à recopier
		this->creeSommet(sommet->identifiant, sommet->valeur);		// on crée la copie du sommet courant avec le même identifiant
	}


	// -------------------- et maintenant on recopie les aretes --------------------

	// attention, la recopie des aretes est plus compliquee car il faut rebrancher les aretes sur les nouveaux sommets qui viennent d'etre crees.
	// Pour retrouver les "bons sommets" on utilise les clefs qui ont ete conservees

	const PElement<Arete<Ar, So>> * pA;
	for (pA = graphe.listeAretes; pA; pA = pA->suivant) {
		const Arete<Ar, So> * a = pA->valeur;			// arete courante a recopier
		Sommet<So> * d, *f;						// le debut et la fin de la nouvelle arete qui va etre creee
		PElement< Sommet<So> > * p;

		// on recherche d dans la nouvelle liste de sommets grace a son identifiant
		SommetDejaPresentDansLaCopie<So> conditionDebut(a->debut);
		p = PElement< Sommet<So> >::appartient(listeSommets, conditionDebut);
		d = p->valeur;

		// on recherche f dans la nouvelle liste de sommets grace a sa identifiant
		SommetDejaPresentDansLaCopie<So> conditionFin(a->fin);
		p = PElement< Sommet<So> >::appartient(listeSommets, conditionFin);
		f = p->valeur;

		this->creeArete(a->valeur, d, f);
	}
}


#pragma endregion

#pragma region CONSULTATION
template <class Ar, class So>
PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >  *  Graphe<Ar, So>::adjacences(const Sommet<So> * sommet) const {
	const PElement< Arete<Ar, So> > * l;

	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > * r;				// pair< Sommet<So> *, Arete<Ar,So>* >

	for (l = listeAretes, r = NULL; l; l = l->suivant)

		if (sommet == l->valeur->debut)
			r = new PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >(new std::pair< Sommet<So> *, Arete<Ar, So>* >(l->valeur->fin, l->valeur), r);
		else
			if (sommet == l->valeur->fin)
				r = new PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >(new std::pair< Sommet<So> *, Arete<Ar, So>* >(l->valeur->debut, l->valeur), r);

	return r;
}


template <class Ar, class So>
PElement< Arete<Ar, So> > *  Graphe<Ar, So>::aretesAdjacentes(const Sommet<So> * sommet) const {
	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > * ladj = this->adjacences(sommet);
	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > * l;

	PElement< Arete<Ar, So> > * r;

	for (l = ladj, r = NULL; l; l = l->suivant)
		r = new PElement< Arete<Ar, So> >(l->valeur->second, r);

	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj);

	return r;
}


template <class Ar, class So>
PElement< Sommet<So> > *  Graphe<Ar, So>::voisins(const Sommet<So> * sommet) const {
	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > * ladj = this->adjacences(sommet);
	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > > * l;

	PElement< Sommet<So> > * r;

	for (l = ladj, r = NULL; l; l = l->suivant)
		r = new PElement< Sommet<So> >(l->valeur->first, r);

	PElement< std::pair< Sommet<So> *, Arete<Ar, So>* > >::efface2(ladj);

	return r;
}

template <class Ar, class So>
Arete<Ar, So> * Graphe<Ar, So>::getAreteParSommets(const Sommet<So> * s1, const Sommet<So> * s2) const {
	PElement<Arete<Ar, So> > * l;

	for (l = this->listeAretes; l; l = l->suivant)
		if (l->valeur->estEgal(s1, s2))
			return l->valeur;

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
	PElement< Arete<Ar, So>> * pA;
	for (pA = this->listeAretes; pA; pA = pA->suivant)
		if (!fenetre.dessine(pA->valeur)) return false; // tente de dessiner puis retourne false en cas d'echec
	return true;
}

template <class Ar, class So>
template< class FENETRE>
bool Graphe<Ar, So>::dessineTousSommets(FENETRE & fenetre) const {
	PElement< Sommet<So>> * pS;
	for (pS = this->listeSommets; pS; pS = pS->suivant)
		if (!fenetre.dessine(pS->valeur)) return false;	// tente de dessiner puis retourne false en cas d'echec
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