#pragma once

#include<iostream>
#include <vector>
#include <cmath>


// d�finition du circuit grace � une classe
class circuit {
public:
	// fonction renvoyant si l'on est � un chekcpoint
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