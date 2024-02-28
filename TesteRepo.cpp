#include "Repo.h"
#include "Produs.h"

#include <assert.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using std::ostream;
using std::stringstream;
using std::vector;

void test_adauga() {
	RepoProdus repo;
	Produs p{ "sare", "aliment", 5, "ion" };
	try {
		repo.adauga(p);
		assert(true);
	}
	catch (RepoProdusExceptie&) {
		assert(false);
	}
	try {
		repo.adauga(p);
		assert(false);
	}
	catch (RepoProdusExceptie&) {
		assert(true);
	}
}

void test_cauta_el(){
	RepoProdus repo;
	Produs p{ "sare", "aliment", 5, "ion" };
	Produs p1{ "piper", "aliment", 8, "ana" };
	Produs p2{ "burete", "curat", 10, "ionel" };
	Produs p3{ "vanish", "solutii", 15, "ionel" };
	Produs p4{ "perwol", "solutii", 20, "ionela" };
	Produs p5{ "ariel", "solutii",20, "ionela" };
	Produs p6{ "mere", "fructe",4, "aurel" };
	repo.adauga(p);
	repo.adauga(p1);
	repo.adauga(p2);
	repo.adauga(p3);
	repo.adauga(p4);
	repo.adauga(p5);
	repo.adauga(p6);
	Produs el = repo.cauta_el("sare", 5);
	assert(el.get_nume()==p.get_nume());
	assert(el.get_tip()== p.get_tip());
	assert(el.get_pret()== p.get_pret());
	assert(el.get_producator()== p.get_producator());
	try {
		Produs elem = repo.cauta_el("usturoi", 9);
		assert(false);
	}
	catch (RepoProdusExceptie&) {
		assert(true);
	}
}

void test_cauta_poz() {
	RepoProdus repo;
	Produs p{ "sare", "aliment", 5, "ion" };
	Produs p1{ "piper", "aliment", 8, "ana" };
	Produs p2{ "burete", "curat", 10, "ionel" };
	Produs p3{ "vanish", "solutii", 15, "ionel" };
	Produs p4{ "perwol", "solutii", 20, "ionela" };
	Produs p5{ "ariel", "solutii",20, "ionela" };
	Produs p6{ "mere", "fructe",4, "aurel" };
	repo.adauga(p);
	repo.adauga(p1);
	repo.adauga(p2);
	repo.adauga(p3);
	repo.adauga(p4);
	repo.adauga(p5);
	repo.adauga(p6);
	int ind = repo.cauta_poz("burete", 10);
	assert(ind == 2);
}

void test_sterge() {
	RepoProdus repo;
	Produs p{ "sare", "aliment", 5, "ion" };
	Produs p1{ "piper", "aliment", 8, "ana" };
	Produs p2{ "burete", "curat", 10, "ionel" };
	Produs p3{ "vanish", "solutii", 15, "ionel" };
	Produs p4{ "perwol", "solutii", 20, "ionela" };
	Produs p5{ "ariel", "solutii",20, "ionela" };
	Produs p6{ "mere", "fructe",4, "aurel" };
	repo.adauga(p);
	repo.adauga(p1);
	repo.adauga(p2);
	repo.adauga(p3);
	repo.adauga(p4);
	repo.adauga(p5);
	repo.adauga(p6);
	try {
		repo.sterge(p1);
		vector <Produs> rez = repo.get_all();
		assert(rez.size() == 6);
		assert(true);
	}
	catch (RepoProdusExceptie&) {
		assert(false);
	}
	try {
		Produs p7{ "pere","fructe", 7, "iancu" };
		repo.sterge(p7);
		assert(false);
	}
	catch (RepoProdusExceptie&) {
		assert(true);
	}
}
void test_modificare() {
	RepoProdus repo;
	Produs p{ "sare", "aliment", 5, "ion" };
	Produs p1{ "piper", "aliment", 8, "ana" };
	Produs p2{ "burete", "curat", 10, "ionel" };
	Produs p3{ "vanish", "solutii", 15, "ionel" };
	Produs p4{ "perwol", "solutii", 20, "ionela" };
	Produs p5{ "ariel", "solutii",20, "ionela" };
	Produs p6{ "mere", "fructe",4, "aurel" };
	repo.adauga(p);
	repo.adauga(p1);
	repo.adauga(p2);
	repo.adauga(p3);
	repo.adauga(p4);
	repo.adauga(p5);
	repo.adauga(p6);
	try {
		repo.modificare(p1, 5);
		vector <Produs> rez = repo.get_all();
		assert(rez[1].get_pret() == 5);
		assert(true);
	}
	catch (RepoProdusExceptie&) {
		assert(false);
	}
	try {
		Produs p7{ "pere","fructe", 7, "iancu" };
		repo.modificare(p7, 5);
		assert(false);
	}
	catch (RepoProdusExceptie&) {
		assert(true);
	}
}

void test_get_all() {
	RepoProdus repo;
	vector<Produs> rez = repo.get_all();
	assert(rez.size() == 0);
	Produs p{ "sare", "aliment", 5, "ion" };
	Produs p1{ "piper", "aliment", 8, "ana" };
	Produs p2{ "burete", "curat", 10, "ionel" };
	repo.adauga(p);
	repo.adauga(p1);
	repo.adauga(p2);
	rez = repo.get_all();
	assert(rez.size() == 3);
}

void test_repo()
{
	test_adauga();
	test_cauta_el();
	test_cauta_poz();
	test_sterge();
	test_modificare();
	test_get_all();
}