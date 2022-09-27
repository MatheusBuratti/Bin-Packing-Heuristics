#pragma once
#include <algorithm>
#include <vector>

#include "problem.hpp"
class Greedy {
   public:
    static Solution nextFitDecreasing(Problem P) {
        Solution S;
        S.item.resize(P.n);
        for (std::vector<int>::iterator it = P.items.begin(); it != P.items.end(); it++) {
            S.item[it - P.items.begin()].weight = *it;    // cópia dos items, vai ajudar mais tarde quando for fazer trocas
            S.item[it - P.items.begin()].bin_index = -1;  // -1 vai servir como flag para item que não foi colocado em nenhuma bin
        }

        // Sort decrescente dos items
        std::sort(S.item.begin(), S.item.end(), greaterItemSol());

        std::vector<ItemSol>::iterator it_items;
        for (it_items = S.item.begin(); it_items != S.item.end(); it_items++) {
            if (it_items->bin_index == -1) {  // Item não associado a uma bin

                S.bins.push_back(it_items->weight);  // Abre uma bin nova
                it_items->bin_index = (S.bins.end() - 1 - S.bins.begin());

                // Parte onde procura o próximo item que cabe no restante da bin
                int freeSpace = P.binCapacity - *(S.bins.end() - 1);
                std::vector<ItemSol>::iterator it_nextFit;
                it_nextFit = std::lower_bound(it_items, S.item.end(), freeSpace, [](ItemSol A, int B) { return A.weight > B; });

                while (it_nextFit != S.item.end()) {  // Procura repetidamente caso apenas um item não tenha completado a bin

                    // Item já associado a uma bin
                    if (it_nextFit->bin_index != -1)
                        it_nextFit++;

                    // Item não associado a uma bin
                    else {
                        *(S.bins.end() - 1) += it_nextFit->weight;
                        freeSpace -= it_nextFit->weight;
                        it_nextFit->bin_index = S.bins.end() - 1 - S.bins.begin();  // Associa o item à bin atual
                        it_nextFit++;
                        it_nextFit = std::lower_bound(it_nextFit, S.item.end(), freeSpace, [](ItemSol A, int B) { return A.weight > B; });
                    }
                }
            }
        }
        return S;
    }
};
