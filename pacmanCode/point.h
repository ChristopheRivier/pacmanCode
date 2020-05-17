#ifndef POINT
#define POINT

#include <string>

class Singleton {
	Singleton() {} // constructeur privé
	int width;
	int height;
	double poidAttaque = 1000;
	double poidVisite = 850;
	double poidBouffe = 10;
	double poidBouffeMax = 100;
	double poidVide = 10;
	double poidFuite = -1100;
	static Singleton* singleton;

public:
	static Singleton& get() { // pour obtenir le singleton
	   // Instanciation au premier appel seulement
		static Singleton singleton;
		return singleton;
	}
	double getPoidFuite() { return poidFuite; }
	void setPoidFuite(double a) { poidFuite = a; }
	double getPoidVide() {
		return poidVide;
	}
	void setPoidVide(double a) { poidVide = a; }
	double getPoidAttaque() {
		return poidAttaque;
	}
	void setPoidAttaque(double  a) {
		poidAttaque = a;
	}
	double getPoidVisite() {
		return poidVisite;
	}
	void setPoidVisite(double e) {
		poidVisite = e;
	}
	double getPoidBouffe() {
		return poidBouffe;
	}
	void setPoidBouffe(double e) { poidBouffe = e; }
	double getPoidBouffeMax() { return poidBouffeMax; }
	void setPoidBouffeMax(double a) { poidBouffeMax = a; }
	// ...
	void setWidth(int w) {
		width = w-1;
	}
	void setHeight(int h) {
		height = h-1;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
};

class Point {
public:
	int x, y;

	Point() :x(0), y(0) {}
	Point(int a, int b):x(a),y(b){}
	std::string toString() { return  std::to_string(x) + " " + std::to_string(y); }
	Point getN() {
		Point ret(this->x, this->y);
		ret.goN();
		return ret;
	}
	Point getS() {
		Point ret(this->x, this->y);
		ret.goS();
		return ret;
	}
	Point getE() {
		Point ret(this->x, this->y);
		ret.goE();
		return ret;
	}
	Point getW() {
		Point ret(this->x, this->y);
		ret.goW();
		return ret;
	}
	Point getInv(char w) {
		switch (w) {
		case 'N':
			return getS();
		case 'S':
			return getN();
		case 'E':
			return getW();
		case 'W':
			return getE();
		}
		return *this;
	}
	Point get(char w) {
		switch (w) {
		case 'N':
			return getN();
		case 'S':
			return getS();
		case 'E':
			return getE();
		case 'W':
			return getW();
		}
		return *this;
	}
	bool go(char w) {
		switch (w) {
		case 'N':
			return goN();
		case 'S':
			return goS();
		case 'E':
			return goE();
		case 'W':
			return goW();
		case '?':
			//in that case we will do the test after
			return true;
		}
		return false;
	}
	bool goN() {
		if (y > 0) {
			--y;
			return true;
		}
		else
		{
			y = Singleton::get().getHeight();
			return true;
		}
	}
	bool goE() {
		if (x < Singleton::get().getWidth()) {
			++x;
			return true;
		}
		else
		{
			x = 0;
			return true;
		}
	}
	bool goW() {
		if (x > 0) {
			--x;
			return true;
		}
		else
		{
			x = Singleton::get().getWidth();
			return true;
		}
	}
	bool goS() {
		if (y < Singleton::get().getHeight()) {
			++y;
			return true;
		}
		else
		{
			y = 0;
			return true;
		}
	}
	bool is(char w) {
		switch (w) {
		case 'N':
			return N();
		case 'S':
			return S();
		case 'E':
			return E();
		case 'W':
			return W();
		case '?':
			//in that case we will do the test after
			return true;
		}
		return false;
	}
	bool N() {
		if (y > 0) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool E() {
		if (x < 14) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool W() {
		if (x > 0) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool S() {
		if (y < 14) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(const Point& a) {
		return this->x == a.x && this->y == a.y;
	}
	bool operator!=(const Point& a) {
		return this->x != a.x || this->y != a.y;
	}
};

class PointList{
public:
	Point pos;
	std::vector<Point> lst;
	PointList(){}
	PointList(int x, int y) { pos = Point(x, y); }
	bool changePos(Point p) {
		if (std::find(lst.begin(), lst.end(), p) != lst.end() && lst.size()>0)
			return false;
		else
		{
			lst.push_back(pos);
			pos = p;
			return true;
		}
	}
	bool operator==(const PointList& a) {
		bool ret = true;
		return this->pos == a.pos && std::equal(this->lst.begin(),this->lst.end(),a.lst.begin());
	}
	bool operator!=(const PointList& a) {
		return !( *this == a) ;
	}
	std::string toString() {
		std::string ret;
		ret = "pos: " + pos.toString();
		for (std::vector<Point>::iterator it=lst.begin(); it != lst.end(); ++it)
		{
			ret += "; "+ (*it).toString();
		}
		return ret;
	}

};

#endif // !POINT

