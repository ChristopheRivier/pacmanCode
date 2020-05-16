#pragma once

#include "point.h"
#include "element.h"
class Action {
public:
	enum EAction {
		Move=0,
		Speed,
		Switch
	};
	void setPosition(Point p) { pos = p; }
	Point getPoint() { return pos; }
	void setId(int i) { id = i; }
	int getId() { return id; }
	void setAction(EAction a) { ty = a; }
	EAction getAction() { return ty; }
	void setSwitch(Element::Echifoumi e) { typeSwitch = e; }
	Element::Echifoumi getSwitch() { return typeSwitch; }
	std::string toString() {
		switch (ty)
		{
		case Action::Move:
			return "MOVE " + std::to_string(id) + " " + pos.toString();
			break;
		case Action::Speed:
			return "SPEED " + std::to_string(id);
			break;
		case Action::Switch:
			return "SWITCH " + std::to_string(id) + " " +PacMan::getStrType(typeSwitch);
			break;
		default:
			return "";
			break;
		}
	}
private:
	Point pos;
	int id;
	EAction ty;
	Element::Echifoumi typeSwitch;
};