#pragma once
class Graphe;
class Sommet;
class Arete;

class IVisiteur {
public:
	virtual void visite(Graphe*) = 0;
	virtual void visite(Arete*) = 0;
	virtual void visite(Sommet*) = 0;
};