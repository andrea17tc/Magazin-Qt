#include "Produs.h"
#include "Repo.h"
#include "validator.h"

#include <vector>
#include <string>

void ValidatorProdus::validator(const Produs& p) {
	/*Valideaza un produs dat
	param: p- produsul de validat
	type: Produs&
	return: - 
	raises: - daca produsul este valid
			mesaj daca produsul nu e valid
	*/
	vector <string> msgs;
	if (p.get_nume().size() == 0) msgs.push_back("Nume invalid!");
	if (p.get_tip().size() == 0) msgs.push_back("Tip invalid!");
	if (p.get_pret() < 0) msgs.push_back("Pret invalid!");
	if (p.get_producator().size() == 0) msgs.push_back("Producator invalid!");
	if (msgs.size() > 0) {
		throw ValidatorExceptie(msgs);
	}

}

ostream& operator<<(ostream& out, const ValidatorExceptie& ex) {
	/*Suprascrie operatorul << pentru a afisa mesajul in caz de exceptie*/
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}