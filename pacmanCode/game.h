#pragma once

#include <vector>
#include <map>
#include "element.h"
#include "carte.h"
#include "actions.h"
class Game {
	Carte* cart;
	std::vector<PacMan> myPac;
	std::vector<PacMan> hisPac;
	std::vector<Element> pillule;
	std::map<int, Action> lstAction;
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
		if (prof == 14 )
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
	Action deplacementSpeed(PacMan& e) {
		Point sauv = Point(e.getX(), e.getY());
		std::map<int, Action>::iterator lastAction = lstAction.find(e.getId());
		if (e.isMine()) {
			if (lastAction != lstAction.end() && (*lastAction).second.getAction() == Action::Move) {
				cart->deplacement((*lastAction).second.getPoint());
			}
			cart->deplacement(sauv);
		}
		Point p = deplacement(e);
		if (e.isSpeed()) {
			e.setPoint(p);
			//on informe qu’on est déjà passer par là
			if(e.isMine())
				cart->pass(p);
			p = deplacement(e);
		}
		Action ret;
		ret.setId(e.getId());
		ret.setAction(Action::Move);
		ret.setPosition(p);
		//check if adversaire can beat me only if possible
		//if(cpt%10==0)
		if(false)
		for (std::vector<PacMan>::iterator it = hisPac.begin();
			it != hisPac.end();
			++it) {
			int minx = abs(p.x - (*it).getX());
			int miny = abs(p.y - (*it).getY());
			if (minx + miny <= 1 && !e.CanIBeat((*it))) {
				ret.setAction(Action::Switch);
				ret.setSwitch(e.getAttaque((*it).getChifoumi()));
			}
			//if(e.getX())
		}
		std::cerr << ret.toString() << std::endl;

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
			if(e.isMine())
				cart->deplacement(pos.getE());
			return pos.getE();
		}
		if ((pW >= pS ||pS==.0)&&
			(pW >= pE ||pE==.0)&&
			(pW >= pN ||pN==.0)&&
			pW!=.0) {
			if (e.isMine())
				cart->deplacement(pos.getW());
			return pos.getW();
		}
		if ((pS >= pN ||pN==.0)&&
			(pS >= pW ||pW==.0)&&
			(pS >= pE||pE==.0)&&
			pS!=.0) {
			if (e.isMine())
				cart->deplacement(pos.getS());
			return pos.getS();
		}
		if ((pN >= pE ||pE==.0)&&
			(pN >= pW ||pW==.0)&&
			(pN >= pS||pS==.0)&&
			pN!=.0) {
			if (e.isMine())
				cart->deplacement(pos.getN());
			return pos.getN();
		}
		return pos;
	}

	std::string calculDeplacement(){
		cart->clear();
		Singleton::get().setPoidBouffeMax(300);
		Singleton::get().setPoidBouffe(900);
		if (myPac.size() > 3) {
			Singleton::get().setPoidAttaque(2000);
		}
		else {
			Singleton::get().setPoidAttaque(1000);
		}
		if (cpt < 74) {
			Singleton::get().setPoidFuite(-1600);
			Singleton::get().setPoidVide(1);
			Singleton::get().setPoidVisite(800);
		}
		else {
			Singleton::get().setPoidFuite(-800);
			Singleton::get().setPoidVide(1);

			Singleton::get().setPoidVisite(1100);
		}

		int tt = cpt % 10;

		bool speedPossible = (cpt%10 == 0);
		for (std::vector<PacMan>::iterator it = hisPac.begin(); it != hisPac.end(); ++it) {
			cart->addEl(*it);
			Action a = deplacementSpeed(*it);
			if (a.getAction() == Action::Move) {
				cart->delPac(*it);
				(*it).setPoint(a.getPoint());
				cart->addEl(*it);
			}
		}
		for (std::vector<Element>::iterator it = pillule.begin(); it != pillule.end(); ++it) {
			cart->addEl(*it);
		}
		cart->printCarte();
		std::string ret;
		for (std::vector<PacMan>::iterator it = myPac.begin(); it != myPac.end(); ++it) {
			cart->addEl(*it);
		}
		for (std::vector<PacMan>::iterator it = myPac.begin(); it != myPac.end(); ++it) {
			if (!(*it).isDead()) {
				Action a;
				a.setId((*it).getId());
				//if (!(*it).isSpeed()&& speedPossible&&noSpeedTest &&( ss.rfind("SWITCH")!=0||cpt<50)) {
				if (!(*it).isSpeed() && speedPossible && noSpeedTest) {
					a.setAction(Action::Speed);
				}
				else {
					a = deplacementSpeed((*it));
					std::cerr << a.toString() << std::endl;

				}
				std::map<int,Action>::iterator ee = lstAction.find((*it).getId());
				if (ee == lstAction.end()) {
					lstAction.insert(std::pair<int, Action>((*it).getId(), a));
				}
				else
					(*ee).second = a;
			}
			else {
				lstAction.erase((*it).getId());
			}
		}
		for (std::map<int,Action>::iterator it = lstAction.begin(); it != lstAction.end(); ++it) {
			if (it != lstAction.begin())
				ret += "|";
			ret += (*it).second.toString();
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
	/** For TU*/
	Carte* getCarte() { return cart; }
};