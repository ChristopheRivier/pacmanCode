#pragma once

#include "point.h"

class Element {

public:
	enum EType {
		None = 0,
		Pac,
		Bouffe
	};
	Element(Point p, EType e, int i, int v, bool m) :pos(p), typ(e), id(i), val(v),mine(m) {}
	bool isMine() { return mine; }
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	double getPoid() {
		switch (typ)
		{
		case Element::None:
			return 2;
			break;
		case Element::Pac:
			return -1000;
			break;
		case Element::Bouffe:
			return val * 600;
			break;
		default:
			return -100;
			break;
		}
	}
private:
	Point pos;
	EType typ;
	int id;
	bool mine;
	int val;

};
