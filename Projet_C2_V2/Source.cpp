#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <time.h>    
#include "jsoncpp-master\include\json\value.h""
#include "jsoncpp-master\include\json\json.h"
#include "simu.h"
#include "json/coureurs.json"

using namespace std;
using namespace sf;

class coureur {
public:
	float vitesse() {
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
	int masse = 45;
	int taille = 130;
	int poids_chaussure = 100;
	int vitesse_moyenne = 7;
	int semaine_prep = 8;
	float hydratation = 1;
	float distance_parcouru = 0;
	float temps_course = 3;
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
	float longeur = 42.195;
	int ravitaillement = 5;
};

class denivele {
public:
	float pente = rand() % 20 + 1;
	float distance = rand() % 4 + 1;
};




int main()
{
	srand(time(NULL));
	coureur a;
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
	cout << a.vitesse() << endl;/*
	ifstream people_file("json/coureurs.json", ifstream::binary);
	people_file >> coureurs;
	
	cout << coureurs; //This will print the entire json object.*/
}