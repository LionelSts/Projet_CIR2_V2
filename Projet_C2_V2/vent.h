#pragma once
#include<iostream>

// class initialisant le vent de fa�on al�atoire en km/h et en longueur 
class vent {
public:
	vent();
	int get_distance();
	int get_vitesse();
private:
	int vitesse, distance;
};
