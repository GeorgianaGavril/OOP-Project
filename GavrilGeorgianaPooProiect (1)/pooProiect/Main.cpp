#include <iostream>
#include "Calculator.h"
#include "Expresie.h"
#include "Stiva.h"
using namespace std;

int main() {
	Calculator c;
	int continuare = 1;
	while (continuare) {
		cin >> c;
		if (!strcmp(c.getExpresie(), "exit")) {
			continuare = 0;
		}
		else if (!c) {
			c.eliminareSpatii();
			c.rezultatFinal();
			cout << c[0] << endl << endl;
		}
		else {
			cout << "Expresie incorecta!" << endl << endl;
		}
	}
}