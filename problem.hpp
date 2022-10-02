#pragma once
#include <list>
#include <string>
#include <vector>

struct Problem {
    std::string identifier;  // Identificador do problema
    int binCapacity;         // Capacidade das bins
    int n;                   // Quantidade de itens
    int bestSolution;        // Melhor solução
    std::vector<int> items;  // Items
};

struct ItemSolution {
    int weight;
    std::list<int>::iterator bin_index;  // bins_index_i = índice j de bins_j onde item_i foi colocado
};

struct greaterItemSolution {  // Retorna o item com maior peso
    inline bool operator()(const ItemSolution A, const ItemSolution B) {
        return (A.weight > B.weight);
    }
};

struct Solution {
    std::vector<ItemSolution> item;
    std::list<int> bins;
    Solution(Problem P) {  // Construtor da solução
        item.resize(P.n);
        for (std::vector<int>::iterator it = P.items.begin(); it != P.items.end(); it++) {
            item[it - P.items.begin()].weight = *it;            // cópia dos items, vai ajudar mais tarde quando for fazer trocas
            item[it - P.items.begin()].bin_index = bins.end();  // bins.end() é flag para item que não foi colocado em nenhuma bin
        }
    }
};
