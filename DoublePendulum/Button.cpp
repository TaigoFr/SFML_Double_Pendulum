#include "Global.h"


void Button::setUp(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y, std::string str, unsigned char_size, float scroll_start, float sscroll_max, float sscroll_min, float sscrol_step) {
	setOutlineColor(colorr);
	setOutlineThickness(5);
	setFillColor(sf::Color::Transparent);
	setSize(sf::Vector2f(size_xx, size_yy));
	setPosition(pos_x, pos_y);
	setFont("font.ttf");
	setUpText(text, str, colorr, pos_x, pos_y, size_xx, char_size, font);
	setUpScroll(scroll, colorr, pos_x, pos_y, size_xx, size_yy);
	scroll_max = sscroll_max;
	scroll_min = sscroll_min;
	if (scroll_start < scroll_min) 
		scroll_pos = sscroll_max / 2;
	else
		scroll_pos = scroll_start;
	scroll_step = sscrol_step;
};

void Button::setUpScroll(sf::RectangleShape &shape, sf::Color colorr, float xx, float yy, float size_xx, float size_yy) {
	shape.setSize(sf::Vector2f(size_xx, 20));
	shape.setOrigin(0, shape.getSize().y / 2);
	shape.setPosition(xx, yy + size_yy / 2);
	shape.setFillColor(colorr);
}

void Button::draw(sf::RenderWindow &window) {
	window.draw(*this);
	if (!text.getString().isEmpty()) window.draw(text);
	this->scroll.setPosition(this->getPosition().x, this->getPosition().y + scroll_pos / scroll_max * (this->getLocalBounds().height));
	window.draw(this->scroll);
}

void Button::ChangeValue(Button& button, bool up_down, float num) {
	if (func != NULL) func(button, up_down, num);
}

bool Button::isClicked(float x, float y) {

	if ((abs(x - getPosition().x) <= getSize().x) && (abs(y - getPosition().y) <= getSize().y)) {
		return true;
	}
	return false;
}

int isClicked(Button *button, int number, sf::Vector2i mouse) {
	for (int i = 0; i < number; i++)
		if (button[i].isClicked((float)mouse.x, (float)mouse.y))
			return i;

	return -1;
}

void Button::setUpText(sf::Text &ttext, std::string str, sf::Color colorr, float xx, float yy, float size_xx, unsigned char_size, sf::Font &ffont) {
	ttext.setFont(ffont);
	ttext.setString(str);
	ttext.setCharacterSize(char_size);
	ttext.setOrigin(ttext.getGlobalBounds().width / 2, ttext.getGlobalBounds().height);
	ttext.setFillColor(colorr);
	ttext.setPosition(xx + size_xx / 2, yy - ttext.getGlobalBounds().height);
}
