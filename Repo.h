#pragma once
#include "Produs.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class RepoProdus {
	private:
		vector <Produs> all;
		bool exist(const Produs& p) const;
	public:
		RepoProdus() = default;
		RepoProdus(const RepoProdus& ot) = delete;
		void adauga(const Produs& p);
		void adauga_cos(const Produs& p);
		int cauta_poz(string nume, int pret) const;
		void sterge(Produs& p);
		void modificare(Produs& p, int pret);
		vector<Produs>& get_all() noexcept;
		const Produs& cauta_el(string nume, int pret)const ;
		int cauta(string nume) const;
		void golire();
};

class RepoProdusExceptie {
private: 
	string msg;
public:
	RepoProdusExceptie(string m) :msg{ m } {};
	friend ostream& operator<<(ostream& out, const RepoProdusExceptie& ex);
};
ostream& operator<<(ostream& out, const RepoProdusExceptie& ex);

class RepoCos:public RepoProdus {
private :
	vector<Produs> cos;
public :
	RepoCos() = default;
	RepoCos(const RepoCos& ot) = delete;
};