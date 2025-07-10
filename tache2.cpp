// Tache 2 - Verifier que le graphe est connexe

#include <iostream>
#include <vector>
using namespace std;

typedef vector<double> Ligne;
typedef vector<Ligne> Matrice;

struct Grille
{
	int taille;
	Matrice tab;
	vector<bool> visited; // Noeds
};

int init (Grille& mat);
void afficher (Grille mat);

void noeuds_0 (Grille& mat);
void visit (Grille& mat, int n);
int connexe (Grille mat);

int main()
{
	cout << endl;		// retirer sur le projet final !
	
	Grille mat_adj;
	
	init(mat_adj);
	
	
	
	// - Tache 2 -
	noeuds_0(mat_adj);
	visit(mat_adj, 0);
	if (connexe(mat_adj) == 1) {
		cout << "Matrice non-connexe !" << endl;
		return 1;
	} else {
		cout << "Connexe !" << endl;
	}
	
	
	
	afficher(mat_adj);
	cout << endl << "Yihee !" << endl;
	
	return 0;
}


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


