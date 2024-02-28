#include "Produs.h"
#include "Service.h"
#include "Repo.h"
#include "validator.h"

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iomanip>
#include <random>


using std::vector;
using std::string;
using std::function;
using std::copy;

void ServiceProdus::adauga(string nume, string tip, int pret, string producator) {
	Produs p{ nume, tip, pret, producator };
	val.validator(p);
	repo.adauga(p);
	this->notify_all();
}

void ServiceProdus::adauga_cos(string nume, string tip, int pret, string producator) {
	Produs p{ nume, tip, pret, producator };
	val.validator(p);
	repo.adauga_cos(p);
	this->notify_all();
}

void ServiceProdus::sterge(Produs& p) {
	try {
		repo.sterge(p);
		this->notify_all();
	}
	catch(RepoProdusExceptie&){}
	
}

void ServiceProdus::modificare(Produs& p, int pret) {
	try {
		repo.modificare(p, pret);
	}
	catch (RepoProdusExceptie&) {};
}

const Produs ServiceProdus::cauta_el(string nume, int pret) {
	try {
		Produs p = repo.cauta_el(nume, pret);
		return p;
	}
	catch (RepoProdusExceptie&) { };
}

const Produs ServiceProdus::cauta(string nume) {
	try {
		int ind = repo.cauta(nume);
		vector <Produs> rez{ repo.get_all() };
		return rez[ind];
	}
	catch (RepoProdusExceptie&) {};
}

vector<Produs> ServiceProdus::sort_gen(bool(*mic)(const Produs&, const Produs&)) {
	vector<Produs> v{ repo.get_all() };
	for(int i=0;i<v.size()-1;i++)
		for(int j=i+1;j<v.size();j++)
			if (!mic(v[i], v[j])) {
				Produs aux = v[j];
				v[j] = v[i];
				v[i] = aux;
			}
	return v;
}

vector<Produs> ServiceProdus::sort_nume() {
	return sort_gen(cmp_nume2);
}

vector<Produs> ServiceProdus::sort_pret() {
	return sort_gen(cmp_pret);
}

vector<Produs> ServiceProdus::sort_nume_tip() {
	return sort_gen([](const Produs& p1, const Produs& p2) {
		if (p1.get_nume() == p2.get_nume()) {
			return p1.get_tip() <= p2.get_tip();
		}
		return cmp_nume2(p1, p2);
	});
}



vector<Produs> ServiceProdus::filtrare_nume(string nume) {
	return filtrare([nume](const Produs& p) {
		return p.get_nume() == nume;
		});
	/*vector<Produs> v{ repo.get_all() };
	vector<Produs> rez;
	copy_if(v.begin(), v.end(), rez.begin(), [nume](const Produs& p) {return p.get_nume() == nume; });
	return rez;*/
}

vector<Produs> ServiceProdus::filtrare_pret_mai_mic(int pret) {
	return filtrare([pret](const Produs& p) {
		return p.get_pret() < pret;
		});
}

vector<Produs> ServiceProdus::filtrare_producator(string producator) {
	return filtrare([producator](const Produs& p) {
		return p.get_nume() == producator;
		});
}

vector<Produs> ServiceProdus::filtrare(function<bool(const Produs&)> fct) {
	vector<Produs> rez;
	for (const auto& produs : repo.get_all()) {
		if (fct(produs)) {
			rez.push_back(produs);
		}
	}
	return rez;
}

void ServiceProdus::golire() {
	/*Goleste vectorul de produse.*/
	repo.golire();
	this->notify_all();
}

void ServiceProdus::salveaza_fisier(string fname){
	/*Salveaza produsele din cos in fisierul de nume dat.
	param: fname
	type: string
	return : -
	*/
	std::ofstream out(fname);
	for (auto& p : repo.get_all()) {
		out << p.get_nume() << ";" << p.get_tip() << ";" << p.get_pret() << ";" << p.get_producator() << "\n";
	}
	out.close();
}