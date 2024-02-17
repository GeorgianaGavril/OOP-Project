#pragma once
#include "Stiva.h"

class Expresie {
private:
	char* coada;
	int lungimeCoada;
public:
	Expresie();

	Expresie(const char* coada, int lungimeCoada);

	Expresie(const Expresie& e);

	~Expresie();

	char* getCoada();

	int getLungimeCoada();

	void setCoada(const char* stiva, int lungimeStiva);

	int ordine(const char simbol);

	void adaugaElement(const char* element);

	void algoritm(const char* sir);

	Expresie& operator=(const Expresie& e);

	char operator[](int index);
};