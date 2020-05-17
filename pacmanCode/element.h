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
		ciseau,
		mort
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

			return -800;
			break;
		case Element::Bouffe:
			if (val > 1)
				return val * (Singleton::get().getPoidBouffe()*Singleton::get().getPoidBouffeMax());
			else
				return Singleton::get().getPoidBouffe();
			break;
		default:
			return -100;
			break;
		}
	}
	int getId() { return id; }
	void setPoint(Point p) {
		pos.x = p.x;
		pos.y = p.y;
	}
	virtual bool isDead() { return false; }
	virtual bool isPac() { return false; }
	virtual void print() {
		std::cerr << "el=Element(Point(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "), Element::Bouffe, " + std::to_string(getId()) + "," +
			std::to_string(val) + " ," + (isMine() ? "true" : "false") + ");" << std::endl;
		std::cerr << "g.addPillule(el);" << std::endl;
	}

protected:
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
		else
			chichi = mort;
	}
	bool isDead() { return chichi == mort; }
	double getPoid(Echifoumi chi) {
		if (!isMine() && ((chi == pierre && chichi == ciseau) ||
			(chi == papier && chichi == pierre) ||
			(chi == ciseau && chichi == papier))) {
			return Singleton::get().getPoidAttaque();
		}
		else
			return isMine() ? -1000:Singleton::get().getPoidFuite();
	}
	Echifoumi getChifoumi() { return chichi; }
	bool isPac() { return true; }
	bool isSpeed() { return val > 0; }
	void print() {
		std::cerr << "e=PacMan(Point(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "), Element::Pac, " + std::to_string(getId()) + "," +
			std::to_string(val) + " ," + (isMine() ? "true" : "false") + ", \"" +
			getStrType() + "\");" << std::endl;
		std::cerr << "g.addPac(e);" << std::endl;
	}
	std::string getStrType() {
		return getStrType(chichi);
	}
	static std::string getStrType(Echifoumi tt) {
		switch (tt) {
		case ciseau:
			return "SCISSORS";
			break;
		case pierre:
			return "ROCK";
		case papier:
			return "PAPER";
		default:
			return "PAPER";
		}
	}
	bool CanIBeat(PacMan b) {
		if (((b.getChifoumi() == papier && chichi == ciseau) ||
			(b.getChifoumi() == ciseau && chichi == pierre) ||
			(b.getChifoumi() == pierre && chichi == papier))) {
			return true;
		}
		return false;
	}

	Echifoumi getAttaque(Echifoumi e) {
		switch (e)
		{
		case Element::pierre:
			return papier;
			break;
		case Element::papier:
			return ciseau;
			break;
		case Element::ciseau:
			return pierre;
			break;
		default:
			return papier;
			break;
		}
	}
private:
	Echifoumi chichi;
};