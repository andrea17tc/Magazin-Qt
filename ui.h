#pragma once

#include "Produs.h"
#include "Service.h"

class UI{
private:
	ServiceProdus& srv;
	ServiceProdus& cos;
	void adauga();
	void adauga_cos();
	void afisare(const vector<Produs>& magazin);
	void afisare_cos();
	void sterge();
	void modifica();
	void cauta();
	void filtrare();
	void sortare();
	void golire();
	void populeaza();
	void salveaza_fisier();
public:
	UI(ServiceProdus& srv, ServiceProdus& srv_cos) noexcept :srv{ srv }, cos{ srv_cos } {};
	UI(const UI& ot) = delete;
	void run();
};	