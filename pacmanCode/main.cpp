#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool param = true;
#include "point.h"
#include "element.h"
#include "carte.h"

#include "game.h"


/**
 * Grab the pellets as fast as you can!
 **/

int main()
{
	int width; // size of the grid
	int height; // top left corner is (x=0, y=0)
	cin >> width >> height; cin.ignore();
	cerr << width << " " << height << endl;
	Game g;
	g.initCarte(width, height);
	for (int i = 0; i < height; i++) {
		string row;
		getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
		g.addCarteLine(i, row);
	}
	g.printCarte();

	// game loop
	while (1) {
		g.init();
		int myScore;
		int opponentScore;
		cin >> myScore >> opponentScore; cin.ignore();
		int visiblePacCount; // all your pacs and enemy pacs in sight
		cin >> visiblePacCount; cin.ignore();
		for (int i = 0; i < visiblePacCount; i++) {
			int pacId; // pac number (unique within a team)
			bool mine; // true if this pac is yours
			int x; // position in the grid
			int y; // position in the grid
			string typeId; // unused in wood leagues
			int speedTurnsLeft; // unused in wood leagueccs
			int abilityCooldown; // unused in wood leagues
			cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; cin.ignore();
			if (param) {
				cerr << pacId << " " << mine << " " << x << " " << y << " " << typeId << " " << speedTurnsLeft << " " << abilityCooldown << endl;
			}
			PacMan e(Point(x,y),Element::Pac,pacId, speedTurnsLeft, mine,typeId);
			g.addPac(e);

		}
		int visiblePelletCount; // all pellets in sight
		cin >> visiblePelletCount; cin.ignore();
		for (int i = 0; i < visiblePelletCount; i++) {
			int x;
			int y;
			int value; // amount of points this pellet is worth
			cin >> x >> y >> value; cin.ignore();
			if (param) {
				cerr << x << " " << y << " " << value << endl;
			}
			Element e(Point(x, y), Element::Bouffe, 0, value, false);
			g.addPillule(e);
		}
		cout << g.calculDeplacement() << endl;

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		//cout << "MOVE 0 15 10" << endl; // MOVE <pacId> <x> <y>
	}
}