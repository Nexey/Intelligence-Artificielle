#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "../Exceptions/Erreur.h"

template <class T>
class PElement {
public:
	T * valeur;				// valeur
	PElement<T> * suivant;	// suivant

	PElement(T * v, PElement<T> * s) : valeur(v), suivant(s) {}

	static const std::string toString(const PElement<T> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const PElement<T> * l);

	// Ne recopie pas les donnees *v. realise donc une copie partageant les donnees v avec l
	static  PElement<T> * copie1(PElement<T> * l);

	// Recopie  toutes les donnees *v. realise donc une copie ne partageant aucune donnee  avec l
	static  PElement<T> * copie2(const PElement<T> * l);

	// Recopie  toutes les donnees *v a l'aide de la methode v->copie(). realise donc une copie ne partageant aucune donnee  avec l
	// Alors si la classe T possede la methode virtuelle copie(), l peut etre heterogene.
	// Et la methode copie3 produit une copie de cette liste heterogene.
	static PElement<T> * copie3(const PElement<T> * l);

	/**
	 * concatene l2 a la fin de l1. Ne cree aucun maillon.
	 *
	 * En sortie l1 pointe sur le debut de la concatenation
	 *
	 * DONNEES : l1, l2 (peuvent etre vides toutes les deux)
	 *
	 * RESULTATS : l1 contenant la concatenation
	 *
	 * Exemple 1 : si en entree l1 = (2,5,4) et l2 = (7,11) alors en sortie l1 = (2,5,4,7,11) et l2 = (7,11)
	 * Exemple 2 : si en entree l1 = () et l2 = (7,11) alors en sortie l1 = (7,11) et  l2 = (7,11)
	 * Exemple 3 : si en entree l1 = (9,5) et l2 = () alors en sortie l1 = (9,5) et l2 = ()
	 *
	 * */
	static void concat(PElement<T> * & l1, PElement<T> *  l2);

	/**
	 * efface toute la liste l
	 * mais n'efface pas les donnees *v
	 *
	 * */
	static void efface1(PElement<T>* & l);

	/**
	 * efface toute la liste l
	 * et efface toutes les donnees *v
	 *
	 * */
	static void efface2(PElement<T>* & l);

	/**
	 * recherche si a appartient a l
	 *
	 * renvoie un pointeur sur le maillon de l contenant a
	 * renvoie NULL si a n'appartient pas a l
	 *
	 * */
	static  PElement< T > * appartient(const T * a, PElement<T> * l);

	/**
	 * HYPOTHESES : l'evaluation de condition() produit un booleen
	 * condition est supposee avoir la signature : bool condition( const T * a)
	 *
	 * renvoie un pointeur sur le 1er maillon de l verifiant la condition "condition"
	 * renvoie NULL si aucun maillon ne verifie la condition
	 *
	 * */
	template <class FONCTEUR>
	static PElement< T > * appartient(PElement<T> * l, const FONCTEUR & condition);

	// Insere * a dans l de telle sorte que l reste ordonnee par ordre croissant (l'element en tete est le plus petit).
	// Ne realise pas de copie de *a. En sortie l et a partagent donc physiquement des donnees.

	// A l'instar de la methode precedente (appartient), cette fonction aurait aussi pu etre ecrite avec un argument foncteur
	// Donnees : a (l'element a inserer), l, estPlusPetitOuEgal(la fonction de comparaison))
	// Resultats : l modifiee par l'insertion
	// Hypotheses : on suppose l ordonnee par ordre croissant a l'appel
	static void insertionOrdonnee(T * a, PElement<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2));


	static void insertion(T * a, PElement<T> * & l);

	// Retire la 1ère occurrence de a de l si a est present dans l, sinon ne fait rien
	// L'element trouve n'est pas efface
	// La comparaison est faite sur les pointeurs
	// Donnees : a, l
	// Resultats : l (eventuellement modifiee), par return : true si l'element a ete trouve, false sinon
	static bool retire(const T * a, PElement<T> * & l);


	// Retire l'element situe en tete de l et le renvoie. Le 1er maillon de l est efface.
	// l est donc modifiee par l'appel. En sortie l compte un element de moins.
	// lance une exception Erreur si l == NULL a l'appel
	static T * depiler(PElement<T> * & l);

	//-------------------------- PElement<T> ------------------------------
};

template<class T>
void PElement<T>::insertion(T * a, PElement<T> * & l) {
	if (!l)
		l = new PElement<T>(a, l);
	else
		PElement<T>::insertion(a, l->suivant);
}

