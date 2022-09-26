#include <string>
#include <vector>

#ifndef PROBLEMH
#define PROBLEMH

struct Problem {
    std::string identifier;  // Identificador do problema
    int binCapacity;         // Capacidade das bins
    int n;                   // Quantidade de itens
    int bestSolution;        // Melhor solução
    std::vector<int> items;  // Items
};

struct Solution {
    std::vector<int> bins_index;  // bins_index_i = ponteiro para bins_j onde item_i foi colocado
    std::vector<int> bins;
};

#endif  // !PROBLEMH
