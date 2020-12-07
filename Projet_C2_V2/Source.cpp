#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cmath>
#include "simu.h"

using namespace std;
using namespace sf;

// class initialisant les denivele de façon aléatoire en % et en longueur 
class denivele {
public:
	denivele() {
		pente = rand() % 40 -20;
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

// class initialisant le vent de façon aléatoire en km/h et en longueur 
class vent {
public:
	vent() {
		vitesse = rand() % 80;
		distance = rand() % 2 + 1;
	}
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

// définition de la classe coureur
class coureur {
public:
	// calcul de la vitesse du coureur en temps normal
	double vitesse() {
		double vitesse = (vitesse_moyenne * (poids_chaussure / 100 * (98.9 / 100)));
		if (distance_parcouru < (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8))) {
			if (((hydratation / (0.5 * temps_course)) < 0.8)) {
				
				return  vitesse*(100-(((1 / 0.6)* (1 / (hydratation/(0.5*temps_course))))*0.01));
			}
			return vitesse;
		}
		
		if ((hydratation / (0.5 * temps_course)) < 0.8) {
			
			vitesse = vitesse * (100 - (((1 / 0.6) * (1 / (hydratation / (0.5 * temps_course)))) * 0.01));
			vitesse -= (((0.2 * (distance_parcouru - (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) / (42.195 - (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) * vitesse);
			return vitesse;
		}
		vitesse -= (((02 * (distance_parcouru -(42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) / (42.195-(42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) * vitesse);
		return vitesse;
		
	}

	//initialisation aléatoire des caraéctéristiques du coureur
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
		temps_course = 0.01;
	};

	int get_taille() {
		return taille;
	}
	int get_masse() {
		return masse;
	}
	float get_distance() {
		return distance_parcouru;
	}

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

// définition du circuit grace à une classe
class circuit {
public:
	// fonctino renvoyant si l'on est à un chekcpoint
	bool checkpoint(int position_actu) {
		if (position_actu % 5 == 1) {
			return true;
		}
		return false;
	}

	// initialisation du circuit
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
			vent vent_rand; // initialisation des aléas climatique tous les 4 km
			denivele denivele_rand; // initialisation des denivele tous les 4 km
			for (int y = i; y <= vent_rand.get_distance(); y++)
			{
				vent_map[y] = vent_rand.get_vitesse();
			}
			for (int y = i; y <= denivele_rand.get_distance(); y++) {
				denivele_map[y] = denivele_rand.get_pente();
			}
		}
	}
	int get_vent(float distance) {
		int indice = trunc(distance);
		return vent_map[indice];
	}
	int get_denivele(float distance) {
		int indice = trunc(distance);
		return denivele_map[indice];
	}

private:
	double longueur;
	int ravitaillement;
	// vector <vent> vent_map;
	// vector <denivele> denivele_map;
	vector <int> vent_map;
	vector <int> denivele_map;

};


// fonction de calcul de la vitesse instantanée d'un coureur
double vitesse_actuelle(coureur coureur, circuit map) {
	double vitesse;
	double PTmax;
	double PR;
	// vitesse de course à l'aide de la puissance intrinsèque
	PTmax = coureur.vitesse()*coureur.get_masse()*coureur.get_taille() + 0.5 * 1.225 * 0.137 * coureur.get_taille()*coureur.vitesse();
	PR = PTmax - 0.5 * 1.225 * 0.137 * coureur.get_taille() * (coureur.vitesse() + pow(map.get_vent(coureur.get_distance()), 2)* coureur.vitesse());
	vitesse = PR / (coureur.get_masse() * 0.98);
	// vitesse de course après prise en compte de la pente
	if (map.get_vent(coureur.get_distance())<0) {
		return vitesse*(100+(map.get_vent(coureur.get_distance())/1.5*0.0035));
	}
	return vitesse * (100 - (map.get_vent(coureur.get_distance()) / 1.5 * 0.01));
}

int main() {
	srand(time(NULL));
	coureur a(0);
	circuit circuit_actuel;
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