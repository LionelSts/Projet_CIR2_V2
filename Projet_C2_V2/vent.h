#pragma once
#include<iostream>

// class initialisant le vent de façon aléatoire en km/h et en longueur 
class vent {
public:
	vent();
	int get_distance();
	int get_vitesse();
private:
	int vitesse, distance;
};
