#include "denivele.h"

// class initialisant les denivele de façon aléatoire en % et en longueur 



denivele::denivele() {
	pente = (rand() % 30) - 15;
	distance = (rand() % 2) + 1;
};

int denivele::get_distance() {
	return distance;
}
int denivele :: get_pente() {
	return pente;
}