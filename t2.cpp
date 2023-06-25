#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <array>
#include <queue>
using namespace std;

class Heroi {
	public:
    Heroi(int id, vector<Heroi> afins, vector<Heroi> conflitos);
    int id;
    vector<Heroi> afins;
	vector<Heroi> conflitos;
	unsigned int estado;
};

class Conjunto {
	public:
    Conjunto(set<Heroi> conj);
	set<Heroi> conj;
};

Heroi::Heroi(int id, vector<Heroi> afins, vector<Heroi> conflitos)
	:id{id}, afins{afins}, conflitos{conflitos}, estado{0} {}

Conjunto::Conjunto(set<Heroi> conj)
	:conj{conj} {}

void BuscaLargura(int* herois_estado, int h, int** adjacencia, int num_herois, int triangulos) {

	queue<int> fila;
	printf("ini: %d ", h);
	fila.push(h);
	herois_estado[h] = 1;
	

	while (fila.size() != 0) {
		int aux = fila.front();
		fila.pop();
		
		for (int i = 1; i <= num_herois; i++) {

			if (adjacencia[aux][i] == 1) {

				if (herois_estado[i] == 1 ) {
					printf("esta fora: %d-%d\n", aux, i);
					triangulos++;
					//printf("%d\n", *triangulos);
				} else
					if (herois_estado[i] == 0) {
						
						printf("esta dentro: %d-%d\n", aux, i);
						fila.push(i);
						herois_estado[i] = 1;
						//herois_estado[aux] = 1;
					}
				
			}
			
		}
		herois_estado[aux] = 2;

	}
}

int BuscaEnvelope(int num_herois, int** adjacencia) {

	int triangulos = 0;

	int herois_estado[num_herois+1];

	for (int i = 1; i < num_herois+1; i++)
		herois_estado[i] = 0;

	for (int i = 1; i < num_herois+1; i++)
		if (herois_estado[i] == 0)
			BuscaLargura(herois_estado, i, adjacencia, num_herois, triangulos);
	
	return triangulos;
}

int main() {

    int num_herois, num_pares, num_conflitos;
	fscanf(stdin, "%d", &num_herois);
    fscanf(stdin, "%d", &num_pares);
	fscanf(stdin, "%d", &num_conflitos);

	int **adjacencia;
	adjacencia = new int *[num_herois];
	for (int i = 0; i < 10; i++)
   		adjacencia[i] = new int[num_herois];

	for (int i = 1; i <= num_herois; i++) {
		for (int j = 1; j <= num_herois; j++) {
			adjacencia[i][j] = 0;
		}
		printf("\n");
	}

	int h1, h2;

	for (int i = 1; i <= num_pares; i++) {
		fscanf(stdin, "%d", &h1);
    	fscanf(stdin, "%d", &h2);
		adjacencia[h1][h2] = 2;
		adjacencia[h2][h1] = 2;
	}

	for (int i = 1; i <= num_conflitos; i++) {
		fscanf(stdin, "%d", &h1);
    	fscanf(stdin, "%d", &h2);
		adjacencia[h1][h2] = 1;
		adjacencia[h2][h1] = 1;
	}

	for (int i = 1; i <= num_herois; i++) {
		for (int j = 1; j <= num_herois; j++) {
			printf("%d", adjacencia[i][j] );
		}
		printf("\n");
	}

	int t = BuscaEnvelope(num_herois, adjacencia);
	printf("resultado: %d\n", t);

	/*vector<Heroi> herois;

	for (int i = 0; i < num_herois; i++) {
		vector<Heroi> afins;
		vector<Heroi> conflitos;
		Heroi h(i+1, afins, conflitos);
		herois.push_back(h);
	}

	int h1, h2;

	for (int i = 0; i < num_pares; i++) {
		fscanf(stdin, "%d", &h1);
    	fscanf(stdin, "%d", &h2);
		herois.at(h1-1).afins.push_back(herois.at(h2-1));
		herois.at(h2-1).afins.push_back(herois.at(h1-1));
	}

	for (int i = 0; i < num_conflitos; i++) {
		fscanf(stdin, "%d", &h1);
    	fscanf(stdin, "%d", &h2);
		herois.at(h1-1).conflitos.push_back(herois.at(h2-1));
		herois.at(h2-1).conflitos.push_back(herois.at(h1-1));
	}


	printf("%d\n", herois.at(0).afins.at(0).id);
	printf("%d\n", herois.at(1).afins.at(0).id);
	printf("%d\n", herois.at(2).afins.at(0).id);
	printf("%d\n", herois.at(3).afins.at(0).id);
	printf("%d\n", herois.at(0).conflitos.at(0).id);
	printf("%d\n", herois.at(1).conflitos.at(0).id);
	printf("%d\n", herois.at(2).conflitos.at(0).id);
	printf("%d\n", herois.at(3).conflitos.at(0).id);*/


	return 0;
}
