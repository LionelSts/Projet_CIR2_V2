#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cmath>
#include <windows.h>
#include "denivele.h"
#include "vent.h"
#include "coureur.h"
#include "circuit.h"

using namespace std;
using namespace sf;

// fonction de calcul de la vitesse instantanée d'un coureur
double vitesse_actuelle(coureur coureur, circuit map) {
	double vitesse;
	double PTmax;
	double PR;
	double Pa;
	double vitesse_coureur = (coureur.vitesse() / 3.6);
	// vitesse de course à l'aide de la puissance intrinsèque
	Pa = 0.5 * 1.205 * 0.137 * (coureur.get_taille()/100) * (vitesse_coureur + pow(map.get_vent(coureur.get_distance()), 2)* vitesse_coureur);
	PTmax = vitesse_coureur *coureur.get_masse()*(coureur.get_taille()/100) + 0.5 * 1.225 * 0.137 * (coureur.get_taille()/100)* vitesse_coureur;
	PR = PTmax - Pa;
	vitesse = PR / (coureur.get_masse() * 0.98);
	// vitesse de course après prise en compte de la pente
	if (map.get_denivele(coureur.get_distance())<0) {
		return (vitesse*(1+(map.get_denivele(coureur.get_distance())/1.5*0.0035)));
	}
	return (vitesse * (1 - ((-map.get_denivele(coureur.get_distance())) / 1.5 * 0.01)));
}

int main() {
	// ouvertur du fichier pour l'output
	ofstream myfile;
	myfile.open("result.txt", ios::out | ios::app);
	if (myfile.fail())

	{
		exit(1);
	}

	// initalisation pour les rand()
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

	// création de la carte
	circuit circuit_actuel;

	// ouverture de la fenêtre
	RenderWindow window(VideoMode(1300, 700), "Simulation");

	// création et chargement des textures
	Texture t0, t1, t2, t3, t4, t5, t6, t7;
	t0.loadFromFile("images/depart.png");
	t1.loadFromFile("images/road.png");
	t2.loadFromFile("images/vent.png");
	t3.loadFromFile("images/coureur.png");
	t4.loadFromFile("images/vent_descente.png");
	t5.loadFromFile("images/vent_monte.png");
	t6.loadFromFile("images/descente.png");
	t7.loadFromFile("images/monte.png");
	Sprite sprite0(t0);
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);
	Sprite sprite5(t5);
	Sprite sprite6(t6);
	Sprite sprite7(t7);

	

	// initialisation des conditions de fin
	int course_fini = 0;
	int duree = 0;
			while (!course_fini && duree < 600) // répétion jusqu'a la fin de la course / jusqu'a time out (10 heures)
			{
				// affichage de la carte
				window.clear(Color(220, 220, 220));

				// affichage du départ
				sprite0.setPosition(0, 0);
				window.draw(sprite0);
				for (double i = 1; i < 42; i++) {

					if (circuit_actuel.get_vent(i) != 0 && circuit_actuel.get_denivele(i) ==0) { // si il y a du vent et pas de denivele on affiche la texture avec le vents
						sprite2.setPosition((float)(i * 30), 0);
						window.draw(sprite2);
					}
					if (circuit_actuel.get_vent(i) != 0 && circuit_actuel.get_denivele(i) < 0) { // si il y a du vent et et une descente on affiche la descente vent
						sprite4.setPosition((float)(i * 30), 0);
						window.draw(sprite4);
					}
					if (circuit_actuel.get_vent(i) != 0 && circuit_actuel.get_denivele(i) > 0) { // si il y a du vent et une monté on affiche la monté vent
						sprite5.setPosition((float)(i * 30), 0);
						window.draw(sprite5);
					}
					if (circuit_actuel.get_vent(i) == 0 && circuit_actuel.get_denivele(i) < 0) { // si il n'y a pas de vent et une descente on affiche la descente
						sprite6.setPosition((float)(i * 30), 0);
						window.draw(sprite6);
					}
					if (circuit_actuel.get_vent(i) == 0 && circuit_actuel.get_denivele(i) > 0) { // si il n'y a pas de vent et une monté on affiche la monté
						sprite7.setPosition((float)(i * 30), 0);
						window.draw(sprite7);
					}
					if(circuit_actuel.get_vent(i) == 0 && circuit_actuel.get_denivele(i) == 0)
					{	 // sinon juste la texture
						sprite1.setPosition((float)(i * 30), 0);
						window.draw(sprite1);
					}
				}

				// affichage de l'arrivée
				sprite0.setPosition(1260, 0);
				window.draw(sprite0);

				// avancement de duree pour éviter une génératino infinie
				duree++;
				int coureur_fini = 0;
				
				for (int i = 0; i < 9; i++)// on le fait joueur par joueur
				{
					// affichage du joueur
					sprite3.setPosition((float)trunc(peloton[i].get_distance()*30), (float)(i*68 + 30));
					window.draw(sprite3);

					// on fait écouler le temps de son chrono
					peloton[i].time_passe();
					if (peloton[i].etat() && peloton[i].get_distance() < 42.125) {
						if (vitesse_actuelle(peloton[i], circuit_actuel) > 0) {
							peloton[i].courir((double)vitesse_actuelle(peloton[i], circuit_actuel));
							if (circuit_actuel.checkpoint((int)trunc(peloton[i].get_distance())) && !peloton[i].get_checkpoint_status()) { // si il est sur un kilometrage check point et qu'il ne l'a pas encore pris, il le prend
								peloton[i].change_checkpoint_status(1);
								peloton[i].boire();
							}
							if (!circuit_actuel.checkpoint((int)trunc(peloton[i].get_distance())) && peloton[i].get_checkpoint_status() == 0) { // si il a pris le checkpint mais qu'il n'est pas sur un kilometrage à checkpoint, il peut reprendre le prochain
								peloton[i].change_checkpoint_status(0);
							}
						}
					}
					else {
						coureur_fini++;
					}
				}
				// on affiche toutes les entitées créées 
				window.display();

				// si tout les coureurs ont fini, on fini la course
				if (coureur_fini == 8) {
					course_fini = 1;
				}
				// on attendre 250 ms afin que la génération ne se passe pas trop vite 
				Sleep(250);
				
			}
			window.close();// la fenettre se ferme

			// on stock tous dans le document txt
			for (int i = 0; i < 9; i++)
			{
				myfile << "Le coureur " << to_string(peloton[i].get_id()) << " a parcouru " << to_string(peloton[i].get_distance()) << " en " << to_string(peloton[i].get_temps()) << endl;
			}
			myfile.close();
	
}