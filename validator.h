#pragma once
#include "Produs.h"
#include "Repo.h"

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

class ValidatorProdus {
public:

	void validator(const Produs& p);
};

class ValidatorExceptie {
private:
	vector <string> msgs;
public:
	ValidatorExceptie(const vector<string>& errors) :msgs{ errors } {};
	friend ostream& operator<<(ostream& out, const ValidatorExceptie& ex);
};

ostream& operator<<(ostream& out, const ValidatorExceptie& ex);