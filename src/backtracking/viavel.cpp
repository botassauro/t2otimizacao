#include <iostream>
#include <iterator>
#include <vector>
using namespace std;


bool is_group_valid(int** matriz_afins, vector<int> group, int n, int num_afinidades[]) {

    // ex: 010101
    int sum = 0;

    // p/ cada heroi de 1 até n
    for (int i = 1; i <= n; i++)
        // se o heroi i está no grupo atual
        if (group.at(i) == 1) {
            
            // checa na linha i da matriz adj se todos os herois que devem estar no grupo
            // estao no grupo
            for (int j = 1; j <= n; j++) {
                if (group.at(j) == 1)
                    sum = sum + matriz_afins[i][j];
            }
            // se sim, a soma vai ser igual ao num de afinidades que aquele heroi i possui
            // se nao, o grupo é invalido
            printf("sum %d: %d\n", i, sum);
            if (sum != num_afinidades[i])
                return false;
            sum = 0;
        }

    return true;
}