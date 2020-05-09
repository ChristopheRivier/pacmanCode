#pragma once

#include <vector>
#include "element.h"
#include "carte.h"
class Game {
	Carte* cart;
	std::vector<PacMan> myPac;
	std::vector<PacMan> hisPac;
	std::vector<Element> pillule;

public:
	Game() :cart(NULL) {}
	void initCarte(int w, int h) {
		Singleton::get().setHeight(h);
		Singleton::get().setWidth(w);
		cart = new Carte(w, h);
	}
	void addCarteLine(int i, std::string l) {
		cart->addLine(i, l);
	}
	void printCarte() {
		cart->printCarte();
	}
	void init() {
		myPac.clear();
		hisPac.clear();
		pillule.clear();
	}
	void addPac(PacMan& e) {
		if (e.isMine())
			myPac.push_back(e);
		else
			hisPac.push_back(e);
	}
	void addPillule(Element& e) {
		pillule.push_back(e);
	}

	double poidTuile(int prof, Point fils, Point from, Element::Echifoumi chi) {
		double p = .0;
		double dividende = 4;
		if (cart->isWall(fils))
			return -10;
		if (prof == 10 )	
			return p;
		prof++;
		p = cart->getPoid(fils,chi);
		if (cart->deplacementPossible(fils.getE(), from))
			p += poidTuile(prof, fils.getE(), fils,chi)/dividende;
		if (cart->deplacementPossible(fils.getW(), from))
			p += poidTuile(prof, fils.getW(), fils,chi)/dividende;
		if (cart->deplacementPossible(fils.getN(), from))
			p += poidTuile(prof, fils.getN(), fils,chi)/dividende;
		if (cart->deplacementPossible(fils.getS(), from))
			p += poidTuile(prof, fils.getS(), fils,chi)/dividende;

		return p;
	}
	//calcul for one pac where to go
	std::string deplacement(PacMan& e) {
		double pN=-1,pE=-1,pW=-1,pS = -1;
		Point pos(e.getX(), e.getY());
		if (cart->deplacementPossible(pos.getN(), pos))
			pN = poidTuile(0, pos.getN(), pos,e.getChifoumi());
		if (cart->deplacementPossible(pos.getE(), pos))
			pE = poidTuile(0, pos.getE(), pos, e.getChifoumi());
		if (cart->deplacementPossible(pos.getS(), pos))
			pS = poidTuile(0, pos.getS(), pos, e.getChifoumi());
		if (cart->deplacementPossible(pos.getW(), pos))
			pW = poidTuile(0, pos.getW(), pos, e.getChifoumi());
		if (pE >= pS &&
			pE >= pW &&
			pE >= pN)
			return std::to_string(e.getId())+" " + pos.getE().toString();
		if (pW >= pS &&
			pW >= pE &&
			pW >= pN)
			return std::to_string(e.getId()) +" " + pos.getW().toString();
		if (pS >= pN &&
			pS >= pW &&
			pS >= pE)
			return std::to_string(e.getId()) + " " + pos.getS().toString();
		if (pN >= pE &&
			pN >= pW &&
			pN >= pS)
			return std::to_string(e.getId()) + " " + pos.getN().toString();
		return "0 0 0";
	}

	std::string calculDeplacement(){
		cart->clear();
		for (std::vector<PacMan>::iterator it = hisPac.begin(); it != hisPac.end(); ++it) {
			cart->addEl(*it);
		}
		for (std::vector<Element>::iterator it = pillule.begin(); it != pillule.end(); ++it) {
			cart->addEl(*it);
		}
		cart->printCarte();
		std::string ret;
		for (std::vector<PacMan>::iterator it = myPac.begin(); it != myPac.end(); ++it) {
			cart->addEl(*it);
			if (it != myPac.begin())
				ret += "|";
			ret += "MOVE " + deplacement(*it);
		}
			return ret;
	}
	/**
	for debug TU add all pass to tuile
	*/
	void allPass() {
		cart->allPass();
	}

};