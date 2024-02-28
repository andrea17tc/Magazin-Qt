#include "Produs.h"
#include <string>


bool cmp_nume(const Produs& p1, string nume) {
	/*Compara numele a doua produse
	return - true - daca cele doua produse au acelasi nume
			false - daca nu au acelasi nume
	*/
	if (p1.get_nume()==nume)
		return true;
	return false;
}
bool cmp_nume2(const Produs& p1, const Produs& p2) {
	/*Compara numele a doua produse
	return - true - daca cele doua produse au acelasi nume
			false - daca nu au acelasi nume
	*/
	if (p1.get_nume() < p2.get_nume())
		return true;
	return false;
}
bool cmp_pret(const Produs& p1, const Produs& p2) {
	/*Compara numele a doua produse
	return - true - daca cele doua produse au acelasi nume
			false - daca nu au acelasi nume
	*/
	if (p1.get_pret() < p2.get_pret())
		return true;
	return false;
}