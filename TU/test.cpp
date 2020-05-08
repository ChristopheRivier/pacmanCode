#include "pch.h"
#include "../pacmanCode/game.h"
TEST(TestCaseName, TestName) {
	Game g;
	g.initCarte(4, 4);
	g.addCarteLine(0, "####");
	g.addCarteLine(1, "#  #");
	g.addCarteLine(2, "#  #");
	g.addCarteLine(3, "####");

	Element e(Point(1, 1), Element::Pac, 0, 0, true);
	g.addPac(e);
	Element p(Point(1,2 ), Element::Bouffe, 0, 1, false);

	g.addPillule(p);
	p = Element(Point(2, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	p = Element(Point(2, 1), Element::Bouffe, 0, 10, false);
	g.addPillule(p);

	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 2 1");
	;
}

TEST(TestCaseName, changementDeCote) {
	Game g;
	g.initCarte(4, 4);
	g.addCarteLine(0, "####");
	g.addCarteLine(1, "    ");
	g.addCarteLine(2, "#  #");
	g.addCarteLine(3, "####");

	Element e(Point(0, 1), Element::Pac, 0, 0, true);
	g.addPac(e);
	Element p(Point(1, 2), Element::Bouffe, 0, 1, false);

	g.addPillule(p);
	p = Element(Point(2, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	p = Element(Point(3, 1), Element::Bouffe, 0, 10, false);
	g.addPillule(p);

	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 3 1");
	;
}