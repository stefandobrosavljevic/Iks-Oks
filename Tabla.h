#pragma once
#include <math.h>
#include <iostream>
using namespace std;

class Tabla
{
private:
	char **mat;
	void upis();
	void prikaz();
	void drugiIgrac();
	int proveriOptimalno(int);
	bool xPobedio();
	bool oPobedio();
    bool tie();
	bool pravilaIgre();
public:
	Tabla();
	~Tabla();
	void play();
};

Tabla::Tabla()
{
    mat = new char*[3];
    for(int i=0;i<3;i++){
        mat[i] = new char[3];
        for(int j=0;j<3;j++){
            mat[i][j] = '_';
        }
    }
}

Tabla::~Tabla()
{
    for (int i = 0; i < 3; i++)
        delete[] mat[i];
    delete[] mat;
}

void Tabla::prikaz()
{
	cout << "\n\n";
	for (int i = 0; i < 3; i++) {
		cout << "\t";
		for (int j = 0; j < 3; j++)
			cout << mat[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

void Tabla::upis()
{
	do
	{
        cout << "Vrsta i kolona?" << endl;
        int vrst;
        int kol;
		cin >> vrst >> kol;
		if (vrst < 0 || vrst >2 || kol < 0 || kol >2) {
			cout << "Pogresne dimenzije, uniesite ponovo\n";
            continue;
		}

		if (mat[vrst][kol] == '_') {
			mat[vrst][kol] = 'O';
		    return;
		}
		else
			cout << "Vec je odabrano to polje!" << endl;
	}
	while (true);
}

bool Tabla::xPobedio()
{
	for (int i = 0; i < 3; i++) {
		if (mat[i][0] == 'X' && mat[i][1] == 'X' && mat[i][2] == 'X')
			return true;
		if (mat[0][i] == 'X' && mat[1][i] == 'X' && mat[2][i] == 'X')
			return true;
	}
	if (mat[0][0] == 'X' && mat[1][1] == 'X' && mat[2][2] == 'X')
		return true;
	if (mat[0][2] == 'X' && mat[1][1] == 'X' && mat[2][0] == 'X')
		return true; 
	return false;
}

bool Tabla::oPobedio()
{
	for (int i = 0; i < 3; i++) {
		if (mat[i][0] == 'O' && mat[i][1] == 'O' && mat[i][2] == 'O')
			return true;
		if (mat[0][i] == 'O' && mat[1][i] == 'O' && mat[2][i] == 'O')
			return true;
	}
	if (mat[0][0] == 'O' && mat[1][1] == 'O' && mat[2][2] == 'O')
		return true;
	if (mat[0][2] == 'O' && mat[1][1] == 'O' && mat[2][0] == 'O')
		return true; 
	return false;
}

bool Tabla::tie()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(mat[i][j] == '_')
                return false;
    return true;
}

bool Tabla::pravilaIgre()
{
	if (xPobedio() || oPobedio() || tie())
		return true;
    return false;
}

void Tabla::play()
{
	while (!pravilaIgre()){
		upis();
		if (pravilaIgre())
			break;
		drugiIgrac();
		prikaz();
    }
    if(oPobedio())
        cout << "    *****  O pobedio  *****"<< endl;
    if(xPobedio())
        cout << "    *****  X pobedio  *****"<< endl;
    if(tie())
        cout << "    *****  Nereseno  *****"<< endl;
}

void Tabla::drugiIgrac()
{
    int najVrsta;
    int najKolona;
	int best = (int)-INFINITY;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (mat[i][j] == '_') {
				mat[i][j] = 'X';
				int pom = proveriOptimalno(1);
				if (best < pom) {
					best = pom;
                    najVrsta = i;
                    najKolona = j;
				}
				mat[i][j] = '_';
			}
		}
	}
   mat[najVrsta][najKolona] = 'X';
}

int Tabla::proveriOptimalno(int koji)
{
    if(oPobedio())
        return -10;
    else if(xPobedio())
        return 10;
    else if (tie())
        return 0;
    //igra kao covek
    if(koji == 1)
    {
        int best = (int)INFINITY;
	    for (int i = 0; i < 3; i++) {
		    for (int j = 0; j < 3; j++) {
                if(mat[i][j] == '_')
                {
                    mat[i][j] = 'O';
                    int pom = proveriOptimalno(0);
                    mat[i][j] = '_';
                    if(best > pom)
                        best = pom;
                }
            }
        }
        return best;
    }

    //igra kompijuter
    else
    {
        int best = (int)-INFINITY; 
        for (int i = 0; i < 3; i++) {
		    for (int j = 0; j < 3; j++) {
                if(mat[i][j] == '_')
                {
                    mat[i][j] = 'X';
                    int pom = proveriOptimalno(1);
                    mat[i][j] = '_';
                    if(best < pom)
                        best = pom;
                }
            }
        }
        return best;
    }    
}

