#pragma once
#include "Global.h"


class Button : public sf::RectangleShape {
public:
	Button() {};
	Button(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y, std::string str, unsigned char_size, float scroll_start, float sscroll_max, float sscroll_min, float sscroll_step) { 
		setUp(size_xx, size_yy, colorr, pos_x, pos_y, str, char_size, scroll_start, sscroll_max, sscroll_min, sscroll_step);
	};

	void setFunction(void(*ffunc)(Button& button, bool up_down, float num )) { func = ffunc; }

	void setUp(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y, std::string str, unsigned char_size, float scroll_start, float sscroll_max, float sscroll_min, float sscrol_step);

	bool isClicked(float x, float y);

	void draw(sf::RenderWindow &windowfloat);

	void ChangeValue(Button& button, bool up_down, float num);

	void setScrollPos(float add) { scroll_pos = add;}

	float getScrollMax() { return scroll_max; }
	float getScrollMin() { return scroll_min; }
	float getScrollStep() { return scroll_step; }

private:

	float scroll_pos;
	float scroll_max;
	float scroll_min;
	float scroll_step;

	void(*func)(Button& button, bool up_down, float num) = NULL;

	sf::Font font;
	sf::Text text;

	sf::Color color;

	sf::RectangleShape scroll;

	void setFont(std::string str) { font.loadFromFile(str); }

	static void setUpText(sf::Text &ttext, std::string str, sf::Color color, float pos_x, float pos_y,float size_x, unsigned char_size, sf::Font &ffont);
	static void setUpScroll(sf::RectangleShape &shape, sf::Color color, float xx, float yy, float size_xx, float size_yy);

};

int isClicked(Button *button, int number, sf::Vector2i mouse);