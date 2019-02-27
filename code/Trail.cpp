#include "Global.h"

int Trail::alphaT = 50;
int Trail::betaT = 50;
int Trail::gamaT = 49;

sf::VertexArray Trail::vertex (sf::Lines, 1000);

void Trail::append(sf::Vertex vertexToAppend) {
	vertex[vertex.getVertexCount() - 1] = vertexToAppend;
	vertex[vertex.getVertexCount() - 1].color = Trail::setColor();
}

void Trail::vertexReorder() {

	for (int i = 1; i < vertex.getVertexCount(); i++) {
		if (vertex[i].position.x <= 0) vertex[i].position = vertex[vertex.getVertexCount() - 1].position;
		vertex[i - 1] = vertex[i];
	}
}

int Trail::getAlpha() {
	if (alphaT == 255) { betaT++; gamaT = 50; }
	if (alphaT == 49) { betaT--; gamaT = 254; }
	return alphaT;
}
int Trail::getBeta() {
	if (betaT == 49) { gamaT--; alphaT = 50; }
	if (betaT == 255) { gamaT++; alphaT = 254; }
	return betaT;
}
int Trail::getGama() {
	if (gamaT == 49) { alphaT++; betaT = 50; }
	if (gamaT == 255) { alphaT--; betaT = 254; }
	return gamaT;
}