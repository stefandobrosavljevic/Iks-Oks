#pragma once
#include <math.h>
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
	void proveriOptimalno(int);
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
            continue;
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
			return 1;
		}
		if (mat[0][i]->vrednost == 'X' &&
			mat[1][i]->vrednost == 'X' &&
			mat[2][i]->vrednost == 'X') {
			//cout << "\n\t**X je pobedio**" << endl;
			return 1;
		}
	}
	if (mat[0][0]->vrednost == 'X' &&
		mat[1][1]->vrednost == 'X' &&
		mat[2][2]->vrednost == 'X') {
		//cout << "\n\t**X je pobedio**" << endl;
		return 1;
	}
	if (mat[0][2]->vrednost == 'X' &&
		mat[1][1]->vrednost == 'X' &&
		mat[2][0]->vrednost == 'X') {
		//cout << "\n\t**X je pobedio**" << endl;
		return 1;
	}
	return 0;
}

bool Tabla::oPobedio()
{
	for (int i = 0; i < 3; i++) {

		if (mat[i][0]->vrednost == 'O' &&
			mat[i][1]->vrednost == 'O' &&
			mat[i][2]->vrednost == 'O') {
			//cout << "\n\t**O je pobedio**" << endl;
			return 1;
		}
		if (mat[0][i]->vrednost == 'O' &&
			mat[1][i]->vrednost == 'O' &&
			mat[2][i]->vrednost == 'O') {
			//cout << "\n\t**O je pobedio**" << endl;
			return 1;
		}
	}
	if (mat[0][0]->vrednost == 'O' &&
		mat[1][1]->vrednost == 'O' &&
		mat[2][2]->vrednost == 'O') {
		//cout << "\n\t**O je pobedio**" << endl;
		return 1;
	}
	if (mat[0][2]->vrednost == 'O' &&
		mat[1][1]->vrednost == 'O' &&
		mat[2][0]->vrednost == 'O') {
		//cout << "\n\t**O je pobedio**" << endl;
		return 1;
	}
	return 0;
}

bool Tabla::pravilaIgre()
{
	if (xPobedio() || oPobedio())
		return 0;
	else
		return 1;
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
	cout << "*********Kraj igre************" << endl;
}

void Tabla::drugiIgrac()
{
    int najVrsta;
    int najKolona;
	int best = (int)INFINITY;
    //int best = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j]->vrednost == '_') {
				mat[i][j]->vrednost = 'X';
				proveriOptimalno(1);
				cout << "Best: " << best << endl;
                cout << "Opt: " << opt << endl << endl;
				if (best > opt) {
					best = opt;
                    najVrsta = i;
                    najKolona = j;
				}
				opt = 0;
				mat[i][j]->vrednost = '_';
			}
		}
	}
   mat[najVrsta][najKolona]->vrednost = 'X';
}

void Tabla::proveriOptimalno(int koji)
{
    if(koji == 1)
    {
	    for (int i = 0; i < 3; i++) {
		    for (int j = 0; j < 3; j++) {
                if(mat[i][j]->vrednost == '_')
                {
                    mat[i][j]->vrednost = 'O';
                    if(oPobedio()){
                        opt--;
                        mat[i][j]->vrednost = '_';
                        return;
                    }
                    proveriOptimalno(0);
                    mat[i][j]->vrednost = '_';
                }
            }
        }
    }

    else if(koji == 0)
    {
	    for (int i = 0; i < 3; i++) {
		    for (int j = 0; j < 3; j++) {
                if(mat[i][j]->vrednost == '_')
                {
                    mat[i][j]->vrednost = 'X';
                    if(xPobedio()){
                        //opt++;
                        mat[i][j]->vrednost = '_';
                        return;
                    }
                    proveriOptimalno(1);
                    mat[i][j]->vrednost = '_';
                }
            }
        }
    }    
}