template<class T>
std::ostream& operator <<(std::ostream & os, const PElement<T> * p) { return os << PElement<T>::toString(p); }

template <class T>
/*static*/ const std::string PElement<T>::toString(const PElement<T> * p, const char * debut, const char * separateur, const char * fin) {
	PElement<T> * r;
	std::ostringstream oss;

	for (r = (PElement<T>*) p, oss << debut; r; r = r->suivant)
		oss << *(r->valeur) << separateur;

	oss << fin;
	return oss.str();
}

template <class T>
/* static */ void PElement<T>::concat(PElement<T> * & l1, PElement<T> * l2) {
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concat(l1->suivant, l2);
}

template <class T>
/* static */ int PElement<T>::taille(const PElement<T> * l) {
	if (!l) return 0;
	else
		return 1 + PElement<T>::taille(l->suivant);
}


/**
 *
 * ne recopie pas les donnees *v. realise donc une copie partageant les donnees v avec l
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie1(PElement<T> * l) {
	if (!l)
		return NULL;
	else
		return new PElement<T>(l->valeur, PElement<T>::copie1(l->suivant));
}

/**
 *
 * recopie  toutes les donnees *v. realise donc une copie ne partageant aucune donnee  avec l
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie2(const PElement<T> * l) {
	if (!l)
		return NULL;
	else
		return new PElement<T>(new T(*(l->valeur)), PElement<T>::copie2(l->suivant));
}

/**
 *
 * recopie  toutes les donnees *v a l'aide de la methode v->copie(). realise donc une copie ne partageant aucune donnee  avec l
 *
 * Alors si la classe T possede la methode virtuelle copie(), l peut etre heterogene. Et la methode copie3 produit une copie de cette liste heterogene.
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie3(const PElement<T> * l) {
	if (!l)
		return NULL;
	else
		return new PElement<T>(l->valeur->copie(), PElement<T>::copie3(l->suivant));
}



/**
 * efface toute la liste l
 * mais n'efface pas les donnees *v
 *
 * */
template <class T>
/* static */ void PElement<T>::efface1(PElement<T>* & l) {
	if (l) {
		PElement<T>::efface1(l->suivant);
		delete l; l = NULL;
	}
}
/**
 * efface toute la liste l
 * et efface toutes les donnees *v
 *
 * */
template <class T>
/* static */ void PElement<T>::efface2(PElement<T>* & l) {
	if (l) {
		PElement<T>::efface2(l->suivant);
		delete l->valeur; delete l; l = NULL;
	}
}
/**
 * recherche si a appartient a l
 *
 * renvoie un pointeur sur le maillon de l contenant a
 * renvoie NULL si a n'appartient pas a l
 *
 * */
template <class T>
PElement< T > * PElement< T >::appartient(const T * a, PElement<T> * l) {
	for (; l; l = l->suivant)
		if (a->getIdentifiant() == l->valeur->getIdentifiant())
			return l;
	std::cout << "oui";
	return l;
}

/**
 * HYPOTHESES : l'evaluation de condition() produit un booleen
 * condition est supposee avoir la signature : bool condition( const T * a)
 *
 * renvoie un pointeur sur le 1er maillon de l verifiant la condition "condition"
 * renvoie NULL si aucun maillon ne verifie la condition
 *
 * */
template <class T>
template <class FONCTEUR>
/*static*/ PElement< T > * PElement< T >::appartient(PElement<T> * l, const FONCTEUR & condition) {
	for (; l; l = l->suivant)
		if (condition(l->valeur))
			return l;

	return l;
}

/**
 * Insere * a dans l de telle sorte que l reste ordonnee par ordre croissant (l'element en tete est le plus petit).
 * Ne realise pas de copie de *a. En sortie l et a partagent donc physiquement des donnees.
 *
 * A l'instar de la methode precedente (appartient), cette fonction aurait aussi pu etre ecrite avec un argument foncteur
 *
 * Donnees : a (l'element a inserer), l, estPlusPetitOuEgal(la fonction de comparaison))
 * Resultats : l modifiee par l'insertion
 * Hypotheses : on suppose l ordonnee par ordre croissant a l'appel
 *
 * */
template<class T>
/*static*/ void PElement<T>::insertionOrdonnee(T * a, PElement<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (!l || estPlusPetitOuEgal(a, l->valeur))
		l = new PElement<T>(a, l);
	else
		PElement<T>::insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
}

