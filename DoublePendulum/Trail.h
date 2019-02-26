#pragma once
#include <SFML/Graphics.hpp>
class Trail{
public:

	Trail() {}

	static sf::Color setColor() { return sf::Color(getAlpha(), getBeta(), getGama(), 255);}

	void setPosition(sf::Vector2f pposition) { position = pposition; return;}

	sf::Vector2f getPosition() { return position; }

	static void vertexReorder();
	
	static sf::VertexArray getVertexArray() { return vertex; }

	static void append(sf::Vertex vertexToAppend);

private:

	static int alphaT;
	static int betaT;
	static int gamaT;

	static int getAlpha();
	static int getBeta();
	static int getGama();

	static sf::VertexArray vertex;

	sf::Vector2f position;

};