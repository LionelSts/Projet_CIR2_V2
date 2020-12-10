#pragma once
#include <iostream>
#include <fstream>
// d�finition de la classe coureur
class coureur {
public:
	// calcul de la vitesse du coureur en temps normal
	double vitesse();

	// fonction qui v�rifie l'etat du coureurs : renvoie 1 si il court, 0 si il a abandonn�
	int etat();

	//initialisation al�atoire des cara�ct�ristiques du coureur
	coureur(int a);

	int get_taille();
	int get_masse();
	double get_distance();
	int get_id();
	double get_temps();
	void boire();
	int get_checkpoint_status();
	void change_checkpoint_status(int status);
	void courir(double distance);
	void time_passe();

private:
	int dossard, masse, taille, poids_chaussure, semaine_prep;
	std::string nom;
	double vitesse_moyenne, hydratation, distance_parcouru, temps_course;
	double abandon; // variable pour dire quand le coureurs va abandonner en cas de non hydratation
	int checkpoint_pris = 1; // sert � ne pas prendre plusieurs fois le m�me checkpoint

};
