#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<double> Ligne;
typedef vector<Ligne> Matrice;
typedef vector<int> Liste;
typedef vector<Liste> Page;

struct Grille
{
	int taille;
	Matrice tab;
	vector<bool> visited;
	vector<Page> degres;
	Ligne moy;
};


// Tache 1
int init (Grille& mat);
void afficher (Grille mat);

// Tache 2
void noeuds_0 (Grille& mat);
void visit (Grille& mat, int n);
int connexe (Grille mat);

// Tache 3
void separation (Grille& mat);
void algo (Grille& mat, Liste& list, int step, int start);
void reset (Grille& mat);

// Tache 4
double deg_moy (Grille mat, int n);
double deg_moy_tot (Grille& mat);

int main()
{
	cout << endl;		// retirer sur le projet final !
	
	Grille mat_adj;
	
	// Tache 1	
	afficher(mat_adj); // retirer sur le projet final !
	
	// Tache 2
	noeuds_0(mat_adj);
	visit(mat_adj, 0);
	if (connexe(mat_adj) == 1) {
		cout << "Matrice non-connexe !" << endl;
		return 1;
	} else {
		cout << "Connexe !" << endl;
	}
	
	// Tache 3
	separation(mat_adj);
	
	// Tache 4
	cout << deg_moy_tot(mat_adj) << endl;
	
	cout << "Yihee !" << endl;
	
	//~ // Afficher les visited
	//~ for (int i(0) ; i < mat_adj.taille ; ++i)
	//~ {
		//~ cout << mat_adj.visited[i] << endl;
	//~ }
	
	return 0;
}


// Tache 1

int init (Grille& mat)
{
	// Vérifier qu'il s'agit bien du bon format P1
	string format;
	cin >> format;
	if (format != "P1") {
		return 1;
	}
	
	// Stocker la taille de la matrice et vérifier qu'elle soit non vide et carrée
	int col(0);
	int li(0);
	cin >> col;
	cin >> li;
	if ((col == 0) or (li == 0)) {
		return 2;
	} else if (col != li) {
		return 3;
	}
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
	
	return 0;
}


void afficher (Grille mat)
{
	for (size_t i(0) ; i < mat.tab.size() ; ++i) {
		for (size_t j(0) ; j < mat.tab[i].size() ; ++j) {
			cout << mat.tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	return;
}



// Tache 2

void noeuds_0 (Grille& mat)
{
	for (int i(0) ; i < mat.taille ; ++i)
	{
		mat.visited.push_back(0);
	}
	
	return;
}


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

int connexe (Grille mat)
{
	// Vérifier que le tableau visited est rempli de 1
	for (int i(0) ; i < mat.taille ; ++i) {
		if (mat.visited[i] == 0) {
			return 1;
		}
	}
	
	return 0;
}


// Tache 3


void separation (Grille& mat)
{
	
	for (int i(0) ; i < mat.taille ; ++i)
	{
		reset(mat);
		
		Liste depart = {i};
		Page new_page = {depart};
		mat.degres[i] = new_page;
		
		int step(0);
		//~ mat.visited[i] = 1; // inutile, car déjà dans algo
		algo(mat, mat.degres[i][step], step + 1, i);
	}
	
	return;
}

void algo (Grille& mat, Liste& list, int step, int start) // start = i, de la premiere iteration
{
	sort(list.begin(), list.end());
	Liste new_list;
	mat.degres[start].push_back(new_list);
	
	
	for (size_t i(0) ; i < list.size() ; ++i)
	{
		mat.visited[list[i]] = 1;
		for (int j(0) ; j < mat.taille ; ++j)
		{
			if ((mat.visited[j] == 0) and (mat.tab[list[i]][j] == 1)) {
				mat.degres[start][step].push_back(j);
			}
		}
	}
	
	if (mat.degres[start][step].size() > 0) {
		algo(mat, mat.degres[start][step], step + 1, start);
	}
	
	return;
}

void reset (Grille& mat)
{
	for (int i(0) ; i < mat.taille ; ++i) {
		mat.visited[i] = 0;
	}
	
	return;
}



// Tache 4

double deg_moy (Grille mat, int n)
{
	double somme(0);
	for (int l(0) ; l < mat.degres[n].size() ; ++l) {
		for (int i(0) ; i < mat.degres[n][l].size() ; ++i) {
			somme = somme + l;
		}
	}
	double moy(0);
	double tot(0);
	tot = mat.taille;
	moy = somme / tot;
	
	return moy;
}

double deg_moy_tot (Grille& mat)
{
	for (int n(0) ; n < mat.taille ; ++n) {
		mat.moy[n] = deg_moy(mat, n);
	}
	
	double somme(0);
	for (int i(0) ; i < mat.taille ; ++i) {
		somme = somme + mat.moy[i];
	}
	
	double moy_tot(0);
	double tot(0);
	tot = mat.taille;
	moy_tot = somme / tot;
	
	return moy_tot;
}


