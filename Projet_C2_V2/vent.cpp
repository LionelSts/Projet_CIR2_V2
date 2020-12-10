#include "vent.h"

// class initialisant le vent de façon aléatoire en km/h et en longueur 
vent::vent() {
	vitesse = rand() % 20;
	distance = (rand() % 2) + 1;
}
int vent::get_distance() {
	return distance;
}
int vent::get_vitesse() {
	return vitesse;
}