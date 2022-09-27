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

struct ItemSol {
    int weight;
    int bin_index;
};

struct greaterItemSol {
    inline bool operator()(const ItemSol A, const ItemSol B) {
        return (A.weight > B.weight);
    }
};

struct Solution {
    std::vector<ItemSol> item;  // bins_index_i = índice j de bins_j onde item_i foi colocado
    std::vector<int> bins;
};

#endif  // !PROBLEMH
