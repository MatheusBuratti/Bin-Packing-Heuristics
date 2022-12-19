#pragma once
#include <cmath>
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
    std::list<item *> storedItems;  // Lista de ponteiros dos items que estão guardados nesta bin
    bin() {
        fullness = 0;
    }
    bin(item *item) {
        storedItems.push_back(item);
        fullness = item->weight;
    }
};
struct Solution {
    std::vector<item> items_vector;
    std::list<bin> bins_list;
    Solution(Problem P) {  // Construtor da solução
        for (std::vector<int>::iterator it = P.items_weights.begin(); it != P.items_weights.end(); it++) {
            item I(*it, bins_list.end());
            items_vector.push_back(I);  // Cópia dos pesos dos items para dentro dos
        }
    }
};

/*
    Variação do fitness caso faça uma troca
    Uma função para cada um dos tipos de swap possíveis
*/
static bool _deltaFitness(Problem P, item A0, bin beta) {
    if (beta.fullness + A0.weight > P.binCapacity)  // Item não cabe na bin
        return false;
    //  deltaFitness = (La - wA0)² + (Lb + wA0)² - La² - Lb²
    int La = A0.assignedBin->fullness, wA0 = A0.weight, Lb = beta.fullness;
    return ((La - wA0) * (La - wA0) + (Lb + wA0) * (Lb + wA0) - La * La - Lb * Lb) > 0;
}
static bool _deltaFitness(Problem P, item A0, item B0) {
    // Item A0 não cabe em B Item B0 não cabe em A
    if (B0.assignedBin->fullness - B0.weight + A0.weight > P.binCapacity || A0.assignedBin->fullness - A0.weight + B0.weight > P.binCapacity)
        return false;
    // deltaFitness = (La - wA0 + wB0)² + (Lb - wB0 + wA0)² - La² - Lb²
    int La = A0.assignedBin->fullness, wA0 = A0.weight, Lb = B0.assignedBin->fullness, wB0 = B0.weight;
    return ((La - wA0 + wB0) * (La - wA0 + wB0) + (Lb - wB0 + wA0) * (Lb - wB0 + wA0) - La * La - Lb * Lb) > 0;
}

static bool _deltaFitness(Problem P, item A0, bin beta, double tempA) {
    if (beta.fullness + A0.weight > P.binCapacity)  // Item não cabe na bin
        return false;
    //  deltaFitness = (La - wA0)² + (Lb + wA0)² - La² - Lb²
    double La = A0.assignedBin->fullness, wA0 = A0.weight * tempA, Lb = beta.fullness;
    return ((La - wA0) * (La - wA0) + (Lb + wA0) * (Lb + wA0) - La * La - Lb * Lb) > 0;
}
static bool _deltaFitness(Problem P, item A0, item B0, double tempA, double tempB) {
    // Item A0 não cabe em B Item B0 não cabe em A
    if (B0.assignedBin->fullness - B0.weight + A0.weight > P.binCapacity || A0.assignedBin->fullness - A0.weight + B0.weight > P.binCapacity)
        return false;
    // deltaFitness = (La - wA0 + wB0)² + (Lb - wB0 + wA0)² - La² - Lb²
    double La = A0.assignedBin->fullness, wA0 = A0.weight * tempA, Lb = B0.assignedBin->fullness, wB0 = B0.weight * tempB;
    return ((La - wA0 + wB0) * (La - wA0 + wB0) + (Lb - wB0 + wA0) * (Lb - wB0 + wA0) - La * La - Lb * Lb) > 0;
}