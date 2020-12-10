#include "circuit.h"
#include "vent.h"
#include "denivele.h"
// définition du circuit grace à une classe

// initialisation du circuit
circuit::circuit() {
	longueur = 42.195;
	ravitaillement = 5;
	for (int i = 0; i <= 42; i++)
	{
		denivele_map.push_back(0);
		vent_map.push_back(0);
	}
	for (int i = 0; i <= 40; i += 4)
	{
		vent vent_rand; // initialisation des aléas climatique tous les 4 km
		denivele denivele_rand; // initialisation des denivele tous les 4 km
		for (int y = i; y - i <= vent_rand.get_distance() - 1; y++)
		{
			vent_map[y] = vent_rand.get_vitesse();
		}
		for (int y = i; y - i <= denivele_rand.get_distance() - 1; y++) {
			denivele_map[y] = denivele_rand.get_pente();
		}
	}
}

// fonction renvoyant si l'on est à un chekcpoint
bool circuit::checkpoint(int position_actu) {
	if (position_actu % 5 == 1) {
		return true;
	}
	return false;
}


int circuit::get_vent(double distance) {
	unsigned int indice = (int)trunc(distance);  // on ne garde que la borne kilometrique
	return vent_map[indice];
}
int circuit::get_denivele(double distance) {
	int indice = (int)trunc(distance); // on ne garde que la borne kilometrique
	return denivele_map[indice];
}