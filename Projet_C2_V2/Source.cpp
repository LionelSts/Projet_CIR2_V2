#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <time.h>    
#include "json-develop\include\nlohmann\json_fwd.hpp"
#include "simu.h"
#include "json/coureurs.json"

using namespace std;
using namespace sf;
using json = nlohmann::json;

class coureur {
public:
	double vitesse() {
		if (distance_parcouru < (42.195 / 2 * (1 + (semaine_prep - 8) / 8))) {
			if (((hydratation / (0.5 * temps_course)) < 0.8)) {
				return (vitesse_moyenne * (poids_chaussure / 100 * (98.9 / 100)) * (((1 / 0.6)* (1 / (hydratation/(0.5*temps_course))))*0.99));
			}
			return (vitesse_moyenne * (poids_chaussure / 100 * (98.9 / 100)));
		}
		
		if ((hydratation / (0.5 * temps_course)) < 0.8) {
			return (vitesse_moyenne * (poids_chaussure / 100 * (98.9 / 100)) * (((hydratation / (0.5 * temps_course)) - 0.2) * 10 * 0.99)) * ((distance_parcouru - ((42.195 / 2) * (1 + (semaine_prep - 8) / 8))) / ((42.195 / 2) * (1 + (semaine_prep - 8) / 8)) * 0.8);
		}
		return vitesse_moyenne * (poids_chaussure / 100 * (98.9 / 100))*((distance_parcouru-((42.195/2)*(1+(semaine_prep-8)/8)))/ ((42.195 / 2) * (1 + (semaine_prep - 8) / 8))*0.8);
		
	}
private:
	int masse;
	int taille;
	int poids_chaussure;
	int vitesse_moyenne;
	int semaine_prep;
	float hydratation;
	float distance_parcouru;
	float temps_course;

coureur() {
	masse = 45;
	taille = 130;
	poids_chaussure = 100;
	vitesse_moyenne = 7;
	semaine_prep = 8;
	hydratation = 1;
	distance_parcouru = 0;
	temps_course = 3;
};
coureur(int num) {
	masse = 45;
	taille = 130;
	poids_chaussure = 100;
	vitesse_moyenne = 7;
	semaine_prep = 8;
	hydratation = 1;
	distance_parcouru = 0;
	temps_course = 3;
};
};

class circuit {
public:
	int vent() {};
	bool checkpoint(int position_actu) {
		if (position_actu % 5 == 1) {
			return true;
		}
		return false;
	}
private:
	float longueur;
	int ravitaillement;

circuit() {
	longueur = 42.195;
	ravitaillement = 5;
}
};

class denivele {
private:
	float pente;
	float distance;

denivele() {
	pente = rand() % 20;
	distance = rand() % 4 + 1;
}
};

class vent {
private:
	float vitesse;
	float distance;

vent(){
	vitesse = rand() % 80;
	distance = rand() % 2 + 1;
};
};




int main()
{
	srand(time(NULL));
	// coureur a;
	RenderWindow window(VideoMode(1300, 700), "Simulation");
	Event f;
	Text text;
	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "impossible de charger la police d'ecriture" << endl;
	}
	text.setFont(font);
	sf::RectangleShape rectangle(sf::Vector2f(1, 100));
	int i = 0;
	while (window.isOpen())
	{
		while (window.pollEvent(f))
		{
			window.clear();
			text.setCharacterSize(30);
			text.setPosition(0, 0);
			text.setString("Démarage d'une simulation");
			rectangle.setPosition(400, 100);
			i++;
			rectangle.setSize(sf::Vector2f(i%700, 100));
			if (f.type == Event::Closed) {
				window.close();
			}
			window.draw(text);
			window.draw(rectangle);
			window.display();

		}
	}
	// cout << a.vitesse() << endl;