/**
 * retire la 1ere occurrence de a de l si a est present dans l, sinon ne fait rien
 *
 * L'element trouve n'est pas efface
 *
 * La comparaison est faite sur les pointeurs
 *
 * Donnees : a, l
 * Resultats : l (eventuellement modifiee), par return : true si l'element a ete trouve, false sinon
 * */
template<class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l) {
	if (!l)
		return false;
	else
		if (a == l->valeur) {
			PElement<T> * r = l; l = l->suivant; delete r;
			return true;
		}
		else
			return PElement<T>::retire(a, l->suivant);
}

/**
 * retire l'element situe en tete de l et le renvoie. Le 1er maillon de l est efface.
 *
 * l est donc modifiee par l'appel. En sortie l compte un element de moins.
 * lance une exception Erreur si l == NULL a l'appel
 *
 * */
template <class T>
/* static */ T * PElement<T>::depiler(PElement<T> * & l) {
	if (!l) throw Erreur("impossible de depiler une pile vide");
	T * a = l->valeur;
	PElement<T> * tete = l;

	l = l->suivant; delete tete;
	return a;

}





/**
 *
 * ne recopie pas les donnees *v. realise donc la reunion au sens ensembliste de l1 et l2  partageant les donnees v avec l1 et l2.
 *
 * Suppose que l1 et l2 sont des ensembles. Elles ne contiennent donc aucun doublon.
 *
 * DONNEES : l1 et l2 (representant des ensembles)
 * RESULTAT : l1 U l2 au sens ensembliste partageant les donnees v avec l1 er l2
 *
 * */
template <class T>
PElement<T> * reunion(PElement<T> * l1, PElement<T> * l2) {
	PElement<T> * r = PElement<T>::copie1(l2);
	PElement<T> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->suivant)
		if (!PElement<T>::appartient(pl1->valeur, r))
			r = new PElement<T>(pl1->valeur, r);

	return r;
}



/**
 * partage p en deux listes p et p1 de taille egale : Laisse dans p les elements de rang impair et place dans p1 les elements de rang pair
 *
 * DONNEES : p
 * RESULTATS : p (modifiee) et p1
 *
 * */
template <class T>
void partage(PElement<T> * & p, PElement<T> * & p1) {
	if (p == NULL || p->suivant == NULL)
		p1 = NULL;
	else {
		PElement<T> *  r1, *r2;

		r1 = p->suivant;
		r2 = r1->suivant;

		partage(r2, p1);

		r1->suivant = p1;
		p->suivant = r2;
		p1 = r1;
	}
}

/**
 * realise la fusion ordonnee de p1 et p2 et place le resultat dans p1. En sortie p2 est donc vide.
 * Ne cree aucun maillon.
 *
 * Suppose que p1 et p2 sont ordonnees par ordre croissant en entree. La liste resultante est aussi ordonnee par ordre croissant.
 *
 * Utilise la fct estPlusPetitOuEgal pour les comparaisons 1 a 1.
 *
 * On suppose que estPlusPetitOuEgal(a1,a2) renvoie true si a1 <= a2 où <= est une relation d'ordre sur T et renvoie false si a1 > a2
 *
 * DONNEES : p1 et p2
 * RESULTATS: P1 et p2
 *
 * */
template <class T>
void fusion(PElement<T> * & p1, PElement<T> * & p2, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (!p2) return; // p2 est vide, il n'y a rien a faire

	if (!p1) // p1 est vide et p2 ne l'est pas
	{
		p1 = p2; p2 = NULL;
		return;
	}

	// a present, p1 et p2 sont non vides

	if (estPlusPetitOuEgal(p1->valeur, p2->valeur)) // p1->v <= p2->v
	{
		PElement<T> * r;
		r = p1->suivant;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->suivant = r;
	}
	else // p1->v > p2->v
	{
		PElement<T> * r;
		r = p2->suivant;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->suivant = p1;
		p1 = p2;
		p2 = NULL;
	}
}


/**
 * trie p par tri recursif dichotomique (trifusion)
 *
 * ne cree pas de nouveau maillon. La liste originale p est modifiee
 *
 * Utilise la fct estPlusPetitOuEgal pour les comparaisons 1 a 1.
 *
 * range les elements par ordre croissant
 *
 * On suppose que estPlusPetitOuEgal(a1,a2) renvoie true si a1 <= a2 où <= est une relation d'ordre sur T et renvoie false si a1 > a2
 *
 * DONNEES : p
 * RESULTATS : p modifiee
 *
 * */
template <class T>
void tri(PElement<T>* & p, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)) {
	if (p != NULL && p->suivant != NULL) {
		PElement<T> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}




