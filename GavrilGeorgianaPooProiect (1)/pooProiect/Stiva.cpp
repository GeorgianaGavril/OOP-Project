#include <iostream>
#include "Stiva.h"
using namespace std;

/* Aici este o stiva pentru care am creat functii de pop si push pentru algoritmul Shunting Yard.*/

Stiva::Stiva() {
	stiva = nullptr;
	lungimeStiva = 0;
}

Stiva::Stiva(const char* stiva, int lungimeStiva) {
	if (stiva != nullptr && lungimeStiva > 0) {
		this->lungimeStiva = lungimeStiva;
		this->stiva = new char[lungimeStiva + 1];
		strcpy_s(this->stiva, lungimeStiva + 1, stiva);
	}
	else {
		this->stiva = nullptr;
		this->lungimeStiva = 0;
	}
}

Stiva::Stiva(const Stiva& s) {
	if (s.stiva != nullptr && s.lungimeStiva > 0) {
		this->lungimeStiva = s.lungimeStiva;
		this->stiva = new char[s.lungimeStiva + 1];
		strcpy_s(this->stiva, s.lungimeStiva + 1, s.stiva);
	}
	else {
		this->stiva = nullptr;
		this->lungimeStiva = 0;
	}
}

Stiva::~Stiva() {
	if (stiva != nullptr) {
		delete[] stiva;
		stiva = nullptr;
	}
}

int Stiva::getLungimeStiva() {
	return lungimeStiva;
}

char* Stiva::getStiva() {
	if (stiva != nullptr && lungimeStiva > 0) {
		return stiva;
	}
	return nullptr;
}

void Stiva::setStiva(const char* stiva, int lungimeStiva) {
	if (stiva != nullptr && lungimeStiva > 0) {
		this->lungimeStiva = lungimeStiva;
		if (this->stiva != nullptr) {
			delete[] this->stiva;
		}
		this->stiva = new char[lungimeStiva + 1];
		strcpy_s(this->stiva, lungimeStiva + 1, stiva);
	}
}

void Stiva::push(const char element) {
	if (stiva == nullptr) {
		lungimeStiva = 1;
		stiva = new char[lungimeStiva + 1];
		stiva[0] = element;
		stiva[lungimeStiva] = '\0';
	}
	else {
		char* copie = new char[lungimeStiva + 1];
		strcpy_s(copie, lungimeStiva + 1, stiva);

		delete[] stiva;

		lungimeStiva++;
		stiva = new char[lungimeStiva + 1];
		strcpy_s(stiva, lungimeStiva + 1, copie);
		stiva[lungimeStiva - 1] = element;
		stiva[lungimeStiva] = '\0';

		delete[] copie;
		copie = nullptr;
	}
}

void Stiva::pop() {
	if (stiva != nullptr && lungimeStiva > 0) {
		char* copie = new char[lungimeStiva];
		strncpy_s(copie, lungimeStiva, stiva, lungimeStiva - 1);

		delete[] stiva;
		stiva = nullptr;

		lungimeStiva--;
		stiva = new char[lungimeStiva + 1];
		strncpy_s(stiva, lungimeStiva + 1, copie, lungimeStiva);
		stiva[lungimeStiva] = '\0';

		delete[] copie;
		copie = nullptr;
	}
}

Stiva& Stiva::operator=(const Stiva& s) {
	if (this != &s) {
		if (stiva != nullptr) {
			delete[] stiva;
			stiva = nullptr;
		}

		if (s.stiva != nullptr && s.lungimeStiva > 0) {
			this->lungimeStiva = s.lungimeStiva;
			this->stiva = new char[s.lungimeStiva + 1];
			strcpy_s(this->stiva, s.lungimeStiva + 1, s.stiva);
		}
		else {
			this->stiva = nullptr;
			this->lungimeStiva = 0;
		}
	}
	return *this;
}

char Stiva::operator[](int index) {
	if (index >= 0 && index < lungimeStiva) {
		return stiva[index];
	}
	return '\0';
}