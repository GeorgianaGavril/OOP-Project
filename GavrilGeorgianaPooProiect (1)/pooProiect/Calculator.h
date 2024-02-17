#pragma once
#include <iostream>
using namespace std;

class Calculator {
private:
	char* expresie;
	int lungimeExpresie;
	double* rezultat;
	int lungimeRezultat;
	const char* operatii = "+ - * / ^ # ( ) [ ]";
	static string tipExpresie;
public:
	Calculator();

	Calculator(const char* expresie, int lungimeExpreise, double* rezultat, int lungimeRezultat);

	Calculator(const Calculator& e);

	~Calculator();

	char* getExpresie();

	int getLungimeExpresie();

	void setExpresie(const char* expresie, int lungimeExpresie);

	double* getRezultat();

	int getLungimeRezultat();

	void setRezultat(double* rezultat, int lungimeRezultat);
	
	void rezultatFinal();

	void eliminareSpatii();

	void push(double element);

	void pop();

	static string getTipExpresie();

	double operator[](int index);

	int operator!();

	Calculator& operator=(const Calculator& c);

	friend istream& operator>>(istream& in, Calculator& c);
	friend ostream& operator<<(ostream& out, Calculator c);
};