#pragma once

#include "point.h"

class Element {

public:
	enum EType {
		None = 0,
		Pac,
		Bouffe
	};
	enum Echifoumi {
		pierre = 0,
		papier,
		ciseau
	};
	Element(Point p, EType e, int i, int v, bool m) :pos(p), typ(e), id(i), val(v),mine(m) {}
	bool isMine() { return mine; }
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	virtual double getPoid(Echifoumi chi) {
		switch (typ)
		{
		case Element::None:
			return 2;
			break;
		case Element::Pac:

			return -1000;
			break;
		case Element::Bouffe:
			if (val > 1)
				return val * 600;
			else
				return .0;
			break;
		default:
			return -100;
			break;
		}
	}
	int getId() { return id; }
	virtual bool isPac() { return false; }
private:
	Point pos;
	EType typ;
	int id;
	bool mine;
	int val;

};


class PacMan :public Element {
public:
	
	PacMan(Point p, EType e, int i, int v, bool m,std::string typeId) :
		Element(p, e, i, v, m) {
		setChi(typeId);
	}
	void setChi(std::string t) {
		if (t.compare("ROCK") == 0)
			chichi = pierre;
		else if (t.compare("PAPER") == 0)
			chichi = papier;
		else if (t.compare("SCISSORS") == 0)
			chichi = ciseau;
	}
	double getPoid(Echifoumi chi) {
		if (!isMine()&&((chi == pierre && chichi == ciseau) ||
			(chi == papier && chichi == pierre) ||
			(chi == ciseau && chichi == papier))) {
			return 800;
		}
		else
			return -100;
	}
	Echifoumi getChifoumi() { return chichi; }
	bool isPac() { return true; }
private:
	Echifoumi chichi;
};