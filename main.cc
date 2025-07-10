// Projet Propagatio, 324265.cc, v2.0, Arthur Chansel 324265

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> Liste;
typedef vector<Liste> Page;

struct Grille
{
	int taille;
	vector<vector<double>> tab;
	vector<bool> visited;
	vector<Page> degres;
	vector<double> moy;
};

const string P1("P1 missing or incorrect");
const string WRONG_NB_COL_LGN("Nb columns and/or nb lines incorrect");
const string MATRIX_SQUARE("Matrix is not square");
const string IRREGULAR_CONTENT("Matrix description with incorrect content");
const string DISCONNECTED_GRAPH("Matrix corresponds to a disconnected graph");

// Tache 1
void init (Grille& mat);
void verification (Grille& mat);
void symetrie (Grille& mat);

// Tache 2
void visit (Grille& mat, int n);
void connexe (Grille& mat);
void reset (Grille& mat);

// Tache 3
void algo_recursif (Grille& mat, Liste& list, int step, int start);
void afficher_page (vector<Page> Livre);

// Tache 4
void separation (Grille& mat);
double deg_moy (Grille& mat, int n);
double deg_moy_tot (Grille& mat);



int main()
{
	Grille mat_adj;
	
	// Tache 1
	init(mat_adj);
	verification(mat_adj);
	symetrie(mat_adj);
	
	// Tache 2
	mat_adj.visited = vector<bool> (mat_adj.taille, 0);
	visit(mat_adj, 0);
	connexe(mat_adj);
	reset(mat_adj);
	
	// Tache 3
	Liste depart = {0};
	mat_adj.degres.push_back({depart});
	mat_adj.visited[0] = 1;
	
	algo_recursif(mat_adj, depart, 1, 0);
	afficher_page(mat_adj.degres);
	
	// Tache 4
	separation(mat_adj);
	cout << deg_moy_tot(mat_adj) << endl;
	
	return 0;
}


// Tache 1

void init (Grille& mat)
{
	// Vérifier qu'il s'agit bien du bon format P1
	string format;
	cin >> format;
	if (format != "P1") {
		cout << P1 << endl;
		exit(0);
	}
	
	// Stocker la taille de la matrice et vérifier qu'elle soit non vide et carrée
	int col(0);
	int li(0);
	cin >> col;
	cin >> li;
	if ((col == 0) or (li == 0)) {
		cout << WRONG_NB_COL_LGN << endl;
		exit(0);
	} else if (col != li) {
		cout << MATRIX_SQUARE << endl;
		exit(0);
	}
	mat.taille = li;
	
	// Stocker toutes les valeurs dans la matrice
	double a(2);
	// Si la matrice a un coefficient égal à 2, il y a eu une erreur de cin
	for (int i(0) ; i < li ; ++i)
	{
		vector<double> ligne;
		for (int j(0) ; j < col ; ++j)
		{
			cin >> a;
			ligne.push_back(a);
		}
		mat.tab.push_back(ligne);
	}
	
	return;
}

void verification (Grille& mat)
{
	// Vérifier qu'il n'y a que des 0 et des 1
	for (int i(0) ; i < mat.taille ; ++i)
	{
		for (int j(0) ; j < mat.taille ; ++j)
		{
			if ((mat.tab[i][j] != 0) and (mat.tab[i][j] != 1))
			{
				cout << IRREGULAR_CONTENT << endl;
				exit(0);
			}
		}
	}
	
	return;
}

void symetrie (Grille& mat)
{
	for (int i(0) ; i < mat.taille ; ++i) {
		// Diagonale nulle
		mat.tab[i][i] = 0;
		for (int j(0) ; j < mat.taille ; ++j) {
			// Symétrie
			if (mat.tab[i][j] == 1) {
				mat.tab[j][i] = 1;
			}
		}
	}
	return;
}


// Tache 2

void visit (Grille& mat, int n)
{
	// Noeud de départ est visité
	mat.visited[n] = 1;
	
	// Parcourir la n-ième ligne et appeller récursivement les noeuds reliés
	for (int j(0) ; j < mat.taille ; ++j) {
		if ((mat.tab[n][j] == 1) and (mat.visited[j] == 0)) {
			// Appel récursif
			visit(mat, j);
		}
	}
	
	return;
}

void connexe (Grille& mat)
{
	// Vérifier que le tableau visited est rempli de 1
	for (int i(0) ; i < mat.taille ; ++i) {
		if (mat.visited[i] == 0) {
			cout << DISCONNECTED_GRAPH << endl;
			exit(0);
		}
	}
	
	return;
}

void reset (Grille& mat)
{
	for (int i(0) ; i < mat.taille ; ++i)
	{
		mat.visited[i] = 0;
	}
		
	return;
}


// Tache 3

void algo_recursif (Grille& mat, Liste& list, int step, int start)
{
	Liste new_line;
	
	for (size_t i(0) ; i < list.size() ; ++i) {
		for (int j(0) ; j < mat.taille ; ++j) {
			if ((mat.visited[j] == 0) and (mat.tab[list[i]][j] == 1)) {
				mat.visited[j] = 1;
				new_line.push_back(j);
			}
		}
	}
	sort(new_line.begin(), new_line.end());
	
	if (new_line.size() > 0) {
		mat.degres[start].push_back(new_line);
		algo_recursif(mat, new_line, step + 1, start);
		// start = numéro du noeud de départ
	}
	
	return;
}

void afficher_page (vector<Page> Livre)
{
	for (size_t l(0) ; l < Livre[0].size() ; l++) {
		for (size_t i(0) ; i < Livre[0][l].size() ; ++i) {
			if (i != Livre[0][l].size() - 1) {
				cout << Livre[0][l][i] << " ";
			} else {
				cout << Livre[0][l][i];
			}
		}
		cout << endl;
	}
	
	return;
}


// Tache 4

void separation (Grille& mat)
{
	// Voir mat.degres comme un Livre dont chaque Page est composée de listes
	for (int i(1) ; i < mat.taille ; ++i)
	{
		reset(mat);
		
		Liste depart = {i};
		Page new_page = {depart};
		mat.degres.push_back(new_page);
		
		mat.visited[i] = 1;
		algo_recursif(mat, depart, 1, i);
	}
	
	return;
}

double deg_moy (Grille& mat, int n)
{
	double somme(0);
	for (size_t l(0) ; l < mat.degres[n].size() ; ++l) {
		for (size_t i(0) ; i < mat.degres[n][l].size() ; ++i) {
			somme = somme + l;
		}
	}
	double moy(0);
	double tot(0);
	tot = mat.taille - 1;
	moy = somme / tot;
	
	return moy;
}

double deg_moy_tot (Grille& mat)
{
	for (int n(0) ; n < mat.taille ; ++n) {
		mat.moy.push_back(deg_moy(mat, n));
	}
	
	double somme(0);
	for (int i(0) ; i < mat.taille ; ++i) {
		somme = somme + mat.moy[i];
	}
	
	double moy_tot(0);
	double tot(0);
	tot = mat.taille;
	cout << setprecision(6) << fixed;
	if (mat.taille == 1) {
		moy_tot = 0;
	} else {
		moy_tot = somme / tot;
	}
	
	return moy_tot;
}

