#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "simu.h"

using namespace std;
using namespace sf;

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
	coureur(int a) {
		dossard = a;
		nom = "Jack";
		masse = rand() % 75 + 45;
		taille = rand() % 70 + 130;
		poids_chaussure = rand() % 200 + 100;
		vitesse_moyenne = rand() % 13 + 7;
		semaine_prep = rand() % 8 + 8;
		hydratation = 1;
		distance_parcouru = 0;
		temps_course = 3;
	};
private:
	int dossard;
	string nom;
	int masse;
	int taille;
	int poids_chaussure;
	int vitesse_moyenne;
	long int semaine_prep;
	float hydratation;
	float distance_parcouru;
	float temps_course;

};

class circuit {
public:
	bool checkpoint(int position_actu) {
		if (position_actu % 5 == 1) {
			return true;
		}
		return false;
	}
	circuit() {
		longueur = 42.195;
		ravitaillement = 5;
		for (int i = 0; i < 42; i++)
		{
			denivele_map.push_back(0);
			vent_map.push_back(0);
		}
		for (int i = 0; i <= 40; i+=4)
		{
			vent vent_rand;
			denivele denivele_rand;
			for (int y = i; y <= vent_rand.get_distance(); y++)
			{
				vent_map[y] = vent_rand.get_vitesse();
			}
			for (int y = i; y <= denivele_rand.get_distance(); y++) {
				denivele_map[y] = denivele_rand.get_pente();
			}
		}
	}

private:
	double longueur;
	int ravitaillement;
	// vector <vent> vent_map;
	// vector <denivele> denivele_map;
	vector <int> vent_map;
	vector <int> denivele_map;

};

class denivele {
public:
	denivele() {
		pente = rand() % 20;
		distance = rand() % 4 + 1;
	}
	int get_distance() {
		return distance;
	}
	int get_pente() {
		return pente;
	}

private:
	int pente;
	int distance;
};

class vent {
public:
	vent() {
		vitesse = rand() % 80;
		distance = rand() % 2 + 1;
	};
	int get_distance() {
		return distance;
	}
	int get_vitesse() {
		return vitesse;
	}

private:
	int vitesse;
	int distance;
};




int main() {
	srand(time(NULL));
	coureur a(0);
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
			rectangle.setSize(sf::Vector2f(i % 700, 100));
			if (f.type == Event::Closed) {
				window.close();
			}
			window.draw(text);
			window.draw(rectangle);
			window.display();

		}
	}
	cout << a.vitesse() << endl;
}