#include <iostream>
#include <string>
#include "Calculator.h"
#include "Expresie.h"
#include "Stiva.h"
using namespace std;

/* Aici se realizeaza a doua partea din algoritm: evaluarea expresiei postfix si afisarea rezultatului final.*/

Calculator::Calculator() {
	expresie = nullptr;
	lungimeExpresie = 0;
	rezultat = nullptr;
	lungimeRezultat = 0;
}

Calculator::Calculator(const char* expresie, int lungimeExpresie, double* rezultat, int lungimeRezultat) {
	if (expresie != nullptr && lungimeExpresie > 0) {
		this->lungimeExpresie = lungimeExpresie;
		this->expresie = new char[lungimeExpresie + 1];
		strcpy_s(this->expresie, lungimeExpresie + 1, expresie);
	}
	else {
		this->expresie = nullptr;
		this->lungimeExpresie = 0;
	}

	if (rezultat != nullptr && lungimeRezultat > 0) {
		this->lungimeRezultat = lungimeRezultat;
		this->rezultat = new double[lungimeRezultat];
		for (int i = 0; i < lungimeRezultat; i++) {
			this->rezultat[i] = rezultat[i];
		}
	}
	else {
		this->rezultat = nullptr;
		this->lungimeRezultat = 0;
	}
}

Calculator::Calculator(const Calculator& c) {
	if (c.expresie != nullptr && c.lungimeExpresie > 0) {
		this->lungimeExpresie = c.lungimeExpresie;
		this->expresie = new char[c.lungimeExpresie + 1];
		strcpy_s(this->expresie, c.lungimeExpresie + 1, c.expresie);
	}
	else {
		this->expresie = nullptr;
		this->lungimeExpresie = 0;
	}

	if (c.rezultat != nullptr && c.lungimeRezultat > 0) {
		this->lungimeRezultat = c.lungimeRezultat;
		this->rezultat = new double[c.lungimeRezultat];
		for (int i = 0; i < c.lungimeRezultat; i++) {
			this->rezultat[i] = c.rezultat[i];
		}
	}
	else {
		this->rezultat = nullptr;
		this->lungimeRezultat = 0;
	}
}

Calculator::~Calculator() {
	if (expresie != nullptr) {
		delete[] expresie;
		expresie = nullptr;
	}
	if (rezultat != nullptr) {
		delete[] rezultat;
		rezultat = nullptr;
	}
}

int Calculator::getLungimeExpresie() {
	return lungimeExpresie;
}

char* Calculator::getExpresie() {
	if (expresie != nullptr && lungimeExpresie > 0) {
		return expresie;
	}
	return nullptr;
}

void Calculator::setExpresie(const char* expresie, int lungimeExpresie) {
	if (expresie != nullptr && lungimeExpresie > 0) {
		this->lungimeExpresie = lungimeExpresie;
		if (this->expresie != nullptr) {
			delete[] this->expresie;
		}
		this->expresie = new char[lungimeExpresie + 1];
		strcpy_s(this->expresie, lungimeExpresie + 1, expresie);
	}
}

double* Calculator::getRezultat() {
	if (rezultat != nullptr && lungimeRezultat > 0) {
		return rezultat;
	}
	return nullptr;
}

int Calculator::getLungimeRezultat() {
	return lungimeRezultat;
}

void Calculator::setRezultat(double* rezultat, int lungimeRezultat) {
	if (rezultat != nullptr && lungimeRezultat > 0) {
		this->lungimeRezultat = lungimeRezultat;
		if (this->rezultat != nullptr) {
			delete[] this->rezultat;
		}
		this->rezultat = new double[lungimeRezultat];
		for (int i = 0; i < lungimeRezultat; i++) {
			this->rezultat[i] = rezultat[i];
		}
	}
}

void Calculator::push(double element) {
	double* nouRezultat = new double[lungimeRezultat + 1];

	for (int i = 0; i < lungimeRezultat; i++) {
		nouRezultat[i] = rezultat[i];
	}

	nouRezultat[lungimeRezultat] = element;
	lungimeRezultat++;

	delete[] rezultat;
	rezultat = nouRezultat;
}

void Calculator::pop() {
	if (rezultat != nullptr && lungimeRezultat > 0) {
		lungimeRezultat--;

		if (lungimeRezultat > 0) {
			double* nouRezultat = new double[lungimeRezultat];

			for (int i = 0; i < lungimeRezultat; i++) {
				nouRezultat[i] = rezultat[i];
			}

			delete[] rezultat;

			rezultat = nouRezultat;
		}
		else {
			delete[] rezultat;
			rezultat = nullptr;
		}
	}
	else {
		delete[] rezultat;
		rezultat = nullptr;
	}
}

