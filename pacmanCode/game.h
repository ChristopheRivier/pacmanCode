#pragma once

#include <vector>
#include "element.h"
#include "carte.h"
class Game {
	Carte* cart;
	std::vector<Element> myPac;
	std::vector<Element> hisPac;
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
	void addPac(Element& e) {
		if (e.isMine())
			myPac.push_back(e);
		else
			hisPac.push_back(e);
	}
	void addPillule(Element& e) {
		pillule.push_back(e);
	}

	double poidTuile(int prof, Point fils, Point from) {
		double p = .0;
		double dividende = 4;
		if (cart->isWall(fils))
			return -10;
		if (prof == 10 )
			return p;
		prof++;
		p = cart->getPoid(fils);
		if (cart->deplacementPossible(fils.getE(), from))
			p += poidTuile(prof, fils.getE(), fils)/dividende;
		if (cart->deplacementPossible(fils.getW(), from))
			p += poidTuile(prof, fils.getW(), fils)/dividende;
		if (cart->deplacementPossible(fils.getN(), from))
			p += poidTuile(prof, fils.getN(), fils)/dividende;
		if (cart->deplacementPossible(fils.getS(), from))
			p += poidTuile(prof, fils.getS(), fils)/dividende;

		return p;
	}
	//calcul for one pac where to go
	std::string deplacement(Element& e) {
		double pN=.0,pE=.0,pW=.0,pS = .0;
		Point pos(e.getX(), e.getY());
		if (cart->deplacementPossible(pos.getN(), pos))
			pN = poidTuile(0, pos.getN(), pos);
		if (cart->deplacementPossible(pos.getE(), pos))
			pE = poidTuile(0, pos.getE(), pos);
		if (cart->deplacementPossible(pos.getS(), pos))
			pS = poidTuile(0, pos.getS(), pos);
		if (cart->deplacementPossible(pos.getW(), pos))
			pW = poidTuile(0, pos.getW(), pos);
		if (pE >= pS &&
			pE >= pW &&
			pE >= pN)
			return "0 " + pos.getE().toString();
		if (pW >= pS &&
			pW >= pE &&
			pW >= pN)
			return "0 " + pos.getW().toString();
		if (pS >= pN &&
			pS >= pW &&
			pS >= pE)
			return "0 " + pos.getS().toString();
		if (pN >= pE &&
			pN >= pW &&
			pN >= pS)
			return "0 " + pos.getN().toString();
		return "0 0 0";
	}

	std::string calculDeplacement(){
		cart->clear();
		for (std::vector<Element>::iterator it = hisPac.begin(); it != hisPac.end(); ++it) {
			cart->addEl(*it);
		}
		for (std::vector<Element>::iterator it = pillule.begin(); it != pillule.end(); ++it) {
			cart->addEl(*it);
		}
		return "MOVE " + deplacement(myPac[0]);
	}
};