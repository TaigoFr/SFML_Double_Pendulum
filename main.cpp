 
#include "Global.h"


float r1 = 500;
float r2 = 500;
float m1 = 40;
float m2 = 40;
const float init_1 = PI;
const float init_2 = -PI / 2;
float a1 = init_1;
float a2 = init_2;
float a1_v = 0;
float a2_v = 0;
float g = 1;

std::vector<sf::Vector2f> trail(1000);

void increaseMass1(Button& button, bool up_down, float num) {
	if (num <= 0) {

		if (up_down) {
			if (m1 < button.getScrollMax())
				m1 += button.getScrollStep();
		}
		else {
			if (m1 > button.getScrollMin())
				m1 -= button.getScrollStep();
		}
	}
	else {
		m1 = (num / button.getSize().y) * button.getScrollMax();
	}
	button.setScrollPos(m1);
}
void increaseMass2(Button& button, bool up_down, float num) {
	if (num <= 0) {
	if (up_down) {
		if (m2 < button.getScrollMax())
			m2 += button.getScrollStep();
	}
	else {
		if (m2 > button.getScrollMin())
			m2 -= button.getScrollStep();
	}
	}
	else {
		m2 = (num / button.getSize().y) * button.getScrollMax();
	}
	button.setScrollPos(m2);

}
void increaseArm1(Button& button, bool up_down, float num) {
	if (num <= 0) {
		if (up_down) {
			if (r1 < button.getScrollMax())
				r1 += button.getScrollStep();
		}
		else {
			if (r1 > button.getScrollMin())
				r1 -= button.getScrollStep();
		}
	}
	else {
		r1 = (num / button.getSize().y) * button.getScrollMax();
	}
	button.setScrollPos(r1);

}
void increaseArm2(Button& button, bool up_down, float num) {
	if (num <= 0) {
		if (up_down) {
			if (r2 < button.getScrollMax())
				r2 += button.getScrollStep();
		}
		else {
			if (r2 > button.getScrollMin())
				r2 -= button.getScrollStep();
		}
	}
	else {
		r2 = (num / button.getSize().y) * button.getScrollMax();
	}
	button.setScrollPos(r2);
}
void increaseGravity(Button& button, bool up_down, float num) {
	if (num <= 0) {
		if (up_down) {
			if (g < button.getScrollMax())
				g += button.getScrollStep();
		}
		else {
			if (g > button.getScrollMin())
				g -= button.getScrollStep();
		}
	}
	else {
		g = (num / button.getSize().y) * button.getScrollMax();
	}

	button.setScrollPos(g);
}

int main() {

	//sf::ContextSettings settings;
	///settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode((unsigned)screenWidth, (unsigned)screenHeight), "Double Pendulum");//, sf::Style::Default, settings);

	window.setView(sf::View(sf::FloatRect(0, 0, screenWidth * 3840 / sf::VideoMode::getDesktopMode().width, screenHeight * 2160 / sf::VideoMode::getDesktopMode().height)));
	window.setPosition(sf::Vector2i(0, 0));

	sf::Event event;

	sf::CircleShape circle1;
	circle1.setOutlineColor(sf::Color::Blue);
	circle1.setOutlineThickness(5);

	sf::CircleShape circle2;
	circle2.setOutlineColor(sf::Color::Blue);
	circle2.setOutlineThickness(5);


	std::vector<Trail> trail(500);


	const int buttons_number = 5;
	Button button[buttons_number];
	std::string texts[buttons_number] = { "Mass1", "Mass2", "Arm1", "Arm2", "Gravity" };
	sf::Vector3f scroll[buttons_number] = {sf::Vector3f(m1, 100, 1), sf::Vector3f(m2, 100, 1), sf::Vector3f(a1, 800, 20), sf::Vector3f(a2, 800, 20), sf::Vector3f(g, 9.5, 0) };
	float scroll_step[buttons_number] = { 10, 10, 10, 10, 0.5};
	void(*func[buttons_number])(Button& button, bool up_down, float num) = { increaseMass1, increaseMass2, increaseArm1, increaseArm2, increaseGravity };

	for (int i = buttons_number - 1; i >= 0; i--) {
		button[i].setUp(50, 400, sf::Color::White, 2560 - (i + 1) * 200, 100, texts[i], 40, scroll[i].x, scroll[i].y, scroll[i].z, scroll_step[i]);
		button[i].setFunction(func[i]);
	}


	bool mouse_button_clicked = false;


	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {

		sf::sleep(sf::milliseconds(15));


		float num1 = -g * (2 * m1 + m2) * sin(a1);
		float num2 = -m2 * g * sin(a1 - 2 * a2);
		float num3 = -2 * sin(a1 - a2) * m2;
		float num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
		float den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a1_a = (num1 + num2 + num3 * num4) / den;

		num1 = 2 * sin(a1 - a2);
		num2 = (a1_v * a1_v * r1 * (m1 + m2));
		num3 = g * (m1 + m2) * cos(a1);
		num4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
		den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a2_a = (num1 * (num2 + num3 + num4)) / den;

		float x1 = r1 * sin(a1);
		float y1 = r1 * cos(a1);

		float x2 = r2 * sin(a2);
		float y2 = r2 * cos(a2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { a1 = init_1; a2 = init_2; a1_v = 0; a2_v = 0; a1_a = 0; a2_a = 0; }


		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(2560 / 3, 1600 / 3)),
			sf::Vertex(sf::Vector2f(line1[0].position.x + x1, line1[0].position.y + y1))
		};

		circle1.setRadius(m1);
		circle1.setPosition(line1[1].position.x, line1[1].position.y);
		circle1.setOrigin(circle1.getRadius(), circle1.getRadius());


		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(line1[1].position)),
			sf::Vertex(sf::Vector2f(line2[0].position.x + x2, line2[0].position.y + y2))
		};

		circle2.setRadius(m2);
		circle2.setPosition(line2[1].position.x, line2[1].position.y);
		circle2.setOrigin(circle2.getRadius(), circle2.getRadius());

		a1 += a1_v + a1_a/2;
		a2 += a2_v + a2_a/2;
		a1_v += a1_a;
		a2_v += a2_a;


		window.pollEvent(event);
		if (event.type == sf::Event::MouseWheelMoved) {
			int i = isClicked(button, buttons_number, sf::Mouse::getPosition(window));
			if (i >= 0) { button[i].ChangeValue(button[i], (event.mouseWheel.delta > 0) ? 0 : 1, 0); }
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			mouse_button_clicked = true;

		if (mouse_button_clicked && (event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) {
			mouse_button_clicked = false;
			int i = isClicked(button, buttons_number, sf::Mouse::getPosition(window));
			if (i >= 0) { button[i].ChangeValue(button[i], 1, sf::Mouse::getPosition(window).y - button[i].getPosition().y); }
		}

		if (event.type == sf::Event::Closed) {
			window.close();
			exit(1);
		}



		Trail::vertexReorder();
		trail[trail.size() - 1].setPosition(circle2.getPosition());
		Trail::append(trail[trail.size() - 1].getPosition());

		window.clear();

		for (int i = 0; i < buttons_number; i++) {
			button[i].draw(window);
		}

		window.draw(Trail::getVertexArray());
		window.draw(circle1);
		window.draw(circle2);
		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
		window.display();
	}


	return 0;
}