int Calculator::operator!() {
	for (int i = 0; i < lungimeExpresie; i++) {
		if (!strchr(" .+-*/^#()[]0123456789", expresie[i])) {
			return 0;
		}

		if (expresie[i] == '/') {
			for (int j = i + 1; j < lungimeExpresie; j++) {
				if (expresie[j] == ' ') {
					continue;
				}
				else if (expresie[j] == '0') {
					return 0;
				}
				else break;
			}
		}

		if (i < lungimeExpresie - 1 && strchr("+-*/^#", expresie[i]) && strchr("+-*/^#", expresie[i + 1])) {
			return 0;
		}
	}
	return 1;
}

void Calculator::eliminareSpatii() {
	for (int i = 0; i < lungimeExpresie; i++) {
		if (expresie[i] == ' ') {
			for (int j = i; j < lungimeExpresie; j++) {
				expresie[j] = expresie[j + 1];
			}
			expresie[lungimeExpresie - 1] = '\0';
			lungimeExpresie--;
			i--;
		}
	}
}

void Calculator::rezultatFinal() {
	Expresie e;
	e.algoritm(expresie);
	cout << e.getCoada() << endl;
	for (int i = 0; i < e.getLungimeCoada(); i++) {
		if (isdigit(e[i])) {
			string sir = "";
			while (e[i] != '|') {
				sir = sir + e[i];
				i++;
			}
			double x = atof(sir.c_str());
			push(x);
		}
		else if (strchr("+/-*^#", e[i])) {
			double a, b, c, d, x, f;
			switch (e[i]) {
			case '+':
				a = rezultat[lungimeRezultat - 2] + rezultat[lungimeRezultat - 1];
				pop();
				pop();
				push(a);
				break;
			case '-':
				b = rezultat[lungimeRezultat - 2] - rezultat[lungimeRezultat - 1];
				pop();
				pop();
				push(b);
				break;
			case '*':
				c = rezultat[lungimeRezultat - 2] * rezultat[lungimeRezultat - 1];
				pop();
				pop();
				push(c);
				break;
			case '/':
				d = rezultat[lungimeRezultat - 2] / rezultat[lungimeRezultat - 1];
				pop();
				pop();
				push(d);
				break;
			case '^':
				x = pow(rezultat[lungimeRezultat - 2], rezultat[lungimeRezultat - 1]);
				pop();
				pop();
				push(x);
				break;
			case '#':
				f = pow(rezultat[lungimeRezultat - 2], 1.0 / rezultat[lungimeRezultat - 1]);
				pop();
				pop();
				push(f);
				break;
			}
		}
	}
}

double Calculator::operator[](int index) {
	if (index >= 0 && index < getLungimeRezultat()) {
		return rezultat[index];
	}
	return -1;
}

Calculator& Calculator::operator=(const Calculator& c) {
	if (this != &c) {
		if (expresie != nullptr) {
			delete[] expresie;
			expresie = nullptr;
		}
		if (rezultat != nullptr) {
			delete[] rezultat;
			rezultat = nullptr;
		}

		if (c.expresie != nullptr && c.lungimeExpresie > 0) {
			this->lungimeExpresie = c.lungimeExpresie;
			this->expresie = new char[c.lungimeExpresie + 1];
			strcpy_s(this->expresie, c.lungimeExpresie + 1, c.expresie);
		}
		else {
			this->expresie = nullptr;
			this->lungimeExpresie = 0;
		}

		if (c.rezultat != nullptr && c.lungimeRezultat > 0) {
			this->lungimeRezultat = c.lungimeRezultat;
			this->rezultat = new double[c.lungimeRezultat];
			for (int i = 0; i < c.lungimeRezultat; i++) {
				this->rezultat[i] = c.rezultat[i];
			}
		}
		else {
			this->rezultat = nullptr;
			this->lungimeRezultat = 0;
		}
	}
	return *this;
}

istream& operator>>(istream& in, Calculator& c) {
	cout << "Introduceti expresia matematica:" << endl;
	cout << "Operatiile si parantezele folosite sunt: " << c.operatii << endl;
	string sir;
	getline(in, sir);
	delete[] c.expresie;
	if (c.rezultat != nullptr) {
		delete[] c.rezultat;
	}
	c.lungimeRezultat = 0;
	c.expresie = new char[sir.length() + 1];
	strcpy_s(c.expresie, sir.length() + 1, sir.c_str());
	c.lungimeExpresie = sir.length();
	return in;
}

ostream& operator<<(ostream& out, Calculator c) {
	out << "Rezultatul expresiei este:" << endl;
	out << c.rezultat[0] << endl;
	return out;
}

string Calculator::tipExpresie = "infix";

string Calculator::getTipExpresie() {
	return Calculator::tipExpresie;
}