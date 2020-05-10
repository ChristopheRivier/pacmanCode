#pragma once

#include <vector>
#include "element.h"
#include "carte.h"
class Game {
	Carte* cart;
	std::vector<PacMan> myPac;
	std::vector<PacMan> hisPac;
	std::vector<Element> pillule;
	int cpt = 0;
	///test sans speed
	bool noSpeedTest = true;
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
		if (prof == 11 )
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
	std::string deplacementSpeed(PacMan& e) {
		Point sauv = Point(e.getX(), e.getY());
		cart->deplacement(sauv);
		Point p = deplacement(e);
		if (e.isSpeed()) {
			e.setPoint(p);
			//on informe qu’on est déjà passer par là
			cart->pass(p);
			p = deplacement(e);
		}
		std::string ret = "MOVE " + std::to_string(e.getId()) + " " + p.toString();
		//check if adversaire can beat me only if possible
		//if(cpt%10==0)
		if(false)
		for (std::vector<PacMan>::iterator it = hisPac.begin();
			it != hisPac.end();
			++it) {
			int minx = abs(p.x - (*it).getX());
			int miny = abs(p.y - (*it).getY());
			if (minx + miny <= 1 && !e.CanIBeat((*it))) {
				ret = "SWITCH " + std::to_string(e.getId()) + " " + e.getAttaque((*it).getChifoumi());
			}
			//if(e.getX())
		}

		return ret;
	}
	//calcul for one pac where to go
	Point deplacement(PacMan& e) {
		double pN = .0, pE = .0, pW = .0, pS = .0;
		Point pos(e.getX(), e.getY());
		if (cart->deplacementPossible(pos.getN(), pos))
			pN = poidTuile(0, pos.getN(), pos, e.getChifoumi());
		if (cart->deplacementPossible(pos.getE(), pos))
			pE = poidTuile(0, pos.getE(), pos, e.getChifoumi());
		if (cart->deplacementPossible(pos.getS(), pos))
			pS = poidTuile(0, pos.getS(), pos, e.getChifoumi());
		if (cart->deplacementPossible(pos.getW(), pos))
			pW = poidTuile(0, pos.getW(), pos, e.getChifoumi());
		if ((pE >= pS || pS==.0)&&
			(pE >= pW || pW==.0)&&
			(pE >= pN || pN==.0)&& 
			pE!=.0) {
			cart->deplacement(pos.getE());
			return pos.getE();
		}
		if ((pW >= pS ||pS==.0)&&
			(pW >= pE ||pE==.0)&&
			(pW >= pN ||pN==.0)&&
			pW!=.0) {
			cart->deplacement(pos.getW());
			return pos.getW();
		}
		if ((pS >= pN ||pN==.0)&&
			(pS >= pW ||pW==.0)&&
			(pS >= pE||pE==.0)&&
			pS!=.0) {
			cart->deplacement(pos.getS());
			return pos.getS();
		}
		if ((pN >= pE ||pE==.0)&&
			(pN >= pW ||pW==.0)&&
			(pN >= pS||pS==.0)&&
			pN!=.0) {
			cart->deplacement(pos.getN());
			return pos.getN();
		}
		return pos;
	}

	std::string calculDeplacement(){
		cart->clear();
		int tt = cpt % 10;
		bool speedPossible = (cpt%10 == 0);
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
			std::string ss= deplacementSpeed(*it);
			//if (!(*it).isSpeed()&& speedPossible&&noSpeedTest &&( ss.rfind("SWITCH")!=0||cpt<50)) {
			if (!(*it).isSpeed() && speedPossible && noSpeedTest ) {
					ret += "SPEED " + std::to_string((*it).getId());
			}
			else
				ret += ss;
		}
		++cpt;
		return ret;
	}

	/**
	for debug TU add all pass to tuile
	*/
	void allPass() {
		cart->allPass();
	}
	void notPass(int a, int b) {
		cart->notPass(a, b);
	}
	/**
	for debug only
	*/
	void setCpt(int c) {
		cpt = c;
	}
	void noSpeed() {
		noSpeedTest = false;
	}
};