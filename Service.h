#pragma once

#include "Produs.h"
#include "Repo.h"
#include "validator.h"
#include "Observer.h"

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using std::vector;
using std::function;

class ServiceProdus : public Observable {
private:
	RepoProdus& repo;
	ValidatorProdus& val;

	vector<Produs> sort_gen(bool(*mic)(const Produs&, const Produs&));

	
	vector<Produs> filtrare(function<bool(const Produs&)> fct);

public:
	ServiceProdus(RepoProdus& repo, ValidatorProdus& val) noexcept :repo{ repo }, val{ val } {};

	ServiceProdus(const RepoProdus& ot) = delete;

	vector<Produs>& get_all() noexcept {
		return repo.get_all();
	}
	
	void adauga(string nume, string tip, int pret, string producator);

	void adauga_cos(string nume, string tip, int pret, string producator);

	void generare(int nr, ServiceProdus& srv);

	void sterge(Produs& p);

	void modificare(Produs& p, int pret);

	const Produs cauta_el(string nume, int pret);

	const Produs cauta(string nume);

	vector<Produs> sort_nume();

	vector<Produs> sort_pret();

	vector<Produs> sort_nume_tip();
	
	vector<Produs> filtrare_pret_mai_mic(int pret);

	vector<Produs> filtrare_nume(string nume);

	vector<Produs> filtrare_producator(string producator);

	void golire();

	void salveaza_fisier(string fname);

};