#include "pch.h"
#include "../pacmanCode/game.h"
TEST(TestCaseName, TestName) {
	Game g;
	g.initCarte(4, 4);
	g.setCpt(10);
	g.addCarteLine(0, "####");
	g.addCarteLine(1, "#  #");
	g.addCarteLine(2, "#  #");
	g.addCarteLine(3, "####");

	PacMan e(Point(1, 1), Element::Pac, 0, 0, true,"ROCK");
	g.addPac(e);
	Element p(Point(1,2 ), Element::Bouffe, 0, 1, false);

	g.addPillule(p);
	p = Element(Point(2, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	p = Element(Point(2, 1), Element::Bouffe, 0, 10, false);
	g.addPillule(p);

	g.noSpeed();
	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 2 1");
	;
}

TEST(TestCaseName, changementDeCote) {
	Game g;
	g.initCarte(4, 4);

	g.setCpt(10);
	g.addCarteLine(0, "####");
	g.addCarteLine(1, "    ");
	g.addCarteLine(2, "#  #");
	g.addCarteLine(3, "####");

	PacMan e(Point(0, 1), Element::Pac, 0, 0, true, "ROCK");
	g.addPac(e);
	Element p(Point(1, 2), Element::Bouffe, 0, 1, false);

	g.addPillule(p);
	p = Element(Point(2, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	p = Element(Point(3, 1), Element::Bouffe, 0, 10, false);
	g.addPillule(p);

	g.noSpeed();
	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 3 1");
	;
}

TEST(TestCaseName, TestCombat) {
	Game g;
	g.initCarte(4, 4);
	g.setCpt(10);
	g.addCarteLine(0, "####");
	g.addCarteLine(1, "    ");
	g.addCarteLine(2, "#  #");
	g.addCarteLine(3, "####");

	PacMan e(Point(1, 1), Element::Pac, 0, 0, false, "SCISSORS");
	g.addPac(e);
	e=PacMan(Point(0, 1), Element::Pac, 0, 0, true, "ROCK");
	g.addPac(e);
	Element p(Point(1, 2), Element::Bouffe, 0, 1, false);

	g.addPillule(p);
	p = Element(Point(2, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	p = Element(Point(3, 1), Element::Bouffe, 0, 1, false);
	g.addPillule(p);

	g.noSpeed();
	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 1 1");
	;
}

TEST(TestCaseName, CoincedansMur) {
	Game g;
	g.initCarte(8, 8);

	g.setCpt(10);
	g.addCarteLine(0, "########");
	g.addCarteLine(1, "# # #  #");
	g.addCarteLine(2, "# # #  #");
	g.addCarteLine(3, "# # #  #");
	g.addCarteLine(4, "# # #  #");
	g.addCarteLine(5, "# # #  #");
	g.addCarteLine(6, "# # #  #");
	g.addCarteLine(7, "########");

	PacMan e(Point(1, 1), Element::Pac, 0, 0, true, "SCISSORS");
	g.addPac(e);
	g.allPass();
	g.noSpeed();
	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 1 2");
}

TEST(TestSpeed, simpleSpeed) {
	Game g;
	g.initCarte(8, 8);
	g.addCarteLine(0, "########");
	g.addCarteLine(1, "#      #");
	g.addCarteLine(2, "# #### #");
	g.addCarteLine(3, "#   #  #");
	g.addCarteLine(4, "# # #  #");
	g.addCarteLine(5, "# # #  #");
	g.addCarteLine(6, "# # #  #");
	g.addCarteLine(7, "########");

	PacMan e(Point(1, 1), Element::Pac, 0, 5, true, "SCISSORS");
	g.addPac(e);
	g.allPass();
	g.notPass(1, 2);
	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 1 3");
}

TEST(TestSpeed, avecOpposant ) {
	//see lumix
	Game g;
	g.initCarte(35, 14);
	g.addCarteLine(0, "###################################");
	g.addCarteLine(1, "    #   ### # #     # # ###   #    ");
	g.addCarteLine(2, "### # # ### # # # # # # ### # # ###");
	g.addCarteLine(3, "      #         # #         #      ");
	g.addCarteLine(4, "##### # ##### ####### ##### # #####");
	g.addCarteLine(5, "# #   #   #             #   #   # #");
	g.addCarteLine(6, "# # # ### # # # ### # # # ### # # #");
	g.addCarteLine(7, "#   #         #     #         #   #");
	g.addCarteLine(8, "### # ### # ### ### ### # ### # ###");
	g.addCarteLine(9, "    #   # #             # #   #    ");
	g.addCarteLine(10, "### ### # ### # ### # ### # ### ###");
	g.addCarteLine(11, "#         #   #     #   #         #");
	g.addCarteLine(12, "# # ### # # # ### ### # # # ### # #");
	g.addCarteLine(13, "###################################");


	PacMan e(Point(16, 5), Element::Pac, 0, 0, false, "ROCK");
	g.addPac(e);
	e = PacMan(Point(2, 9), Element::Pac, 1, 5, false, "PAPER");
	g.addPac(e);
	e = PacMan(Point(32, 9), Element::Pac, 1, 5, true, "PAPER");
	g.addPac(e);

	e = PacMan(Point(33, 9), Element::Pac, 3, 5, true, "ROCK");
	g.addPac(e);
	e = PacMan(Point(1, 9), Element::Pac, 3, 0, false, "PAPER");
	g.addPac(e);

	g.allPass();
	EXPECT_EQ(g.calculDeplacement(), "MOVE 1 31 10|SWITCH 3 SCISSORS");
}


TEST(TestCase, ErreurVisite) {

	Game g;
	g.initCarte(33, 14);
	g.addCarteLine(0, "#################################");
	g.addCarteLine(1, "###   #   # # ##### # #   #   ###");
	g.addCarteLine(2, "##### # ### # ##### # ### # #####");
	g.addCarteLine(3, "      #                   #      ");
	g.addCarteLine(4, "### ### ### # ##### # ### ### ###");
	g.addCarteLine(5, "            #       #            ");
	g.addCarteLine(6, "##### # ##### # # # ##### # #####");
	g.addCarteLine(7, "      #       #   #       #      ");
	g.addCarteLine(8, "### # ### # # ##### # # ### # ###");
	g.addCarteLine(9, "    #       #       #       #    ");
	g.addCarteLine(10, "##### ### ##### # ##### ### #####");
	g.addCarteLine(11, "#       #   #       #   #       #");
	g.addCarteLine(12, "# # # # # # # # # # # # # # # # #");
	g.addCarteLine(13, "#################################");
	PacMan e(Point(31, 7), Element::Pac, 0, 0, true, "ROCK");
	g.addPac(e);
	e = PacMan(Point(1, 7), Element::Pac, 0, 0, false, "ROCK");
	g.addPac(e);
	e = PacMan(Point(15, 5), Element::Pac, 1, 0, true, "PAPER");
	g.addPac(e);
	e = PacMan(Point(17, 5), Element::Pac, 1, 0, false, "PAPER");
	g.addPac(e);
	e = PacMan(Point(13, 6), Element::Pac, 2, 0, true, "SCISSORS");
	g.addPac(e);

	Element el(Point(30, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(29, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(28, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(27, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(32, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(0, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(2, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(3, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(4, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(5, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(14, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(16, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(18, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(19, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(15, 6), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(15, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 4), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 3), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 1), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 8), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(13, 9), Element::Bouffe, 0, 1, false);
	g.addPillule(el);

	el = Element(Point(7, 4), Element::Bouffe, 0, 10, false);
	g.addPillule(el);

	el = Element(Point(25, 4), Element::Bouffe, 0, 10, false);
	g.addPillule(el);

	el = Element(Point(11, 5), Element::Bouffe, 0, 10, false);
	g.addPillule(el);

	el = Element(Point(21, 5), Element::Bouffe, 0, 10, false);
	g.addPillule(el);

	EXPECT_EQ(g.calculDeplacement(), "SPEED 0|SPEED 1|SPEED 2");
	EXPECT_FALSE(g.getCarte()->isPasser(Point(30, 7)));

}
TEST(TestCase, Gourmand) {
	//see lumix
	Game g;
	g.initCarte(31, 16);
	g.addCarteLine(0, "###############################");
	g.addCarteLine(1, "### # # # #   ###   # # # # ###");
	g.addCarteLine(2, "### # # # # # ### # # # # # ###");
	g.addCarteLine(3, "      #   # # # # # #   #      ");
	g.addCarteLine(4, "### # ### # # # # # # ### # ###");
	g.addCarteLine(5, "    #       #     #       #    ");
	g.addCarteLine(6, "### ##### ### ### ### ##### ###");
	g.addCarteLine(7, "# #           ###           # #");
	g.addCarteLine(8, "# # # # ### # ### # ### # # # #");
	g.addCarteLine(9, "# #   # ### #     # ### #   # #");
	g.addCarteLine(10, "# # ### ### # ### # ### ### # #");
	g.addCarteLine(11, "#           #     #           #");
	g.addCarteLine(12, "### ### # # ### ### # # ### ###");
	g.addCarteLine(13, "#   #   #             #   #   #");
	g.addCarteLine(14, "# # # # ##### # # ##### # # # #");
	g.addCarteLine(15, "###############################");

	PacMan e(Point(9, 5), Element::Pac, 0, 2, true, "ROCK");
	g.addPac(e);


	Element el(Point(7, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(6, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(5, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(10, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(11, 5), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(9, 3), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(9, 2), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(9, 1), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(19, 10), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(19, 9), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(19, 8), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(19, 7), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(19, 13), Element::Bouffe, 0, 1, false);
	g.addPillule(el);
	el = Element(Point(9, 4), Element::Bouffe, 0, 10, false);
	g.addPillule(el);
	el = Element(Point(8, 5), Element::Bouffe, 0, 10, false);
	g.addPillule(el);
	

	EXPECT_EQ(g.calculDeplacement(), "MOVE 0 9 3");

}