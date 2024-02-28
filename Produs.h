#pragma once
#include <string>

using std::string;

class Produs {
	private:
		string nume;
		string tip;
		int pret;
		string producator;

	public:
		/*Construieste obiectul produs cu atributele date*/
		Produs(string nume, string tip, int pret, string producator) :nume{ nume }, tip{ tip }, pret{ pret }, producator{ producator } {};
		/*Returneaza numele
		return nume
		rtype: string
		*/
		string get_nume() const {
			return nume;
		}
		/*Returneaza tipul
		return tip
		rtype: string
		*/
		string get_tip() const{
			return tip;
		}
		/*Returneaza pretul
		return pret
		rtype: int
		*/
		int get_pret() const noexcept{
			return pret;
		}
		/*Returneaza producatorul
		return producator
		rtype: string
		*/
		string get_producator() const noexcept {
			return producator;
		}
		/*Seteaza pretul cu valoarea data
		param: value - valoarea noua
		type:int
		return -
		*/
		void set_pret(int value) noexcept {
			pret = value;
		}
};

bool cmp_nume(const Produs& p1, string nume);
bool cmp_nume2(const Produs& p1, const Produs& p2);
bool cmp_pret(const Produs& p1, const Produs& p2);