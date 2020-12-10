#include "coureur.h"
// calcul de la vitesse du coureur en temps normal
	double coureur::vitesse() {
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
	int coureur::etat(){

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
	coureur::coureur(int a) {
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

	int coureur::get_taille() {
		return taille;
	}
	int coureur::get_masse() {
		return masse;
	}
	double coureur::get_distance() {
		return distance_parcouru;
	}
	int coureur::get_id() {
		return dossard;
	}
	double coureur::get_temps() {
		return temps_course;
	}
	void coureur::boire() {
		hydratation+= (rand() % 50)/100 + 0.1;
	}
	int coureur::get_checkpoint_status() {
		return checkpoint_pris;
	}
	void coureur::change_checkpoint_status(int status) {
		checkpoint_pris = status;
	}
	void coureur::courir(double distance) {
		distance_parcouru += ((distance*3.6)/60);
	}
	void coureur::time_passe() {
		if (distance_parcouru < 42.125) { // si le coureur a fini la course son temps ne passe plus
			temps_course += 0.016666;
		}
	}

