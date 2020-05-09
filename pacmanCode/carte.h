#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "element.h"

class Tuile {
	char input;
	bool visite = false;
	std::vector<Element*> lst;

public:
	Tuile() { input = '\0'; }
	void setChar(char c) { input = c; }
	char getChar() { return input; }
	
	bool isWall() { return input == '#'; }
	bool isFree() { return !isWall(); }
	void clearPass() {
		lst.clear();
	}
	void addEl(Element& e) {
		if (e.isPac())
			passer();
		lst.push_back(&e);
	}
	double getPoid(Element::Echifoumi chi) {
		double a = .0;
		for (std::vector<Element*>::iterator it = lst.begin(); it != lst.end(); ++it) {
			a += (*it)->getPoid(chi);
		}
		if(!visite)
			a += 600.;
		return a;
	}
	void passer() { visite = true; }
	bool isPasser() { return visite; }
};

class Carte {
	int width;
	int height;
	Tuile** cart;
	Point init;
public:
	Carte(int w, int h) :width(w), height(h) {
		cart = new Tuile * [w];
		for (int i = 0; i < w; ++i)
			cart[i] = new Tuile[h];
	}
	~Carte(){
		for (int i = 0; i < width; ++i)
			delete[] cart[i];
		delete []cart;

	}
	void reinitCarte() {
		for (int i = 0; i < width; ++i)
			delete[] cart[i];
		delete[]cart;
		cart = NULL;
	}
	Carte& operator=(const Carte& c) {
		reinitCarte();
		this->width = c.width;
		this->height=c.height;
		this->init = c.init;

		Tuile** cart;
		cart = new Tuile * [width];
		for (int i = 0; i < width; ++i) {
			cart[i] = new Tuile[height];
			for (int j = 0; j < height; ++j) {
				this->cart[i][j] = c.cart[i][j];
			}
		}
	}

	void addTuile(int i, int j, char in) {
		cart[i][j].setChar(in);
	}
	void addLine(int i, std::string line) {
		std::vector < Tuile> v;
		for (int j = 0; j < width; ++j) {
			cart[j][i].setChar(line[j]);
		}
	}
	bool isWall(Point p) {
		return cart[p.x][p.y].isWall();
	}

	bool deplacementPossible(Point p,Point from) {
		return p!=from && cart[p.x][p.y].isFree();
	}
	void position(Point p) {
		cart[p.x][p.y].passer();
	}
	void addEl(Element& e) {
		cart[e.getX()][e.getY()].addEl(e);
	}
	double getPoid(Point& p,Element::Echifoumi monType) {
		return cart[p.x][p.y].getPoid(monType);
	}
	void printCarte() {
		if (true) {
			/*for (int j = 0; j < height; ++j)
			{
				std::cerr << "	ca.addLine(" << j<<",\"";
				for (int i = 0; i < width; ++i)
				{
					std::cerr << cart[i][j].getChar();
				}
				std::cerr<< "\");"<<std::endl;
			}
				std::cerr << "Game a;" << std::endl;
				std::cerr << "a.addCarte(ca);" << std::endl;
				std::cerr << "InfoBoucle boul;" << std::endl;
		*/
			for (int j = 0; j < height; ++j)
			{
				for (int i = 0; i < width; ++i)
				{
					std::cerr << cart[i][j].isPasser() ? "1 ":"0 ";
				}
				std::cerr << "" << std::endl;
			}
		}
	}
	void clear() {
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				cart[i][j].clearPass();
			}
		}
	}
	/**
	for debug TU add all pass to tuile
	*/
	void allPass() {
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				cart[i][j].passer();
			}
		}

	}
	
};