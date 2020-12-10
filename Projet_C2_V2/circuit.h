#pragma once

#include<iostream>
#include <vector>
#include <cmath>


// définition du circuit grace à une classe
class circuit {
public:
	// fonction renvoyant si l'on est à un chekcpoint
	bool checkpoint(int position_actu);

	// initialisation du circuit
	circuit();
	int get_vent(double distance);
	int get_denivele(double distance);

private:
	double longueur;
	int ravitaillement;
	std::vector <int> vent_map;
	std::vector <int> denivele_map;

};