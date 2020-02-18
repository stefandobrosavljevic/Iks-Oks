#pragma once
#include <iostream>
using namespace std;
int opt = 0;

struct polje 
{
	char vrednost;
	int vrsta;
	int kolona;
};


class Tabla
{
private:
	polje*** mat;
public:
	Tabla();
	~Tabla();

	void upis();
	void prikaz();
	void drugiIgrac();
	bool pravilaIgre();
	bool xPobedio();
	bool oPobedio();
	void play();
	void proveriOptimalno();
};



Tabla::Tabla()
{
	mat = new polje * *[3];
	for (int i = 0; i < 3; i++) {
		mat[i] = new polje * [3];
		for (int j = 0; j < 3; j++) {
			mat[i][j] = new polje;
			mat[i][j]->vrednost = '_';
		}
	}

}

Tabla::~Tabla()
{
	if (mat != 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				delete mat[i][j];
			}
			delete[] mat[i];
		}
		delete[] mat;
	}
}

void Tabla::prikaz()
{
	cout << "\n\n";
	for (int i = 0; i < 3; i++) {
		cout << "\t";
		for (int j = 0; j < 3; j++) {
			cout << mat[i][j]->vrednost << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Tabla::upis()
{
	int vrst;
	int kol;
	int pom = 0;
	cout << "Vrsta i kolona?" << endl;
	do
	{
		cin >> vrst >> kol;
		if (vrst < 0 || vrst >2 || kol < 0 || kol >2) {
			cout << "Pogresne dimenzije, uniesite ponovo\n";
		}

		if (mat[vrst][kol]->vrednost == '_') {
			mat[vrst][kol]->vrednost = 'O';
			pom = 1;
		}
		else
			cout << "Vec je odabrano to polje!" << endl;
	}
	while (pom == 0);
}

bool Tabla::xPobedio()
{
	for (int i = 0; i < 3; i++) {
		if (mat[i][0]->vrednost == 'X' &&
			mat[i][1]->vrednost == 'X' &&
			mat[i][2]->vrednost == 'X') {
			//cout << "\n\t**X je pobedio**" << endl;
			return 0;
		}
		if (mat[0][i]->vrednost == 'X' &&
			mat[1][i]->vrednost == 'X' &&
			mat[2][i]->vrednost == 'X') {
			//cout << "\n\t**X je pobedio**" << endl;
			return 0;
		}
	}
	if (mat[0][0]->vrednost == 'X' &&
		mat[1][1]->vrednost == 'X' &&
		mat[2][2]->vrednost == 'X') {
		//cout << "\n\t**X je pobedio**" << endl;
		return 0;
	}
	if (mat[0][2]->vrednost == 'X' &&
		mat[1][1]->vrednost == 'X' &&
		mat[2][0]->vrednost == 'X') {
		//cout << "\n\t**X je pobedio**" << endl;
		return 0;
	}
	return 1;
}

bool Tabla::oPobedio()
{
	for (int i = 0; i < 3; i++) {

		if (mat[i][0]->vrednost == 'O' &&
			mat[i][1]->vrednost == 'O' &&
			mat[i][2]->vrednost == 'O') {
			//cout << "\n\t**O je pobedio**" << endl;
			return 0;
		}
		if (mat[0][i]->vrednost == 'O' &&
			mat[1][i]->vrednost == 'O' &&
			mat[2][i]->vrednost == 'O') {
			//cout << "\n\t**O je pobedio**" << endl;
			return 0;
		}
	}
	if (mat[0][0]->vrednost == 'O' &&
		mat[1][1]->vrednost == 'O' &&
		mat[2][2]->vrednost == 'O') {
		//cout << "\n\t**O je pobedio**" << endl;
		return 0;
	}
	if (mat[0][2]->vrednost == 'O' &&
		mat[1][1]->vrednost == 'O' &&
		mat[2][0]->vrednost == 'O') {
		//cout << "\n\t**O je pobedio**" << endl;
		return 0;
	}
	return 1;
}

bool Tabla::pravilaIgre()
{
	if (xPobedio() && oPobedio())
		return 1;
	else
		return 0;
}

void Tabla::play()
{
	do 
	{
		upis();
		if (!pravilaIgre())
			break;
		drugiIgrac();
		prikaz();
	} while (pravilaIgre());
	prikaz();
	cout << "*******Kraj igre************" << endl;
}




void Tabla::drugiIgrac()
{
	int best = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j]->vrednost == '_') {
				mat[i][j]->vrednost = 'X';
				proveriOptimalno();
				if (best < opt) {
					best = opt;
				}
				cout << best << endl;
				opt = 0;
				mat[i][j]->vrednost = '_';
			}
		}
	}
	//cout << "Optimalno resenje: " << best;
}


void Tabla::proveriOptimalno()
{
	for (int q = 0; q < 3; q++) {
		for (int w = 0; w < 3; w++) {
			if (mat[q][w]->vrednost == '_') {
				mat[q][w]->vrednost = 'O';
				if (!oPobedio())
					opt--;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (mat[i][j]->vrednost == '_') {
							mat[i][j]->vrednost = 'X';
							if (!xPobedio())
								opt++;
							if (pravilaIgre())
								opt++;
							proveriOptimalno();
							mat[i][j]->vrednost = '_';
						}
					}
				}
				mat[q][w]->vrednost = '_';
			}
		}
	}
}






