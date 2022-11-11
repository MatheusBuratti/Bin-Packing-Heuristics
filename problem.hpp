#pragma once
#include <list>
#include <string>
#include <vector>

struct Problem {
    std::string identifier;          // Identificador do problema
    int binCapacity;                 // Capacidade das bins
    int n;                           // Quantidade de itens
    int bestSolution;                // Melhor solução
    std::vector<int> items_weights;  // Items
};

struct bin;
struct item {
    int weight;
    std::list<bin>::iterator assignedBin;  // "ponteiro" para bins_vector onde o item está alocado
    item(int W, std::list<bin>::iterator defaultVal) {
        weight = W;
        assignedBin = defaultVal;
    }
};
struct bin {
    int fullness;
    std::list<std::vector<item>::iterator> storedItems;  // Lista de ponteiros dos items que estão guardados nesta bin
    bin() {
        fullness = 0;
    }
    bin(std::vector<item>::iterator item) {
        storedItems.push_back(item);
        fullness = item->weight;
    }
    void addItem(std::vector<item>::iterator item) {
        storedItems.push_back(item);
        fullness += item->weight;
    }
    void rmItem(std::vector<item>::iterator item) {
        storedItems.remove(item);
        fullness -= item->weight;
    }
};
struct Solution {
    std::vector<item> items_vector;
    std::list<bin> bins_list;
    Solution(Problem P) {  // Construtor da solução
        for (auto it = P.items_weights.begin(); it != P.items_weights.end(); it++) {
            item I(*it, bins_list.end());
            items_vector.push_back(I);  // Cópia dos pesos dos items para dentro dos
        }
    }
};
