#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cmath>
#include<windows.h>
#include "simu.h"

using namespace std;
using namespace sf;

// class initialisant les denivele de façon aléatoire en % et en longueur 
class denivele {
public:
	denivele() {
		pente = (rand() % 40) -20;
		distance = (rand() % 2) + 1;
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
		vitesse = rand() % 40;
		distance = (rand() % 2) + 1;
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
		double vitesse = vitesse_moyenne;
		vitesse-= ( vitesse*(poids_chaussure / 100 * 0.011)); // on initialise la vitesse du coureur en fonction du poids de ses chaussures
		if (distance_parcouru < (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8))) {
			if (((hydratation / (0.5 * temps_course)) < 0.9)) {
				
				return  (vitesse * (1 - ((2 * (1 / (hydratation / (0.5 * temps_course)))) * 0.01))); // on applique un problème d'hydratation au coureurs
			}
			return vitesse;
		}
		
		if ((hydratation / (0.5 * temps_course)) < 0.9) {
			
			vitesse = vitesse * (1 - ((2 * (1 / (hydratation / (0.5 * temps_course)))) * 0.01)); // on applique un problème d'hydratation au coureurs
			vitesse -= (((0.2 * (distance_parcouru - (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) / (42.195 - (42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) * vitesse); // on applique la fatigue 
			return vitesse;
		}
		vitesse -= (((02 * (distance_parcouru -(42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) / (42.195-(42.195 / 2 * (1 + ((double)semaine_prep - 8) / 8)))) * vitesse); // on applique la fatigue 
		return vitesse;
	}

	// fonction qui vérifie l'etat du coureurs : renvoie 1 si il court, 0 si il a abandonné
	int etat(){

		// défini à quelle moment le coureur commence a etre dehydrate
		if ((hydratation / (0.5 * temps_course)) < 0.4 && abandon==-3) {
			abandon = distance_parcouru;
		}

		// le coureur a bus suffisament
		if((hydratation / (0.5 * temps_course)) > 0.4){
			abandon = -3;
		}

		// si la distance d'abandon est atteinte
		if (abandon +2 > distance_parcouru) {
			return 0;
		}

		return 1;
	}

	//initialisation aléatoire des caraéctéristiques du coureur
	coureur(int a) {
		dossard = a;
		nom = "Jack";
		masse = (rand() % 75) + 45;
		taille = (rand() % 70) + 130;
		poids_chaussure = (rand() % 200) + 100;
		vitesse_moyenne = (rand() % 13) + 7.;
		semaine_prep = (rand() % 8) + 8;
		hydratation = 0.5* vitesse_moyenne/5;
		distance_parcouru = 0.1;
		temps_course = 0.01;
		abandon = -3;
	};

	int get_taille() {
		return taille;
	}
	int get_masse() {
		return masse;
	}
	double get_distance() {
		return distance_parcouru;
	}
	int get_id() {
		return dossard;
	}
	double get_temps() {
		return temps_course;
	}
	void boire() {
		hydratation+= (rand() % 50)/100;
	}
	int get_checkpoint_status() {
		return checkpoint_pris;
	}
	void change_checkpoint_status(int status) {
		checkpoint_pris = status;
	}
	void courir(double distance) {
		distance_parcouru += (distance*3.6)/60;
	}
	void time_passe() {
		if (distance_parcouru < 42.125) { // si le coureur a fini la course son temps ne passe plus
			temps_course += (1 / 60);
		}
	}

private:
	int dossard;
	string nom;
	int masse;
	int taille;
	int poids_chaussure;
	double vitesse_moyenne;
	int semaine_prep;
	double hydratation;
	double distance_parcouru;
	double temps_course;
	double abandon; // variable pour dire quand le coureurs va abandonner en cas de non hydratation
	int checkpoint_pris = 1; // sert à ne pas prendre plusieurs fois le même checkpoint

};

// définition du circuit grace à une classe
class circuit {
public:
	// fonction renvoyant si l'on est à un chekcpoint
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
		for (int i = 0; i <= 42; i++)
		{
			denivele_map.push_back(0);
			vent_map.push_back(0);
		}
		for (int i = 0; i <= 40; i+=4)
		{
			vent vent_rand; // initialisation des aléas climatique tous les 4 km
			denivele denivele_rand; // initialisation des denivele tous les 4 km
			for (int y = i; y-i <= vent_rand.get_distance()-1; y++)
			{
				vent_map[y] = vent_rand.get_vitesse();
			}
			for (int y = i; y - i <= denivele_rand.get_distance()-1; y++) {
				denivele_map[y] = denivele_rand.get_pente();
			}
		}
	}
	int get_vent(double distance) {
		unsigned int indice = (int)trunc(distance);  // on ne garde que la borne kilometrique
		return vent_map[indice];
	}
	int get_denivele(double distance) {
		int indice = (int)trunc(distance); // on ne garde que la borne kilometrique
		return denivele_map[indice];
	}

private:
	double longueur;
	int ravitaillement;
	vector <int> vent_map;
	vector <int> denivele_map;

};


// fonction de calcul de la vitesse instantanée d'un coureur
double vitesse_actuelle(coureur coureur, circuit map) {
	double vitesse;
	double PTmax;
	double PR;
	double Pa;
	// vitesse de course à l'aide de la puissance intrinsèque
	Pa = 0.5 * 1.205 * 0.137 * (coureur.get_taille()/100) * (coureur.vitesse() + pow(map.get_vent(coureur.get_distance()), 2)* coureur.vitesse());
	PTmax = coureur.vitesse()*coureur.get_masse()*(coureur.get_taille()/100) + 0.5 * 1.225 * 0.137 * (coureur.get_taille()/100)*coureur.vitesse();
	PR = PTmax - Pa;
	vitesse = PR / (coureur.get_masse() * 0.98);
	// vitesse de course après prise en compte de la pente
	if (map.get_denivele(coureur.get_distance())<0) {
		return (vitesse*(1+(map.get_denivele(coureur.get_distance())/1.5*0.0035)));
	}
	return (vitesse * (1 - ((-map.get_denivele(coureur.get_distance())) / 1.5 * 0.01)));
}

int main() {
	srand(time(NULL));
	// création des coureurs
	vector <coureur> peloton;
	coureur a(0);
	peloton.push_back(a);
	coureur b(1);
	peloton.push_back(b);
	coureur c(2);
	peloton.push_back(c);
	coureur d(3);
	peloton.push_back(d);
	coureur e(4);
	peloton.push_back(e);
	coureur g(5);
	peloton.push_back(g);
	coureur h(6);
	peloton.push_back(h);
	coureur j(7);
	peloton.push_back(j);
	coureur k(8);
	peloton.push_back(k);
	circuit circuit_actuel;

	RenderWindow window(VideoMode(1300, 700), "Simulation");
	Event f;
	Text text;
	Font font;
	// création et chargement des textures
	Texture t0, t1, t2, t3;
	t0.loadFromFile("images/depart.png");
	t1.loadFromFile("images/road.png");
	t2.loadFromFile("images/vent.png");
	t3.loadFromFile("images/coureur.png");
	Sprite sprite0(t0);
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "impossible de charger la police d'ecriture" << endl;
	}
	text.setFont(font);
	RectangleShape depart(sf::Vector2f(20, 20));

	// génération et affichage de la carte

	

	// initialisation des conditions de fin
	int course_fini = 0;
	int duree = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(f))
		{
			
			while (!course_fini || duree > 420) // répétion jusqu'a la fin de la course / jusqu'a time out (7 heures)
			{
				window.clear(Color(220, 220, 220));
				duree++;
				int coureur_fini = 0;
				for (int i = 0; i < 9; i++)// on le fait joueur par joueur
				{
					if (i == 3) {
						sprite3.setPosition((float)trunc(peloton[i].get_distance()*23+22), 40);
					}
					peloton[i].time_passe();
					if (peloton[i].get_distance() > 0) {
						if (peloton[i].etat() || peloton[i].get_distance() < 42.125) {
							peloton[i].courir((double)vitesse_actuelle(peloton[i], circuit_actuel));
							if (circuit_actuel.checkpoint((int)trunc(peloton[i].get_distance())) && !peloton[i].get_checkpoint_status()) { // si il est sur un kilometrage check point et qu'il ne l'a pas encore pris, il le prend
								peloton[i].change_checkpoint_status(1);
								peloton[i].boire();
							}
							if (!circuit_actuel.checkpoint((int)trunc(peloton[i].get_distance())) && peloton[i].get_checkpoint_status() == 0) { // si il a pris le checkpint mais qu'il n'est pas sur un kilometrage à checkpoint, il peut reprendre le prochain
								peloton[i].change_checkpoint_status(0);
							}
						}
						else {
							coureur_fini++;
						}
					}
					/*
						cout << "Vitesse :" << vitesse_actuelle(peloton[i], circuit_actuel) * 3.6 << endl;
						cout << "Distance :" << peloton[i].get_distance() << endl;
						peloton[i].courir(vitesse_actuelle(peloton[i], circuit_actuel));*/
				}
				
				text.setCharacterSize(30);
				text.setPosition(0, 0);
				text.setFillColor(Color::Black);
				text.setString("Simulation en cours");
				sprite0.setPosition(2 * 22, 50);
				window.draw(sprite0);
				for (double i = 3; i < 43; i++) {
					if (circuit_actuel.get_vent(i - 2) != 0) {
						sprite2.setPosition((float)(i * 22), 50);
						window.draw(sprite2);
					}
					else
					{
						sprite1.setPosition((float)(i * 22), 50);
						window.draw(sprite1);
					}

				}
				sprite0.setPosition(43 * 22, 50);
				window.draw(sprite0);
				window.draw(text);
				window.draw(depart);
				window.draw(sprite3);
				window.display();

				if (coureur_fini == 8) {
					course_fini = 1;
				}
				Sleep(250);
				
			}
			if (f.type == Event::Closed) {
				window.close();
			}
			for (int i = 0; i < 10; i++)
			{
				cout << "Le coureur " << peloton[i].get_id() << " a parcouru " << peloton[i].get_distance() << " en " << peloton[i].get_temps() << endl;
			}
			cout << a.vitesse() << endl;
		}
	}
	
}