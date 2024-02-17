#include <iostream>
#include "Expresie.h"
#include "Stiva.h"
using namespace std;

/* Aici se realizeaza prima parte din algoritm: convertirea expresiei matematici infix in postfix*/

Expresie::Expresie() {
	coada = nullptr;
	lungimeCoada = 0;
}

Expresie::Expresie(const char* coada, int lungimeCoada) {
	if (coada != nullptr && lungimeCoada > 0) {
		this->lungimeCoada = lungimeCoada;
		this->coada = new char[lungimeCoada + 1];
		strcpy_s(this->coada, lungimeCoada + 1, coada);
	}
	else {
		this->coada = nullptr;
		this->lungimeCoada = 0;
	}
}

Expresie::Expresie(const Expresie& e) {
	if (e.coada != nullptr && e.lungimeCoada > 0) {
		this->lungimeCoada = e.lungimeCoada;
		this->coada = new char[e.lungimeCoada + 1];
		strcpy_s(this->coada, e.lungimeCoada + 1, e.coada);
	}
	else {
		this->coada = nullptr;
		this->lungimeCoada = 0;
	}
}

Expresie::~Expresie() {
	if (coada != nullptr) {
		delete[] coada;
		coada = nullptr;
	}
}

int Expresie::getLungimeCoada() {
	return lungimeCoada;
}

char* Expresie::getCoada() {
	if (coada != nullptr && lungimeCoada > 0) {
		return coada;
	}
	return nullptr;
}

void Expresie::setCoada(const char* coada, int lungimeCoada) {
	if (coada != nullptr && lungimeCoada > 0) {
		this->lungimeCoada = lungimeCoada;
		if (this->coada != nullptr) {
			delete[] this->coada;
		}
		this->coada = new char[lungimeCoada + 1];
		strcpy_s(this->coada, lungimeCoada + 1, coada);
	}
}

int Expresie::ordine(const char simbol) {
	if (simbol == '+' || simbol == '-') {
		return 1;
	}

	if (simbol == '*' || simbol == '/') {
		return 2;
	}

	if (simbol == '#') {
		return 3;
	}

	if (simbol == '^') {
		return 4;
	}

	return -1;
}

void Expresie::adaugaElement(const char* element) {
	if (strlen(element) > 0) {
		if (coada != nullptr && lungimeCoada > 0) {
			char* copie = new char[lungimeCoada + 1];
			strcpy_s(copie, lungimeCoada + 1, coada);
			delete[] coada;
			lungimeCoada = lungimeCoada + strlen(element);
			coada = new char[lungimeCoada + 1];
			strcpy_s(coada, lungimeCoada + 1, copie);
			strcat_s(coada, lungimeCoada + 1, element);
		}
		else {
			lungimeCoada = strlen(element);
			coada = new char[lungimeCoada + 1];
			strcpy_s(coada, lungimeCoada + 1, element);
		}
	}
}

void Expresie::algoritm(const char* sir) {
	Stiva stiva;
	for (int i = 0; i < strlen(sir); i++) {
		if (sir[i] == '+' || sir[i] == '-' || sir[i] == '*' || sir[i] == '/' || sir[i] == '^' || sir[i] == '#') {
			if (stiva.getLungimeStiva() > 0 && ordine(sir[i]) < ordine(stiva[stiva.getLungimeStiva() - 1])) {
				const char ultimulCaracter[2] = { stiva.getStiva()[stiva.getLungimeStiva() - 1], '\0' };
				adaugaElement(ultimulCaracter);
				adaugaElement("|");
				stiva.pop();
				stiva.push(sir[i]);
			}
			else {
				stiva.push(sir[i]);
			}
		}
		else if (sir[i] == '(' || sir[i] == '[') {
			stiva.push(sir[i]);
		}
		else if (sir[i] == ')') {
			int j = stiva.getLungimeStiva() - 1;
			while (j >= 0 && stiva[j] != '(') {
				const char ultimulCaracter[2] = { stiva[j], '\0'};
				adaugaElement(ultimulCaracter);
				adaugaElement("|");
				stiva.pop();
				j--;
			}
			if (stiva[j] == '(') {
				stiva.pop();
			}
		}
		else if (sir[i] == ']') {
			int j = stiva.getLungimeStiva() - 1;
			while (j >= 0 && stiva[j] != '[') {
				const char ultimulCaracter[2] = { stiva[j], '\0'};
				adaugaElement(ultimulCaracter);
				adaugaElement("|");
				stiva.pop();
				j--;
			}
			if (stiva[j] == '[') {
				stiva.pop();
			}
		}
		else if (isdigit(sir[i])) {
			while (i < strlen(sir) && (isdigit(sir[i]) || sir[i] == '.')) {
				const char ultimulCaracter[2] = { sir[i], '\0' };
				adaugaElement(ultimulCaracter);
				i++;
			}
			i--;
			adaugaElement("|");
		}
	}

	int i = stiva.getLungimeStiva() - 1;
	while (i >= 0 && stiva.getLungimeStiva() > 0) {
		const char ultimulCaracter[2] = { stiva[i], '\0'};
		adaugaElement(ultimulCaracter);
		adaugaElement("|");
		stiva.pop();
		i--;
	}
}

Expresie& Expresie::operator=(const Expresie& e) {
	if (this != &e) {
		if (coada != nullptr) {
			delete[] coada;
			coada = nullptr;
		}

		if (e.coada != nullptr && e.lungimeCoada > 0) {
			this->lungimeCoada = e.lungimeCoada;
			this->coada = new char[e.lungimeCoada + 1];
			strcpy_s(this->coada, e.lungimeCoada + 1, e.coada);
		}
		else {
			this->coada = nullptr;
			this->lungimeCoada = 0;
		}
	}
	return *this;
}

char Expresie::operator[](int index) {
	if (index >= 0 && index < lungimeCoada) {
		return coada[index];
	}
	return NULL;
}
