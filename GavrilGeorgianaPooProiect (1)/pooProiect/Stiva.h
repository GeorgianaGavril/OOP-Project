#pragma once

class Stiva {
private:
	char* stiva;
	int lungimeStiva;
public:
	Stiva();

	Stiva(const char* stiva, int lungimeStiva);

	Stiva(const Stiva& s);

	~Stiva();

	char* getStiva();

	int getLungimeStiva();

	void setStiva(const char* stiva, int lungimeStiva);

	void push(const char element);

	void pop();

	Stiva& operator=(const Stiva& s);

	char operator[](int index);
};