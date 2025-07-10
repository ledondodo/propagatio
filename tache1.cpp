// Tache 1 - Initialisation de la Matrice d'adjacence

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<double> Ligne;
typedef vector<Ligne> Matrice;

struct Grille
{
	int taille;
	Matrice tab;
	vector<bool> visited; // Noeuds
};

void init (Grille& mat);
void symetrie (Grille& mat);
void verification (Grille mat);
void afficher (Grille mat);

int main()
{
	cout << endl;		// retirer sur le projet final !
	
	Grille mat_adj;
	
	init(mat_adj);
	symetrie(mat_adj);
	verification(mat_adj);
	afficher(mat_adj);
	
	
	cout << "Yihee !" << endl;

	
	return 0;
}

void init (Grille& mat)
{
	// Vérifier qu'il s'agit bien du bon format P1
	string format;
	do {
		cin >> format;
		if (format != "P1")
		{
			cout << "Format de fichier non valide." << endl;
		}
	} while (format != "P1");
	
	// Stocker la taille de la matrice et vérifier qu'elle soit carrée
	int col(0);
	int li(0);
	do {
		cin >> col;
		cin >> li;
		if (col != li)
		{
			cout << "La matrice n'est pas carrée." << endl;
		}
	} while (col != li);
	mat.taille = li;
	
	// Stocker toutes les valeurs dans la matrice
	double a(2);						// Si la matrice a un coefficient égal à 2, c'est que l'opération ne s'est pas bien produite
	for (int i(0) ; i < li ; ++i)
	{
		Ligne ligne;
		
		for (int j(0) ; j < col ; ++j)
		{
			cin >> a;
			ligne.push_back(a);
		}
		
		mat.tab.push_back(ligne);
	}
	
	return;
}

void symetrie (Grille& mat)
{
	for (int i(0) ; i < mat.taille ; ++i)
	{
		// Diagonale nulle
		mat.tab[i][i] = 0;
		
		for (int j(0) ; j < mat.taille ; ++j)
		{
			// Symétrie
			if ((mat.tab[i][j] == 1) or (mat.tab[j][i] == 1))
			{
				mat.tab[i][j] = 1;
				mat.tab[j][i] = 1;
			}
		}
	}
	return;
}

void verification (Grille mat)
{
	// Vérifier qu'il n'a a pas que des 0 et des 1
	for (int i(0) ; i < mat.taille ; ++i)
	{
		for (int j(0) ; j < mat.taille ; ++j)
		{
			if ((mat.tab[i][j] != 0) and (mat.tab[i][j] != 1))
			{
				cout << "Erreur de cin !" << endl;
			}
		}
	}
	
	return;
}

void afficher (Grille mat)
{
	for (size_t i(0) ; i < mat.tab.size() ; ++i)
	{
		for (size_t j(0) ; j < mat.tab[i].size() ; ++j)
		{
			cout << mat.tab[i][j] << " ";
		}
	cout << endl;
	}
	cout << endl;
	
	return;
}
