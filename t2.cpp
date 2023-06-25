#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <array>
#include <queue>
using namespace std;

#define NAO_PROCESSADO 0
#define EM_PROCESSO 1
#define PROCESSADO 2

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

int BuscaLargura(int* herois_estado, int h, int** adjacencia, int num_herois, set<int> conj) {

	queue<int> fila;
	printf("ini: %d ", h);
	fila.push(h);
	herois_estado[h] = EM_PROCESSO;
	int triangulos = 0;

	while (fila.size() != 0) {
		int aux = fila.front();
		fila.pop();
		
		for (int i = 1; i <= num_herois; i++) {
			auto pos = conj.find(i);
			if (pos != conj.end())
				if (adjacencia[aux][i] == 1) {

					if (herois_estado[i] == EM_PROCESSO ) {
						printf("esta fora: %d-%d\n", aux, i);
						triangulos++;
						//printf("%d\n", *triangulos);
					} else
						if (herois_estado[i] == NAO_PROCESSADO) {
							
							printf("esta dentro: %d-%d\n", aux, i);
							fila.push(i);
							herois_estado[i] = EM_PROCESSO;
						}
					
				}
			
		}
		herois_estado[aux] = PROCESSADO;

	}
	return triangulos;
}

int BuscaEnvelope(int num_herois, int** adjacencia, set<int> conj) {

	int triangulos = 0;

	int herois_estado[num_herois+1];

	for (int i = 1; i < num_herois+1; i++)
		herois_estado[i] = NAO_PROCESSADO;

	for (int i = 1; i < num_herois+1; i++) {
		auto pos = conj.find(i);
		if (pos != conj.end())
			if (herois_estado[i] == NAO_PROCESSADO)
				triangulos = triangulos + BuscaLargura(herois_estado, i, adjacencia, num_herois, conj);
	}
	return triangulos;
}

int main() {

    int num_herois, num_pares, num_conflitos;
	fscanf(stdin, "%d", &num_herois);
    fscanf(stdin, "%d", &num_pares);
	fscanf(stdin, "%d", &num_conflitos);

	int **adjacencia;
	adjacencia = new int *[num_herois];
	for (int i = 0; i <= num_herois; i++)
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

	set<int> conj;
	conj.insert(2);
	conj.insert(4);
	conj.insert(5);
	
	int t = BuscaEnvelope(num_herois, adjacencia, conj);
	printf("resultado: %d\n", t);



	return 0;
}
